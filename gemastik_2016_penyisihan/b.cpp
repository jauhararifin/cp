#include <bits/stdc++.h>

#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

int t,n;
pii p[50001],q[50000];
char tmp1[9],tmp2[9];
vector<int> satu;

int to_int(char* s) {
	int h = 3600 * ((int) (s[0]-'0') * 10 + (int) (s[1]-'0'));
	h += 60 * ((int) (s[3]-'0') * 10 + (int) (s[4]-'0'));
	h += (int) (s[6]-'0') * 10 + (int) (s[7]-'0');
	return h;
}

typedef struct _node {
	int lo,hi;
	vector<int> v;
	_node *l,*r;
} node;
void destroy(node* r) {
	if (r != NULL) {
		destroy(r->l); destroy(r->r);
		delete(r);
	}
}
node* init_rtree(int l, int r) {
	if (l > r) return NULL;
	
	node* tmp = new node;
	tmp->l = tmp->r = NULL;
	tmp->hi = tmp->lo = 0;
	if (l == r) {
		tmp->v.push_back(p[l].se);
		tmp->lo = tmp->hi = p[l].fi;
	} else {
		node *ll = init_rtree(l, (l+r)/2);
		node *rr = init_rtree((l+r)/2+1,r);
		tmp->lo = ll->lo;
		tmp->hi = rr->hi;
		tmp->l = ll; tmp->r = rr; 
		int i = 0; int j = 0;
		while (i < (int)ll->v.size() && j < (int) rr->v.size())
			if (ll->v[i] < rr->v[j]) tmp->v.push_back(ll->v[i++]);
			else tmp->v.push_back(rr->v[j++]);
		while (i < (int)ll->v.size()) tmp->v.push_back(ll->v[i++]);
		while (j < (int)rr->v.size()) tmp->v.push_back(rr->v[j++]);
	}
	return tmp;
}

int query_xbelow_yabove(node *root, int x, int y) {
	if (root == NULL || x < root->lo) return 0;
	else if (x < root->hi) return query_xbelow_yabove(root->l, x, y) + query_xbelow_yabove(root->r, x, y);
	else return (int) (root->v.end() - lower_bound(root->v.begin(), root->v.end(), y));
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s %s", tmp1, tmp2);
			q[i] = pii(to_int(tmp1), to_int(tmp2)-1);
		}
		memcpy(p, q, sizeof q);
		sort(p, p + n);
		
		p[n] = pii(1000000,1000000);
		satu.clear();
		int lo = p[0].fi;
		int hi = p[0].se;
		for (int i = 0; i < n; i++) {
			for (int j = lo; j < p[i+1].fi && j <= hi; j++) satu.push_back(j);
			
			if (p[i+1].fi > hi) lo = p[i+1].fi, hi = p[i+1].se;
			else if (p[i+1].fi >= lo && p[i+1].se > hi) lo = hi+1, hi = p[i+1].se;
			else if (p[i+1].fi >= lo && p[i+1].se <= hi) lo = p[i+1].se+1;
			
			else if (p[i+1].fi < lo && p[i+1].se < lo);
			else if (p[i+1].fi < lo && p[i+1].se <= hi) lo = p[i+1].se+1;
			else if (p[i+1].fi < lo && p[i+1].se > hi) lo = hi+1, hi = p[i+1].se;
		}
		
		node *rtree = init_rtree(0, n-1);
		
		for (int i = 0; i < n; i++)
			if (lower_bound(satu.begin(), satu.end(), q[i].fi) < upper_bound(satu.begin(), satu.end(), q[i].se))
				printf("1\n");
			else {
				int tmp = query_xbelow_yabove(rtree, q[i].fi, q[i].se);
				if (tmp > 1)
					printf("-1\n");
				else
					printf("2\n");
			}
		
		destroy(rtree);
	}
	return 0;
}
