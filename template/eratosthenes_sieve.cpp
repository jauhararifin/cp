#include <bits/stdc++.h>

using namespace std;

void generate_eratosthenes_factor_sieve(int n, int* sv) {
  sv[1] = 1;
  for (int i = 2; 1LL*i*i <= n; i++)
    if (sv[i] == 0)
      for (int j = i; j <= n; j += i)
        sv[j] = i;
  for (int i = 1; i <= n; i++)
    if (sv[i] == 0)
      sv[i] = i;
}

void generate_eratosthenes_prime_sieve(int n, bool* sv) {
  memset(sv, 0, sizeof(bool) * (n + 1));
  sv[1] = 1;
  for (int i = 2; 1LL*i*i <= n; i++)
    if (sv[i] == 0)
      for (int j = i + i; j <= n; j += i)
        sv[j] = 1;
}

int main() {
  return 0;
}