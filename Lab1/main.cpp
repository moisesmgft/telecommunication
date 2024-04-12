#include <iostream>
#include "bits.hpp"
#include "hamming.hpp"
#include "mr.hpp"

using namespace std;

int main() {

    vector<double> ps = {5e-1, 2e-1, 1e-1, 
                         5e-2, 2e-2, 1e-2, 
                         5e-3, 2e-3, 1e-3, 
                         5e-3, 2e-4, 1e-4, 
                         5e-5, 2e-5};

    for (auto p: ps) {
        vector<bool> original, error, hamming_encoded, hamming_decoded, mr_encoded, mr_decoded;
        double hamming_error, mr_error;

        bits::generate_bits(original, 1e6, 0.5);
        bits::communicate_bits_through_bsc(original, error, p);

        hamming::encode(error, hamming_encoded);


        mr::encode(error, mr_encoded);
        mr::decode(mr_encoded, mr_decoded);

        mr_error = bits::error_percentage(original, mr_decoded);

        cout << "p = " << p << ": ";
        cout << mr_error;
        cout << "\n";
    }


    return 0;
}