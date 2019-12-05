#include <gmpxx.h>
#include <mpi.h>
#include <ctime>
#include <iostream>
#include "Converter.hpp"
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"
#include "Utils.h"

using namespace std;

/*
Requirements:
    libgmp3-dev
    libopenmpi-dev

How to compile:
    mpic++ *.cpp -lgmpxx -lgmp --std=c++11 -o main && mpiexec -np 2 -hostfile hostfile ./main 8

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
    //cout << "Finished processing range " << ranges.at(rank)[0] << " to " << (ranges.at(rank)[1] - 1) << " with rank " << rank << endl;
    cout << "Finished processing rank:  " << rank << endl;

    delete stance;

    return valid_tables;
}

int main(int argc, char const* argv[]) {
    unsigned long arg_table_size;

    try {
        if(argc == 1){
            arg_table_size = 8;
        } else if(argc == 2) {
            arg_table_size = strtoul(argv[1], NULL, 10);
        } else {
            cout << "Expected input: ./main <table_size>" << endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    clock_t begin = clock();

    int world_size, self_rank, dest = 0, tag = 12321;
    MPI_Status status;

    // Inicializa o MPI
    MPI_Init(NULL, NULL);
    // Obtém o número total de nós
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Obtém o número do nó atual
    MPI_Comm_rank(MPI_COMM_WORLD, &self_rank);

    unsigned long my_result = 0, result = 0;
    // Gera os escopos que será atribuito a cada rank
    vector<mpz_class*> ranges = PossibilitiesGenerator::generate_ranges(arg_table_size, world_size);

    // Itera pelo escopo
    my_result = run_range(ranges, arg_table_size, self_rank);
    // Caso seja o rank 0 (nó mestre), recebe todos os resultados obtidos e soma eles
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
    } 
    // Caso contrário, envia para o nó mestre o resultado obtido
    else {
        MPI_Send(&my_result, 1, MPI_UNSIGNED_LONG, dest, tag, MPI_COMM_WORLD);
    }

    // Finaliza o MPI
    MPI_Finalize();
    return 0;
}
