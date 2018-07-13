#include <bits/stdc++.h>

#define pii pair<int,int>

using namespace std;

int n,m,k,level[200000];
vector<pii> adj[200000];
vector<int> choice[200000];
bool counted[200000];
bool ans[200000];

void print_solution(int i) {
  if (k <= 0) return;
  if (i >= n) {
    k--;
    for (int j = 0; j < m; j++)
      printf("%d", ans[j] ? 1 : 0);
    printf("\n");
  } else
    for (int c : choice[i]) {
      ans[c] = 1;
      print_solution(i + 1);
      ans[c] = 0;
    }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; i++) {
    int x,y; scanf("%d%d", &x, &y); x--; y--;
    adj[x].push_back(pii(y,i));
    adj[y].push_back(pii(x,i));
  }

  memset(level, -1, sizeof level);
  memset(counted, 0, sizeof counted);
  queue<pii> que; que.push(pii(0,0)); counted[0] = 1;
  while (!que.empty()) {
    pii t = que.front(); que.pop();
    level[t.first] = t.second;
    for (pii x : adj[t.first])
      if (!counted[x.first]) {
        counted[x.first] = 1;
        que.push(pii(x.first, t.second + 1));
      }
  }

  for (int i = 1; i < n; i++)
    for (pii x : adj[i])
      if (level[x.first] == level[i] - 1)
        choice[i].push_back(x.second);

  long long ways = 1LL;
  for (int i = 1; i < n && ways < k; i++)
    ways *= (long long) choice[i].size();
  k = (int) min(ways, (long long) k);

  memset(ans, 0, sizeof ans); 
  printf("%d\n", k);
  print_solution(1);

  return 0;
}