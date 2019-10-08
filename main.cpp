#include <gmpxx.h>
#include <boost/program_options.hpp>
#include <ctime>
#include <iostream>
#include "Converter.hpp"
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"

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
    - Merge all solutions
    - Calculate time
    - Count solutions and print
    - Print all solutions formatted if desired

*/

int main(int argc, char const *argv[]) {
    //Parameter handling
    po::options_description desc_allowed("Allowed options");
    desc_allowed.add_options()
        ("help", "Produce help message");

    po::options_description desc_required("Required options");
    desc_required.add_options()
        ("table", po::value<unsigned long>()->default_value(8), "Size of the N-Queens Table");

    po::options_description cmdline_options;
    cmdline_options.add(desc_allowed).add(desc_required);

    po::variables_map vm;
    store(po::command_line_parser(argc, argv).options(cmdline_options).run(), vm);
    notify(vm);

    if(vm.count("help")){
        cout << desc_allowed << endl;
        cout << desc_required << endl;

        return 1;
    }
    if(vm.count("table")){
        cout << "Defined table size as: " << vm["table"].as<unsigned long>() << endl;
    }

    // NQueensTable *stance = new NQueensTable(8);

    // cout << stance->serialize() << endl;
    // stance->update_from_serial("5|4|7|6|0|1|2|3");

    // cout << stance->serialize() << endl;
    // stance->show();

    // delete stance;

    clock_t begin = clock();

    // vector<unsigned long *> poss = PossibilitiesGenerator::generate_all_possibilites(8, 8);
    clock_t end = clock();

    // for(auto vi : poss){
    //     for (auto vj : vi){
    //         cout << vj << "  ";
    //     }
    //     cout << endl;
    // }

    // cout << poss.size() << endl;
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    // for(auto it:poss){
    //     free(it);
    // }

    return 0;
}
