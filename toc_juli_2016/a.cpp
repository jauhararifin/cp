#include <bits/stdc++.h>

using namespace std;

int n,t,v[100];
double p[100][100];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%lf", &p[i][j]);
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
		scanf("%d", &v[i]), v[i]--;
	int h = 0;
	for (int i = 0; i < n; i++) {
		double tmp = 1;
		for (int j = 0; j < t; j++)
			tmp *= p[i][v[j]];
		if (tmp >= 2)
			h++;
	}
	printf("%d\n", h);
	return 0;
}
