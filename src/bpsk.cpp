#include "bpsk.hpp"

void bpsk::encode(vector<int> &input, vector<float> &output) {
    output.assign(input.size(), 1.0);
    for (int i = 0; i < (int)input.size(); i++)
        if (input[i])
            output[i] = -1.0;
}

void bpsk::decode(const vector<bool> &input, vector<bool> &output)
{
}
