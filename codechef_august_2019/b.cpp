#include <bits/stdc++.h>

using namespace std;

int t;
long long n,k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld%lld", &n, &k);
        if ((n / k) % k != 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}