#include <bits/stdc++.h>

using namespace std;

int t,n;
long long c[100000],h[100000];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(c, 0, sizeof c);
        for (int i = 0; i < n; i++) {
            long long x; scanf("%lld", &x);
            c[max(0LL,i-x)] += 1;
            if (i+x+1 < n)
                c[i+x+1] -= 1;
        }
        long long x = 0;
        for (int i = 0; i < n; i++) {
            x += c[i];
            c[i] = x;
        }
        unordered_set<long long> p,q;
        for (int i = 0; i < n; i++) {
            long long x; scanf("%lld", &x);
            p.insert(x);
            q.insert(c[i]);
        }
        if (p == q) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}