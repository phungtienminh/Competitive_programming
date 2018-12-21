#include <bits/stdc++.h>

using namespace std;

const int N = 15;

int n, trace[13][1 << 12][13], dp[13][1 << 12][13], cnt1 = 0, cnt2 = 0, u, v;
bool must[N][N], ban[N][N];

void maximize (int &x, int y) {
    x = max(x, y);
}

int main(){
    #ifndef Futymy
        freopen("arthin.txt", "r", stdin);
        freopen("arthout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    while (scanf("%d %d", &u, &v) == 2 && u && v) {
        must[u][v] = must[v][u] = true;
        cnt1++;
    }

    while (scanf("%d %d", &u, &v) == 2 && u && v) {
        ban[u][v] = ban[v][u] = true;
        cnt2++;
    }

    memset(dp, -0x3f, sizeof(dp));
    dp[1][1][1] = 0;
    for (int i = 1; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            for (int last = 1; last <= n; last++) {
                if (dp[i][mask][last] > -1e9) {
                    int cur = dp[i][mask][last];
                    for (int nxt = 1; nxt <= n; nxt++) {
                        if ((mask & (1 << (nxt - 1))) == 0) {
                            if (i < n - 1) {
                                if (ban[last][nxt]) continue;
                                if (must[last][nxt]) {
                                    if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur + 1) {
                                        maximize(dp[i + 1][mask | (1 << (nxt - 1))][nxt], cur + 1);
                                        trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                    }
                                }
                                else {
                                    if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur) {
                                        maximize(dp[i + 1][mask | (1 << (nxt - 1))][nxt], cur);
                                        trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                    }
                                }
                            }
                            else {
                                if (ban[last][nxt] || ban[nxt][1]) continue;
                                if (must[last][nxt]) {
                                    if (must[nxt][1]) {
                                        if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur + 2) {
                                            maximize(dp[i + 1][mask | (1 << (nxt - 1))][nxt], cur + 2);
                                            trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                        }
                                    }
                                    else {
                                        if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur + 1) {
                                            dp[i + 1][mask | (1 << (nxt - 1))][nxt] = cur + 1;
                                            trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                        }
                                    }
                                }
                                else {
                                    if (must[nxt][1]) {
                                        if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur + 1) {
                                            dp[i + 1][mask | (1 << (nxt - 1))][nxt] = cur + 1;
                                            trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                        }
                                    }
                                    else {
                                        if (dp[i + 1][mask | (1 << (nxt - 1))][nxt] < cur) {
                                            dp[i + 1][mask | (1 << (nxt - 1))][nxt] = cur;
                                            trace[i + 1][mask | (1 << (nxt - 1))][nxt] = last;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    bool f = false;
    int pos = 0;
    for (int i = 1; i <= n; i++) if (dp[n][(1 << n) - 1][i] == cnt1) f = true, pos = i;

    if (!f) printf("Meeting cancelled.");
    else {
        vector <int> vec;
        int cur = n, mask = (1 << n) - 1;
        while (cur > 0) {
            vec.push_back(pos);
            int last = trace[cur][mask][pos];
            int nmask = mask ^ (1 << (pos - 1));
            int ncur = cur - 1;
            cur = ncur; mask = nmask; pos = last;
        }

        for (int i = (int)vec.size() - 1; i >= 0; i--) printf("%d ", vec[i]);
    }
    return 0;
}
