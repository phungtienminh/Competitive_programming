#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int maxn = 1005;
int a[N], n, m, e, p, b;
pair <int, int> trace[N][maxn];
bool dp[N][maxn];
vector <int> g[N];

void dfs (int u) {
    for (int i = 0; i < g[u].size(); i++) {
        for (int j = 0; j <= b; j++) {
            if (dp[u][j]) {
                int v = g[u][i];
                if (j + a[v] <= b && !dp[v][j + a[v]]) {
                dp[v][j + a[v]] = true;
                trace[v][j + a[v]] = make_pair(u, j);
                dfs(v);
                }
            }
        }
    }
} int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> e >> p >> b;
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(dp, 0, sizeof(dp));
    dp[e][a[e]] = true;

    for (int j = 0; j <= b; j++) {
        for (int i = 1; i <= n; i++) {
            if (!dp[i][j]) continue;
            for (int k = 0; k < g[i].size(); k++) {
                int v = g[i][k];
                if (j + a[v] <= b && !dp[v][j + a[v]]) {
                    dp[v][j + a[v]] = true;
                    trace[v][j + a[v]] = make_pair(i, j);
                }
            }
        }
    }

    int pos = p;
    int val = b;
    vector <int> res;
    while (!(pos == e && val == a[e])) {
        res.push_back(pos);
        int nxtpos = trace[pos][val].first;
        int nxtval = trace[pos][val].second;
        pos = nxtpos; val = nxtval;
    }

    res.push_back(e);
    for (int i = (int)res.size() - 1; i >= 0; i--) cout << res[i] << " ";
    return 0;
}
