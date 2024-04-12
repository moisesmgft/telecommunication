#include <iostream>
#include <iomanip>
#include "bits.hpp"
#include "hamming.hpp"
#include "mr.hpp"

using namespace std;

int main() {

    cout << fixed << setprecision(7);
    vector<double> ps = {5e-1, 2e-1, 1e-1, 
                         5e-2, 2e-2, 1e-2, 
                         5e-3, 2e-3, 1e-3, 
                         5e-4, 2e-4, 1e-4, 
                         5e-5, 2e-5, 1e-5};

    vector<bool> og, encoded, decoded;
    bits::generate_bits(og, 1e7, 0.5);
    hamming::encode(og,encoded);
    hamming::decode(encoded,decoded);
    cout << bits::error_percentage(og,decoded) << endl;


    cout << "p,mr,hamming\n";
    for (auto p: ps) {
        vector<bool> original, error, hamming_encoded, hamming_encoded_error, hamming_decoded, mr_encoded, mr_encoded_error, mr_decoded;
        double hamming_error, mr_error;

        bits::generate_bits(original, 1e6, 0.5);

        hamming::encode(original, hamming_encoded);
        bits::communicate_bits_through_bsc(hamming_encoded, hamming_encoded_error, p);
        hamming::decode(hamming_encoded_error, hamming_decoded);

        mr::encode(original, mr_encoded);
        bits::communicate_bits_through_bsc(mr_encoded, mr_encoded_error, p);
        mr::decode(mr_encoded_error, mr_decoded);

        mr_error = bits::error_percentage(original, mr_decoded);
        hamming_error = bits::error_percentage(original, hamming_decoded);




        cout << p << ",";
        cout << mr_error << ",";
        cout << hamming_error;
        cout << "\n";
    }


    return 0;
}