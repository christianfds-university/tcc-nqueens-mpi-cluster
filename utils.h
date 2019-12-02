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
        while(number != 0){
            mpz_class aux = number % base;
            values.push_back(aux.get_ui());
            number = number / base;
        }
        
        return values;
    }

    static void normalize_vector(vector<unsigned long> &vec, unsigned long size) {
        while(vec.size() < size){
            vec.push_back(0);
        }
    }
};

#endif  // UTILS_H