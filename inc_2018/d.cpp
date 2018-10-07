#include <bits/stdc++.h>

using namespace std;

char s[100001],p[100001];
int ns[256],np[256];

int main() {
    memset(ns, 0, sizeof ns);
    memset(np, 0, sizeof np);
    scanf("%s%s", s, p);
    char *pp = p;
    char *ps = s;
    while (*ps != 0)
        ns[*(ps++)]++;
    while (*pp != 0)
        np[*(pp++)]++;

    for (int i = 0; i < 256; i++)
        if (np[i] > ns[i]) {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");

    return 0;
}