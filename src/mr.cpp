#include "mr.hpp"
#include <map>
#include <iterator>
#include <random>

namespace mr {

map<int,vector<int>> XOR_BITS = {
    {9, {0,1,2}}, {10, {3,4,5}}, {11, {6,7,8}},
    {12, {0,3,6}}, {13, {1,4,7}}, {14, {2,5,8}},
    {15, {0,4,8}}
}; 

map<int,vector<int>> MASK_TO_FLIPPED;

void encode(vector<bool> &input, vector<bool> &output) {
    
    int size = 0, original_size = input.size();
    while (size < input.size())
        size += 9;

    for (int i = input.size(); i < size; i++)
        input.push_back(false);

    int blocks = size / 9;
    output.assign(16*blocks, 0);

    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < 9; j++)
            output[16*i + j] = input[9*i + j];
        
        for (int j = 9; j < 16; j++)
            for (auto l: XOR_BITS.at(j))
                output[16*i + j] = (output[16*i + j] != input[9*i + l]);
    }   
    
    for (int i = original_size; i < size; i++)
        input.pop_back();

}

void decode(vector<bool> &input, vector<bool> &output) {

    populate_map();

    int size = 0, original_size = input.size();
    while (size < input.size())
        size += 16;

    int blocks = size / 16;
    output.assign(9*blocks, 0);

    int mask, flipped;
    for (int i = 0; i < blocks; i++) {

        auto it = input.begin() + 16*i;
        get_error_mask(it, mask);
        get_flipped_mask(mask, flipped);

        for (int j = 0; j < 9; j++) {
            if (!b(flipped,15-j))
                output[9*i + j] = !(input[16*i + j]);
            else
                output[9*i + j] = (input[16*i + j]);
        }

    }
}

void get_error_mask(vector<bool>::iterator& begin, int& mask) {

    mask = 0;
    for (int j = 9; j < 16; j++) {
        for (auto l: XOR_BITS.at(j)) 
            if (*(begin + l))
                mask ^= (1 << (15 - j));
    }

    for (int j = 9; j < 16; j++) {
        int b = (mask & (1 << (15 - j))) >> (15 - j);
        if (b != *(begin + j))
            mask &= ~(1 << (15 - j));
        else
            mask |= (1 << (15 - j));
    }

}

void get_flipped_mask(int& mask, int& flipped) {

    vector<int>& candidates = MASK_TO_FLIPPED[mask];
    vector<int>::iterator begin = candidates.begin(), end = candidates.end();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, distance(begin,end) - 1);
    advance(begin, dis(gen));
    flipped = *begin;

}

void populate_map() {

    map<int,int> mask_to_count;

    for (int flip = 0; flip < (1 << 16); flip++) {
        int msg = (1 << 16) - 1;
        for (int i = 0; i < 16; i++)
            if (!(flip & (1 << i)))
                msg &= ~(1 << i);
        
        int mask = 0;
        if (x(msg,0,1,2) == b(msg,9)) mask |= (1 << 6);
        if (x(msg,3,4,5) == b(msg,10)) mask |= (1 << 5);
        if (x(msg,6,7,8) == b(msg,11)) mask |= (1 << 4);
        if (x(msg,0,3,6) == b(msg,12)) mask |= (1 << 3);
        if (x(msg,1,4,7) == b(msg,13)) mask |= (1 << 2);
        if (x(msg,2,5,8) == b(msg,14)) mask |= (1 << 1);
        if (x(msg,0,4,8) == b(msg,15)) mask |= (1 << 0);

        if (__builtin_popcount(flip) > mask_to_count[mask]) {
            mask_to_count[mask] = __builtin_popcount(flip);
            MASK_TO_FLIPPED[mask].clear();
            MASK_TO_FLIPPED[mask].push_back(reverseBits(flip,16));
        }
        else if (__builtin_popcount(flip) == mask_to_count[mask]) {
            MASK_TO_FLIPPED[mask].push_back(reverseBits(flip,16));
        }

    }
}

bool b(int num, int n) {
    return num & (1 << n);
}

bool x(int num, int k, int l, int m) {
    return b(num,k) ^ b(num,l) ^ b(num,m);
}

int reverseBits(int number, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int bit = (number >> i) & 1;
        result |= (bit << (n - 1 - i));
    }
    return result;
}


}