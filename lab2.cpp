#include <iostream>
#include <fstream>
#include <iomanip>
#include "src/bits.hpp"
#include "src/hamming.hpp"
#include "src/mr.hpp"
#include "src/ldpc.hpp"

using namespace std;

int main() {

    vector<bool> input,out,decoded;
    bits::generate_bits(input, 12, 0.5);
    vector<vector<int>> AL = {{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
    ldpc::encode(input, AL, 4, out);
    ldpc::decode(out, AL, 4, decoded, 100);

    int i = 0;
    for (auto b: input) 
        cout << b << (++i % 4 == 0 ? "     " : "");
    cout << endl;
    i = 0;
    for (auto b: out)
        cout << b << (++i % 8 == 0 ? " " : "");
    cout << endl;
    i = 0;
    for (auto b: decoded)
        cout << b << (++i % 4 == 0 ? "     " : "");
    cout << endl;

}