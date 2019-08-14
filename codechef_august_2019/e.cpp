#include <bits/stdc++.h>

using namespace std;

int t,n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        vector<int> a; a.push_back(0);
        for (int i = 0; i < n; i++) {
            int x; scanf("%d", &x);
            a.push_back(x ^ a.back());
        }
        // for (auto x : a) cout<<x<<" "; cout<<endl;
        unordered_map<int,vector<int> > mp;
        for (int i = 0; i < (int) a.size(); i++) mp[a[i]].push_back(i);
        long long h = 0;
        for (auto x : mp) {
            // cout<<x.first<<": "; for (int z : x.second) cout<<z<<" "; cout<<endl;
            int nx = (int) x.second.size();
            for (int i = 0; i < (int) nx; i++)
                h += (long long) (nx - i - 1 - i) * (long long) -x.second[i];
            h -= ((long long) nx * (long long) (nx - 1)) / 2LL;
        }
        printf("%lld\n", h);
    }
    return 0;
}