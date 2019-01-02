#include <bits/stdc++.h>

using namespace std;

const int N = 35;
const int maxn = 1e4 + 5;

int n, dp[N][N][N], a[maxn], pts[N][N][N], ptr = 0;
pair <pair <int, int>, int> trace[N][N][N];

bool cmp (int i1, int j1, int k1, int i2, int j2, int k2) {
    if (i1 < i2) return true;
    if (i1 == i2 && j1 < j2) return true;
    if (i1 == i2 && j1 == j2 && k1 < k2) return true;
    return false;
}

int main(){
    #ifndef Futymy
        freopen("drum2.in", "r", stdin);
        freopen("drum2.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n * (n + 1) * (2 * n + 1) / 6; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= i; k++) {
                pts[i][j][k] = ++ptr;
            }
        }
    }

    memset(dp, -0x3f, sizeof(dp)); dp[1][1][1] = a[pts[1][1][1]];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (dp[i][j][k] > -1e9) {
                    if (dp[i + 1][j][k + 1] < dp[i][j][k] + a[pts[i + 1][j][k + 1]]) {
                        dp[i + 1][j][k + 1] = dp[i][j][k] + a[pts[i + 1][j][k + 1]];
                        trace[i + 1][j][k + 1] = make_pair(make_pair(i, j), k);
                    }
                    else if (dp[i + 1][j][k + 1] == dp[i][j][k] + a[pts[i + 1][j][k + 1]]) {
                        if (cmp(i, j, k, trace[i + 1][j][k + 1].first.first, trace[i + 1][j][k + 1].first.second, trace[i + 1][j][k + 1].second)) {
                            trace[i + 1][j][k + 1] = make_pair(make_pair(i, j), k);
                        }
                    }

                    if (dp[i + 1][j + 1][k] < dp[i][j][k] + a[pts[i + 1][j + 1][k]]) {
                        dp[i + 1][j + 1][k] = dp[i][j][k] + a[pts[i + 1][j + 1][k]];
                        trace[i + 1][j + 1][k] = make_pair(make_pair(i, j), k);
                    }
                    else if (dp[i + 1][j + 1][k] == dp[i][j][k] + a[pts[i + 1][j + 1][k]]) {
                        if (cmp(i, j, k, trace[i + 1][j + 1][k].first.first, trace[i + 1][j + 1][k].first.second, trace[i + 1][j + 1][k].second)) {
                            trace[i + 1][j + 1][k] = make_pair(make_pair(i, j), k);
                        }
                    }

                    if (dp[i + 1][j + 1][k + 1] < dp[i][j][k] + a[pts[i + 1][j + 1][k + 1]]) {
                        dp[i + 1][j + 1][k + 1] = dp[i][j][k] + a[pts[i + 1][j + 1][k + 1]];
                        trace[i + 1][j + 1][k + 1] = make_pair(make_pair(i, j), k);
                    }
                    else if (dp[i + 1][j + 1][k + 1] == dp[i][j][k] + a[pts[i + 1][j + 1][k + 1]]) {
                        if (cmp(i, j, k, trace[i + 1][j + 1][k + 1].first.first, trace[i + 1][j + 1][k + 1].first.second, trace[i + 1][j + 1][k + 1].second)) {
                            trace[i + 1][j + 1][k + 1] = make_pair(make_pair(i, j), k);
                        }
                    }
                }
            }
        }
    }

    int ans = 0, pi = 0, pj = 0, pk = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= i; k++) {
                if (dp[i][j][k] > ans) {
                    ans = dp[i][j][k];
                    pi = i; pj = j; pk = k;
                }
            }
        }
    }

    printf("%d\n", ans);
    stack <int> st;
    while (pi > 0) {
        st.push(pts[pi][pj][pk]);
        int ni = trace[pi][pj][pk].first.first;
        int nj = trace[pi][pj][pk].first.second;
        int nk = trace[pi][pj][pk].second;
        pi = ni; pj = nj; pk = nk;
    }

    while (!st.empty()) printf("%d ", st.top()), st.pop();
    return 0;
}
