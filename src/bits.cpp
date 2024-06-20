#include "bits.hpp"
#include <random>
#include <cmath>

namespace bits {

void generate_bits(vector<bool> &bits, int n, float q) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);

    bits.assign(n,false);
    for (auto b: bits) 
        if (dis(gen) < q + 1e-7)
            b  = true;

}

void communicate_bits_through_bsc(const vector<bool> &input, vector<bool> &output, float p) {

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);

    output.assign(input.begin(), input.end());
    for (int i = 0; i < input.size(); i++)
        if (dis(gen) < p + 1e-7) 
            output[i] = !output[i];

}

double error_percentage(const vector<bool> &original, const vector<bool> &decoded) {

    int size = min(original.size(), decoded.size());
    int error = 0;
    
    for (int i = 0; i < size; i++)
        if (original[i] != decoded[i])
            error++;

    return double(error) / double(size);
}

double error_percentage(const vector<int> &original, const vector<int> &decoded) {

    int size = min(original.size(), decoded.size());
    int error = 0;
    
    for (int i = 0; i < size; i++)
        if (original[i] != decoded[i])
            error++;

    return double(error) / double(size);
}


double error_percentage(const vector<int> &original, const vector<bool> &decoded) {

    int size = min(original.size(), decoded.size());
    int error = 0;
    
    for (int i = 0; i < size; i++)
        if (original[i] != decoded[i])
            error++;

    return double(error) / double(size);
}

void communicate_bits_through_awgn(const vector<float> &input, vector<float> &output, float var) {
    output.clear();

    default_random_engine gen;
    normal_distribution<float> gaussian(0.0, sqrt(var));

    for (const float &value: input) {
        float noise = gaussian(gen);
        output.push_back(value + noise);
    }
}

}
