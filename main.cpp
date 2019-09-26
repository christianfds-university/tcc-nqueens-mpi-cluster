#include <iostream>
#include "NQueensTable.hpp"
#include "PossibilitiesGenerator.hpp"

using namespace std;

int main(int argc, char const *argv[]){
    /*
    NQueensTable *stance = new NQueensTable(8);

    cout << stance->serialize() << endl;
    
    stance->update_from_serial("5|4|7|6|0|1|2|3");

    cout << stance->serialize() << endl;
    stance->show();

    delete stance;
    */
    
    vector<vector<int>> poss = PossibilitiesGenerator::generate_possibilites(5, 2);

    for(auto vi : poss){
        for (auto vj : vi){
            cout << vj << "  ";
        }
        cout << endl;
    }

    cout << poss.size() << endl;

    return 0;
}
