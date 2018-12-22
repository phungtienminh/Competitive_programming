#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m, ans = 0;
char a[N][N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int main(){
    #ifndef Futymy
        freopen("cartin.txt", "r", stdin);
        freopen("cartout.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= m + 1; j++) if (i == 0 || j == 0 || i == n + 1 || j == m + 1) a[i][j] = '.';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '#') {
                for (int k = 0; k < 4; k++) {
                    if (i + dx[k] >= 0 && i + dx[k] <= n + 1 && j + dy[k] >= 0 && j + dy[k] <= m + 1 && a[i + dx[k]][j + dy[k]] == '.') ans++;
                }
            }
        }
    }
    cout << ans;
    return 0;
}
/*
6 6
......
.###..
.##.#.
.##.#.
.####.
......
*/
