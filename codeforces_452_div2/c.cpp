#include <bits/stdc++.h>

using namespace std;

int n;

vector<int> four(int start, int end) {
    vector<int> ans;
    while (start < end) {
        ans.push_back(start++); start++;
        ans.push_back(end--); end--; 
    }
    return ans;
}

int main() {
    scanf("%d", &n);

    vector<int> answer;
    if (n % 4 == 0) answer = four(1, n);
    else if (n % 4 == 1) answer = four(2, n);
    else if (n % 4 == 2) { answer = four(3,n); answer.push_back(1); }
    else { answer = four(4, n); if (n >= 3) answer.push_back(3); }
    
    printf("%d\n", n % 4 == 0 || n % 4 == 3 ? 0 : 1);
    printf("%d", (int) answer.size());
    for (int i = 0; i < (int) answer.size(); i++)
        printf(" %d", answer[i]);
    printf("\n");

    return 0;
}