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

    ofstream file("../results.csv");

    cout << fixed << setprecision(7);
    file << fixed << setprecision(7);

    vector<int> sizes = {100,200,500,1000};
    unordered_map<int,vector<vector<int>>> edges;
    unordered_map<int,vector<vector<int>>> inverted_edges;
    for(auto p : sizes) {
        vector<vector<int>> local, inv;
        int num = p-(p % 3 <= 1 ? p % 3 : (p % 3)-3);
        ldpc::create_graph(num, 2, 3, local);
        // ldpc::invert_graph(local, inv, num);
        edges[p] = local;
        inverted_edges[p] = inv;
    }

    cout << "p,\"size\",\"error\"\n";
    file << "p,\"size\",\"error\"\n";

    vector<bool> original(1e6,false);
    for(double p = 0.5; p >= 0.005; p *= 0.7) {
        vector<bool> encoded_error;
        bits::communicate_bits_through_bsc(original, encoded_error, p);
        for(auto s : sizes) {
            vector<bool> decoded;
            double final_error;
            ldpc::decode(encoded_error, edges[s],  s-(s % 3 <= 1 ? s % 3 : (s % 3)-3), decoded, 30);
            final_error = bits::error_percentage(original, decoded);

            cout << p << "," << s << "," << final_error << "\n";
            file << p << "," << s << "," << final_error << "\n";
        }
    }

    return 0;

}