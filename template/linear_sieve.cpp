#include <bits/stdc++.h>

using namespace std;

vector<int> generate_prime(int n) {
  bool* sv = (bool*) malloc(sizeof(bool) * (n + 1));
  memset(sv, 0, sizeof(bool) * (n + 1));
  
  vector<int> primes;
  for (int i = 2; i <= n; i++) {
    if (!sv[i]) primes.push_back(i);
    for (int j = 0; j < (int) primes.size() && i * primes[j] <= n; j++) {
      sv[i * primes[j]] = 1;
      if (i % primes[j] == 0) break;
    }
  }
  return primes;
}

int main() {
  return 0;
}