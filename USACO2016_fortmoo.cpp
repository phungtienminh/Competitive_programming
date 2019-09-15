#include <bits/stdc++.h>

using namespace std;

const int N = 205;

int n, m, ans = 0, row[N][N], nxt[N][N];
vector <int> col[N][N];
char a[N][N];

int main(){
    #ifndef Futymy
        freopen("fortmoo.in", "r", stdin);
        freopen("fortmoo.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) row[i][j] = row[i][j - 1] + (a[i][j] == 'X');
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            for (int k = 1; k <= n; k++) {
                if (row[k][j] == row[k][i - 1]) {
                    col[i][j].push_back(k);
                }
            }
        }
    }

    for (int j = 1; j <= m; j++) {
        for (int i = n + 1; i >= 1; i--) {
            if (i == n + 1 || a[i][j] == 'X') nxt[i][j] = i;
            else nxt[i][j] = nxt[i + 1][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int len = 1; j + len - 1 <= m; len++) {
                if (row[i][j + len - 1] == row[i][j - 1]) {
                    int threshold = min(nxt[i][j], nxt[i][j + len - 1]);
                    int pos = lower_bound(col[j][j + len - 1].begin(), col[j][j + len - 1].end(), threshold) - col[j][j + len - 1].begin();
                    --pos;

                    if (pos >= 0) {
                        int nr = col[j][j + len - 1][pos];
                        ans = max(ans, len * (nr - i + 1));
                    }
                }
            }
        }
    }

    cout << ans;
    return 0;
}
