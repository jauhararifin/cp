#include <bits/stdc++.h>

using namespace std;

int n,c,a[200000];
map<int,int> mp;

int main() {
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    c = 0;
    long long result = 0;
    for (int i = 0; i < n; i++) {
        long long count = c - mp[a[i]] - mp[a[i]-1] - mp[a[i]+1];
        result += count * a[i];
        mp[a[i]]++; c++;
    }
    mp.clear(); c = 0;
    for (int i = n-1; i >= 0; i--) {
        long long count = c - mp[a[i]] - mp[a[i]-1] - mp[a[i]+1];
        result -= count * a[i];
        mp[a[i]]++; c++;
    }
    printf("%lld\n", result);

    return 0;
}