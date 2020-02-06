#include <bits/stdc++.h>

using namespace std;

char s[200001];
int ns,q,sz,ans[100000];
pair<pair<int,int>,int> queries[100000];

bool cmp(pair<pair<int,int>,int>& a, pair<pair<int,int>,int>& b) {
	pair<int,int> ta = {a.first.first / sz, a.first.second};
	pair<int,int> tb = {b.first.first / sz, b.first.second};
	return ta < tb;
}

int main() {
	scanf("%s", s);
	ns = (int) strlen(s);
	for (sz = 0; sz * sz < ns; sz++);

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &queries[i].first.first, &queries[i].first.second);
		queries[i].first.first--;
		queries[i].first.second--;
		queries[i].second = i;
	}

	sort(queries, queries + q, cmp);

	int lo = 0;
	int hi = 0;
	int di = 1;
	unordered_map<int,int> mp;
	mp[s[0]] = 1;
	for (int i = 0; i < q; i++) {
		int tlo = queries[i].first.first;
		int thi = queries[i].first.second;
		int tid = queries[i].second;

		while (hi < thi) {
			hi++;
			mp[s[hi]]++;
			if (mp[s[hi]] == 1) di++;
		}

		while (lo > tlo) {
			lo--;
			mp[s[lo]]++;
			if (mp[s[lo]] == 1) di++;
		}

		while (hi > thi) {
			mp[s[hi]]--;
			if (mp[s[hi]] == 0) di--;
			hi--;
		}

		while (lo < tlo) {
			mp[s[lo]]--;
			if (mp[s[lo]] == 0) di--;
			lo++;
		}

		if (tlo == thi) ans[tid] = 1;
		else if (s[tlo] != s[thi]) ans[tid] = 1;
		else if (di <= 2) ans[tid] = 0;
		else ans[tid] = 1;
	}

	for (int i = 0; i < q; i++)
		if (ans[i]) printf("Yes\n");
		else printf("No\n");

	return 0;
}
