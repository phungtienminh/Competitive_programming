#include <bits/stdc++.h>

using namespace std;

const int N = 6e4 + 5;

int dp[1024], n, start = 0, fin, m, need[N], have[N], x;
pair <int, int> trace[1024];

void dotrace (int pos) {
    if (pos == start) return;
    dotrace(trace[pos].second);
    printf("%d\n", trace[pos].first);
}

int main(){
    #ifndef Futymy
        freopen("bungin.txt", "r", stdin);
        freopen("bungout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    while (scanf("%d", &x) == 1 && x) start |= (1 << (x - 1));
    scanf("%d", &fin);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        while (scanf("%d", &x) == 1 && x) need[i] |= (1 << (x - 1));
        while (scanf("%d", &x) == 1 && x) have[i] |= (1 << (x - 1));
    }

    //for (int i = 1; i <= m; i++) cout << need[i] << " " << have[i] << "\n";
    memset(dp, 0x3f, sizeof(dp)); dp[start] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] < 1e9) {
            for (int i = 1; i <= m; i++) {
                if ((mask & need[i]) == need[i]) {
                    if (dp[mask | have[i]] > dp[mask] + 1) {
                        //cout << (mask | have[i]) << " " << i << " " << mask << " " << need[i] << "\n";
                        dp[mask | have[i]] = dp[mask] + 1;
                        trace[mask | have[i]] = {i, mask};
                    }
                }
            }
        }
    }

    //for (int i = 0; i < (1 << n); i++) cout << i << " " << dp[i] << "\n";

    int ans = 1e9, pos = start;
    for (int i = 0; i < (1 << n); i++) if (i & (1 << (fin - 1))) if (dp[i] < ans) ans = dp[i], pos = i;
    dotrace(pos);
    return 0;
}
