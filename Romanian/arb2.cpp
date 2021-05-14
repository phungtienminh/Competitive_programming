#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct edge {
    int v, w, cost;
    edge (int v = 0, int w = 0, int cost = 0): v(v), w(w), cost(cost) {}
};

vector <edge> g[N];
int n, d[N], dp[N], f[N], Max = 0;
long long ans = 0;

void dfs (int u, int p) {
    f[u] = d[u];
    Max = max(Max, d[u]);
    for (auto v: g[u]) {
        if (v.v == p) continue;
        d[v.v] = d[u] + v.w;
        dfs(v.v, u);
        f[u] = max(f[u], f[v.v]);
    }
}

void redfs (int u, int p, int costToPar) {
    if (costToPar != -1) dp[u] = costToPar;
    else dp[u] = 1e9;
    bool leaf = true;
    int sum = 0;
    for (auto v: g[u]) {
        if (v.v == p) continue;
        leaf = false;
        redfs(v.v, u, v.cost);
        sum += dp[v.v];
    }

    if (!leaf) dp[u] = min(dp[u], sum);
    for (auto v: g[u]) if (v.v != p) ans += 1LL * (f[u] - f[v.v]) * dp[v.v];
}

int readInt(){
    char c;
    int ans = 0;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    #ifndef Futymy
        freopen("arb2.in", "r", stdin);
        freopen("arb2.out", "w", stdout);
    #endif // Futymy
    n = readInt();
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w, cost;
        u = readInt(); v = readInt(); w = readInt(); cost = readInt();
        g[u].push_back(edge(v, w, cost));
        g[v].push_back(edge(u, w, cost));
    }

    dfs(1, 1);
    redfs(1, 1, -1);
    //for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    //cout << "\n";
    printf("%lld", ans);
    return 0;
}
/*
7
1 2 2 1
2 4 2 1
2 5 1 1
1 3 1 1
3 6 2 1
3 7 1 1
*/
