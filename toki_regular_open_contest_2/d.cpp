#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n,x,y,c,d,m1,m2;
vector<pair<ll,ll> > a_arr, b_arr;

bool visited[100000];
void calculate_arr(ll x, ll c, ll m, vector<pair<ll,ll> > &result) {
  ll temp = x % m;
  memset(visited, 0, sizeof visited);
  while (!visited[temp]) {
    visited[temp] = 1;
    result.push_back(make_pair(temp, 1));
    temp = (temp * c) % m;
  }
  int na = (int) result.size();
  int loop = -1;
  ll xxx = n;
  for (int i = 0; i < na; i++) {
    if (loop > -1 || result[i].first == temp) {
      if (loop == -1) loop = i;
      result[i].second = (xxx / (na - loop)) + ((i - loop) < (xxx % (na - loop)) ? 1 : 0);
    } else
      xxx--;
  }
}

int main() {
  scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &x, &y, &c, &d, &m1, &m2);

  calculate_arr(x, c, m1, a_arr);
  calculate_arr(y, d, m2, b_arr);
  int na = (int) a_arr.size(), nb = (int) b_arr.size();

  // printf("a: "); for (pair<ll,ll> temp : a_arr) printf("(%lld, %lld) ", temp.first, temp.second); printf("\n");
  // printf("b: "); for (pair<ll,ll> temp : b_arr) printf("(%lld, %lld) ", temp.first, temp.second); printf("\n");

  sort(a_arr.begin(), a_arr.end()); reverse(a_arr.begin(), a_arr.end());
  sort(b_arr.begin(), b_arr.end()); reverse(b_arr.begin(), b_arr.end());

  // printf("after sorted\n");
  // printf("a: "); for (pair<ll,ll> temp : a_arr) printf("(%lld, %lld) ", temp.first, temp.second); printf("\n");
  // printf("b: "); for (pair<ll,ll> temp : b_arr) printf("(%lld, %lld) ", temp.first, temp.second); printf("\n");

  ll h = 0;
  int i = 0, j = 0;
  while (i < na && a_arr[i].second == 0) i++;
  while (j < nb && b_arr[j].second == 0) j++;
  while (i < na && j < nb) {
    // printf("(%lld, %lld) - (%lld, %lld)\n", a_arr[i].first, a_arr[i].second, b_arr[j].first, b_arr[j].second);
    ll num = min(a_arr[i].second, b_arr[j].second);
    a_arr[i].second -= num;
    b_arr[j].second -= num;
    h += num * a_arr[i].first * b_arr[j].first;
    while (i < na && a_arr[i].second == 0) i++;
    while (j < nb && b_arr[j].second == 0) j++;
  }
  printf("%lld\n", h);

  return 0;
}