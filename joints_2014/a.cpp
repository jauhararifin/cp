#include <bits/stdc++.h>

const int inf = 2000000000;

using namespace std;

int n,k,kata[100],prefsum[100],h,mi,ma,x;
char temp[101];

inline int querysum(int s, int e) { return prefsum[e] - (s > 0 ? prefsum[s-1] : 0) + e - s; }
inline int getbit(int num, int i) { return (num>>i) & 1; }
inline void binaryPrint(int num) { int t = n; while (t--) { cout<<(num&1); num >>= 1; } cout<<endl; }

int main(void) {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%s", temp), kata[i] = (int) strlen(temp);
	prefsum[0] = kata[0];
	for (int i = 1; i < n; i++)
		prefsum[i] = kata[i] + prefsum[i-1];
	
	h = inf;
	for (int bm = 0; bm < (1<<n); bm++)
		if (__builtin_popcount(bm) == k && bm>>(n-1) == 1) {
			mi = inf;
			ma = -inf;
			x = 0;
			for (int i = 0; i < n; i++)
				if (getbit(bm, i)) {
					mi = min(mi, querysum(x,i));
					ma = max(ma, querysum(x,i));
					x = i+1;
				}
			h = min(h, ma-mi);
		}
		
	printf("%d\n", h);
	return 0;
}
