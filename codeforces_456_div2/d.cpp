#include <bits/stdc++.h>

using namespace std;

long long n,m,r,k;

long long calc(long long row, long long col) {
	long long x = min(col, m - r + 1LL) - max(1LL, col - r + 1LL) + 1LL;
	long long y = min(row, n - r + 1LL) - max(1LL, row - r + 1LL) + 1LL;
	return x*y;
}

int main() {
	scanf("%lld%lld%lld%lld", &n, &m, &r, &k);

	priority_queue<pair<long long,pair<int,int> > > pque;
	int cmid = (m+1)/2;
	int rmid = (n+1)/2;
	pque.push(make_pair(calc(rmid,cmid), make_pair(rmid, cmid)));
	set<pair<int,int> > st;
	double res = 0.0;
	for (int i = 0; i < k; i++) {
		pair<long long,pair<int,int> > t = pque.top(); pque.pop();
		while (t.second.first <= 0 || t.second.second <= 0 || st.find(t.second) != st.end())
			t = pque.top(), pque.pop();
		st.insert(t.second);

		res += t.first;

		int y = t.second.first;
		int x = t.second.second;

		pque.push(make_pair(calc(y-1,x),make_pair(y-1,x)));
		pque.push(make_pair(calc(y+1,x),make_pair(y+1,x)));
		pque.push(make_pair(calc(y,x-1),make_pair(y,x-1)));
		pque.push(make_pair(calc(y,x+1),make_pair(y,x+1)));
	}
	res /= (n - r + 1LL) * (m - r + 1LL);

	printf("%.9lf\n", res);

	return 0;
}