#include <bits/stdc++.h>

using namespace std;

const int N = 20;

long long dp[N][6][6][6][6][27];
int ve, vc, ce, cc;
string s;

bool vowels (char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> ve >> vc >> ce >> cc >> s;
    s = "#" + s;
    dp[0][0][0][0][0][0] = 1;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j <= ve; j++) {
            for (int k = 0; k <= vc; k++) {
                for (int l = 0; l <= ce; l++) {
                    for (int m = 0; m <= cc; m++) {
                        for (int last = 0; last < 27; last++) {
                            if (dp[i][j][k][l][m][last]) {
                                if (s[i + 1] != '*') {
                                    if (vowels(s[i + 1])) {
                                        if (s[i + 1] - 'a' + 1 == last) dp[i + 1][j + 1][k + 1][0][0][s[i + 1] - 'a' + 1] += dp[i][j][k][l][m][last];
                                        else dp[i + 1][1][k + 1][0][0][s[i + 1] - 'a' + 1] += dp[i][j][k][l][m][last];
                                    }
                                    else {
                                        if (s[i + 1] - 'a' + 1 == last) dp[i + 1][0][0][l + 1][m + 1][s[i + 1] - 'a' + 1] += dp[i][j][k][l][m][last];
                                        else dp[i + 1][0][0][1][m + 1][s[i + 1] - 'a' + 1] += dp[i][j][k][l][m][last];
                                    }
                                }
                                else {
                                    for (char nxt = 'a'; nxt <= 'z'; nxt++) {
                                        if (vowels(nxt)) {
                                            if (nxt - 'a' + 1 == last) dp[i + 1][j + 1][k + 1][0][0][nxt - 'a' + 1] += dp[i][j][k][l][m][last];
                                            else dp[i + 1][1][k + 1][0][0][nxt - 'a' + 1] += dp[i][j][k][l][m][last];
                                        }
                                        else {
                                            if (nxt - 'a' + 1 == last) dp[i + 1][0][0][l + 1][m + 1][nxt - 'a' + 1] += dp[i][j][k][l][m][last];
                                            else dp[i + 1][0][0][1][m + 1][nxt - 'a' + 1] += dp[i][j][k][l][m][last];
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

    long long ans = 0;
    for (int i = 0; i <= ve; i++) for (int j = 0; j <= vc; j++) for (int k = 0; k <= ce; k++) for (int l = 0; l <= cc; l++) for (int m = 0; m < 27; m++) ans += dp[s.length() - 1][i][j][k][l][m];
    cout << ans;
    return 0;
}
