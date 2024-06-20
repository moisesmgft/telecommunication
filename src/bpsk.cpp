#include "bpsk.hpp"
#include <cmath>

namespace bpsk {

void encode(vector<int> &input, vector<float> &output) {
    output.assign(input.size(), 1.0);
    for (int i = 0; i < (int)input.size(); i++)
        if (input[i])
            output[i] = -1.0;
}

void decode(vector<float> &input, vector<int> &output, const vector<vector<int>>& graph, int max_iterations, int dc, int block_size, float var) {
    int dv = graph[0].size(), n = graph.size(), blocks = 0;
    vector<vector<int>> c_edges(n*dv/dc);
    vector<float> new_input = input;

    for(int i = 0; i < new_input.size(); i++) {
        new_input[i] = 2*new_input[i] / var;
    }

    while(new_input.size() % (block_size) != 0)
        new_input.emplace_back(1.0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < dv; j++) {
            c_edges[graph[i][j]].push_back(i*dv+j);
        }
    }
    
    while(block_size * blocks < new_input.size())
        blocks++;

    output.resize(new_input.size(), 1);
    
    for(int b = 0; b < blocks; b++){
        vector<float> edges(n*dv, 0);
        int iterations = max_iterations;

        while(iterations--) {
            vector<float> copy(n*dv);
            for(int i = 0; i < n; i++) {
                for(int j = i*dv; j < (i+1)*dv; j++) {
                    copy[j] = new_input[block_size*b + i];
                    for(int k = i*dv; k < (i+1)*dv; k++) {
                        if(k != j) {
                            copy[j] += edges[k];
                        }
                    }
                }
            }
            edges = copy;
            if(iterations == 0) break;
            bool stop_criteria = true;

            for(int i = 0; i < c_edges.size(); i++) {
                float prod = 1.0;
                for(int edge : c_edges[i]) 
                    prod *= (edges[edge] >= 0) - (edges[edge] < 0);
                
                if(prod < 0) {
                    stop_criteria = false;
                    break;
                }
            }

            if(stop_criteria)
                break;

            for(int i = 0; i < c_edges.size(); i++) {
                for(int j = 0; j < dc; j++) {
                    float prod = 1.0, least = 1e9;
                    for(int k = 0; k < dc; k++) {
                        if(k  != j) {
                            prod *= (edges[c_edges[i][k]] >= 0) - (edges[c_edges[i][k]] < 0);
                            least = min(least, abs(edges[c_edges[i][k]]));
                        }
                    }
                    copy[c_edges[i][j]] = prod*least;
                }
            }

            edges = copy;
        }

        for(int i = 0; i < n; i++) {
            float res = new_input[block_size*b + i];
            for(int j = i*dv; j < (i+1)*dv; j++) {
                res += edges[j];
            }
            if(res >= 0) output[block_size*b + i] = 0;
        }
    }
}

void to_binary(const vector<float>& input, vector<bool>& output) {
    output.assign(input.size(), false);
    for (int i = 0; i < input.size(); i++) if (input[i] < 0)
        output[i] = true;
}

}