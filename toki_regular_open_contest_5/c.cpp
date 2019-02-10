#include <bits/stdc++.h>

using namespace std;

int n,k;
int pos[100000], psum[100000];
vector<int> v;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        pos[x-1] = i;
    }

    // for (int i = 0; i < n; i++)
    //     cout<<pos[i]<<" ";
    // cout<<endl;

    memset(psum, 0, sizeof psum);
    for (int i = 1; i < n; i++) {
        int from = min(pos[i], pos[i-1]);
        int to = max(pos[i], pos[i-1]);
        // cout<<from<<" "<<to<<endl;
        psum[from]++; psum[to]--;
    }

    int m = 0;
    for (int i = 0; i < n - 1; i++) {
        m += psum[i];
        v.push_back(m);
    }

    // for (auto x : v)
    //     cout<<x<<" ";
    // cout<<endl;

    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    m = 0;
    int h = 0;
    for (int i = 0; i < n && m < k; i++) {
        m += v[i];
        h++;
    }
    if (m < k)
        printf("-1\n");
    else
        printf("%d\n", h);

    return 0;
}