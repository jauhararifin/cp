#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,a,b; scanf("%d%d%d", &n, &a, &b);
    if (n % b == 0)
        printf("YES\n%d %d\n", 0, n / b);
    else {
        for (int i = 1; n > 0; i++) {
            n -= a;
            if (n % b == 0) {
                printf("YES\n%d %d\n", i, n / b);
                return 0;
            }
        }
        printf("NO\n");
    }
    return 0;
}