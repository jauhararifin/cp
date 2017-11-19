#include <bits/stdc++.h>

using namespace std;

long long n,x;

int main() {
    scanf("%d", &n);
    vector<long long> p;
    long long total = 0;
    for (int i = 0; i < n; i++)
        scanf("%lld", &x), total += x;
    for (int i = 0; i < n; i++)
        scanf("%lld", &x), p.push_back(x);
    sort(p.begin(), p.end());
    if (p[n-1] + p[n-2] >= total)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}