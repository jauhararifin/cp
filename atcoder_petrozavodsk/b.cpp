#include <bits/stdc++.h>

using namespace std;

int n;
long long x[10000],y[10000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &x[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &y[i]);
    
    long long minus = 0LL, plus = 0LL;
    for (int i = 0; i < n; i++) {
        long long c = x[i] - y[i];
        if (c > 0LL)
            plus += c;
        else if (c < 0LL)
            minus -= c / 2;
    }
    if (minus >= plus)
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}