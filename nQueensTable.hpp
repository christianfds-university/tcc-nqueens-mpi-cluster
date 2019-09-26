// Guard
#if !defined(N_QUEENS_TABLE_HPP)
#define N_QUEENS_TABLE_HPP

// Dependencies and settings
#include <string>
#include <vector>

using namespace std;

// File Starts Here
class NQueensTable {
   private:
    long long N;
    vector<long long> board;

   public:
    NQueensTable(long long N);

    // Presentation
    void show();

    // Serialization
    void update_from_vector(vector<long long> vec);
    void update_from_serial(string s);
    string serialize();

    ~NQueensTable();
};
#endif  // N_QUEENS_TABLE_HPP