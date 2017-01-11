#include <bits/stdc++.h>

const int inf = 2000000000;

using namespace std;

int n,q,r,x,y,z,memo[100][100];

int main(void) {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			memo[i][j] = inf;
	
	scanf("%d%d%d", &n ,&q, &r);
	while (q--) {
		scanf("%d%d%d", &x, &y, &z);
		memo[x][y] = memo[y][x] = z;
	}
	
	while (r--) {
		scanf("%d%d", &x, &y);
		
		while (memo[x][y] == inf)
			for (int i = 0; i < n; i++) {
				for (int j = i; j < n; j++)
					if (memo[i][j] < inf)
						for (int k = j + 1; k < n; k++)
							if (memo[j+1][k] < inf)
								memo[i][k] = memo[k][i] = memo[i][j] + memo[j+1][k];
				for (int j = i; j < n; j++)
					if (memo[i][j] < inf)
						for (int k = j; k > i; k--)
							if (memo[k][j] < inf)
								memo[i][k-1] = memo[k-1][i] = memo[i][j] - memo[k][j];
				if (i > 0)
					for (int j = 0; j <= i-1; j++)
						if (memo[i-1][j] < inf)
							for (int k = i; k < n; k++)
								if (memo[j][k] < inf) 
									memo[i][k] = memo[k][i] = memo[j][k] - memo[j][i-1];
			}
		
		printf("%d\n", memo[x][y]);
	}
	
	return 0;
}
