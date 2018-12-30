#include <bits/stdc++.h>

using namespace std;

int t,n,k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        n <<= 1; k <<= 1;
        int p = __gcd(n, k + n/2);
        if (p > k) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}