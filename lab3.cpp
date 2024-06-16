#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "src/bits.hpp"
#include "src/ldpc.hpp"
#include "src/bpsk.hpp"

using namespace std;

int main() {

    const string file_path = "../data/lab3_results.csv";
    const float Es = 1.0;
    const float eps = 1e-3;
    const size_t input_size = 1e6;

    ofstream file(file_path);
    cout << fixed << setprecision(8);
    file << fixed << setprecision(8);
    cout << "SNR,\"No decoding\", Demodulated";
    file << "SNR,\"No decoding\", Demodulated";
    
    vector<int> original(input_size,0);
    vector<float> modulated;
    bpsk::encode(original, modulated);

    for (float snr = 0.0; snr <= 5.0 + eps; snr += 0.5) {
        // snr = 10 log10(1/n0) => 10 ^ (snr/10) = 1 / n0
        float N0 = 1 / pow(10.0F, snr / 10.0F);
        float var = N0 / 2.0F;

        vector<float> past_gaussian;
        bits::communicate_bits_through_awgn(modulated, past_gaussian, var);

        vector<int> demodulated, no_decoding;
        // bpsk::decode

        double demodulated_error = bits::error_percentage(original, demodulated);
        double no_decoding_error = bits::error_percentage(original, no_decoding);

        cout << snr << "," << no_decoding_error << "," << demodulated_error << "\n";
        file << snr << "," << no_decoding_error << "," << demodulated_error << "\n";
    }

    file.close();
    return 0;
}