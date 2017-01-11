#include <bits/stdc++.h>

#define ll long long
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

int n,q,t[100000],last[100001],m[100000];
ll psum[100000];

struct node { int* a; ll* p; node *left,*right; };
node* gen_stree(int l, int r) {
	int* a = (int*) malloc(sizeof(int)*(r-l+1));
	ll* p = (ll*) malloc(sizeof(ll)*(r-l+1));
	node *tmp = (node*) malloc(sizeof(node)); tmp->a = a; tmp->p = p;
	if (l == r) {
		a[0] = m[l];
		p[0] = m[l];
		tmp->left = tmp->right = NULL;
	} else {
		tmp->left = gen_stree(l, (l+r)/2);
		tmp->right = gen_stree((l+r)/2+1, r);
		int i = 0; int j = 0; int k = 0;
		while (i < (l+r)/2-l+1 && j < r-(l+r)/2) a[k++] = tmp->left->a[i] < tmp->right->a[j] ? tmp->left->a[i++] : tmp->right->a[j++];
		while (i < (l+r)/2-l+1) a[k++] = tmp->left->a[i++];
		while (j < r-(l+r)/2) a[k++] = tmp->right->a[j++];
		for (int i = 0; i < k; i++) p[i] = (ll)(i > 0 ? p[i-1] : 0) + (ll)a[i];
	}
	return tmp;
}
ll query(node* root, int left, int right, int l, int r) {
	if (root == NULL || l > r || r < left || l > right) return 0;
	if (l >= left && r <= right) {
		int* a = root->a;
		int x = (int) (upper_bound(a, a + (r-l+1), left-1) - a);
		ll h = (ll) left * (ll) x;
		if (x > 0) h -= root->p[x-1];
		return h;
	}
	return query(root->left, left, right, l, (l+r)/2) + query(root->right, left, right, (l+r)/2+1, r);
}
void debug(node* root, int level, int l, int r) {
	if (!root) return;
	for (int i = 0; i < level; i++) printf("\t");
	for (int i = 0; i < r-l+1; i++) printf("%d ", root->a[i]); printf("\n");
	for (int i = 0; i < level; i++) printf("\t");
	for (int i = 0; i < r-l+1; i++) printf("%lld ", root->p[i]); printf("\n");
	debug(root->left, level+1, l, (l+r)/2);
	debug(root->right, level+1, (l+r)/2+1, r);
}

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++)
		scanf("%d", t+i);
	memset(last, -1, sizeof last);
	m[0] = 0; last[t[0]] = 0;
	for (int i = 1; i < n; i++)
		m[i] = max(m[i-1],last[t[i]]+1), last[t[i]] = i;
		
	for (int i = 0; i < n; i++)
		psum[i] = (ll)(i > 0 ? psum[i-1] : 0) + (ll)i-(ll)m[i]+1LL;
	node* root = gen_stree(0, n-1);
	
	int l, r;
	while (q--) {
		scanf("%d%d", &l, &r); l--; r--;
		cout<<psum[r] - (l > 0 ? psum[l-1] : 0) - query(root, l, r, 0, n-1)<<endl;
	}
	return 0;
}
