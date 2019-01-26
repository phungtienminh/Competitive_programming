#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int maxn = 4005;

int n, dp[N][maxn];

struct Item {
    int t1, t2, len;
} a[N];

void maximize (int &x, int y) {
    x = max(x, y);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d", &a[i].t1, &a[i].t2, &a[i].len);
    memset(dp, -0x3f, sizeof(dp)); dp[0][2000] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < maxn; j++) {
            if (dp[i][j] > -1e9) {
                maximize(dp[i + 1][j], dp[i][j]);
                maximize(dp[i + 1][j + (a[i + 1].t1 == 1) + (a[i + 1].t2 == 1) - (a[i + 1].t1 == 0) - (a[i + 1].t2 == 0)], dp[i][j] + a[i + 1].len);
            }
        }
    }

    if (dp[n][2002] < -1e9) printf("%d", -1);
    else printf("%d", dp[n][2002]);
    return 0;
}
