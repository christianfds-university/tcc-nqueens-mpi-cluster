#include <iostream>
#include "nQueensTable.hpp"

using namespace std;

int main(int argc, char const *argv[]){
    /* code */
    cout << "oi" << endl;

    nQueensTable *stance = new nQueensTable(8);

    cout << stance->serialize() << endl;
    
    stance->updateFromSerial("5|4|7|6|0|1|2|3");

    cout << stance->serialize() << endl;
    stance->show();

    delete stance;
    return 0;
}
