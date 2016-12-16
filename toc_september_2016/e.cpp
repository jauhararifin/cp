#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

int n,m;
pii start,finish,p[400][400];
bool memo[400][400][801];

int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &start.fi, &start.se, &finish.fi, &finish.se);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &p[i][j].fi);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &p[i][j].se);
	for (int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for (int k = p[i][j].fi; k <= p[i][j].se; k++)
				memo[i][j][k] = 0;
	queue<pair<pii,pii> > que;
	int h = -1;
	for (int i = p[start.fi][start.se].fi; i <= p[start.fi][start.se].se; i++)
		que.push(make_pair(start,pii(i,0)));
	while (!que.empty()) {
		pair<pii,pii> t = que.front(); que.pop();
		
		if (!memo[t.fi.fi][t.fi.se][t.se.fi]) {
			//printf("%d %d %d %d\n", t.fi.fi, t.fi.se, t.se.fi, t.se.se);			
			memo[t.fi.fi][t.fi.se][t.se.fi] = 1;
			if (t.fi == finish) {
				h = t.se.se;
				break;
			}
			
			if (t.fi.se-1 >= 0 && t.fi.se-1 < m && t.se.fi-1 >= p[t.fi.fi][t.fi.se-1].fi && t.se.fi-1 <= p[t.fi.fi][t.fi.se-1].se && !memo[t.fi.fi][t.fi.se-1][t.se.fi-1])
				que.push(make_pair(pii(t.fi.fi,t.fi.se-1),pii(t.se.fi-1,t.se.se+1)));
			if (t.fi.fi-1 >= 0 && t.fi.fi-1 < n && t.se.fi-1 >= p[t.fi.fi-1][t.fi.se].fi && t.se.fi-1 <= p[t.fi.fi-1][t.fi.se].se && !memo[t.fi.fi-1][t.fi.se][t.se.fi-1])
				que.push(make_pair(pii(t.fi.fi-1,t.fi.se),pii(t.se.fi-1,t.se.se+1)));
			if (t.fi.fi+1 >= 0 && t.fi.fi+1 < n && t.se.fi-1 >= p[t.fi.fi+1][t.fi.se].fi && t.se.fi-1 <= p[t.fi.fi+1][t.fi.se].se && !memo[t.fi.fi+1][t.fi.se][t.se.fi-1])
				que.push(make_pair(pii(t.fi.fi+1,t.fi.se),pii(t.se.fi-1,t.se.se+1)));
			if (t.fi.se+1 >= 0 && t.fi.se+1 < m && t.se.fi-1 >= p[t.fi.fi][t.fi.se+1].fi && t.se.fi-1 <= p[t.fi.fi][t.fi.se+1].se && !memo[t.fi.fi][t.fi.se+1][t.se.fi-1])
				que.push(make_pair(pii(t.fi.fi,t.fi.se+1),pii(t.se.fi-1,t.se.se+1)));
		}
	}
	printf("%d\n", h);
	return 0;
}
