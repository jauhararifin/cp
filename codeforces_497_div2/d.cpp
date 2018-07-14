#include <bits/stdc++.h>
using namespace std;

int t,a,b,c,sv[100001];

int factorize(int n) {
  int h = 1;
  while (n > 1) {
    int p = sv[n];
    int c = 0;
    while (n % p == 0) {
      c++;
      n /= p;
    }
    h *= c + 1;
  }
  return h;
}

int choose_two(int a) {
  return a + (a * (a-1)) / 2;
}

int choose_three(int a) {
  return a + a * (a-1) + (a * (a - 1) * (a - 2)) / 6;
}

int main() {
  memset(sv, 0, sizeof sv);
  sv[1] = 1;
  for (int i = 2; i*i <= 100000; i++)
    if (sv[i] == 0)
      for (int j = i; j <= 100000; j += i)
        sv[j] = i;
  for (int i = 1; i <= 100000; i++)
    if (sv[i] == 0)
      sv[i] = i;

  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &a, &b, &c);
    int fa = factorize(a);
    int fb = factorize(b);
    int fc = factorize(c);
    int fab = factorize(__gcd(a,b));
    int fac = factorize(__gcd(a,c));
    int fbc = factorize(__gcd(b,c));
    int fabc = factorize(__gcd(a,__gcd(b,c)));

    // printf("fa: %d\nfb: %d\nfc: %d\nfab: %d\nfac: %d\nfbc: %d\nfabc: %d\n", fa,fb,fc,fab,fac,fbc,fabc);

    int only_a = fa - fab - fac + fabc;
    int only_b = fb - fab - fbc + fabc;
    int only_c = fc - fac - fbc + fabc;

    int only_ab = fab - fabc;
    int only_ac = fac - fabc;
    int only_bc = fbc - fabc;

    int only_abc = fabc;

    int result = 0;
    int v[7] = {only_a, only_b, only_c, only_ab, only_ac, only_bc, only_abc};
    for (int i = 0; i < 7; i++)
      for (int j = i + 1; j < 7; j++)
        for (int k = j + 1; k < 7; k++)
          result += v[i] * v[j] * v[k];
    result -= only_a * only_b * only_ab + only_a * only_c * only_ac + only_b * only_c * only_bc;

    // printf(">> %intd\n", result);

    int sum = only_a + only_b + only_c + only_ab + only_ac + only_bc + only_abc;
    result += choose_two(only_ab) * (sum - only_ab - only_a - only_b)
    + choose_two(only_ac) * (sum - only_ac - only_a - only_c)
    + choose_two(only_bc) * (sum - only_bc - only_b - only_c)
    + choose_two(only_abc) * (sum - only_abc);

    // printf(">> %intd\n", result);

    result += choose_three(only_abc);

    printf("%d\n", result);
  }
  
  return 0;
}