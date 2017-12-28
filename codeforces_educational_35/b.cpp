#include <bits/stdc++.h>

using namespace std;

int n,a,b;

int main() {
    scanf("%d%d%d", &n, &a, &b);
    int h = -1;
    for (int i = 1; i < n; i++) {
        if (b >= n - i)
            h = max(h, min(n > i ? b/(n-i) : 1000000000, i > 0 ? a/i : 1000000000));
    }
    printf("%d\n", h);
    return 0;
}