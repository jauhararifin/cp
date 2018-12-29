#include <bits/stdc++.h>

using namespace std;

char s[256];

int main() {
    scanf("%s", s);
    int n = (int) strlen(s);
    for (int i = 0; i < n; i++)
        printf("%c", s[(n-1)/2+((i+1)/2)*(i&1?1:-1)]);
    printf("\n");
    return 0;
}