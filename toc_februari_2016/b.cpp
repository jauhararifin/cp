#include <bits/stdc++.h>

#define vi vector<int>
#define vii vector<vi>
#define pii pair<int,int>

using namespace std;

int n,b[9],dm;
pii soal[9];
vii mat;

void debugMat(vii mat) {
	for (int i = 0; i < (int) mat.size(); i++) {
		for (int j = 0; j < (int) mat[i].size(); j++)
			cout<<mat[i][j]<<" ";
		cout<<endl;
	}
}

int det(vii v, int s) {
	if (s == 1)
		return v[0][0];
	else if (s == 2)
		return (v[0][0]*v[1][1])-(v[1][0]*v[0][1]);
	
	int ret = 0;
	for (int i = 0; i < s; i++) {
		vii vt;
		vt.resize(s-1);
		
		for (int j = 1; j < s; j++)
			for (int k = 0; k < s; k++)
				if (k != i)
					vt[j-1].push_back(v[j][k]);
		
		int tmp = v[0][i] * det(vt, s-1);
		if (i % 2 == 0)
			ret += tmp;
		else
			ret -= tmp;
	}
	return ret;
}

vector<double> gauss(vector< vector<double> > A) {
    int n = A.size();

    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n]/A[i][i];
        for (int k=i-1;k>=0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &b[i]);	
		
	mat.resize(n);
	for (int i = 0; i <n; i++)
		mat[i].resize(n+1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++)
			mat[i][(i+j)%n]++;
		mat[i][n] = b[i];
	}
			
	dm = det(mat, n);
	
	if (dm == 0)
		printf("0 1 2 3 4\n");
	else {
		vector<vector<double> > matd(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n+1; j++)
				matd[i].push_back((double) mat[i][j]);
		vector<double> res = gauss(matd);
		
		for (int i = 0; i < n; i++)
			soal[i] = make_pair(res[i], i);
		sort(soal, soal + n);
		for (int i = 0; i < 4; i++)
			printf("%d ", soal[i].second);
		printf("%d\n", soal[4].second);
	}
	
	return 0;
}
