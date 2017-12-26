#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

vector<int> quad;
set<int> quads;
int n, x;

int dist_closest(int a) {
    int index = upper_bound(quad.begin(), quad.end(), a) - quad.begin();
    return min(quad[index] - a, a - quad[index-1]);
}

int dist_to_non_quad(int x) {
    return x == 0 ? 2 : (quads.find(x) != quads.end() ? 1 : 0);
}

bool cmp(pair<int,int> a, pair<int,int> b) {
    if (a.first == b.second)
        return dist_to_non_quad(a.second) > dist_to_non_quad(b.second);
    return a.first < b.first;
}

int main() {
    for (int i = 0; i <= 31623; i++)
        quad.push_back(i*i), quads.insert(i*i);

    vector<pii> vquad, vnon_quad;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (quads.find(x) != quads.end())
            vquad.push_back(make_pair(dist_to_non_quad(x), x));
        else
            vnon_quad.push_back(make_pair(dist_closest(x), x));
    }
    sort(vquad.begin(), vquad.end());
    sort(vnon_quad.begin(), vnon_quad.end());

    long long res = 0;
    if (vquad.size() > vnon_quad.size()) {
        for (int i = 0; i < (vquad.size() - vnon_quad.size())/2; i++)
            res += vquad[i].fi;
    } else {
        for (int i = 0; i < (vnon_quad.size() - vquad.size())/2; i++)
            res += vnon_quad[i].fi;
    }

    printf("%lld\n", res);

    return 0;
}