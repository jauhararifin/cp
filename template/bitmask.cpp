#include <bits/stdc++.h>

using namespace std;

inline bool get_bit(unsigned int bitmask, int pos) {
    return (bitmask >> pos) & 1;
}

inline bool get_bit(unsigned long long bitmask, int pos) {
    return (bitmask >> pos) & 1;
}

inline void set_bit(unsigned int &bitmask, int pos) {
    bitmask |= (unsigned int) 1 << pos;
}

inline void set_bit(unsigned long long &bitmask, int pos) {
    bitmask |= (unsigned long long) 1 << pos;
}

inline void unset_bit(unsigned int &bitmask, int pos) {
    bitmask &= ~((unsigned int) 1 << pos);
}

inline void unset_bit(unsigned long long &bitmask, int pos) {
    bitmask &= ~((unsigned long long) 1 << pos);
}

inline void toggle_bit(unsigned int &bitmask, int pos) {
    bitmask ^= (unsigned int) 1 << pos;
}

inline void toggle_bit(unsigned long long &bitmask, int pos) {
    bitmask ^= (unsigned long long) 1 << pos;
}

int main() {
    return 0;
}