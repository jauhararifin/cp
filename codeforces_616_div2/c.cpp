#include <bits/stdc++.h>

using namespace std;

int t,n,m,k,a[3500],b[3500];

deque<int> q;
stack<pair<int,int> > s1, s2;
int mmin() {
	if (s1.empty() || s2.empty()) return s1.empty() ? s2.top().second : s1.top().second;
	return min(s1.top().second, s2.top().second);
}

void add(int x) {
	int minimum = s1.empty() ? x : min(x, s1.top().second);
	s1.push({x, minimum});
}

void rem() {
	if (s2.empty()) {
		while (!s1.empty()) {
			int el = s1.top().first;
			s1.pop();
			int minimum = s2.empty() ? el : min(el, s2.top().second);
			s2.push({el, minimum});
		}
	}
	int remove_element = s2.top().first;
	s2.pop();
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < n; i++) scanf("%d", a + i);
		k = min(k, m-1);

		for (int i = 0; i < m; i++)
			b[i] = max(a[i], a[i+n-m]);

		// for (int i = 0; i < m; i++) printf(">> %d\n", b[i]);
		// printf("k=%d\n", k);

		q.clear();
		while (!s1.empty()) s1.pop();
		while (!s2.empty()) s2.pop();
		for (int i = 0; i < m-k; i++) {
			add(b[i]);
		}
		int ans = mmin();
		// printf("-- %d\n", mmin());
		for (int i = m-k; i < m; i++) {
			add(b[i]);
			rem();
			// printf("-- %d\n", mmin());
			ans = max(ans, mmin());
		}
		printf("%d\n", ans);
	}
	return 0;
}
