#include <bits/stdc++.h>

using namespace std;

int n,k,x,h;

int main() {
    scanf("%d%d", &n, &k);
    h = 2000000000;
    while (n--) {
        scanf("%d", &x);
        if (k % x == 0)
            h = min(h, k / x);
    }
    printf("%d\n", h);
    return 0;
}