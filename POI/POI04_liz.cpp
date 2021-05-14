#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 105;
const int maxn = 405;
const int mod = 1000000000;

pair <int, int> dp[N][maxn][2][2];
int n, k;

pair <int, int> add (pair <int, int> x, pair <int, int> y) {
    pair <int, int> ans = make_pair(x.first + y.first + (x.second + y.second) / mod, (x.second + y.second) % mod);
    return ans;
}

int num_dig (int x) {
    if (x == 0) return 1;

    int ans = 0;
    while (x) {
        ans++;
        x /= 10;
    }

    return ans;
}

signed main(){
    scanf("%lld %lld", &n, &k);
    memset(dp, 0, sizeof(dp));

    dp[0][0][0][0] = make_pair(0, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (j + i + 1 > k) dp[i + 1][0][1][1] = add(dp[i + 1][0][1][1], dp[i][j][0][0]);
            else dp[i + 1][j + i + 1][0][1] = add(dp[i + 1][j + i + 1][0][1], dp[i][j][0][0]);

            dp[i + 1][j][0][0] = add(dp[i + 1][j][0][0], add(dp[i][j][0][0], dp[i][j][0][1]));
        }

        dp[i + 1][0][1][1] = add(dp[i + 1][0][1][1], dp[i][0][1][0]);
        dp[i + 1][0][1][0] = add(dp[i + 1][0][1][0], add(dp[i][0][1][0], dp[i][0][1][1]));
    }

    pair <int, int> ans = add(dp[n][0][1][0], dp[n][0][1][1]);
    if (ans.first == 0) printf("%lld", ans.second);
    else {
        printf("%lld", ans.first);
        int res = num_dig(ans.second);
        for (int i = 1; i <= 9 - res; i++) printf("0");
        printf("%lld", ans.second);
    }
    return 0;
}
