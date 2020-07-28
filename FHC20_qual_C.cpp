#include <bits/stdc++.h>

using namespace std;

const int N = 8e5 + 5;

int t, n, dp[N][2];
pair <int, int> a[N];
map <int, int> mm;

void solve (int test) {
    mm.clear();
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    memset(dp, -0x3f, sizeof(dp));
    dp[1][0] = dp[1][1] = a[1].second;
    mm[a[1].first] = max(mm[a[1].first], dp[1][0]);
    mm[a[1].first + a[1].second] = max(mm[a[1].first + a[1].second], dp[1][1]);

    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i][1] = a[i].second;
        dp[i][0] = max(dp[i][0], mm[a[i].first - a[i].second] + a[i].second);
        dp[i][1] = max(dp[i][1], mm[a[i].first] + a[i].second);
        mm[a[i].first] = max(mm[a[i].first], dp[i][0]);
        mm[a[i].first + a[i].second] = max(mm[a[i].first + a[i].second], dp[i][1]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, max(dp[i][0], dp[i][1]));
    cout << "Case #" << test << ": " << ans << "\n";
}

int main(){
    freopen("timber_input.txt", "r", stdin);
    freopen("timber_output.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int test = 1; test <= t; test++) solve(test);
    return 0;
}
