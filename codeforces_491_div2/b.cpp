#include <bits/stdc++.h>

using namespace std;

int n,a[100];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", a + i);
  
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += a[i];

  int minimum_sum = (9*n+1)/2;
  sort(a, a + n);
  int ans = 0;
  for (int i = 0; i < n && sum < minimum_sum; sum += 5-a[i], i++, ans++);

  printf("%d\n", ans);

  return 0;
}