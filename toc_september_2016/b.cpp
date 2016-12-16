#include <bits/stdc++.h>

#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define vi vector<int>

using namespace std;

int n,x,y,z,p[50000],v[50001],q,part,qn;
ll ans[50000];
pii range[50000];
pair<int,pii> query[50000];
pair<pii,pii> update[50000];
vi adj[50001];

void generate_list(vi *adj, int* arr, pii *range) {
	stack<pii> st; st.push(pii(1,0));
	int i = 0;
	while (!st.empty()) {
		pii t = st.top(); st.pop();
		if (t.se)
			range[t.fi].se = i-1;
		else {
			range[t.fi].fi = i;
			arr[i++] = v[t.fi];
			st.push(pii(t.fi,1));
			for (int j = 0; j < (int) adj[t.fi].size(); j++)
				st.push(pii(adj[t.fi][j],0));
		}
	}
}

bool cmp(pair<int,pii> a, pair<int,pii> b) { return a.fi/part == b.fi/part ? (a.se.fi/part == b.se.fi/part ? a.se.se < b.se.se : a.se.fi < b.se.fi) : a.fi < b.fi; }

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
		scanf("%d",&x), adj[x].push_back(i); 
	for (int i = 1; i <= n; i++)
		scanf("%d", v+i);
	generate_list(adj, p, range);
	
	for (part = 1; part*part < n; part++);
	memcpy(v, p, sizeof p);
	memset(update, -1, sizeof update);
	scanf("%d", &q);
	qn = 0;
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &x, &y);
		if (x) {
			scanf("%d", &z);
			if (v[range[y].fi] != z) {
				update[i] = make_pair(pii(i,range[y].fi),pii(v[range[y].fi],z));
				v[range[y].fi] = z;
			}
		} else
			query[qn++] = make_pair(i, range[y]);
	}
	sort(query, query + qn, cmp);
	
	ll h = 0;
	pair<int,pii> last = make_pair(-1, pii(-1,-1));
	memset(v, 0, sizeof v);
	for (int i = 0; i < qn; i++) {
		while (last.fi < query[i].fi) {
			last.fi++;
			if (update[last.fi].fi.fi == -1) continue;
			if (update[last.fi].fi.se <= last.se.se && update[last.fi].fi.se >= last.se.fi) {
				h += 2*(v[update[last.fi].se.se] - v[update[last.fi].se.fi] + 1);
				v[update[last.fi].se.se]++;
				v[update[last.fi].se.fi]--;
			}
			p[update[last.fi].fi.se] = update[last.fi].se.se;
		}
		while (last.fi > query[i].fi) {
			last.fi--;
			if (update[last.fi].fi.fi == -1) continue;
			if (update[last.fi].fi.se <= last.se.se && update[last.fi].fi.se >= last.se.fi) {
				h += 2*(-v[update[last.fi].se.se] + v[update[last.fi].se.fi] + 1);
				v[update[last.fi].se.se]--;
				v[update[last.fi].se.fi]++;
			}
			p[update[last.fi].fi.se] = update[last.fi].se.fi;
		}
		
		while (last.se.se < query[i].se.se) last.se.se++, h += 2*(v[p[last.se.se]]++) + 1;
		while (last.se.se > query[i].se.se) h += -2*(v[p[last.se.se]]--) + 1, last.se.se--;
		while (last.se.fi > query[i].se.fi) last.se.fi--, h += 2*(v[p[last.se.fi]]++) + 1;
		while (last.se.fi < query[i].se.fi) h += last.se.fi >= 0 ? -2*(v[p[last.se.fi]]--) + 1 : 0, last.se.fi++;
		ans[query[i].fi] = h;
	}
	
	sort(query, query + qn);
	for (int i = 0; i < qn; i++)
		printf("%lld\n", ans[query[i].fi]);
		
	return 0;
}
