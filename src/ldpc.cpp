#include "ldpc.hpp"
#include <map>
#include <iterator>
#include <random>
#include <unordered_set>
#include <set>
#include <algorithm>

namespace ldpc {

vector<int> random_vector(int size, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, max - 1);

    std::unordered_set<int> unique_numbers;
    std::vector<int> random_values;

    size = std::min(size, max);

    while (random_values.size() < size) {
        int number = dis(gen);
        if (unique_numbers.insert(number).second) {
            random_values.push_back(number);
        }
    }
    sort(random_values.begin(), random_values.end());

    return random_values;
}

void create_graph(int n, int dv, int dc, vector<vector<int>> &edges){
    int m = n * dv / dc, remain = n;

    edges.resize(m);

    vector<int> info_uses(n);
    vector<int> pari_uses(m);
    
    std::set<int> parity;
    for(int i = 0; i < n; i++) 
        parity.insert(i);

    for(int i = 0; i < m; i++) {
        vector<int> rd = random_vector(dc, parity.size());
        int k = 0, current = 0;
        vector<int> rem;
        for(auto value : parity) {
            if(k == rd[current]) {
                current++;
                info_uses[value]++;
                edges[i].push_back(value);
                if(info_uses[value] >= dc) {
                    rem.push_back(value);
                }
            }
            k++;
        }
        for(auto value : rem) 
            parity.erase(value);
    }
}

void encode(vector<bool> &input, vector<vector<int>> &graph, int N, vector<bool> &output) {

    int M = graph.size(), sz = 0, blocks = 0, original_sz = input.size();

    while(sz < input.size())
        sz += N, blocks++;

    output.assign((N + M) * blocks, false);
    while(input.size() < sz)
        input.push_back(false);

    for (int b = 0; b < blocks; b++) {
        // Copy the message
        for (int i = 0; i < N; i++)
            output[(N + M) * b + i] = input[N * b + i];
        // Write the parity bits
        for (int i = 0; i < M; i++) {
            bool x = 0;
            for (auto j: graph[i])
                x = (x != input[N * b + j]);
            output[(N + M) * b + N + i] = x; 
        }
    }

    while (input.size() != original_sz)
        input.pop_back();

}

void decode(vector<bool> &input, vector<vector<int>> &graph, int N, vector<bool> &output, int max_iterations) {

    int M = graph.size(), blocks = 0;

    while((N+M) * blocks < input.size())
        blocks++;
    output.assign(N * blocks, false);

    bool change = true;
    while(max_iterations-- && change) {

        change = false;
        for(int b = 0; b < blocks; b++) {
            vector<int> wrong_cnt(N + M, 0);
            for(int i = 0; i < M; i++) {
                bool x = input[(N + M) * b + (N + i)];
                for (auto j: graph[i])
                    x = (x != input[(N + M) * b + j]);

                if (x) {
                    wrong_cnt[N + i]++;
                    for (auto j: graph[i])
                        wrong_cnt[j]++;
                }
            }

            int id = max_element(wrong_cnt.begin(), wrong_cnt.end()) - wrong_cnt.begin();
            if (wrong_cnt[id]) {
                input[(N + M) * b + id] = !input[(N + M) * b + id];
                change = true;
            }

        }

    }

    for(int b = 0; b < blocks; b++)
        for(int i = 0; i < N; i++)
            output[N * b + i] = input[(N + M) * b + i];
    
}

}