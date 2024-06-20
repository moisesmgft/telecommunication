#ifndef BPSK_HPP
#define BPSK_HPP

#include <vector>

namespace bpsk {

using namespace std;

void encode(vector<int>& input, vector<float>& output);

void decode(vector<float>& input, vector<int>& output, const vector<vector<int>>& graph, int max_iterations, int dc, int block_size, float var);

void to_binary(const vector<float>& input, vector<bool>& output);

};

#endif // BPSK_HPP