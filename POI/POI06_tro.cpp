#include <bits/stdc++.h>

using namespace std;

const int N = 10005;
vector <int> g[N];
string s;
int cur = 0;
int cur_node = 2;
int dp[N][3], f[N][3], child[N];
//dp[i][j]: maximum number of color blue, j is the color of vertex i in the subtree rooted at i.
//f[i][j]: maximum number of color blue, j is the color of vertex i in the subtree rooted at i.
//0: Green
//1: Red
//2: Blue

void dfs (int u) {
    child[u] = s[cur] - '0';
    if (s[cur] == '0') return;
    else if (s[cur] == '1') {
        g[u].push_back(cur_node);
        //g[cur_node].push_back(u);
        cur_node++;
        cur++;
        dfs(cur_node - 1);
    }
    else {
        g[u].push_back(cur_node);
        //g[cur_node].push_back(u);
        cur_node++;
        cur++;
        dfs(cur_node - 1);

        g[u].push_back(cur_node);
        //g[cur_node].push_back(u);
        cur_node++;
        cur++;
        dfs(cur_node - 1);
    }
}

void calc (int u, int p) {
    if (child[u] == 0) {
        dp[u][0] = f[u][0] = 1;
        dp[u][1] = dp[u][2] = f[u][1] = f[u][2] = 0;
        return;
    }

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p) continue;

        calc(v, u);
    }

    if (child[u] == 1) {
        int v = g[u][0];
        dp[u][0] = 1 + max(dp[v][1], dp[v][2]);
        f[u][0] = 1 + min(f[v][1], f[v][2]);

        dp[u][1] = max(dp[v][0], dp[v][2]);
        f[u][1] = min(f[v][0], f[v][2]);

        dp[u][2] = max(dp[v][0], dp[v][1]);
        f[u][2] = min(f[v][0], f[v][1]);
    }
    else {
        int v1 = g[u][0];
        int v2 = g[u][1];

        dp[u][0] = 1 + max(dp[v1][1] + dp[v2][2], dp[v1][2] + dp[v2][1]);
        f[u][0] = 1 + min(f[v1][1] + f[v2][2], f[v1][2] + f[v2][1]);

        dp[u][1] = max(dp[v1][0] + dp[v2][2], dp[v1][2] + dp[v2][0]);
        f[u][1] = min(f[v1][0] + f[v2][2], f[v1][2] + f[v2][0]);

        dp[u][2] = max(dp[v1][0] + dp[v2][1], dp[v1][1] + dp[v2][0]);
        f[u][2] = min(f[v1][0] + f[v2][1], f[v1][1] + f[v2][0]);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    dfs(1);
    calc(1, 1);

    int ans = 0;
    int res = 0x3f3f3f3f;

    for (int i = 0; i < 3; i++) {
        ans = max(ans, dp[1][i]);
        res = min(res, f[1][i]);
    }

    cout << ans << " " << res;
    return 0;
}
