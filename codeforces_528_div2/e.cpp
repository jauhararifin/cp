#include <bits/stdc++.h>

using namespace std;

int t,k,n;
char s[1000001],a[1000001],b[1000001];
unordered_map<char,char> p;
bool used[27];

void fill_remaining(int i) {
    int ls = 1;
    for (int j = i+1; j < n; j++) {
        if (p[s[j]] > 0)
            s[j] = p[s[j]];
        else {
            while (used[ls]) ls++;
            used[ls] = 1;
            p[s[j]] = ls;
            s[j] = ls; 
        }
    }
}

bool s_lowerbound(int i) {
    if (i >= n)
        return 1;
    
    if (p[s[i]] > 0) {
        if (p[s[i]] < a[i])
            return 0;
        else if (p[s[i]] == a[i]) {
            bool res = s_lowerbound(i+1);
            if (res) s[i] = p[s[i]];
            return res;
        } else {
            s[i] = p[s[i]];
            fill_remaining(i);
            return 1;
        }
    }

    int sub = a[i];
    for (; sub <= k && used[sub]; sub++);
    if (sub > k) return 0;
    
    char temp = s[i];
    p[s[i]] = sub;
    used[sub] = 1;
    s[i] = sub;
    if (sub > a[i]) {
        fill_remaining(i);
        return 1;
    } else {
        if (!s_lowerbound(i+1)) {
            used[sub] = 0;
            int sub2 = sub+1;
            for (; sub2 <= k && used[sub2]; sub2++);
            if (sub2 <= k) {
                p[temp] = sub2;
                used[sub2] = 1;
                s[i] = sub2;
                fill_remaining(i);
                return 1;
            } else {
                p[temp] = 0;
                s[i] = temp;
                return 0;
            }
        }
        return 1;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%s%s%s", &k, s, a, b);
        n = (int) strlen(s);
        for (int i = 0; i < n; i++)
            s[i] -= ('a'-1), a[i] -= ('a'-1), b[i] -= ('a'-1);

        p.clear();
        memset(used, 0, sizeof used);
        if (!s_lowerbound(0)) {
            printf("NO\n");
            continue;
        }

        int j = 1;
        for (int i = 1; i <= k; i++)
            if (p[i] == 0) {
                while (used[j]) j++;
                p[i] = j;
                used[j] = 1;
            }

        if (strcmp(s, b) <= 0) {
            printf("YES\n");
            for (int i = 1; i <= k; i++)
                printf("%c", p[i]-1+'a');
            printf("\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}