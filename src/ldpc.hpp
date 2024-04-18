#ifndef LDPC_HPP
#define LDPC_HPP

#include <vector>

namespace ldpc {

using namespace std;

vector<vector<int>> edges;

void create_graph(int n, int dv, int dc);

void encode(vector<bool> &input, vector<bool> &output);

void decode(vector<bool> &input, vector<bool> &output);

};

#endif // LDPC_HPP