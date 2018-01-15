#include <bits/stdc++.h>

using namespace std;

int n,a[200000];
bool vis[200000];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);

	map<int,int> segments;
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (last < 0 || a[i] != a[last]) {
			segments[i] = 0;
			last = i;
		}
		segments[last]++;
	}

	// printf("SEG:"); for (auto i = segments.begin(); i != segments.end(); i++)
	// 	printf(" (%d,%d)", i->first, i->second); printf("\n");

	priority_queue<pair<int,int> > pque;
	for (auto i = segments.begin(); i != segments.end(); i++)
		pque.push(make_pair(i->second, -i->first));

	int h = 0;
	memset(vis, 0, sizeof vis);
	while (!pque.empty()) {
		pair<int,int> t = pque.top(); pque.pop(); t.second *= -1;
		// printf("size:%d, idx:%d\n", t.first, t.second);
		if (t.second < 0 || t.second >= n)
			continue;
		if (!vis[t.second])
			vis[t.second] = 1;
		else
			continue;
		
		int idx = 2000000000;
		int num = -1;
		int sz = 0;
		bool has_left = 0;
		bool has_right = 0;
		int idx_right = -1;
		auto it = segments.find(t.second);
		if (it != segments.begin()) {
			it--;
			idx = it->first;
			num = a[idx];
			sz = it->second;
			it++;
			has_left = 1;
		}
		if (++it != segments.end() && a[it->first] == num) {
			idx = min(idx, it->first);
			idx_right = it->first;
			sz += it->second;
			has_right = 1;
		}
		it--;

		if (has_left && has_right) {
			segments[idx] = sz;
			segments.erase(++it);
			vis[idx_right] = 1;
		}
		segments.erase(t.second);
		pque.push(make_pair(sz, -idx));
		h++;
	}
	printf("%d\n", h);

	return 0;
}