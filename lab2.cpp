#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <iomanip>
#include "src/bits.hpp"
#include "src/hamming.hpp"
#include "src/mr.hpp"
#include "src/ldpc.hpp"

using namespace std;

int main() {

    cout << fixed << setprecision(7);
    vector<int> sizes = {100,200,500,1000};
    unordered_map<int,vector<vector<int>>> edges;
    unordered_map<int,vector<vector<int>>> inverted_edges;
    for(auto p : sizes) {
        vector<vector<int>> local, inv;
        int num = p-(p % 7 <= 3 ? p % 7 : (p % 7)-7);
        ldpc::create_graph(num, 3, 7, local);
        // ldpc::invert_graph(local, inv, num);
        edges[p] = local;
        inverted_edges[p] = inv;
    }
    vector<double> probabilites = {1e-1,5e-2,2e-3,1e-3,5e-4,2e-5,1e-5};

    vector<bool> original(1e5,false);
    for(double p = 0.5; p >= 1e-5; p *= 0.9) {
        for(auto s : sizes) {
            vector<bool> encoded_error, decoded;
            double final_error;
            bits::communicate_bits_through_bsc(original, encoded_error, p);
            ldpc::decode(encoded_error, edges[s],  s-(s % 7 <= 3 ? s % 7 : (s % 7)-7), decoded, 50);
            final_error = bits::error_percentage(original, decoded);

            cout << p << "," << s << "," << final_error << "\n";
        }
    }

    return 0;

}