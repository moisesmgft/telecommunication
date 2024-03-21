#ifndef MR_HPP
#define MR_HPP

#include <vector>

namespace mr {

using namespace std;

void encode(const vector<bool> &input, vector<bool> &output);

void decode(const vector<bool> &input, vector<bool> &output);

};

#endif // MR_HPP