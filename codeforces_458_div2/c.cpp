#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007LL;

int k,pk[1001];
long long cmb[1001][1001];
string n;

long long memo[1001][1001];
long long solve(int pos, int cnt) {
    if (cnt == 0) return 1;
    if (pos >= n.length()) return 0;
    if (memo[pos][cnt] > -1) return memo[pos][cnt];
    if (n[pos] == '1') {
        long long get_0 = cmb[n.length() - pos - 1][cnt];
        // printf("pos: %d, cnt: %d = %lld\n", pos, cnt, get_0);
        long long get_1 = solve(pos + 1, cnt - 1);
        return memo[pos][cnt] = (get_0 % mod + get_1 % mod) % mod;
    } else {
        return memo[pos][cnt] = solve(pos + 1, cnt) % mod;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin>>n;
    cin>>k;
    if (k > 5) {
        cout<<0<<endl;
        return 0;
    }
    if (k == 0) {
        if (n == "0")
            cout<<0<<endl;
        else
            cout<<1<<endl;
        return 0;
    }

    pk[1] = 0;
    for (int i = 2; i <= 1000; i++)
        pk[i] = 1 + pk[__builtin_popcount(i)];
    // for (int i = 1; i < 10; i++) printf("%d %d\n", i, pk[i]);
    cmb[0][0] = 1;
    for (int i = 1; i <= 1000; i++) {
        cmb[i][0] = cmb[i][i] = 1;
        for (int j = 1; j < i; j++)
            cmb[i][j] = (cmb[i-1][j] % mod + cmb[i-1][j-1] % mod) % mod;
    }
    // printf("%dc%d = %lld\n", 4, 1, cmb[4][1]);
    memset(memo, -1, sizeof memo);
    long long result = 0;
    for (int i = 1; i <= 1000; i++)
        if (pk[i] == k - 1)
            result = (result % mod + solve(0, i) % mod) % mod;
    // printf("solve %d %d = %lld\n", 0, 1, solve(0,1));
    if (k == 1) result--;
    cout<<result<<endl;

    return 0;
}