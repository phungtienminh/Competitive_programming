#include <bits/stdc++.h>

using namespace std;

const int N = 40;
const int mod = 1000000;

int dp[2][N][N][N][4][4], a, b, c, d;
bool ok[4][4][4];

void reset (int i){
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            for (int l = 0; l < N; l++) {
                for (int m = 0; m < 4; m++) {
                    for (int n = 0; n < 4; n++) {
                        dp[i % 2][j][k][l][m][n] = 0;
                    }
                }
            }
        }
    }
}

int main(){
    scanf("%d %d %d %d", &a, &b, &c, &d);

    memset(ok, true, sizeof(ok));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if ((i / 2 == j / 2 && j / 2 == k / 2) || (i % 2 == j % 2 && j % 2 == k % 2)) ok[i][j][k] = false;
            }
        }
    }

    for (int i = 0; i <= a; i++) {
        reset(i);
        for (int j = 0; j <= b; j++) {
            for (int k = 0; k <= c; k++) {
                for (int l = 0; l <= d; l++) {
                    for (int m = 0; m < 4; m++) {
                        for (int n = 0; n < 4; n++) {
                            if (i + j + k + l == 0) dp[i % 2][j][k][l][m][n] = 1;
                            if (i && ok[0][m][n]) dp[i % 2][j][k][l][m][n] += dp[(i - 1) % 2][j][k][l][n][0];
                            if (j && ok[1][m][n]) dp[i % 2][j][k][l][m][n] += dp[i % 2][j - 1][k][l][n][1];
                            if (k && ok[2][m][n]) dp[i % 2][j][k][l][m][n] += dp[i % 2][j][k - 1][l][n][2];
                            if (l && ok[3][m][n]) dp[i % 2][j][k][l][m][n] += dp[i % 2][j][k][l - 1][n][3];

                            dp[i % 2][j][k][l][m][n] %= mod;
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 4; i++) {
        ans = (ans + dp[a % 2][b][c][d][i][i]) % mod;
    }

    printf("%d", ans);
    return 0;
}
