#include <bits/stdc++.h>

using namespace std;

const int N = 20;

int n;
pair <int, int> dp[1 << N];

int main(){
    scanf("%d", &n); memset(dp, 0, sizeof(dp));
    for (int i = 0; i < (1 << n); i++) scanf("%d", &dp[i].first);
    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (mask & (1 << i)) {
                dp[mask].second = max(dp[mask].second, dp[mask ^ (1 << i)].first);
                if (dp[mask].first < dp[mask].second) swap(dp[mask].first, dp[mask].second);
            }
        }
    }

    int last = 0;
    for (int i = 1; i < (1 << n); i++) {
        cout << max(last, dp[i].first + dp[i].second) << "\n";
        last = max(last, dp[i].first + dp[i].second);
    }
    return 0;
}
