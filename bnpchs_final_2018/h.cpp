#include <bits/stdc++.h>

using namespace std;

int t,n,x,y;
bool deleted[100000];

int main() {
  scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    scanf("%d", &n);
    vector<pair<int,int> > poses, lefts;
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &x, &y);
      poses.push_back(make_pair(x + y, i));
      lefts.push_back(make_pair(x - y, i));
    }
    memset(deleted, 0, sizeof deleted);
    sort(poses.begin(), poses.end());
    sort(lefts.begin(), lefts.end());

    int left_p = 0;
    int h = 0;
    for (pair<int,int> pos : poses) {
      if (deleted[pos.second]) continue;
      int cnt = 0;
      while (left_p < n && lefts[left_p].first <= pos.first) {
        cnt++;
        deleted[lefts[left_p].second] = 1;
        left_p++;
      }
      if (cnt > 0) h++;
    }
    printf("Kasus #%d: %d\n", tc, h);
  }
  return 0;
}