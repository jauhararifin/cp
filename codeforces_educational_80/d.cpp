#include <bits/stdc++.h>

using namespace std;

int n,m,a[300000][8],bms[300000],st[256];

bool test(int x, pair<int,int> &ret) {
	memset(st, -1, sizeof st);
	for (int i = 0; i < n; i++) {
		int bm = 0;
		for (int j = 0; j < m; j++)
			if (a[i][j] >= x) bm |= 1<<j;
		for (int j = 0; j < 1<<m; j++)
			if ((j & bm) == j)
				st[j] = i;
		bms[i] = bm;
	}

	for (int i = 0; i < n; i++) {
		if (__builtin_popcount(bms[i]) == m) {
			ret = make_pair(i, i);
			return 1;
		}
		int req = ~bms[i] & ((1<<m)-1);
		if (st[req] > -1) {
			ret = make_pair(i, st[req]);
			return 1;
		}
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &a[i][j]);

	set<int> s;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			s.insert(a[i][j]);
	vector<int> v;
	for (int x : s)
		v.push_back(x);

	pair<int,int> ans,temp;
	int lo = 0;
	int hi = v.size()-1;
	while (lo <= hi) {
		int mid = (lo+hi)/2;
		int val = v[mid];
		if (test(val, temp)) {
			ans = temp;
			lo = mid + 1;
		} else
			hi = mid - 1;
	}
	printf("%d %d\n", ans.first+1, ans.second+1);
	
	return 0;
}
