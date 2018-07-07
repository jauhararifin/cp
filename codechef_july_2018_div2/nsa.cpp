#include <bits/stdc++.h>

using namespace std;

int t, ns, bit[28], effects[100000][27];
char s[100001];

int query(int* arr, int i) {
  int sum = 0;
  for(; i > 0; i -= i&-i)
    sum += arr[i];
  return sum;
}

void update(int* arr, int i) {
  for(; i <= 26; i += i&-i) arr[i]++;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%s", s);
    ns = (int) strlen(s);
    for (int i = 0; i < ns; i++)
      s[i] = s[i] - 'a' + 1;

    memset(bit, 0, sizeof bit);
    for (int i = 0; i < ns; i++) {
      int original = query(bit, s[i] - 1);
      for (int j = 1; j <= 26; j++)
        effects[i][j] = query(bit, j - 1) - original;
      update(bit, s[i]);
    }

    // for (int i = 0; i < ns; i++) { printf("%d ->", i); for (int j = 1; j <= 26; j++) printf(" %d", effects[i][j]); printf("\n"); }

    memset(bit, 0, sizeof bit);
    for (int i = ns - 1; i >= 0; i--) {
      int original = query(bit, 26 - s[i]);
      for (int j = 1; j <= 26; j++)
        effects[i][j] += query(bit, 26 - j) - original;
      update(bit, 26 - s[i] + 1);
    }

    // for (int i = 0; i < ns; i++) { printf("%d ->", i); for (int j = 1; j <= 26; j++) printf(" %d", effects[i][j]); printf("\n"); }

    int value_small = 1000000000;
    for (int i = 0; i < ns; i++)
      for (int j = 1; j <= 26; j++)
        value_small = min(value_small, effects[i][j] + abs(s[i] - j));

    memset(bit, 0, sizeof bit);
    long long result = 0;
    for (int i = 0; i < ns; i++) {
      result += (long long) query(bit, s[i] - 1);
      update(bit, s[i]);
    }
    // cout<<"original "<<result<<endl;
    printf("%lld\n", result + (long long) value_small);
  }
  return 0;
}