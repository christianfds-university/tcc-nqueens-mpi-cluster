#include <iostream>
#include "NQueensTable.hpp"

using namespace std;

int main(int argc, char const *argv[]){
    /* code */
    cout << "oi" << endl;

    NQueensTable *stance = new NQueensTable(8);

    cout << stance->serialize() << endl;
    
    stance->update_from_serial("5|4|7|6|0|1|2|3");

    cout << stance->serialize() << endl;
    stance->show();

    delete stance;
    return 0;
}
