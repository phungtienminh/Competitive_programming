#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 205;

int dp[N][N], trace[N][N];
string s, a[N];
int n;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    memset(dp, 0, sizeof(dp));
    memset(trace, 0, sizeof(trace));
    dp[0][0] = 1;

    for (int i = 0; i <= s.length(); i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] += dp[i][j - 1];
            trace[i][j] = 0;
            if (a[j].length() <= i) {
                bool f = true;
                for (int k = (int)a[j].length() - 1; k >= 0; k--) {
                    if (a[j][k] != s[i - (a[j].length() - k)]) {
                        f = false;
                        break;
                    }
                }

                if (f) {
                    dp[i][j] += dp[i - a[j].length()][j - 1];
                    if (dp[i - a[j].length()][j - 1]) trace[i][j] = j;
                }
            }
        }
    }

    int ans = dp[s.length()][n];
    if (ans == 0) cout << "NIE\n";
    else {

        int pos = s.length();
        int cur = n;

        vector <int> res;
        while (pos > 0) {
            if (trace[pos][cur] > 0) {
                res.push_back(trace[pos][cur]);
                pos = pos - a[trace[pos][cur]].length();
                cur--;
            }
            else cur--;
        }

        ans = min(ans, 1000000LL);
        cout << ans << "\n";
        for (int i = (int)res.size() - 1; i >= 0; i--) cout << res[i] << "\n";
    }
    return 0;
}
