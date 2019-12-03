// Guard
#if !defined(UTILS_H)
#define UTILS_H

// Dependencies and settings
#include <string>
#include <vector>
#include <gmpxx.h>

using namespace std;

// File Starts Here
class Utils {
   public:
    static const vector<string> explode(const string& s, const char& c) {
        string buff{""};
        vector<string> v;

        for (auto n : s) {
            if (n != c)
                buff += n;
            else if (n == c && buff != "") {
                v.push_back(buff);
                buff = "";
            }
        }
        if (buff != "") v.push_back(buff);

        return v;
    }
    
    static const vector<unsigned long> to_base(mpz_class number, unsigned long base) {
        vector<unsigned long> values;
        while (number != 0) {
            mpz_class aux = 0;
            mpz_fdiv_qr_ui(number.get_mpz_t(), aux.get_mpz_t(), number.get_mpz_t(), base);
            values.push_back(aux.get_ui());
        }

        return values;
    }

    static const vector<unsigned long> to_base_trunc(mpz_class number, unsigned long base) {
        vector<unsigned long> values(base, 0);
        unsigned long pos = base - 1;
        while (number != 0) {
            mpz_class aux = 0;
            mpz_fdiv_qr_ui(number.get_mpz_t(), aux.get_mpz_t(), number.get_mpz_t(), base);
            values.at(pos--) = aux.get_ui();
        }

        return values;
    }

    static void normalize_vector(vector<unsigned long> &vec, unsigned long size) {
        while(vec.size() < size){
            vec.push_back(0);
        }
    }

    static const void inc_vec(vector<unsigned long>& vec) {
        unsigned long base = vec.size();
        unsigned long pos = base - 1;

        try {
            while(vec.at(pos) == base - 1){
                vec.at(pos--) = 0;
            }
            vec.at(pos) += 1;
        } catch(const std::exception& e){

        }
        
    }
};

#endif  // UTILS_H