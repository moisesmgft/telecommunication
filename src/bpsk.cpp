#include "bpsk.hpp"
#include <cmath>

void bpsk::encode(vector<int> &input, vector<float> &output) {
    output.assign(input.size(), 1.0);
    for (int i = 0; i < (int)input.size(); i++)
        if (input[i])
            output[i] = -1.0;
}

void bpsk::decode(const vector<float> &input, vector<int> &output, const vector<vector<int>>& graph, int max_iterations, int dc) {
    int dv = graph[0].size(), n = input.size();
    vector<float> edges(n*dv);
    vector<vector<int>> c_edges(n*dv/dc);

    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            c_edges[graph[i][j]].push_back(i+j);
        }
    }

    while(max_iterations--) {
        vector<float> copy(n*dv);
        for(int i = 0; i < n; i++) {
            for(int j = i*dv; j < (i+1)*dv; i++) {
                copy[j] = input[i];
                for(int k = i*dv; k < (i+1)*dv; i++) {
                    if(k != j) {
                        copy[j] += edges[k];
                    }
                }
            }
        }
        edges = copy;
        if(max_iterations == 0) break;
        bool stop_criteria = false;

        for(int i = 0; i < c_edges.size(); i++) {
            float prod = 1.0;
            for(int edge : c_edges[i]) 
                prod *= (edges[edge] > 0) - (edges[edge] < 0);
            
            if(prod < 0) {
                stop_criteria = true;
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
                        prod *= (edges[c_edges[i][k]] > 0) - (edges[c_edges[i][k]] < 0);
                        least = min(least, edges[c_edges[i][k]]);
                    }
                }
                copy[c_edges[i][j]] = prod*least;
            }
        }

        edges = copy;
    }

    output.resize(n, 1);

    for(int i = 0; i < input.size(); i++) {
        float res = input[i];
        for(int j = i*dv; j < (i+1)*dv; j++) {
            res += edges[j];
        }
        if(res >= 0) output[i] = 0;
    }
}
