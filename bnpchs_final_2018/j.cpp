#include <bits/stdc++.h>

using namespace std;

int t,n,u[100000],h[100000];

int main() {
  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", u + i);

    memset(h, 0, sizeof h);
    stack<pair<int,int> > st;
    for (int i = 0; i < n; i++) {
      int x = 0;
      while (!st.empty() && u[st.top().first] < u[i]) {
        pair<int,int> top = st.top(); st.pop();
        x += 1 + top.second;
      }
      st.push(make_pair(i, x));
      h[i] += x;
    }

    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
      int x = 0;
      while (!st.empty() && u[st.top().first] < u[i]) {
        pair<int,int> top = st.top(); st.pop();
        x += 1 + top.second;
      }
      st.push(make_pair(i, x));
      h[i] += x;
    }

    printf("Kasus #%d:", tc);
    for (int i = 0; i < n; i++)
      printf(" %d", h[i]);
    printf("\n");
  }
  return 0;
}