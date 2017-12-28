#include <bits/stdc++.h>

using namespace std;

int n,h;

int main() {
    scanf("%d", &n);
    h = 0;
    for (int i = 1; i <= n; i++)
        h += min(i, n - i + 1);
    printf("%d\n", h);
    return 0;
}