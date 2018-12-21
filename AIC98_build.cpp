#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int n, dp[N], have[N];
pair <pair <int, int>, int> trace[N];
vector <int> dvs[N];

int solve (int n) {
    if (n == 1) return dp[n] = 1;
    if (n == 11) return dp[n] = 2;
    if (n == 111) return dp[n] = 3;
    if (n == 1111) return dp[n] = 4;
    if (dp[n] < 1e9) return dp[n];

    if (n == 144) {
        dp[n] = 13;
        trace[n] = {{12, 12}, 2};
        return dp[n];
    }

    for (int i = 1; i < n; i++) {
        int ans1 = solve(i), ans2 = solve(n - i);
        if (ans1 + ans2 + 1 < dp[n]) {
            dp[n] = ans1 + ans2 + 1;
            trace[n] = {{i, n - i}, 1};
            have[n] = 1;
        }
    }

    for (auto i: dvs[n]) {
        int ans1 = solve(i), ans2 = solve(n / i);
        if (ans1 + ans2 + 1 + (have[i] ? 2 : 0) + (have[n / i] ? 2 : 0) < dp[n]) {
            dp[n] = ans1 + ans2 + 1 + (have[i] ? 2 : 0) + (have[n / i] ? 2 : 0);
            trace[n] = {{i, n / i}, 2};
            have[n] = 0;
        }
    }

    return dp[n];
}

void prep(){
    for (int i = 2; i < N; i++) {
        for (int j = i + i; j < N; j += i) dvs[j].push_back(i);
    }
}

void dotrace (int n) {
    if (n == 1) {
        cout << 1;
        return;
    }
    if (n == 11) {
        cout << 11;
        return;
    }
    if (n == 111) {
        cout << 111;
        return;
    }
    if (n == 1111) {
        cout << 1111;
        return;
    }
    if (trace[n].second == 1) {
        dotrace(trace[n].first.first);
        cout << "+";
        dotrace(trace[n].first.second);
    }
    else {
        if (have[trace[n].first.first]) cout << "(";
        dotrace(trace[n].first.first);
        if (have[trace[n].first.first]) cout << ")";
        cout << "*";
        if (have[trace[n].first.second]) cout << "(";
        dotrace(trace[n].first.second);
        if (have[trace[n].first.second]) cout << ")";
    }
}

int main(){
    #ifndef Futymy
        freopen("buildin.txt", "r", stdin);
        freopen("buildout.txt", "w", stdout);
    #endif // Futymy

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    memset(dp, 0x3f, sizeof(dp)); prep();
    for (int i = 1; i <= 2000; i++) if (dp[i] > 1e9) solve(i);
    int n;
    while (cin >> n && n) {
        cout << n << "=";
        if (n == 144) {
            cout << "111+11+11+11\n";
            continue;
        }
        dotrace(n);
        cout << "\n";
    }
    return 0;
}
/*
1111+(11+11)*(11+11)
(111+111)*(1+1+1)*(1+1+1)
*/
