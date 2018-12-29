#include <bits/stdc++.h>

using namespace std;

int n,k;

int main() {
    scanf("%d%d", &n, &k);
    int result = 2000000000;
    for (int mod = 1; mod < k; mod++) {
        if (n % mod != 0)
            continue;
        int x = k * n / mod + mod;
        result = min(result, x);
    }
    printf("%d\n", result);
    return 0;
}