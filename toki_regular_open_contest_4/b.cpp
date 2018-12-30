#include <bits/stdc++.h>

using namespace std;

int n,g1,b1,k1,g2,b2,k2;
char s1[100],s2[100];

int main() {
    scanf("%d%s%s", &n, s1, s2);
    g1 = b1 = k2 = g2 = b2 = k2 = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] == 'G') g1++;
        if (s1[i] == 'B') b1++;
        if (s1[i] == 'K') k1++;
        if (s2[i] == 'G') g2++;
        if (s2[i] == 'B') b2++;
        if (s2[i] == 'K') k2++;
    }
    printf("%d\n", min(g1,k2) + min(b1,g2) + min(k1,b2));
    return 0;
}