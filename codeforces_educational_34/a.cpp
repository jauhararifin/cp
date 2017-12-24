#include <bits/stdc++.h>

using namespace std;

int n,x;

int memo[101];
bool f(int x) {
    if (x < 0) return 0;
    if (memo[x] > -1) return memo[x];
    if (x == 0) return 1;
    return memo[x] = f(x - 3) || f(x - 7);
}

int main() {
    scanf("%d", &n);
    memset(memo, -1, sizeof memo);
    while (n--) {
        scanf("%d", &x);
        printf("%s\n", f(x) ? "YES" : "NO");
    }
    return 0;
}