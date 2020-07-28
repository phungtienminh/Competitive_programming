#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int t, n, m, a[N];
long long dp[N];

void solve (int test) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(dp, 0x3f, sizeof(dp)); dp[1] = 0;
    deque <pair <long long, int> > dq;
    dq.push_back(make_pair(dp[1], 1));

    for (int i = 2; i <= n; i++) {
        while (!dq.empty() && dq.front().second < i - m) dq.pop_front();
        if (a[i] && !dq.empty()) dp[i] = dq.front().first + a[i];
        while (!dq.empty() && dq.back().first >= dp[i]) dq.pop_back();
        dq.push_back(make_pair(dp[i], i));
    }

    long long ans = 1e18;
    for (int i = n - m; i <= n; i++) ans = min(ans, dp[i]);
    if (ans > 1e17) ans = -1;
    cout << "Case #" << test << ": " << ans << "\n";
}

int main(){
    freopen("running_on_fumes_chapter_1_input.txt", "r", stdin);
    freopen("running_on_fumes_chapter_1_output.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int test = 1; test <= t; test++) solve(test);
    return 0;
}
