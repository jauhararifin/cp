#include <bits/stdc++.h>

using namespace std;

int a,b,c;

int main() {
    scanf("%d%d%d", &a, &b, &c);
    for (int i = 2; i <= 100; i++) {
        if (i % a != 0 && i % b != 0 && i % c != 0) {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}