#include <bits/stdc++.h>

using namespace std;

int t,n,a[150],b[150];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < n; i++) scanf("%d", b + i);
        for (int i = 0; i < n; i++) a[i] = max(0, 20 * a[i] - 10 * b[i]);
        int m = a[0];
        for (int i = 0; i < n; i++) m = max(m, a[i]);
        printf("%d\n", m);
    }
    return 0;
}