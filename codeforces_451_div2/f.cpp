#include <bits/stdc++.h>
#define ll long long
#define mod1 2147483647LL
using namespace std;

string s;
ll hs[1000000];

ll _power_ten[1000001];
ll power_ten(int i) {
    if (_power_ten[0] == 0) {
        _power_ten[0] = 1LL;
        for (int i = 1; i <= 1000000; i++)
            _power_ten[i] = (10LL * _power_ten[i-1]) % mod1;
    }
    return _power_ten[i];
}
ll hash_range(int i, int j) {
    return ((hs[j] - ((i == 0 ? 0LL : hs[i-1]) * power_ten(j - i + 1)) % mod1) % mod1 + mod1) % mod1;
}

bool check(int da, int db) {
    if (da <= 0 || db <= 0 || (da + db) >= s.length()) return 0;
    if (s[0] == '0' && da > 1) return 0;
    if (s[da] == '0' && db > 1) return 0;
    if (s[da + db] == '0' && (s.length() - da - db) > 1) return 0;

    ll ha = hash_range(0, da - 1);
    ll hb = hash_range(da, da + db - 1);
    ll hs = hash_range(da + db, s.length() - 1);

    return ((ha + hb) % mod1) == (hs % mod1);
}

int main() {
    ios::sync_with_stdio(0); getline(cin, s);
    hs[0] = (ll) (s[0] - '0');
    for (int i = 1; i < s.length(); i++)
        hs[i] = (((hs[i-1] % mod1) * 10LL) % mod1 + (ll) (s[i] - '0')) % mod1;

    int da = 1, db = 1;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '0' && i < s.length() - 1)
            continue;
        int dsum = s.length() - i;

        if (check(s.length() - dsum - dsum, dsum)) {
            da = s.length() - dsum - dsum;
            db = dsum;
            break;
        }
        if (check(s.length() - dsum - (dsum - 1), dsum - 1)) {
            da = s.length() - dsum - (dsum - 1);
            db = dsum - 1;
            break;
        }
        if (check(dsum, s.length() - dsum - dsum)) {
            da = dsum;
            db = s.length() - dsum - dsum;
            break;
        }
        if (check(dsum - 1, s.length() - dsum - (dsum - 1))) {
            da = dsum - 1;
            db = s.length() - dsum - (dsum - 1);
            break;
        }
    }

    for (int i = 0; i < da; i++)
        printf("%c", s[i]);
    printf("+");
    for (int i = da; i < da + db; i++)
        printf("%c", s[i]);
    printf("=");
    for (int i = da + db; i < s.length(); i++)
        printf("%c", s[i]);
    printf("\n");

    return 0;
}