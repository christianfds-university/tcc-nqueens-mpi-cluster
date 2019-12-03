#include <gmpxx.h>
#include <boost/program_options.hpp>
#include <ctime>
#include <iostream>
#include "Converter.hpp"
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"
#include "utils.h"

using namespace std;
namespace po = boost::program_options;

/*
Requirements:
    libgmp3-dev
    libboost-program-options-dev

How to compile:
    c++ *.cpp -o main -lgmpxx -lgmp -lboost_program_options && ./main

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

int main(int argc, char const* argv[]) {
    unsigned long tableN;

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
            tableN = vm["table"].as<unsigned long>();
            cout << "Defined table size as: " << tableN << endl;
        }
    
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 0;
    }

    clock_t begin = clock();
    vector<mpz_class*> ranges = PossibilitiesGenerator::generate_ranges(tableN, 5);

    unsigned long valid_tables = 0;
    NQueensTable* stance = new NQueensTable(tableN);

    for(auto it:ranges){
        vector<unsigned long> vec = Utils::to_base_trunc(it[0], tableN);

        for (mpz_class value = it[0]; value < it[1]; value++) {
            stance->update_from_vector(vec);
            Utils::inc_vec(vec);
            if(stance->is_a_valid_table()){
                valid_tables++;
            }
        }
        cout << "ended range" << endl;
        free(it);
    }
    delete stance;

    cout << valid_tables << " deram bom!" << endl;
    clock_t end = clock();
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    return 0;
}
