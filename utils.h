// Guard
#if !defined(UTILS_H)
#define UTILS_H

// Dependencies and settings
#include <string>
#include <vector>

using namespace std;

// File Starts Here
class utils {
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
};

#endif  // UTILS_H