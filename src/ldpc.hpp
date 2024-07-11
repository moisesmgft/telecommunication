#ifndef LDPC_HPP
#define LDPC_HPP

#include <vector>

namespace ldpc {

using namespace std;

void create_graph(int n, int dv, int dc, vector<vector<int>> &edges);

void invert_graph(const vector<vector<int>> &original, int n, vector<vector<int>> &output);

void decode(vector<bool> input, vector<vector<int>> &graph, int N, vector<bool> &output, int max_iterations);

};

#endif // LDPC_HPP