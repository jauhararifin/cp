#include <bits/stdc++.h>

using namespace std;

int t;
char s[100001];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int p = 0;
        for (int i = 0; s[i] != 0; i++)
            if (s[i] == '1') p++;
        printf("%s\n", p % 2 ? "WIN" : "LOSE");
    }
    return 0;
}