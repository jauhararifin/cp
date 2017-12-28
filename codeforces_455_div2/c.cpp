#include <bits/stdc++.h>

using namespace std;
const long long mod = 1000000007;

int n;
char p[5001];
long long mem[5001], h;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", p + i);
    
    memset(mem, 0, sizeof mem);
    mem[0] = 1;
    for (int i = 0; i < n - 1; i++)
        if (p[i] == 'f') {
            for (int j = n - 1; j >= 0; j--)
                mem[j + 1] = mem[j];
            mem[0] = 0;
        } else {
            long long acc = 0;
            for (int j = n - 1; j >= 0; j--) {
                acc = ((acc % mod) + (mem[j] % mod)) % mod;
                mem[j] = acc % mod;
            }
        }
    
    h = 0;
    for (int i = 0; i < n; i++)
        h = ((h % mod) + (mem[i] % mod)) % mod;
    printf("%lld\n", h);
    return 0;
}