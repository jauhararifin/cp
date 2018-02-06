#include <bits/stdc++.h>

using namespace std;

long long x,y;

int main() {
    scanf("%lld%lld", &x, &y);
    if (x % y == 0)
        printf("-1\n");
    else
        printf("%lld\n", x);
    return 0;
}