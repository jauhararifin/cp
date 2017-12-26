#include <bits/stdc++.h>

using namespace std;

bool get_bit(unsigned int bitmask, int pos) {
    return (bitmask >> pos) & 1;
}

void set_bit(unsigned int &bitmask, int pos) {
    bitmask |= (unsigned int) 1 << pos;
}

void unset_bit(unsigned int &bitmask, int pos) {
    bitmask &= ~((unsigned int) 1 << pos);
}

void toggle_bit(unsigned int &bitmask, int pos) {
    bitmask ^= (unsigned int) 1 << pos;
}

int main() {
    return 0;
}