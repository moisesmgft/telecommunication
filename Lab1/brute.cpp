#include <vector>
#include <iostream>
#include <map>
using namespace std;

bool b(int num, int n) {
    return num & (1 << n);
}

bool x(int num, int k, int l, int m) {
    return b(num,k) ^ b(num,l) ^ b(num,m);
}

void binary(int number, int n, bool invert) {
    for (int i = n-1; i >= 0; --i) {
        cout << (invert ? !((number >> i) & 1) : ((number >> i) & 1));
    }
}

int reverseBits(int number, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        int bit = (number >> i) & 1;
        result |= (bit << (n - 1 - i));
    }
    return result;
}

int main() {

    map<int,vector<int>> mask_to_flip;
    map<int,int> mask_to_number;
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

        if (__builtin_popcount(flip) > mask_to_number[mask]) {
            mask_to_number[mask] = __builtin_popcount(flip);
            mask_to_flip[mask].clear();
            mask_to_flip[mask].push_back(reverseBits(flip,16));
        }
        else if (__builtin_popcount(flip) == mask_to_number[mask]) {
            mask_to_flip[mask].push_back(reverseBits(flip,16));
        }

    }

    int cnt = 0;
    for (auto &[mask,error]: mask_to_flip) {
        binary(mask,7,false);
        cout << ": ";
        for (auto &flip: error) {
            cnt++;
            binary(flip,16,true);
            cout << "    ";
        }
        cout << endl;
    }

    cout << cnt << endl;

    return 0;
}