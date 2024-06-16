#ifndef BPSK_HPP
#define BPSK_HPP

#include <vector>

namespace bpsk {

using namespace std;

void encode(vector<int>& input, vector<float>& output);

void decode(const vector<bool>& input, vector<bool>& output);

};

#endif // BPSK_HPP