#include <bits/stdc++.h>

using namespace std;

int a,b,c,babak;

bool check(int x, int step) {
    return x >= step && x <= 2*step;
}

int main() {
    scanf("%d%d%d", &a, &b, &c);
    if (a < b) swap(a,b);
    if (a < c) swap(a,c);
    if (a % 4 != 0) {
        printf("TIDAK\n");
        return 0;
    }
    babak = a / 4;
    if (b >= babak && b <= babak*2 && c >= babak && c <= babak*2 && (b+c) == babak*3)
        printf("YA\n");
    else
        printf("TIDAK\n");
    return 0;
}