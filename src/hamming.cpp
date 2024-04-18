#include "hamming.hpp"
#include <iostream>

namespace hamming {

vector<bool> multiplyByHTranspose(const vector<bool>& input) {
    vector<bool> result(3, 0);

    for (int i = 0; i < 3; i++) {
        bool sum = 0;
        for (int j = 0; j < 7; j++) {
            sum ^= (input[j] & H[i][j]);
        }
        result[i] = sum;
    }

    return result;
}

int syndromeToPosition(const std::vector<bool>& syndrome) {
    if(syndrome == std::vector<bool>{1,1,1}) return 1;
    if(syndrome == std::vector<bool>{1,0,1}) return 2;
    if(syndrome == std::vector<bool>{1,1,0}) return 3;
    if(syndrome == std::vector<bool>{0,1,1}) return 4;
    if(syndrome == std::vector<bool>{1,0,0}) return 5;
    if(syndrome == std::vector<bool>{0,1,0}) return 6;
    if(syndrome == std::vector<bool>{0,0,1}) return 7;
    return 0;

}

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

    int size = input.size();
    int blocks = size / 7;
    output.reserve(4*blocks);
    
    for (int i = 0; i < blocks; i++) {

        vector<bool> block(input.begin() + 7*i, input.begin() + 7*i + 7);
        vector<bool> syndrome = multiplyByHTranspose(block);

        int errorPosition = syndromeToPosition(syndrome);

        vector<bool> correctedOutput = block;

        if (errorPosition > 0) { 
            correctedOutput = block;
            correctedOutput[errorPosition - 1] = !correctedOutput[errorPosition - 1];
        } else {
            correctedOutput = block;
        }
        
        
        output.push_back(correctedOutput[0]); 
        output.push_back(correctedOutput[1]); 
        output.push_back(correctedOutput[2]); 
        output.push_back(correctedOutput[3]); 

    }
}

}