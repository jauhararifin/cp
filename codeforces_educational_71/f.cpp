#include <stdio.h>
#include <string.h>

using namespace std;

int q,t,x,y,sum[700][700],a[500001];

int main() {
  memset(sum, 0, sizeof sum);
  memset(a, 0, sizeof a);
  scanf("%d", &q);
  while (q--) {
    scanf("%d%d%d", &t, &x, &y);
    if (t == 1) {
      a[x] += y;
      for (int i = 1; i < 700; i++)
        sum[i][x%i] += y;
    } else {
      if (x < 700)
        printf("%d\n", sum[x][y]);
      else {
        int h = 0;
        for (int i = y; i <= 500000; i += x) h += a[i];
        printf("%d\n", h);
      }
    }
  }
  return 0;
}
