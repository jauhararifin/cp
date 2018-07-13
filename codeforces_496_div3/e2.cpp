#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

int incr = 0;
typedef tree<pair<int,int>, null_type, less<pair<int,int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int n,m,p[200000],mi[200000],ma[200000],c;
long long h;
ordered_multiset xi,yi;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", p + i);

  for (int i = 0; i < n; i++) {
    mi[i] = (p[i] < m) + (i > 0 ? mi[i-1] : 0);
    ma[i] = (p[i] > m) + (i > 0 ? ma[i-1] : 0);
  }

  h = 0;
  c = 0;
  for (int i = 0; i < n; i++) {
    int total = i + 1;
    xi.insert(make_pair(2*(i > 0 ? mi[i-1] : 0) - i, ++incr));
    yi.insert(make_pair(2*(i > 0 ? ma[i-1] : 0) - i, ++incr));

    int bs = xi.order_of_key(make_pair(2*mi[i] - i, 0));
    int sb = yi.order_of_key(make_pair(2*ma[i] - i - 1, 0));
    h += (long long) (total - bs - sb);
  }
  printf("%I64d\n", h);
  
  return 0;
}