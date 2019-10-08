#include <iostream>
#include <ctime>
#include <gmpxx.h>
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"
#include "Converter.hpp"

using namespace std;

/*
How it should work:

--Count available machines on the clusters
--Count possibilities
--Split ranges for each machine
**BEGIN Cluster
  |--Create possibilities on the range
  |--Validate each possibility
  |--Return vector with matched solutions
**END Cluster
--Merge all solutions
--Calculate time
--Count solutions and print
--Print all solutions formatted if desired

*/

int main(int argc, char const *argv[]){
    // NQueensTable *stance = new NQueensTable(8);

    // cout << stance->serialize() << endl;
    
    // stance->update_from_serial("5|4|7|6|0|1|2|3");

    // cout << stance->serialize() << endl;
    // stance->show();

    // delete stance;


    clock_t begin = clock();

    Converter conv = Converter(16);
    mpz_class numb = 35;
    vector<mpz_class> *vec = conv.ConvertToBase(numb);

    for(auto vi : *vec){
        cout << vi << "|";
    }
    cout << endl;

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
