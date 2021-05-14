#include <bits/stdc++.h>

using namespace std;

const int N = 16;

int n, w, a[N], b[N], dp[1 << N], t[1 << N], weight[1 << N];

int main(){
    scanf("%d %d", &w, &n);
    for (int i = 0; i < n; i++) scanf("%d %d", &a[i], &b[i]);
    for (int i = 0; i < (1 << n); i++) {
        int curw = 0, curt = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                curw += b[j];
                curt = max(curt, a[j]);
            }
        }

        t[i] = curt;
        weight[i] = curw;
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[(1 << n) - 1] = 0;
    for (int mask = (1 << n) - 1; mask >= 0; mask--) {
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if (weight[submask] <= w) {
                dp[mask ^ submask] = min(dp[mask ^ submask], dp[mask] + t[submask]);
            }
        }
    }

    printf("%d", dp[0]);
    return 0;
}
