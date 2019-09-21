#include <bits/stdc++.h>

using namespace std;

const int N = 1505;

int t, n, m, a[N], b[N], dp[N];

int main(){
    scanf("%d", &t);
    while (t--) {
        memset(dp, 0, sizeof(dp));
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= m; i++) scanf("%d", &b[i]);
        for (int i = 1; i <= n; i++) {
            int res = 0, prv = 0;
            for (int j = 1; j <= m; j++) {
                prv = res;
                if (b[j] * 2 <= a[i]) res = max(res, dp[j]);
                if (a[i] == b[j]) dp[j] = max(dp[j], prv + 1);
            }
        }

        printf("%d\n", *max_element(dp + 1, dp + m + 1));
    }
    return 0;
}
