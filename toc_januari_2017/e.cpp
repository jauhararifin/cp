#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n,p1,s1,m1,p2,s2,m2;

ll arith(ll a, ll b, ll n) {
	return n*(a-b) + b*((n*(n+1LL))/2LL);
}

ll solve(ll n, ll p, ll s, ll m) {
	if (s == 0)
		return p*n;
	ll sum = 0, pawal = -1, langkah = 0, sumuntil = 0;
	while (n > 0) {
		if (p == pawal && langkah > 0) {
			ll temp = n / langkah;
			sum += sumuntil * temp;
			n -= temp * langkah;
		}
		ll num = (m - p - 1) / s + 1;
		if (num > n)
			break;
		sum += arith(p, s, num);
		sumuntil += arith(p, s, num);
		n -= num;
		langkah += num;
		p = (p + s * num) % m;
		if (pawal == -1) pawal = p, langkah = 0, sumuntil = 0;
	}
	sum += arith(p, s, n);
	return sum;
}

int main() {
	scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &p1, &s1, &m1, &p2, &s2, &m2);
	printf("%lld\n", solve(n, p1, s1, m1) + solve(n, p2, s2, m2));
	return 0;
}