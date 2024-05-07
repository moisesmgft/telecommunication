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
        int num = p;
        ldpc::create_graph(num, 3, 4, local);
        ldpc::invert_graph(local, inv, num);
        edges[p] = local;
        inverted_edges[p] = inv;
    }
    vector<double> probabilites = {1e-1,5e-2,2e-3,1e-3,5e-4,2e-5,1e-5};

    vector<bool> original;
    bits::generate_bits(original, 1e5, 0.5);
    for(double p = 0.5; p >= 1e-5; p *= 0.9) {
        for(auto s : sizes) {
            vector<bool> encoded, encoded_error, decoded;
            double final_error;
            ldpc::encode(original, edges[s],  s, encoded);
            bits::communicate_bits_through_bsc(encoded, encoded_error, p);
            ldpc::decode(encoded_error, edges[s],  s, decoded, 50);
            final_error = bits::error_percentage(original, decoded);

            cout << p << "," << s << "," << final_error << "\n";
        }
    }

    return 0;

}