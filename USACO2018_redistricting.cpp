#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, k, dp[N], g[N], h[N];
string s;
deque <int> dq;

int main(){
    #ifndef Futymy
        freopen("redistricting.in", "r", stdin);
        freopen("redistricting.out", "w", stdout);
    #endif // Futymy

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k >> s; s = "#" + s;
    for (int i = 1; i <= n; i++) g[i] = g[i - 1] + (s[i] == 'G'), h[i] = h[i - 1] + (s[i] == 'H');

    dq.push_back(0);
    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();
        if (!dq.empty()) dp[i] = dp[dq.front()] + (g[i] - g[dq.front()] >= h[i] - h[dq.front()] ? 1 : 0);
        while (!dq.empty() && (dp[dq.back()] > dp[i] || (dp[dq.back()] == dp[i] && g[i] - g[dq.back()] >= h[i] - h[dq.back()]))) dq.pop_back();
        dq.push_back(i);
    }

    cout << dp[n];
    return 0;
}
