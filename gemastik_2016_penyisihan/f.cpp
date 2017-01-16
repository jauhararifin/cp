#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll memo_comb[53][53];
ll comb(int n, int r) {
	if (n < 0 || r > n || r < 0) return 0LL;
	if (memo_comb[n][r] > -1) return memo_comb[n][r];
	if (n == 1 || n == 0 || r == 0 || r == n) return memo_comb[n][r] = 1;
	return memo_comb[n][r] = comb(n-1,r) + comb(n-1,r-1);
}
ll comb(int n, int r1, int r2) {
	return comb(n,r1)*comb(n-r1,r2);
}
ll power(int a, int b) {
	if (b <= 1) return b < 1 ? 1 : a;
	ll c = power(a, b/2);
	return b % 2 ? c*c*a : c*c;
}
int to_int(string s) {
	int h = 0;
	if (s[0] >= '2' && s[0] <= '9') h = s[0]-'2';
	else if (s[0] == 'T') h = 8;
	else if (s[0] == 'J') h = 9;
	else if (s[0] == 'Q') h = 10;
	else if (s[0] == 'K') h = 11;
	else if (s[0] == 'A') h = 12;
	
	if (s[1] == 'H') h += 13;
	else if (s[1] == 'C') h += 26;
	else if (s[1] == 'S') h += 39;
	
	return h;
}
bool win(int a, int b) { return a/13 != b/13 || a > b; }

int t,p[13];
char ps[13][3];
bool used[52],first;

int main() {
	memset(memo_comb, -1, sizeof memo_comb);
	first = 1;
	
	scanf("%d", &t);
	while (t--) {
		memset(used, 0, sizeof used);
		
		for (int i = 0; i < 13; i++) {
			scanf("%s", ps[i]);
			p[i] = to_int(ps[i]);
			used[p[i]] = 1;
		}
		
		if (!first) { printf("\n"); } first = 0;
		for (int i = 0; i < 13; i++) {			
			int q = 0;
			int n = 0;
			vector<int> v; for (int j = p[i]-p[i]%13; j < p[i]-p[i]%13+13; j++)
				if (!used[j]) {
					n++;
					if (win(p[i],j))
						q++;
				}
			int m = 39 - n;
			
			ll h = 0, all = comb(39,13,13);
			for (int a = 0; a <= q; a++)
				for (int b = 0; b <= q; b++)
					if (a+b <= q) {
						int c = q-a-b;
						ll tmp = comb(q,a,b);
						
						int kosong = (a ? 0 : 1) + (b ? 0 : 1) + (c ? 0 : 1);
						if (kosong == 0)
							tmp *= comb(39-q,13-a,13-b);
						else if (kosong == 1)
							tmp *= comb(m,13) * comb(13-a+13-b-c,13-(a ? a : b));
						else if (kosong == 2)
							tmp *= comb(m,13,13);
						
						h += tmp;
					}
			printf("%s: %.6lf%%\n", ps[i], 100.0*h/all);
		}
	}
	return 0;
}
