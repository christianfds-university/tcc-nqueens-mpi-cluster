#include <gmpxx.h>
#include <mpi.h>
#include <boost/program_options.hpp>
#include <ctime>
#include <iostream>
#include "Converter.hpp"
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"
#include "Utils.h"

using namespace std;
namespace po = boost::program_options;

/*
Requirements:
    libgmp3-dev
    libboost-program-options-dev
    libopenmpi

How to compile:
    mpic++ *.cpp -lgmpxx -lgmp -lboost_program_options --std=c++11 -o main && mpiexec -n 4 ./main --table 8

How it should work:
    - Count available machines on the clusters
    - Count possibilities
    - Split ranges for each machine
    **BEGIN Cluster
        - Create possibilities on the range
        - Validate each possibility
        - Return vector with matched solutions
    **END Cluster
    - Calculate time
    - Merge all solutions
    - Count solutions and print
    - Print all solutions formatted if desired

*/

unsigned long run_range(vector<mpz_class*>& ranges, unsigned long arg_table_size, int rank) {
    unsigned long valid_tables = 0;
    NQueensTable* stance = new NQueensTable(arg_table_size);

    vector<unsigned long> vec = Utils::to_base_trunc(ranges.at(rank)[0], arg_table_size);

    for (mpz_class value = ranges.at(rank)[0]; value < ranges.at(rank)[1]; value++) {
        stance->update_from_vector(vec);
        Utils::inc_vec(vec);
        if (stance->is_a_valid_table()) {
            valid_tables++;
        }
    }
    cout << "Finished processing range " << ranges.at(rank)[0] << " to " << (ranges.at(rank)[1] - 1) << " with rank " << rank << endl;

    delete stance;

    return valid_tables;
}

int main(int argc, char const* argv[]) {
    unsigned long arg_table_size;

    try {
        //Parameter handling
        po::options_description desc_allowed("Allowed options");
        desc_allowed.add_options()("help", "Produce help message");

        po::options_description desc_required("Required options");
        desc_required.add_options()("table", po::value<unsigned long>()->default_value(8), "Size of the N-Queens Table");

        po::options_description cmdline_options;
        cmdline_options.add(desc_allowed).add(desc_required);

        po::variables_map vm;
        store(po::command_line_parser(argc, argv).options(cmdline_options).run(), vm);
        notify(vm);

        if (vm.count("help")) {
            cout << desc_allowed << endl;
            cout << desc_required << endl;

            return 1;
        }

        if (vm.count("table")) {
            arg_table_size = vm["table"].as<unsigned long>();
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 0;
    }

    clock_t begin = clock();

    int world_size, self_rank, dest = 0, tag = 12321;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &self_rank);

    unsigned long my_result = 0, result = 0;
    vector<mpz_class*> ranges = PossibilitiesGenerator::generate_ranges(arg_table_size, world_size);

    my_result = run_range(ranges, arg_table_size, self_rank);
    if (self_rank == 0) {
        result = my_result;
        for (int i = 1; i < world_size; i++) {
            int source = i;
            MPI_Recv(&my_result, 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD, &status);
            result += my_result;
        }
        cout << result << " Valid table formations!" << endl;
        clock_t end = clock();
        cout << double(end - begin) / CLOCKS_PER_SEC << endl;
    } else {
        MPI_Send(&my_result, 1, MPI_UNSIGNED_LONG, dest, tag, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}
