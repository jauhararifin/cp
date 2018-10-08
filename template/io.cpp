#include <bits/stdc++.h>

using namespace std;

int __last_read_character = 0;

int skip_whitespace() {
    int x = __last_read_character;
    if (x == EOF)
        return EOF;
    while (x == ' ' || x == '\n' || x == '\r' || x == '\t' || x == 0)
        x = getchar();
    __last_read_character = x;
    return x;
}

template<typename T>
int read_number(T& dest) {
    int x = skip_whitespace();
    dest = 0;
    if (x == EOF) return EOF;
    
    if (x == '-' || x == '+' || (x >= '0' && x <= '9')) {
        bool positive = 1;
        while (x == '-' || x == '+') {
            if (x == '-') positive = !positive;
            x = getchar();
        }

        if (x >= '0' && x <= '9') {
            dest = 0;
            while (x >= '0' && x <= '9') {
                dest = dest * 10LL + (x - '0');
                x = getchar();
            }
            if (!positive) dest *= -1;
            __last_read_character = x;
            return 0;
        }

        __last_read_character = x;
    }
    dest = 0;
    return 0;
}

int read_word(char* str) {
    int x = skip_whitespace();
    if (x == EOF) return EOF;
    while (!(x == ' ' || x == '\n' || x == '\r' || x == '\t' || x == 0 || x == EOF)) {
        *(str++) = x;
        x = getchar();
    }
    *str = 0;
    __last_read_character = x;
    return 0;
}

int read_word(string& str) {
    int x = skip_whitespace();
    if (x == EOF) return EOF;
    while (!(x == ' ' || x == '\n' || x == '\r' || x == '\t' || x == 0 || x == EOF)) {
        str += (char) x;
        x = getchar();
    }
    __last_read_character = x;
    return 0;
}

int main() {
    return 0;
}