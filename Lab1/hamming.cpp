#include "hamming.hpp"

namespace hamming {

void encode(vector<bool>& input, vector<bool>& output) {
    
    int size = 0, original_size = input.size();
    while (size < input.size())
        size += 4;


    for (int i = input.size(); i < size; i++)
        input.push_back(false);

    int blocks = size / 4;
    output.assign(7*blocks, 0);

    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < 4; j++)
            output[7*i + j] = input[4*i + j];

        output[7*i + 4] = input[4*i] ^ input[4*i + 1] ^ input[4*i + 2];
        output[7*i + 5] = input[4*i] ^ input[4*i + 2] ^ input[4*i + 3];
        output[7*i + 6] = input[4*i] ^ input[4*i + 1] ^ input[4*i + 3];
    }

    for (int i = original_size; i < size; i++)
        input.pop_back();

}

void decode(const vector<bool>& input, vector<bool>& output) {
    
}

}