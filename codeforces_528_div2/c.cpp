#include <bits/stdc++.h>

using namespace std;

int ax,ay,bx,by,cx,cy;
vector<int> rx,ry;

int main() {
    scanf("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &cx, &cy);
    rx.push_back(ax);
    ry.push_back(ay);
    while (1) {
        if (ax < bx && ax < cx)
            ax++;
        else if (ax > bx && ax > cx)
            ax--;
        else if (ay < by && ay < cy)
            ay++;
        else if (ay > by && ay > cy)
            ay--;
        else
            break;
        rx.push_back(ax);
        ry.push_back(ay);
    }
    int px = ax, py = ay;
    while (px < bx) px++, rx.push_back(px), ry.push_back(py);
    while (px > bx) px--, rx.push_back(px), ry.push_back(py);
    while (py < by) py++, rx.push_back(px), ry.push_back(py);
    while (py > by) py--, rx.push_back(px), ry.push_back(py);
    px = ax; py = ay;
    while (px < cx) px++, rx.push_back(px), ry.push_back(py);
    while (px > cx) px--, rx.push_back(px), ry.push_back(py);
    while (py < cy) py++, rx.push_back(px), ry.push_back(py);
    while (py > cy) py--, rx.push_back(px), ry.push_back(py);
    
    printf("%d\n", (int) rx.size());
    for (int i = 0; i < (int) rx.size(); i++)
        printf("%d %d\n", rx[i], ry[i]);
    
    return 0;
}