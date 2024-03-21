#ifndef HAMMING_HPP
#define HAMMING_HPP

#include <vector>

namespace hamming {

using namespace std;

/// @brief 
void encode(vector<bool>& input, vector<bool>& output);

/// @brief 
void decode(const vector<bool>& input, vector<bool>& output);

};

#endif // HAMMING_HPP