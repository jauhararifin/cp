#include <bits/stdc++.h>

using namespace std;

int n;
char s[100];

int guess(int i) {
    printf("%d\n", i); fflush(stdout);
    scanf("%s", s);
    if (s[0] == 'V') return 0;
    if (s[0] == 'M') return 1;
    return -1;
}

int inv(int x) {
    if (x == 1) return -1;
    if (x == -1) return 1;
    return 0;
}

int main() {
    scanf("%d", &n);

    int lo = 1;
    int hi = n - 1;
    int last = inv(guess(0));
    if (last == 0) return 0;
    while (lo <= hi) {
        // printf("%d %d\n", lo, hi); fflush(stdout);
        int mid = (lo + hi)/2;
        int c = guess(mid); if (c == 0) return 0;
        if (((mid-lo)%2 == 0 && c == last) || ((mid-lo)%2 == 1 && c != last))
            lo = mid + 1, last = inv(c);
        else
            hi = mid - 1;
    }
    return 0;
}