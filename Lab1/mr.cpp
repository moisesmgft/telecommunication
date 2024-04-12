#include "mr.hpp"

namespace mr {

void encode(vector<bool> &input, vector<bool> &output) {
    
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
        for (int j = 0; j < 3; j++)
            output[7*i + j + 4] = input[4*i + j] ^ input[4*i + j + 1];
    }
    
    for (int i = original_size; i < size; i++)
        input.pop_back();


}

void decode(vector<bool> &input, vector<bool> &output) {

    int blocks = input.size() / 7;
    output.assign(4*blocks, 0);

    for (int i = 0; i < blocks; i++) {
        int mask = 0;

        for (int j = 0; j < 4; j++)
            output[4*i + j] = input[7*i + j];

        for (int j = 0; j < 3; j++)
            if (input[7*i + j + 4] == input[7*i + j] ^ input[7*i + j + 1])
                mask |= 1 << (2 - j);

        //if (mask == 3) 
        //    output[4*i] = !output[4*i];
        if (mask == 6) 
            output[4*i + 3] = !output[4*i + 3];
        if (mask == 4) 
            output[4*i + 2] = !output[4*i + 2];
        if (mask == 2 || mask == 0)
            output[4*i] = !output[4*i], output[4*i + 3] = !output[4*i + 3];
        if (mask == 1)
            output[4*i + 1] = !output[4*i + 1];
    }
}

}
