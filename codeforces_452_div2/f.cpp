#include <bits/stdc++.h>

using namespace std;

int n,m,bit[200001];
char s[200001];
map<char,set<int> > mp;

int bit_query(int i) {
	int sum = 0;
	for (; i > 0; i -= i & (-i))
		sum += bit[i];
	return sum;
}

void update_bit(int i, int v) {
	for (; i <= n; i += i & -i)
		bit[i] += v;
}

void debug_map(map<char,set<int> >& m) {
	for (auto i = m.begin(); i != m.end(); i++) {
		printf("%c ->", i->first);
		for (auto j : i->second)
			printf(" %d", j);
		printf("\n");
	}
	printf("BIT:"); for (int i = 1; i <= n; i++) printf(" %d", bit_query(i)); printf("\n");
}

int find_pos(int i) {
	int lo = 1;
	int hi = n;
	int r = i;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int h = bit_query(mid);
		if (h < i)
			lo = mid + 1;
		else {
			hi = mid - 1;
			r = mid;
		}
	}
	return r;
}

int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", s);

	for (int i = 0; i < n; i++)
		mp[s[i]].insert(i + 1);
	for (int i = 1; i <= n; i++)
		update_bit(i, 1);

	// debug_map(mp);
	while (m--) {
		int l,r; char ct[2]; char c;
		scanf("%d%d%s", &l, &r, ct); c = ct[0];
		l = find_pos(l);
		r = find_pos(r);
		// printf("(%d,%d,%c)\n", l, r, c);
		vector<int> deleting;
		for (auto i = mp[c].lower_bound(l); i != mp[c].upper_bound(r); i++)
			deleting.push_back(*i);
		for (auto i : deleting) {
			mp[c].erase(i);
			update_bit(i, -1);
		}
		// printf("=================================\n");
		// debug_map(mp);
	}
	memset(s, 0, sizeof s);
	for (auto i = mp.begin(); i != mp.end(); i++) {
		for (int j : i->second)
			s[j] = i->first;
	}
	for (int i = 0; i <= n; i++)
		if (s[i])
			printf("%c", s[i]);
	printf("\n");

	return 0;
}