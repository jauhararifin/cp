#include <bits/stdc++.h>

using namespace std;

int n,x[16],y[16];
double memo[65536];
char dummy[256];

double solve(int bitmask) {
    if (__builtin_popcount(bitmask) == 2*n) return 0;
    if (memo[bitmask] > -1) return memo[bitmask];
    vector<double> candidate;
    for (int i = 0; i < 2*n; i++)
        if (!(bitmask & (1<<i))) {
            for (int j = i + 1; j < 2*n; j++)
                if (!(bitmask & (1<<j))) {
                    int next = bitmask | (1 << i) | (1 << j);
                    double r = hypot(x[i]-x[j],y[i]-y[j]);
                    // cout<<bitmask<<" "<<i<<" "<<j<<" "<<r<<endl;
                    candidate.push_back(r + solve(next));
                }
            break;
        }
    double m = 1e12;
    for (auto x : candidate) m = min(m, x);
    return memo[bitmask] = m;
}

int main() {
    for (int tc = 1;; tc++) {
        scanf("%d", &n);
        if (n == 0) return 0;
        for (int i = 0; i < 2*n; i++)
            scanf("%s%d%d", dummy, x + i, y + i);
        memset(memo, -1, sizeof memo);
        printf("Case %d: %.2lf\n", tc, solve(0));
    }
    return 0;
}