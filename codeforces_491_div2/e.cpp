#include <bits/stdc++.h>

using namespace std;

int n;
char s[100];

long long factorial[20];

bool next_possibility(int* initial, int* start, int* end) {
  if (start == end)
    return 0;
  if (*start == 0)
    return next_possibility(initial + 1, start + 1, end);
  if (*start == 1) {
    *start = *initial;
    return next_possibility(initial + 1, start + 1, end);
  }
  *start = *start - 1;
  return 1;
}

long long count(int zero, vector<int>& c) {
  int sum = 0; for (int x : c) sum += x;
  long long result = factorial[sum + zero - 1] * (long long) sum;
  for (int x : c) result /= factorial[x];
  result /= factorial[zero];
  return result;
}

int main() {
  scanf("%s", s);
  n = (int) strlen(s);

  factorial[0] = factorial[1] = 1LL;
  for (int i = 2; i < 20; i++)
    factorial[i] = (long long) i * factorial[i-1]; 

  int initial[10]; memset(initial, 0, sizeof initial);
  for (int i = 0; i < n; i++)
    initial[s[i]-'0']++;

  int temp[10]; memcpy(temp, initial, sizeof initial);

  long long result = 0;
  do {
    int zero = temp[0];
    vector<int> v; for (int i = 1; i < 10; i++) if (temp[i] > 0) v.push_back(temp[i]);
    result += count(zero, v);
  } while (next_possibility(initial, temp, temp + 10));
  printf("%I64d\n", result);

  return 0;
}