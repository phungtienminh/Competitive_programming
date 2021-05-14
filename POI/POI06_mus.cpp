#include <bits/stdc++.h>

using namespace std;

const int N = 105;
bool dp[N][N];
char a[N][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) dp[i][1] = true;

    for (int j = 2; j <= n; j++) {
        for (int i = 0; i < n; i++) {
            for (int k = 1; k < j; k++) {
                dp[i][j] |= (dp[i][k] && dp[(i + k) % n][j - k] && (a[i][(i + k) % n] == '1' || a[(i + j) % n][(i + k) % n] == '1'));
            }
        }
    }

    vector <int> ans;
    for (int i = 0; i < n; i++) if (dp[i][n]) ans.push_back(i + 1);

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
    return 0;
}
