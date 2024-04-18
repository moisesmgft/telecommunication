#include <iostream>
#include <fstream>
#include <iomanip>
#include "src/bits.hpp"
#include "src/hamming.hpp"
#include "src/mr.hpp"

using namespace std;

int main() {

    ofstream file("../results.csv");

    cout << fixed << setprecision(10);
    file << fixed << setprecision(10);

    vector<double> ps = {5e-1, 2e-1, 1e-1, 
                         5e-2, 2e-2, 1e-2, 
                         5e-3, 2e-3, 1e-3, 
                         5e-4, 2e-4, 1e-4, 
                         5e-5, 2e-5, 1e-5};


    cout << "p,\"No encoding\",\"MR\",\"Hamming\"\n";
    file << "p,\"No encoding\",\"MR\",\"Hamming\"\n";
    
    vector<bool> original;
    bits::generate_bits(original, 1e6, 0.5);
    double p = 0.5;
    while (p > 1e-5) { 
        vector<bool> error, hamming_encoded, hamming_encoded_error, hamming_decoded, mr_encoded, mr_encoded_error, mr_decoded;
        double hamming_error, mr_error;

        hamming::encode(original, hamming_encoded);
        bits::communicate_bits_through_bsc(hamming_encoded, hamming_encoded_error, p);
        hamming::decode(hamming_encoded_error, hamming_decoded);

        mr::encode(original, mr_encoded);
        bits::communicate_bits_through_bsc(mr_encoded, mr_encoded_error, p);
        mr::decode(mr_encoded_error, mr_decoded);

        mr_error = bits::error_percentage(original, mr_decoded);
        hamming_error = bits::error_percentage(original, hamming_decoded);

        cout << p << "," << p << "," << mr_error << "," << hamming_error << "\n";
        file << p << "," << p << "," << mr_error << "," << hamming_error << "\n";
        p *= 0.9;
    }

    file.close();
    return 0;
}