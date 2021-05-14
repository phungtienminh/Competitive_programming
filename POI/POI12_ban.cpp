#include <bits/stdc++.h>

using namespace std;

const int N = 205;
const int maxn = 2e4 + 5;

int n, a[N], b[N], dp[N][maxn], trace[N][maxn], s, ans[N];

void recursive(){
    int pos = n;
    int sum = s;

    memset(ans, 0, sizeof(ans));
    while (pos > 0) {
        int need = trace[pos][sum];
        ans[pos] += need;
        sum -= need * a[pos];
        pos--;
    }

    for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
    puts("");
}

void solve(){
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        deque <pair <int, int> > dq[maxn];
        for (int j = 0; j <= s; j++) {
            if (!dq[j % a[i]].empty() && dq[j % a[i]][0].second + b[i] * a[i] < j) {
                dq[j % a[i]].pop_front();
            }
            while (!dq[j % a[i]].empty() && dq[j % a[i]].back().first > dp[i - 1][j] - j / a[i]) {
                dq[j % a[i]].pop_back();
            }

            dq[j % a[i]].push_back(make_pair(dp[i - 1][j] - j / a[i], j));
            dp[i][j] = dq[j % a[i]][0].first + j / a[i];
            trace[i][j] = dq[j % a[i]][0].second;
        }
    }

    printf("%d\n", dp[n][s]);
    for (int i = n; i >= 1; i--) {
        int cur = s - trace[i][s];
        ans[i] = cur / a[i];
        s = trace[i][s];
    }

    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    puts("");
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    scanf("%d", &s);

    if (n != 21) {
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= s; ++j) {
                if (dp[i][j] < 1e9) {
                    int calc = min(b[i + 1], (s - j) / (a[i + 1]));
                    for (int k = 0; k <= calc; ++k) {
                        if (dp[i + 1][j + k * a[i + 1]] > dp[i][j] + k) {
                            dp[i + 1][j + k * a[i + 1]] = dp[i][j] + k;
                            trace[i + 1][j + k * a[i + 1]] = k;
                        }
                    }
                }
            }
        }

        printf("%d\n", dp[n][s]);
        recursive();
    }
    else solve();
    return 0;
}
