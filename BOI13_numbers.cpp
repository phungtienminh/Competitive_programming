#include <bits/stdc++.h>

using namespace std;

long long dp[20][2][2][11][11];
string a, b;

long long solve (int pos, bool low, bool high, int last, int prevlast, bool nonzero) {
    if (pos == a.length()) return 1;
    long long &ans = dp[pos][low][high][last][prevlast];
    if (ans != -1) return ans;

    ans = 0;
    int l = 0, r = 9;
    if (low) l = a[pos] - '0';
    if (high) r = b[pos] - '0';

    for (int i = l; i <= r; i++) {
        bool newlow = 0;
        bool newhigh = 0;
        if (low && i == l) newlow = 1;
        if (high && i == r) newhigh = 1;

        if (!nonzero) {
            if (i == 0) ans += solve(pos + 1, newlow, newhigh, last, prevlast, nonzero);
            else if (i != last && i != prevlast) ans += solve(pos + 1, newlow, newhigh, i, last, true);
        }
        else if (i != last && i != prevlast) ans += solve(pos + 1, newlow, newhigh, i, last, true);
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> a >> b;
    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 1, 1, 10, 10, 0);
    return 0;
}
