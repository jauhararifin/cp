#include <bits/stdc++.h>

using namespace std;

int n,a1,a2,a3,a4,dp[4][1000][4096];
string f[4];

inline bool get_bit(int bitmask, int pos) {
    return (bitmask >> pos) & 1;
}

inline int us_bit_2(int bitmask) {
    return bitmask & ~25;
}
inline int us_bit_3(int bitmask) {
    return bitmask & ~955;
}

int main() {
    ios::sync_with_stdio(0);
    cin>>n>>a1>>a2>>a3>>a4>>f[0]>>f[1]>>f[2]>>f[3];

    memset(dp, 0, sizeof dp);
    for (int j = 0; j < n; j++) {
        for (int bit = 0; bit < 4096; bit++)
            dp[0][j][bit] = (f[0][j] == '*' && get_bit(bit,0) ? a1 : 0) + (j > 0 ? dp[3][j-1][bit>>1|2048] : 0);

        for (int bit = 0; bit < 4096; bit++) {
            dp[1][j][bit] = (f[1][j] == '*' && get_bit(bit,0) ? a1 : 0) + dp[0][j][bit>>1|2048];
            if (j > 0)
                dp[1][j][bit] = min(dp[1][j][bit], dp[0][j][us_bit_2(bit>>1|2048)] + a2);
        }

        for (int bit = 0; bit < 4096; bit++) {
            dp[2][j][bit] = (f[2][j] == '*' && get_bit(bit,0) ? a1 : 0) + dp[1][j][bit>>1|2048];
            if (j > 0)
                dp[2][j][bit] = min(dp[2][j][bit], dp[1][j][us_bit_2(bit>>1|2048)] + a2);
            if (j > 1)
                dp[2][j][bit] = min(dp[2][j][bit], dp[1][j][us_bit_3(bit>>1|2048)] + a3);
        }

        for (int bit = 0; bit < 4096; bit++) {
            dp[3][j][bit] = (f[3][j] == '*' && get_bit(bit,0) ? a1 : 0) + dp[2][j][bit>>1|2048];
            if (j > 0)
                dp[3][j][bit] = min(dp[3][j][bit], dp[2][j][us_bit_2(bit>>1|2048)] + a2);
            if (j > 1)
                dp[3][j][bit] = min(dp[3][j][bit], dp[2][j][us_bit_3(bit>>1|2048)] + a3);
            if (j > 2)
                dp[3][j][bit] = min(dp[3][j][bit], dp[3][j-1][0] + a4);
        }
    }

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < n; j++)
    //         printf("%2d,%2d  ", dp[i][j][4095>>1], dp[i][j][4095]);
    //     printf("\n");
    // }

    cout<<dp[3][n-1][4095]<<endl;

    return 0;
}