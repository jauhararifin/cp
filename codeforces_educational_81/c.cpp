#include <bits/stdc++.h>

using namespace std;

int T,ns,nt;
char s[100001],t[100001];
vector<int> al[26];

int binser(vector<int>& v, int p) {
	int lo = 0;
	int hi = (int) v.size()-1;
	int ans = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (v[mid] > p) {
			ans = v[mid];
			hi = mid - 1;
		} else
			lo = mid + 1;
	}
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", s);
		scanf("%s", t);
		ns = (int) strlen(s);
		nt = (int) strlen(t);

		for (int i = 0; i < 26; i++) al[i].clear();
		for (int i = 0; i < ns; i++) al[s[i]-'a'].push_back(i);

		int last = -1;
		int h = 1;
		bool impossible = 0;
		for (int i = 0; i < nt; i++) {
			int temp = binser(al[t[i]-'a'], last);
			// printf("finding %c, last=%d, got=%d\n", t[i], last, temp);
			if (last == -1 && temp == -1) {
				impossible = 1;
				break;
			} else if (temp == -1) {
				h++;
				last = -1;
				i--;
			} else
				last = temp;
		}

		if (impossible) printf("-1\n");
		else printf("%d\n", h);
	}
	return 0;
}
