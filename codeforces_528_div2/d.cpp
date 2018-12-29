#include <bits/stdc++.h>

using namespace std;

int n,s,d[100000],l;

int main() {
    scanf("%d%d", &n, &s);
    memset(d, 0, sizeof d);
    for (int i = 0; i < n-1; i++) {
        int a,b;
        scanf("%d%d", &a, &b);
        d[a-1]++; d[b-1]++;
    }
    l = 0;
    for (int i = 0; i < n; i++)
        l += d[i] == 1;
    printf("%.10lf\n", (double) s / (double) l * 2.0f);
    return 0;
}