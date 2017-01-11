#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair

struct state { int a,b,c,d,step; };
state make_state(int _a, int _b, int _c, int _d, int _step) { state t; t.a = _a; t.b = _b; t.c = _c; t.d = _d; t.step = _step; return t; }

const int inf = 2000000000;

using namespace std;

int n,r,x,y,memo[46][46];
bool jalan[46][46],visited[46][46][46][46];

int main(void) {
	memset(jalan, 0, sizeof jalan);
	memset(visited, 0, sizeof visited);
	
	scanf("%d%d", &n, &r);
	while (r--) {
		scanf("%d%d", &x, &y);
		jalan[x][y] = 1;
	}
	jalan[0][0] = 1;
	scanf("%d%d", &x, &y);
	
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			memo[i][j] = inf;
	memo[0][0] = 0;
	
	queue<state> que;
	que.push(make_state(0,0,0,0,0));
	while (!que.empty()) {
		state t = que.front();
		que.pop();
		if (t.a < 0 || t.a > n || t.b < 0 || t.b > n || t.c < 0 || t.c > n || t.d < 0 || t.d > n)
			continue;
		if (!jalan[t.c][t.d])
			continue;
		
		memo[t.c][t.d] = min(memo[t.c][t.d], t.step);
		if (visited[t.a][t.b][t.c][t.d])
			continue;
		visited[t.a][t.b][t.c][t.d] = 1;
		
		pii v = mp(t.c - t.a, t.d - t.b);
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				que.push(make_state(t.c, t.d, t.c + v.fi + i, t.d + v.se + j, t.step + 1));
	}
	
	if (memo[x][y] == inf)
		printf("Semar tersesat\n");
	else
		printf("%d\n", memo[x][y]);
	
	return 0;
}
