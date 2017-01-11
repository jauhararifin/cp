#include <bits/stdc++.h>

#define ll long long

using namespace std;

void extended_euclid(ll a, ll b, ll *x, ll *y, ll *gcd) {
	ll old_s = 1; ll s = 0;
	ll old_t = 0; ll t = 1;
	ll old_r = a; ll r = b;
	while (r != 0) {
		ll q = old_r / r;
		ll tmp = old_s; old_s = s; s = tmp - q*s;
		tmp = old_t; old_t = t; t = tmp - q*t;
		tmp = old_r; old_r = r; r = tmp - q*r;
	}
	if (x != NULL) *x = old_s;
	if (y != NULL) *y = old_t;
	if (gcd != NULL) *gcd = old_r;
}

ll solve(ll a, ll b, ll i, ll j) {
	ll x,h,gcd; extended_euclid(a, b, &x, &h, &gcd);
	h = -1;
	if (gcd == 0)
		h = 0;
	else if ((j-i) % gcd == 0) {
		x *= (j-i)/gcd;
		x = ((x % (b/gcd)) + (b/gcd)) % (b/gcd);
		h = a*x + i;
	}
	return h;
}

ll a,n,p,b,m,q;

int main() {
	scanf("%lld%lld%lld%lld%lld%lld", &n, &a, &p, &m, &b, &q);
	p = (n + n - p + 1) % n; q = q - 1;
	
	ll mini = -1;
	for (ll j = b*q; j < b*q+b; j++) {
		ll tmp = solve(a*n, b*m, a*p, j);
		if (tmp > -1) mini = mini < 0 ? tmp : min(mini, tmp);
	}
	for (ll j = b*q+1; j <= b*q+b; j++) {
		ll tmp = solve(a*n, b*m, a*p+a, j);
		if (tmp > -1) mini = mini < 0 ? tmp : min(mini, tmp);
	}
	for (ll i = a*p; i < a*p+a; i++) {
		ll tmp = solve(a*n, b*m, i, b*q);
		if (tmp > -1) mini = mini < 0 ? tmp : min(mini, tmp);
	}
	for (ll i = a*p+1; i <= a*p+a; i++) {
		ll tmp = solve(a*n, b*m, i, b*q+b);
		if (tmp > -1) mini = mini < 0 ? tmp : min(mini, tmp);
	}
		
	if (mini >= 0) {
		double angle = ((ll) (mini/a)) * (360.0/n) + ((ll) (mini/b)) * (360.0/m);
		printf("%.10lf\n", angle);
	} else
		printf("-1\n");
	
	return 0;
}
