#include <iostream>
#include "bits.hpp"
#include "hamming.hpp"
#include "mr.hpp"

using namespace std;

int main() {

    vector<bool> original, error, encoded;

    //bits::generate_bits(original, 16, 0.5);
    original = {0,1,1,0};
    bits::communicate_bits_through_bsc(original, error, 0);
    hamming::encode(original, encoded);

    for (auto b: original) cout << b; cout << "\n";
    for (auto b: error) cout << b; cout << "\n";
    for (auto b: encoded) cout << b; cout << "\n";


    return 0;
}