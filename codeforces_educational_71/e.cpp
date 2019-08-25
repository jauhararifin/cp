#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int query(vector<int>& v) {
  printf("?");
  for (int x : v) printf(" %d", x);
  printf("\n");
  fflush(stdout);
  int x; scanf("%d", &x);
  return x;
}

void answer(int x) {
  printf("! %d\n", x); fflush(stdout);
  exit(0);
}

int main() {
  vector<int> q1; for (int i = 1; i <= 100; i++) q1.push_back(i);
  int ax = query(q1);

  vector<int> q2; for (int i = 1; i <= 100; i++) q2.push_back(i<<7);
  int bx = query(q2);

  int ab = ax ^ bx;
  int a = ab & 0b1111111;
  int x = ax ^ a;
  answer(x);

  return 0;
}
