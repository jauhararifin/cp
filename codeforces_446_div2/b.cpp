#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int,int> > p;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        p.push_back(make_pair(i-x, i-1));
    }
    sort(p.begin(), p.end());
    int last = -1;
    int alive = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].first > last)
            alive += p[i].first - last - 1;
        last = max(last, p[i].second);
    }
    printf("%d\n", alive + 1);
    return 0;
}