#include <bits/stdc++.h>

using namespace std;

int n,a[2][100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a[0] + i);
    for (int i = 0; i < n; i++)
        scanf("%d", a[1] + i);

    for (int i = 1; i < n; i++) {
        a[0][i] += a[0][i-1];
        a[1][n-i-1] += a[1][n-i];
    }
    int m = -1;
    for (int i = 0; i < n; i++)
        m = max(m, a[0][i] + a[1][i]);
    printf("%d\n", m);

    return 0;
}