#include <bits/stdc++.h>

using namespace std;

const int N = 25;

int t, n, m, cnt = 0;
pair <int, int> trace[N][N];
bool visited[N][N], found = false;
vector <pair <int, int> > can[N][N];
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

void dotrace (int r, int c) {
    if (!(r == 1 && c == 1)) dotrace(trace[r][c].first, trace[r][c].second);
    cout << r << " " << c << "\n";
}

void dfs (int r, int c, int step) {
    cnt++;
    if (found) return;
    if (cnt >= 1e6) {
        cout << "IMPOSSIBLE\n";
        found = true;
        return;
    }

    if (step == n * m) {
        cout << "POSSIBLE\n";
        found = true;
        dotrace(r, c);
        return;
    }

    for (auto i: can[r][c]) {
        if (!visited[i.first][i.second]) {
            visited[i.first][i.second] = true;
            trace[i.first][i.second] = {r, c};
            dfs(i.first, i.second, step + 1);
            visited[i.first][i.second] = false;
        }
    }
}

void solve(){
    cin >> n >> m; memset(visited, 0, sizeof(visited)); cnt = 0; found = false;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) can[i][j].clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int r = 1; r <= n; r++) {
                for (int c = 1; c <= m; c++) {
                    if (i == r || j == c || i - j == r - c || i + j == r + c) continue;
                    can[i][j].push_back({r, c});
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) shuffle(can[i][j].begin(), can[i][j].end(), rd);
    visited[1][1] = true;
    dfs(1, 1, 1);
    if (!found) cout << "IMPOSSIBLE\n";
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
