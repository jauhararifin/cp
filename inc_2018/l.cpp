#include <bits/stdc++.h>

using namespace std;

const long long INF = 1000000000000LL;

int n,m,np;
long long mat[16][16];
long long memo[65536][16];

long long dp(vector<int>& join, int n) {    
    int bmm = 0; for (int x : join) bmm |= (1<<x);
    if (memo[bmm][n] > -1) return memo[bmm][n];

    if (join.size() == 2) {
        int enemy; for (int x : join) if (x != n) enemy = x;

        long long result = INF;
        if (mat[n][enemy] > 0)
            result = mat[n][enemy];

        return memo[bmm][n] = result;
    }

    vector<int> bm;
    for (int i = 0; i < join.size() / 2; i++) bm.push_back(0);
    for (int i = 0; i < join.size() / 2; i++) bm.push_back(1);
    long long result = INF;
    do {
        vector<int> a, b;
        bool in_a = 0;
        for (int i = 0; i < join.size(); i++)
            if (bm[i])
                b.push_back(join[i]);
            else {
                if (join[i] == n) in_a = 1;
                a.push_back(join[i]);
            }

        long long x = dp(a, n);
        for (int y : b)
            if (mat[n][y] > 0 && dp(b, y) < INF)
                result = min(result, x + mat[n][y]);
    } while(next_permutation(bm.begin(), bm.end()));

    return memo[bmm][n] = result;
}

int main() {
    memset(memo, -1, sizeof memo);
    scanf("%d", &n);
    np = 1<<n;
    for (int i = 0; i < np; i++)
        for (int j = 0; j < np; j++)
            scanf("%lld", mat[i] + j);

    vector<int> temp; for (int i = 0; i < np; i++) temp.push_back(i);
    long long r = dp(temp, 0);
    if (r < INF) printf("%lld\n", r); else printf("-1\n");
    return 0;
}