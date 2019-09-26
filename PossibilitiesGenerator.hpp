// Guard
#if !defined(POSSIBILITIES_GENERATOR_HPP)
#define POSSIBILITIES_GENERATOR_HPP

// Dependencies and settings
#include <vector>

using namespace std;

// File Starts Here
class PossibilitiesGenerator {
   private:
    static void increase(vector<int> &vec, long long base) {
        vector<int>::iterator it;
        for (it = vec.begin(); it < vec.end(); it++) {
            if(*it == (base - 1))
                *it = 0;
            else{
                (*it)++;
                break;
            }
        }
    }

    static bool is_the_last(vector<int> &vec, long long base) {
        vector<int>::iterator it;
        for (it = vec.begin(); it < vec.end(); it++) {
            if (*it != base - 1) return false;
        }
        return true;
    }

   public:
    static vector<vector<int>> generate_possibilites(long long len, long long base) {
        vector<vector<int>> possibilities;
        vector<int> possibility = vector<int>(len);

        do {
            possibilities.push_back(possibility);
            if(is_the_last(possibility, base))
                break;
            increase(possibility, base);
        } while(true);

        return possibilities;
    }
};

#endif  // POSSIBILITIES_GENERATOR_HPP