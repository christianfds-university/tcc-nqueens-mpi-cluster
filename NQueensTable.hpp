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

    // mpz_class
    void update_from_mpz_class(mpz_class const &vec);
    // vector<unsigned long>
    void update_from_vector(vector<unsigned long> const &vec);
    // 5|4|7|6|0|1|2|3
    void update_from_serial(string s);
    // Serialization
    string serialize();

    bool is_a_valid_table();

    ~NQueensTable();
};
#endif  // N_QUEENS_TABLE_HPP
