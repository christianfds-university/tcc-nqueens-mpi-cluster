// Guard
#if !defined(POSSIBILITIES_GENERATOR_HPP)
#define POSSIBILITIES_GENERATOR_HPP

// Dependencies and settings
#include <cstdlib>
#include <vector>
#include <gmpxx.h>

using namespace std;

// File Starts Here
class PossibilitiesGenerator {
   private:
    static unsigned long *increase(unsigned long *vec, unsigned long len, unsigned long base) {
        for (unsigned long i = 0; i < len; i++) {
            if(vec[i] == (base - 1))
                vec[i] = 0;
            else{
                (vec[i])++;
                break;
            }
        }

        unsigned long *new_vec = (unsigned long *) calloc(len, sizeof(unsigned long));
        for (unsigned long i = 0; i < len; i++) {
            new_vec[i] = vec[i];
        }
        return new_vec;
    }

    static bool is_the_last(unsigned long *vec, unsigned long len, unsigned long base) {
        for (unsigned long i = 0; i < len; i++){
            if (vec[i] != base - 1) return false;
        }
        return true;
    }

   public:
    static vector<unsigned long *> generate_all_possibilites(unsigned long len, unsigned long base) {
        vector<unsigned long *> possibilities;
        unsigned long *base_possibility = (unsigned long *) calloc(len, sizeof(unsigned long));

        int i = 0;
        do {
            possibilities.push_back(base_possibility);
            if(is_the_last(base_possibility, len, base))
                break;
            base_possibility = increase(base_possibility, len, base);
        } while(true);

        return possibilities;
    }

    static mpz_class total_possibilities(unsigned long base) {
        mpz_class value;
        mpz_ui_pow_ui(value.get_mpz_t(), base, base);
        return value;
    }
};

#endif  // POSSIBILITIES_GENERATOR_HPP