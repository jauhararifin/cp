#include <bits/stdc++.h>

using namespace std;

int n;

long long comb(int n, int x) {
	long long a = 1, b = 1;
	for (int i = 1; i <= x; i++)
		b *= i;
	for (int i = n; i >= n - x + 1; i--)
		a *= i;
	return (a / b) % 1000000007;
}

int main() {
	scanf("%d", &n);
	long long result = 0;
	for (int i = 0; 2*i <= n; i++)
		result = (result + comb(n,i)*comb(n-i,i)) % 1000000007;
	printf("%lld\n", result);
	return 0;
}