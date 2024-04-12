#ifndef BITS_HPP
#define BITS_HPP

#include <vector>

namespace bits {

using namespace std;

void generate_bits(vector<bool> &bits, int n, float q);

void communicate_bits_through_bsc(const vector<bool> &input, vector<bool> &output, float p);

double error_percentage(const vector<bool>& original, const vector<bool> decoded);

};

#endif // BITS_HPP