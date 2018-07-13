#include <bits/stdc++.h>

#define double long double

using namespace std;

const int N = 105;

double dp[N][N][10];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int d, n, m, len;
    cin >> d >> n >> m >> len;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 10; k++) {
                dp[i][j][k] = 0.0;
            }
        }
    }

    dp[0][0][0] = 1.0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < d; k++) {
                if (dp[i][j][k] > 0) {
                    for (int l = 0; l < d; l++) {
                        dp[i + 1][(l == k) ? j + 1 : 1][l] += dp[i][j][k];
                    }
                }
            }
        }
    }

    double ways = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < len; j++) {
            ways += dp[m][j][i];
        }
    }

    double ans = n / m * log10(ways) / log10(2.0);

    cout << fixed << setprecision(0) << floor(ans + 1e-15);
    return 0;
}
