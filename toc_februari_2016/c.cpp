#include <bits/stdc++.h>

#define ll long long

using namespace std;

const ll mod = 1000000007;

ll r,c,x,y;

void extended_euclid(ll a, ll b, ll *x, ll *y, ll *gcd) {
	ll s = 0; ll old_s = 1;
	ll t = 1; ll old_t = 0;
	ll r = b; ll old_r = a;
	while (r != 0) {
		ll q = old_r / r;
		ll tmp = old_r; old_r = r; r = tmp - q * r;
		tmp = old_s; old_s = s; s = tmp - q * s;
		tmp = old_t; old_t = t; t = tmp - q * t;
	}
	*x = old_s; *y = old_t; *gcd = old_r;
}
ll im_memo[1001];
ll inverse(ll a) {
	if (a <= 1000 && im_memo[a] > -1) return im_memo[a];
	ll x, y, z;
	extended_euclid(a, mod, &x, &y, &z);
	if (a > 1000) return ((x % mod) + mod) % mod;
	return im_memo[a] = ((x % mod) + mod) % mod;
}
ll f_memo[1001];
ll factorial(ll n) {
	if (n < 0) return 0;
	if (n == 0) return 1LL;
	if (f_memo[n] > -1) return f_memo[n];
	ll h = 1; while (n > 0) h = (h * n--) % mod; return f_memo[n] = ((h % mod) + mod) % mod;
}
ll fi_memo[1001];
ll inv_factorial(ll n) {
	if (n < 0) return 0;
	if (n == 0) return 1LL;
	if (fi_memo[n] > -1) return fi_memo[n];
	ll h = 1; while (n > 0) h = (h * inverse(n--)) % mod; return fi_memo[n] = ((h % mod) + mod) % mod;
}
ll permutation(ll a, ll b) {
	if (b > a) return 0;
	if (b == 0) return 1;
	ll x = 1; for (int i = 0; i < b; i++) x = (x * (a-i)) % mod;
	return ((x % mod) + mod) % mod;
}
ll combination(ll a, ll b) {
	if (b > a) return 0;
	if (b == 0 || b == a) return 1;
	ll x = permutation(a, b);
	while (b > 0) x = (x * inverse(b--)) % mod;
	return ((x % mod) + mod) % mod;
}
ll combination(int a, int b, int c, int d) {
	if (b+c+d > a) return 0;
	ll x = permutation(a, b+c+d) % mod;
	ll y = (((inv_factorial(b) * inv_factorial(c)) % mod) * inv_factorial(d)) % mod;
	//cout<<a<<" "<<b<<" "<<c<<" "<<d<<"c "<<x<<" "<<y<<" "<<inverse(y)<<endl;
	return ((x * y) % mod + mod) % mod;
}
ll im_der[1001][1001];
ll derangement(ll c, ll n) {
	if (n > c) return 0;
	if (im_der[c][n] > -1) return im_der[c][n];
	if (n == 0) return im_der[c][0] = 1;
	if (n == 1) return im_der[c][1] = c-1;
	if (n == 2) return im_der[c][2] = (c-1 + ((c-2)*(c-2)) % mod) % mod;
	return im_der[c][n] = (((c-n)*derangement(c-1,n-1)) % mod + ((n-1)*(derangement(c-2,n-2) % mod + derangement(c-1,n-1) % mod)) % mod) % mod;
}

int main() {
	memset(im_memo, -1, sizeof im_memo);
	memset(im_der, -1, sizeof im_der);
	memset(f_memo, -1, sizeof f_memo);
	memset(fi_memo, -1, sizeof fi_memo);
	
	cin>>r>>c>>x>>y;
	ll h = 0;
	for (int i = 0; i <= min(x,y); i++) {
		ll tmp1 = combination(r, i, x-i, y-i) % mod;
		ll tmp2 = (permutation(c - i, y - i) * permutation(c - i, x - i)) % mod;
		ll tmp3 = (permutation(c,i) * derangement(c,i)) % mod;
		//cout<<i<<" -> "<<tmp1<<" "<<tmp2<<" "<<tmp3<<endl;
		h = (h + (((tmp1 * tmp2) % mod) * tmp3) % mod) % mod;
	}
	
	cout<<((h % mod) + mod) % mod<<endl;
	
	return 0;
}
