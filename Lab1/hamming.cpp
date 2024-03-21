#include "hamming.hpp"

namespace hamming {

void encode(const vector<bool>& input, vector<bool>& output) {
    
    int size = 1;
    while (size < input.size())
        size *= 2;

}

void decode(const vector<bool>& input, vector<bool>& output) {
    
}

}