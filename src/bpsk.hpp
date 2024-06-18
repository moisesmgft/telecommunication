#ifndef BPSK_HPP
#define BPSK_HPP

#include <vector>

namespace bpsk {

using namespace std;

void encode(vector<int>& input, vector<float>& output);

void decode(const vector<float>& input, vector<int>& output, const vector<vector<int>>& graph, int max_iterations, int dc, int block_size, float var);

};

#endif // BPSK_HPP