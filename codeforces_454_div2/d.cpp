#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<int> v[100000];

void print_ans() {
	printf("YES\n");
	for (int i = 0; i < n; i++) {
		printf("%d", v[i][0] + 1);
		for (int j = 1; j < m; j++)
			printf(" %d", v[i][j] + 1);
		printf("\n");
	}
}

int main() {
	scanf("%d%d", &n, &m);

	if (n == 1 && m > 3) {
		for (int j = 1; j < m; j += 2)
			v[0].push_back(j);
		for (int j = 0; j < m; j += 2)
			v[0].push_back(j);
		print_ans();
	} else if (m == 1 && n > 3) {
		for (int j = 1; j < n; j += 2)
			v[j/2].push_back(j);
		for (int j = 0; j < n; j += 2)
			v[j/2 + n/2].push_back(j);
		print_ans();
	} else if (n == 2 && m >= 4) {
		for (int i = 0; i < m; i++) {
			v[0].push_back((m-2+i) % m);
			v[1].push_back(m + i);
			if (i % 2 == 0)
				swap(v[0][i], v[1][i]);
		}
		print_ans();
	} else if (m == 2 && n >= 4) {
		for (int i = 0; i < n; i++) {
			v[i].push_back(2*((n-2+i) % n));
			v[i].push_back(2*i+1);
			if (i % 2 == 0)
				swap(v[i][0], v[i][1]);
		}
		print_ans();
	} else if (n == 3 && m >= 4) {
		for (int i = 0; i < m; i++) {
			v[0].push_back((m-2+i) % m);
			v[1].push_back(m + i);
			v[2].push_back(2*m + (m-2+i) % m);
			if (i % 2 == 0)
				swap(v[0][i], v[1][i]);
			else
				swap(v[1][i], v[2][i]);
		}
		print_ans();
	} else if (m == 3 && n >= 4) {
		for (int i = 0; i < n; i++) {
			v[i].push_back(3*((n-2+i) % n));
			v[i].push_back(3*i+1);
			v[i].push_back(3*((n-2+i) % n) + 2);
			if (i % 2 == 0)
				swap(v[i][0], v[i][1]);
			else
				swap(v[i][1], v[i][2]);
		}
		print_ans();
	} else if (n > 3 && m > 3) {
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < m; j += 2)
				v[i/2 + (i & 1 ? 0 : n/2)].push_back(m * i + j);
			for (int j = 0; j < m; j += 2)
				v[i/2 + (i & 1 ? 0 : n/2)].push_back(m * i + j);
		}
		print_ans();
	} else {
		vector<int> test_v; for (int i = 0; i < n*m; i++) test_v.push_back(i);
		do {
			bool b = 1;
			for (int i = 0; i < n*m && b; i++) {
				int row = i / m;
				int col = i % m;
				int x[4] = {0,0,1,-1};
				int y[4] = {1,-1,0,0};

				vector<int> side;
				for (int r = 0; r < 4; r++) {
					int row = test_v[i]/m;
					int col = test_v[i]%m;
					if (row + y[r] >= 0 && row + y[r] < n && col + x[r] >= 0 && col + x[r] < m)
						side.push_back((row + y[r])*m + col + x[r]);
				}
				// printf("%d %d side %d:", row, col, i); for (int x : side) printf(" %d", x); printf("\n");
				for (int r = 0; r < 4; r++) {
					// if (row + y[r] >= 0 && row + y[r] < n && col + x[r] >= 0 && col + x[r] < m)
					// 	printf("%d %d -> %d %d\n", row + y[r], col + x[r], (row + y[r])*m + col + x[r], test_v[(row + y[r])*m + col + x[r]]);
					if (row + y[r] >= 0 && row + y[r] < n && col + x[r] >= 0 && col + x[r] < m && find(side.begin(), side.end(), test_v[(row + y[r])*m + col + x[r]]) != side.end())
						b = 0;
				}
			}
			if (b) {
				for (int i = 0; i < n; i++)
					for (int j = 0; j < m; j++)
						v[i].push_back(test_v[i*m+j]);
				print_ans();
				return 0;
			}
		} while (next_permutation(test_v.begin(), test_v.end()));
		printf("NO\n");
	}

	return 0;
}