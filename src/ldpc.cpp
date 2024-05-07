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
                if(info_uses[value] >= dv) {
                    rem.push_back(value);
                }
            }
            k++;
        }
        for(auto value : rem) 
            parity.erase(value);
    }

    if(!parity.empty()){
        edges.clear();
        create_graph(n, dv, dc, edges);
    }
}

void decode(vector<bool> &input, vector<vector<int>> &graph, int N, vector<bool> &output, int max_iterations) {

    int M = graph.size(), blocks = 0;


    while(N * blocks < input.size())
        blocks++;

    while(input.size() > N*blocks)
        input.pop_back();

    bool change = true;
    while(max_iterations-- && change) {

        change = false;
        for(int b = 0; b < blocks; b++) {
            vector<int> wrong_cnt(N, 0);
            for(int i = 0; i < M; i++) {
                bool x = false;
                for (auto j: graph[i])
                    x = (x != input[N * b + j]);

                if (x) {
                    for (auto j: graph[i])
                        wrong_cnt[j]++;
                }
            }

            int id = max_element(wrong_cnt.begin(), wrong_cnt.end()) - wrong_cnt.begin();
            if (wrong_cnt[id]) {
                input[N * b + id] = !input[N * b + id];
                change = true;
            }

        }

    }

    output = input;
    
}

}