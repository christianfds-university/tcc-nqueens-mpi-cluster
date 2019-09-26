// Guard
#if !defined(N_QUEENS_TABLE_HPP)
#define N_QUEENS_TABLE_HPP

// Dependencies and settings
#include <string>
#include <vector>

using namespace std;

// File Starts Here
class nQueensTable {
   private:
    long long N;
    vector<long long> board;

   public:
    nQueensTable(long long N);

    // Presentation
    void show();

    // Serialization
    void updateFromSerial(string s);
    string serialize();

    ~nQueensTable();
};
#endif  // N_QUEENS_TABLE_HPP