#ifndef HAMMING_HPP
#define HAMMING_HPP

#include <vector>

namespace hamming {

using namespace std;

/// @brief 
void encode(const vector<bool>& input, vector<bool>& output, int n);

/// @brief 
void decode(const vector<bool>& input, vector<bool>& output, int n);

};

#endif // HAMMING_HPP