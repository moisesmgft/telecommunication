#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "src/bits.hpp"
#include "src/hamming.hpp"
#include "src/ldpc.hpp"
#include "src/bpsk.hpp"

using namespace std;

int main() {
    
    const string file_path = "../data/lab4_results.csv";
    const string g_file_path = "../data/lab4_graph.csv";
    const float Es = 1.0;
    const float eps = 1e-3;
    const size_t input_size = 999999*5;

    ofstream file(file_path);
    ofstream gfile(g_file_path);
    cout << fixed << setprecision(8);
    file << fixed << setprecision(8);
    cout << "SNR,Uncoded,Hamming,Bit-Flip,LLR,MR-LDPC\n";
    file << "SNR,Uncoded,Hamming,Bit-Flip,LLR,MR-LDPC\n";
    
    vector<int> original(input_size,0);
    vector<float> modulated;
    bpsk::encode(original, modulated);
    vector<vector<int>> c_graph, v_graph;
    ldpc::create_graph(1001, 3, 7, c_graph);
    ldpc::invert_graph(c_graph, 1001, v_graph);
    for(auto v_node_edges : v_graph) {
        for(auto it = v_node_edges.begin(); it != v_node_edges.end(); it++) {
            gfile << *it << (it != prev(v_node_edges.end()) ? "," : "\n");
        }
    }
    for (float snr = 0.0; snr <= 5.0 + eps; snr += 0.5) {
        // snr = 10 log10(1/n0) => 10 ^ (snr/10) = 1 / n0
        float N0 = 1 / pow(10.0F, snr / 10.0F);
        float var = N0 / 2.0F;

        vector<float> past_gaussian;
        vector<bool> past_gaussian_bin;
        bits::communicate_bits_through_awgn(modulated, past_gaussian, var);
        bpsk::to_binary(past_gaussian, past_gaussian_bin);

        vector<int> uncoded_result, bpsk_result, hamming_result, bit_flip_result;
        vector<bool> hamming_result_bool, bit_flip_result_bool;
        bpsk::decode(past_gaussian, uncoded_result, v_graph, 1, 7, 1001, var);
        bpsk::decode(past_gaussian, bpsk_result, v_graph, 50, 7, 1001, var);
        ldpc::decode(past_gaussian_bin, v_graph,  input_size, bit_flip_result_bool, 30);
        hamming::decode(past_gaussian_bin, hamming_result_bool);

        for (auto i: bit_flip_result_bool) bit_flip_result.push_back(i);
        for (auto i: hamming_result_bool) hamming_result.push_back(i);

        double uncoded_error = bits::error_percentage(original, uncoded_result);
        double hamming_error = bits::error_percentage(original, hamming_result);
        double bit_flip_error = bits::error_percentage(original, bit_flip_result);
        double bpsk_error = bits::error_percentage(original, bpsk_result);

        cout << snr << "," << uncoded_error << "," << hamming_error << "," << bit_flip_error << "," << bpsk_error << "," << 0.0 << "\n";
        file << snr << "," << uncoded_error << "," << hamming_error << "," << bit_flip_error << "," << bpsk_error << "," << 0.0 << "\n";
    }

    file.close();
    return 0;
}