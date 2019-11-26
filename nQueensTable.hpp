// Guard
#if !defined(N_QUEENS_TABLE_HPP)
#define N_QUEENS_TABLE_HPP

// Dependencies and settings
#include <string>
#include <vector>
#include <gmpxx.h>

using namespace std;

// File Starts Here
class NQueensTable {
   private:
    unsigned long N;
    unsigned long *board;

   public:
    NQueensTable(unsigned long N);

    // Presentation
    void show();

    // Serialization
    void update_from_mpz_class(mpz_class const &vec);
    void update_from_vector(vector<unsigned long> const &vec);
    void update_from_serial(string s);
    string serialize();

    ~NQueensTable();
};
#endif  // N_QUEENS_TABLE_HPP