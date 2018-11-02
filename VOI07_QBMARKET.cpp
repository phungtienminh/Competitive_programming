#include <bits/stdc++.h>

using namespace std;

const int N = 505;
const int maxn = 1e5 + 5;
const long long base = 1e18;

struct BigNum {
    long long fi, se;
    BigNum (long long fi = 0, long long se = 0): fi(fi), se(se) {}
    BigNum operator + (const BigNum &rhs) const {
        long long nfi = fi + rhs.fi, nse = se + rhs.se;
        if (nse >= base) nse -= base, nfi++;
        return BigNum(nfi, nse);
    }
} dp[2][maxn];

int s, n, x[N], m[N];

int dig (long long x) {
    int ans = 0;
    while (x > 0) {
        ans++;
        x /= 10;
    }

    return ans;
}

int main(){
    scanf("%d %d", &s, &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &x[i], &m[i]);
    dp[0][0] = BigNum(0, 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= s; j++) dp[(i + 1) % 2][j] = BigNum(0, 0);
        for (int j = 0; j <= s; j++) {
            if (dp[i % 2][j].fi != 0 || dp[i % 2][j].se != 0) {
                for (int k = 0; k <= m[i + 1]; k++) {
                    if (j + k * x[i + 1] > s) break;
                    dp[(i + 1) % 2][j + k * x[i + 1]] = dp[(i + 1) % 2][j + k * x[i + 1]] + dp[i % 2][j];
                }
            }
        }
    }

    int cur = dig(dp[n % 2][s].se);

    if (dp[n % 2][s].fi > 0) {
        printf("%lld", dp[n % 2][s].fi);
        for (int i = 0; i < 18 - cur; i++) printf("0");
    }
    printf("%lld", dp[n % 2][s].se);
    return 0;
}
