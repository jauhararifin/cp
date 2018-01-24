#include <bits/stdc++.h>
    
using namespace std;
    
int n,k;
    
int s[2001][2001];
void add(int x1, int y1, int x2, int y2) {
    s[y1][x1]++;
    s[y1][x2]--;
    s[y2][x1]--;
    s[y2][x2]++;
}
    
int find() {
    int m = -1;
    for (int i = 0; i < 2*k; i++)
        for (int j = 0; j < 2*k; j++) {
            int top = i > 0 ? s[i-1][j] : 0;
            int bot = j > 0 ? s[i][j-1] : 0;
            int dia = i > 0 && j > 0 ? s[i-1][j-1] : 0;
            m = max(m, s[i][j] = s[i][j] + top + bot - dia);
        }
    return m;
}
    
int main() {
    ios::sync_with_stdio(0);
    cin>>n>>k;
    while (n--) {
        int x,y; string c; cin>>x>>y>>c;
    
        x %= 2*k; y %= 2*k;
        if ((c == "W" && ((x < k && y < k) || (x >= k && y>= k))) || (c == "B" && ((x >= k && y < k) || (x < k && y >= k)))) {
            x %= k, y %= k;
            add(0,0,k-x,k-y);
            add(2*k-x,0,2*k,k-y);
            add(k-x,k-y,2*k-x,2*k-y);
            add(0,2*k-y,k-x,2*k);
            add(2*k-x,2*k-y,2*k,2*k);
        } else {
            x %= k, y %= k;
            add(0,k-y,k-x,2*k-y);
            add(k-x,0,2*k-x,k-y);
            add(k-x,2*k-y,2*k-x,2*k);
            add(2*k-x,k-y,2*k,2*k-y);
        }
    }
    cout<<find()<<endl;
    
    return 0;
}