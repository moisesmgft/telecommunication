#ifndef BITS_HPP
#define BITS_HPP

#include <vector>

namespace bits {

using namespace std;

void generate_bits(vector<bool> &bits, int n, float q);

void communicate_bits_through_bsc(const vector<bool> &input, vector<bool> &output, float p);

double error_percentage(const vector<bool>& original, const vector<bool> &decoded);

double error_percentage(const vector<int>& original, const vector<int> &decoded);

double error_percentage(const vector<int> &original, const vector<bool> &decoded);

void communicate_bits_through_awgn(const vector<float> &input, vector<float> &output, float var);

};

#endif // BITS_HPP