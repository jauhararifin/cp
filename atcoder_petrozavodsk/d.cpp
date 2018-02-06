#include <bits/stdc++.h>

using namespace std;

int n,m,a[100000];
vector<int> adj[100000],frs[100000];
bool vis[100000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    while (m--) {
        int x,y; scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    memset(vis, 0, sizeof vis);
    int nfrs = 0;
    vector<int> total;
    long long sum = 0LL;
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            stack<int> st; st.push(i);
            vector<int> tmp;
            while (!st.empty()) {
                int t = st.top(); st.pop();
                if (vis[t]) continue;
                vis[t] = 1;
                tmp.push_back(a[t]);
                for (int x : adj[t])
                    st.push(x);
            }
            sort(tmp.begin(), tmp.end());
            sum += tmp[0];
            for (int i = 1; i < tmp.size(); i++)
                total.push_back(tmp[i]);
            nfrs++;
        }

    if (nfrs == 1) {
        printf("0\n");
        return 0;
    }
    
    if (total.size() < (nfrs-2)) {
        printf("Impossible\n");
        return 0;
    }
    sort(total.begin(), total.end());
    for (int i = 0; i < nfrs - 2; i++)
        sum += total[i];
    printf("%lld\n", sum);

    return 0;
}