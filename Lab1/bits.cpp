#include "bits.hpp"
#include <random>

namespace bits {

void generate_bits(vector<bool> &bits, int n, float q) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);

    bits.assign(n,false);
    for (auto b: bits) 
        if (dis(gen) < q + 1e-4)
            b  = true;

}

void communicate_bits_through_bsc(const vector<bool> &input, vector<bool> &output, float p) {

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);

    output.assign(input.begin(), input.end());
    for (int i = 0; i < input.size(); i++)
        if (dis(gen) < p + 1e-5) 
            output[i] = !output[i];

}

}



