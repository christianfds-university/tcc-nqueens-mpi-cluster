#include <iostream>
#include <ctime>
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"

using namespace std;

int main(int argc, char const *argv[]){
    // NQueensTable *stance = new NQueensTable(8);

    // cout << stance->serialize() << endl;
    
    // stance->update_from_serial("5|4|7|6|0|1|2|3");

    // cout << stance->serialize() << endl;
    // stance->show();

    // delete stance;

    clock_t begin = clock();
    vector<long long *> poss = PossibilitiesGenerator::generate_all_possibilites(8, 8);
    clock_t end = clock();

    // for(auto vi : poss){
    //     for (auto vj : vi){
    //         cout << vj << "  ";
    //     }
    //     cout << endl;
    // }

    cout << poss.size() << endl;
    cout << double(end - begin) / CLOCKS_PER_SEC << endl;

    for(auto it:poss){
        free(it);
    }

    return 0;
}
