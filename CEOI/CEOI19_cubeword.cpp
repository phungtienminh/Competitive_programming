#include <bits/stdc++.h>

using namespace std;

const int N = 62;
const int mod = 998244353;
const int maxn = 1e5 + 5;

int n, ans = 0, dp[N][N][N];
string a[maxn];
int val[N][N][N];
int cur[N];
map <string, bool> mm;

void add (int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int toInt (char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 52;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        string t = a[i];
        reverse(t.begin(), t.end());
        if (!mm.count(a[i])) val[toInt(a[i][0])][toInt(a[i][a[i].length() - 1])][a[i].length()]++, mm[a[i]] = true;
        if (!mm.count(t)) val[toInt(t[0])][toInt(t[t.length() - 1])][t.length()]++, mm[t] = true;
    }

    //for (int i = 0; i <= 61; i++) cout << val[toInt('r')][i][5] << "\n";

    for (int side = 3; side <= 10; side++) {
        memset(dp, 0, sizeof(dp));
        for (int s = 0; s <= 61; s++) {
            for (int i = 0; i <= 61; i++) {
                for (int j = i; j <= 61; j++) {
                    for (int k = j; k <= 61; k++) {
                        add(dp[i][j][k], 1LL * val[s][i][side] * val[s][j][side] % mod * val[s][k][side] % mod);
                    }
                }
            }
        }

        for (int i = 0; i <= 61; i++) {
            for (int j = i; j <= 61; j++) {
                for (int k = j; k <= 61; k++) {
                    for (int l = k; l <= 61; l++) {
                        bool f1 = (i == j), f2 = (j == k), f3 = (k == l);
                        if (!f1 && !f2 && !f3) add(ans, 24LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (f1 && !f2 && !f3) add(ans, 12LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (!f1 && f2 && !f3) add(ans, 12LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (f1 && f2 && !f3) add(ans, 4LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (!f1 && !f2 && f3) add(ans, 12LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (f1 && !f2 && f3) add(ans, 6LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (!f1 && f2 && f3) add(ans, 4LL * dp[i][j][k] % mod * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                        else if (f1 && f2 && f3) add(ans, 1LL * dp[i][j][k] * dp[i][j][l] % mod * dp[i][k][l] % mod * dp[j][k][l] % mod);
                    }
                }
            }
        }
    }

    cout << ans;
    return 0;
}
