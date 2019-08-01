#include <bits/stdc++.h>

using namespace std;

int n,k,a[300000],b[300000];
long long h;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    h = a[n-1] - a[0];
    for (int i = 0; i < n - 1; i++)
        b[i] = a[i] - a[i+1];
    sort(b, b + n - 1);
    for (int i = 0; i < k - 1; i++)
        h += (long long) b[i];
    cout<<h<<endl;
    return 0;    
}