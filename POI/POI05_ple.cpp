#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int dp[N][22][80][2][2];

struct Data {
    int o, n, w;
} a[N];

void minimize (int &x, int y) {
    x = min(x, y);
}

int main(){
    int w1, w2, n;
    scanf("%d %d", &w1, &w2);
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &a[i].o, &a[i].n, &a[i].w);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < w1; j++) {
            for (int k = 0; k < w2; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 2; m++) {
                        if (dp[i][j][k][l][m] < 1e9) {
                            minimize(dp[i + 1][(j + a[i + 1].o < w1 && l == 0) ? j + a[i + 1].o : 0][(k + a[i + 1].n < w2 && m == 0) ? k + a[i + 1].n : 0][l || j + a[i + 1].o >= w1 ? 1 : 0][m || k + a[i + 1].n >= w2 ? 1 : 0], dp[i][j][k][l][m] + a[i + 1].w);
                            minimize(dp[i + 1][j][k][l][m], dp[i][j][k][l][m]);
                        }
                    }
                }
            }
        }
    }
    //cout << dp[1][0][5][1][0] << "\n";
    printf("%d", dp[n][0][0][1][1]);
    return 0;
}
