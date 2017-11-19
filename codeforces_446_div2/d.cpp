#include <bits/stdc++.h>

using namespace std;

int n,a[22];

int main() {
    scanf("%d", &n);
    vector<int> p;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        p.push_back(a[i]);
    }
    sort(p.begin(), p.end());
    unordered_map<int,int> nmap,imap;
    for (int i = 0; i < n; i++)
        nmap[p[i]] = i, imap[i] = p[i];
    
    printf("%d", imap[(nmap[a[0]] + 1) % n]);
    for (int i = 1; i < n; i++)
        printf(" %d", imap[(nmap[a[i]] + 1) % n]);
    printf("\n");
    return 0;
}