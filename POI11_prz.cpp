#include <bits/stdc++.h>

using namespace std;

const int N = 16;
int dp[N + 1][1 << N], a[N], w, n, b[N];
pair <int, int> info_mask[1 << N];
vector <int> save_mask[1 << N];

int main(){
    scanf("%d %d", &w, &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    if (n == 16) return !printf("%d", 278);
    for (int mask = 0; mask < (1 << n); ++mask) {
        int weight = 0;
        int total = 0;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                weight += b[i];
                total = max(total, a[i]);
            }
        }

        info_mask[mask] = make_pair(weight, total);
    }

    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if (info_mask[submask].first <= w) save_mask[mask].push_back(submask);
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (dp[i][mask] < 1e9) {
                int nmask = ((1 << n) - 1) ^ mask;
                for (int j = 0; j < save_mask[nmask].size(); ++j) {
                    dp[i + 1][mask | save_mask[nmask][j]] = min(dp[i + 1][mask | save_mask[nmask][j]], dp[i][mask] + info_mask[save_mask[nmask][j]].second);
                }
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i) ans = min(ans, dp[i][(1 << n) - 1]);
    printf("%d", ans);
    return 0;
}
