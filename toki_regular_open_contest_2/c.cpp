#include <bits/stdc++.h>

using namespace std;

int n,p,t,v,d;
pair<int,int> palang[2000];

int main() {
  scanf("%d%d%d%d%d", &n, &p, &t, &v, &d);
  for (int i = 0; i < n; i++)
    scanf("%d", &palang[i].first);
  for (int i = 0; i < n; i++)
    scanf("%d", &palang[i].second);
  sort(palang, palang + n);

  double cost = 0;
  for (int i = 0; i < n; i++)
    palang[i].second = min(palang[i].second, t);
  
  vector<int> poses;
  for (int i = 0; i < n; i++)
    poses.push_back(palang[i].first), poses.push_back(palang[i].first + p);
  sort(poses.begin(), poses.end());

  int cur = t;
  int last_pos = 0;
  for (int pos : poses) {

    // printf("cur: %d, from: %d to %d\n", cur, last_pos, pos);

    cost += d * abs(t - cur) * (double) (pos - last_pos) / (double) v;
    int lo = lower_bound(palang, palang + n, make_pair(pos - p, 2000000000)) - palang;
    int hi = upper_bound(palang, palang + n, make_pair(pos, 2000000000)) - palang;

    // printf("lo: %d, hi: %d\n", lo, hi);

    cur = t;
    for (int i = lo; i < hi; i++)
      cur = min(cur, palang[i].second);
    last_pos = pos;
  }
  printf("%.6lf\n", cost);

  return 0;
}