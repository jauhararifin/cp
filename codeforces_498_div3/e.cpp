#include <bits/stdc++.h>

using namespace std;

int n,q,mp[200000],childs[200000];
vector<int> adj[200000],path;

int euler(int node) {
  mp[node] = (int) path.size();
  path.push_back(node);
  childs[node] = 0;
  for (int x : adj[node])
    childs[node] += 1 + euler(x);
  return childs[node];
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    int x; scanf("%d", &x); x--;
    adj[x].push_back(i);
  }
  euler(0);

  while (q--) {
    int u,k; scanf("%d%d", &u, &k); u--; k--;
    if (childs[u] >= k)
      printf("%d\n", path[mp[u] + k] + 1);
    else
      printf("%d\n", -1);
  }

  return 0;
}