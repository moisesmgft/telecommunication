#include "ldpc.hpp"
#include <map>
#include <iterator>
#include <random>
#include <unordered_set>
#include <algorithm>

namespace ldpc {

vector<int> random_vector(int size, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, max - 1);

    std::unordered_set<int> unique_numbers;
    std::vector<int> random_values;

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

    for(int i = 0; i < m; i++) {
        vector<int> rd = random_vector(dc, remain);
        
        int count = 0, current = 0;
        for(int j = 0; j < n; j++, count++) {
            if(count == rd[current] && info_uses[j] < dv) {
                current++;
                info_uses[j]++;
                edges[i].push_back(j);
                if(info_uses[j] >= dv) {
                    remain--;
                }
            } else if(info_uses[j] >= dv) {
                count--;
            }
        }
    }





    



}

void encode(vector<bool> &input, vector<bool> &output) {

}

void decode(vector<bool> &input, vector<bool> &output) {

}

}