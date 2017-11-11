#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n, k;

ll power(ll a, ll b) {
	if (b == 0) return 1LL;
	else if (b == 1) return a;
	ll temp = power(a, b/2);
	if (temp > 1e6)
		return 1e12 + 1;
	return b & 1 ? temp * temp * a : temp * temp;
}

pair<ll,ll> solve(ll n, ll k) {
	if (n == 1) return make_pair(-1,-1);
	ll sum = 0;
	deque<pair<ll,int>> num;
	for (ll i = 1; power(i,k) <= n; i++) {
		sum += power(i,k);
		if (sum < 0) break;
		if (sum == n) return make_pair(1, i);
		while (sum - num.front().first > n) num.pop_front();
		if (num.front().second < i - 1 && sum - num.front().first == n) return make_pair(num.front().second + 1, i);
		num.push_back(make_pair(sum,i));
	}
	return make_pair(-1,-1);
}

int main() {
	scanf("%lld%lld", &n, &k);
	if (k > 1) {
		pair<ll,ll> ans = solve(n,k);
		if (ans.first == -1)
			printf("-1\n");
		else
			printf("%lld %lld\n", ans.first, ans.second);
	} else {
		ll temp = n;
		ll two = 2;
		while (temp % 2 == 0) {
			temp /= 2;
			two *= 2LL;
		}
		if (temp == 1) // impossible
			printf("-1\n");
		else if (temp == n) // odd
			printf("%lld %lld\n", (temp-1)/2, (temp-1)/2+1);
		else if (n / temp >= temp / 2) // case 1
			printf("%lld %lld\n", max(1LL, n / temp - temp / 2), n / temp + temp / 2);
		else // case 2
			printf("%lld %lld\n", max(1LL, n/two - two/2 + 1), n/two + two/2);
	}
	return 0;
}
