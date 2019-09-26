// Guard
#if !defined(POSSIBILITIES_GENERATOR_HPP)
#define POSSIBILITIES_GENERATOR_HPP

// Dependencies and settings
#include <vector>
#include <cstdlib>

using namespace std;

// File Starts Here
class PossibilitiesGenerator {
   private:
    static long long *increase(long long *vec, long long len, long long base) {
        for (long long i = 0; i < len; i++) {
            if(vec[i] == (base - 1))
                vec[i] = 0;
            else{
                (vec[i])++;
                break;
            }
        }

        long long *new_vec = (long long *) calloc(len, sizeof(long long));
        for (long long i = 0; i < len; i++) {
            new_vec[i] = vec[i];
        }
        return new_vec;
    }

    static bool is_the_last(long long *vec, long long len, long long base) {
        for (long long i = 0; i < len; i++){
            if (vec[i] != base - 1) return false;
        }
        return true;
    }

   public:
    static vector<long long *> generate_possibilites(long long len, long long base) {
        vector<long long *> possibilities;
        long long *base_possibility = (long long *) calloc(len, sizeof(long long));

        int i = 0;
        do {
            possibilities.push_back(base_possibility);
            if(is_the_last(base_possibility, len, base))
                break;
            base_possibility = increase(base_possibility, len, base);
        } while(true);

        return possibilities;
    }
};

#endif  // POSSIBILITIES_GENERATOR_HPP