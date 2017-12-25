#include <bits/stdc++.h>

using namespace std;

int n,m,l,r;
char c1,c2,tmp,s[101];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    while (m--) {
        scanf("%d%d%c%c%c%c", &l, &r, &tmp, &c1, &tmp, &c2); l--; r--;
        while (l <= r) {
            if (s[l] == c1) s[l] = c2;
            l++;
        }
    }
    printf("%s\n", s);
    return 0;
}