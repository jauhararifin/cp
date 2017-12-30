#include <bits/stdc++.h>

using namespace std;

int n,m,_x1,_y1,_x2,_y2;

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &_y1, &_x1, &_y2, &_x2);
    if (_x1 == _x2 && _y1 == _y2)
        printf("0\n");
    else if (_x1 == _x2)
        printf("%d\n", _y1 < _y2 ? 1 + n - _y1 : 1 + _y1 - 1);
    else if (_y1 == _y2)
        printf("%d\n", _x1 < _x2 ? 1 + m - _x1 : 1 + _x1 - 1);
    else if (_x1 < _x2 && _y1 < _y2) // right bottom
        printf("%d\n", 1 + max(m - _x1, n - _y1));
    else if (_x1 < _x2 && _y1 > _y2) // right top
        printf("%d\n", 1 + max(m - _x1, _y1 - 1));
    else if (_x1 > _x2 && _y1 < _y2) // left bottom
        printf("%d\n", 1 + max(_x1 - 1, n - _y1));
    else if (_x1 > _x2 && _y1 > _y2) // left top
        printf("%d\n", 1 + max(_x1 - 1, _y1 - 1));

    return 0;
}