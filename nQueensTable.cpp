#include "nQueensTable.hpp"
#include <iostream>
#include "utils.h"

nQueensTable::nQueensTable(long long N) {
    this->N = N;
    this->board = vector<long long int>(this->N);

    for (long long i = 0; i < this->N; i++) {
        this->board.at(i) = -1;
    }
}

void nQueensTable::show() {
    for (long long i = this->N - 1; i >= 0; i--) {
        for (long long j = 0; j < this->N; j++) {
            if(this->board.at(j) == i)
                cout << "Q  ";
            else
                cout << "*  ";
        }
        cout << endl;
    }
    
}

void nQueensTable::updateFromSerial(string s) {
    vector<string> split_result = utils::explode(s, '|');
    if (split_result.size() == this->N) {
        for (long long i = 0; i < this->N; i++) {
            long long position = stoi(split_result.at(i));
            if (position >= this->N || position < -1){
                throw out_of_range("Position invalid!");
            }
            this->board.at(i) = position;
        }
    } else {
        throw length_error("Serial has a size different from expected!");
    }
}

void nQueensTable::updateFromVector(vector<long long> vec) {
    if (vec.size() == this->N) {
        for (long long i = 0; i < this->N; i++) {
            long long position = vec.at(i);
            if (position >= this->N || position < -1){
                throw out_of_range("Position invalid!");
            }
            this->board.at(i) = position;
        }
    } else {
        throw length_error("Serial has a size different from expected!");
    }
}

string nQueensTable::serialize() {
    string result = "";

    for(long long i = 0; i < this->N; i++) {
        if (i != 0)
            result += "|" + to_string(this->board.at(i));
        else
            result += to_string(this->board.at(i));
    }

    return result;
}

nQueensTable::~nQueensTable() {
    this->N = N;
}
