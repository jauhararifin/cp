#include <bits/stdc++.h>

using namespace std;

bool b[100];
double check(int n) {
    vector<int> p; for (int i = 0; i < n; i++) p.push_back(i);
    int sum = 0;
    int x = 0;
    do {
        memset(b, 0, sizeof b);
        int m = 0;
        for (int i : p) {
            if (i == 0 || !b[i-1])
                m++;
            b[i] = 1;
        }
        sum += m;
        x++;
    } while(next_permutation(p.begin(), p.end()));
    return (double) sum / (double) x;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%.2lf\n", 0.5*(n+1));
    return 0;
}