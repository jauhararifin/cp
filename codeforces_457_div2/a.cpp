#include <bits/stdc++.h>

using namespace std;

int x,hh,mm;

int main() {
    scanf("%d%d%d", &x, &hh, &mm);
    int h = 0;
    while (hh % 10 != 7 && hh/10 != 7 && mm % 10 != 7 && mm / 10 != 7) {
        int t = hh*60 + mm; t -= x; t = ((t % 1440) + 1440) % 1440;
        hh = t / 60;
        mm = t % 60;
        h++;
    }
    printf("%d\n", h);
    return 0;
}