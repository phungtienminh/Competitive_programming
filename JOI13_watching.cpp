#include <bits/stdc++.h>

using namespace std;

const int N = 2005;
int dp[N][N], a[N], n, p, q;

int main(){
    scanf("%d %d %d", &n, &p, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    if (p >= n) printf("%d", 1);
    else {

        sort(a + 1, a + n + 1);
        a[0] = -2000000000;

        int l = 1;
        int r = 1000000000;

        while (l <= r) {
            int mid = (l + r)/2;
            memset(dp, 0x3f, sizeof(dp));

            for (int i = 0; i <= n; i++) {
                for (int j = i; j <= p; j++) {
                    dp[i][j] = 0;
                }
            }

            dp[0][0] = dp[0][1] = 0;
            dp[1][0] = 1;
            dp[1][1] = 0;
            int pt = 0;
            int pt2 = 0;

            for (int i = 2; i <= n; i++) {
                for (int j = 0; j <= p; j++) {
                    if (j) {
                        while (a[pt] + mid - 1 < a[i]) pt++;
                        pt--;

                        dp[i][j] = min(dp[i][j], dp[pt][j - 1]);
                    }

                    while (a[pt2] + 2 * mid - 1 < a[i]) pt2++;
                    pt2--;

                    dp[i][j] = min(dp[i][j], dp[pt2][j] + 1);
                }
            }

            int mn = 0x3f3f3f3f;
            for (int i = 0; i <= p; i++) mn = min(mn, dp[n][i]);

            if (mn <= q) r = mid - 1;
            else l = mid + 1;
        }

        printf("%d", l);
    }
    return 0;
}
