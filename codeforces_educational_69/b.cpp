#include <bits/stdc++.h>

using namespace std;

int n;
pair<int,int> a[300000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a, a + n);
    reverse(a, a + n);

    int lo = a[0].second;
    int hi = a[0].second;
    for (int i = 1; i < n; i++)
        if (a[i].second == lo - 1)
            lo--;
        else if (a[i].second == hi + 1)
            hi++;
        else {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");

    return 0;    
}