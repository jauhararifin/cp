#include <bits/stdc++.h>

using namespace std;

const long long mod = 998244353LL;

int n,a[100000],ds[21];
long long ten[21];

int dig(int x) {
    int d = 0;
    while (x > 0) { d++; x /= 10; }
    return d;
}

int main() {
    // for (int i = 1; i <= 20; i++) printf("%d %d\n", i, dig(i));
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    
    memset(ds, 0, sizeof ds);
    for (int i = 0; i < n; i++) ds[dig(a[i])]++;

    ten[0] = 1;
    for (int i = 1; i <= 20; i++) ten[i] = (ten[i-1] * 10LL) % mod;

    long long h = 0LL;
    for (int i = 0; i < n; i++) {
        int t = a[i];
        int nth = 1;
        while (t > 0) {
            long long di = t % 10;

            for (int dx = 1; dx <= 10; dx++) {
                // a
                if (dx >= nth)
                    h = (h + (((di * ten[2*nth-1]) % mod) * ds[dx]) % mod) % mod;
                else
                    h = (h + (((di * ten[dx+nth-1]) % mod) * ds[dx]) % mod) % mod;

                // b
                if (dx >= nth - 1)
                    h = (h + (((di * ten[2*nth-2]) % mod) * ds[dx]) % mod) % mod;
                else
                    h = (h + (((di * ten[nth+dx-1]) % mod) * ds[dx]) % mod) % mod;
            }
            
            t /= 10;
            nth++;
        }
    }

    printf("%I64d\n", h % mod);

    return 0;
}