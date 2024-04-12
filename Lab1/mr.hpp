#ifndef MR_HPP
#define MR_HPP

#include <vector>

namespace mr {

using namespace std;

void encode(vector<bool> &input, vector<bool> &output);

void decode(vector<bool> &input, vector<bool> &output);

void get_error_mask(vector<bool>::iterator& begin, int& mask);

void get_flipped_mask(int& mask, int& flipped);

void populate_map();

bool b(int num, int n);

bool x(int num, int k, int l, int m);

int reverseBits(int number, int n);

};

#endif // MR_HPP