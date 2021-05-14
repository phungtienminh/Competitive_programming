#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e4 + 5;

int z[N], dp[N], n;
int ans = 0x3f3f3f3f3f3f3f3f;
int res = 0;
int cur = 0;
int sum = 0;

bool check (int l, int r) {
    int ret = abs(dp[l] - dp[r]);
    if (l > r) ret = dp[n] - ret;

    return 2 * ret <= dp[n];
}

int dist (int l, int r) {
    int ret = abs(dp[l] - dp[r]);
    ret = min(ret, dp[n] - ret);

    return ret;
}

int next (int i) {
    return (i + 1) % n;
}

signed main(){
    scanf("%lld", &n);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int d;
        scanf("%lld %lld", &z[i], &d);
        sum += z[i];
        dp[i + 1] = dp[i] + d;
    }

    if (n == 1) return !printf("0");
    if (n == 2) return !printf("%d", min(z[0], z[1]) * dist(0, 1));

    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        res += dist(0, i) * z[i];
        if (check(0, i)) {
            r = i;
            cur += z[i];
        }
    }

    for (; l < n; l++) {
        while (next(r) != l && check(l, next(r))) {
            r = next(r);
            int ret = abs(dp[l] - dp[r]);
            if (l < r) ret = dp[n] - ret;
            res += (dist(l, r) - ret) * z[r];
            cur += z[r];
        }

        ans = min(ans, res);
        cur -= z[l];
        res += (dp[l + 1] - dp[l]) * (sum - 2 * cur);
    }

    printf("%lld", ans);
    return 0;
}
