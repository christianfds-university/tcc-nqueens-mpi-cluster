// Guard
#if !defined(CONVERTER_HPP)
#define CONVERTER_HPP

// Dependencies and settings
#include <cstdlib>
#include <iostream>
#include <vector>
#include <gmpxx.h>

using namespace std;

// File Starts Here
class Converter {
   private:
    mpz_class base;

   public:
    Converter(unsigned long base);
    vector<mpz_class> *ConvertToBase(mpz_class number);
    ~Converter();
};

Converter::Converter(unsigned long base) {
    this->base = base;
}

vector<mpz_class> *Converter::ConvertToBase(mpz_class number) {
    vector<mpz_class> *vec = new vector<mpz_class>;

    while(number != 0){
        vec->insert(vec->begin(), 1, number % this->base);
        number = number / this->base;
    }

    return vec;
}

Converter::~Converter() {
}

#endif  // CONVERTER_HPP