#ifndef HAMMING_HPP
#define HAMMING_HPP

#include <vector>

namespace hamming {

using namespace std;

const bool H[3][7] = {
    {1, 1, 1, 0, 1, 0, 0},
    {1, 0, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 0, 1},
};


/// @brief 
void encode(vector<bool>& input, vector<bool>& output);

/// @brief 
void decode(const vector<bool>& input, vector<bool>& output);

};

#endif // HAMMING_HPP