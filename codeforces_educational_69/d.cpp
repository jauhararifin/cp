#include <bits/stdc++.h>

using namespace std;

int n;
long long m,a[300000],k,psum[300000],rsum[300000],p[11];

int main() {
    ios::sync_with_stdio(0);
    cin>>n>>m>>k;
    for (int i = 0; i < n; i++) cin>>a[i];

    psum[0] = 0;
    for (int i = 1; i < n; i++)
        psum[i] = psum[i-1] + a[i-1];
    for (int i = 0; i < n; i++)
        psum[i] = -psum[i];

    rsum[0] = a[0];
    for (int i = 1; i < n; i++)
        rsum[i] = rsum[i-1] + a[i];

    long long h = 0;
    for (int i = 0; i < m; i++)
        p[i] = -1000000000000000LL;
    for (int i = 0; i < n; i++) {
        if (psum[i] > p[i % m])
            p[i % m] = psum[i] - k;
        else
            p[i % m] -= k;
        for (int j = 0; j < m; j++)
            h = max(h, rsum[i] + p[j]);
    }
    cout<<h<<endl;
    
    return 0;
}