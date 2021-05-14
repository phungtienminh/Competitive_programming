#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, e, w, q, d[N], Max = 0, pos = 1;
vector <int> g[N], vecw, vece;

int dfs (int u, int p) {
    int ans = (u >= n - w + 1);
    for (auto v: g[u]) {
        if (v == p) continue;
        d[v] = d[u] + 1;
        ans += dfs(v, u);
    }

    if (ans == w && d[u] > Max) {
        Max = d[u];
        pos = u;
    }

    return ans;
}

int main(){
    scanf("%d %d %d", &n, &e, &w);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    dfs(1, 1); d[pos] = 0; dfs(pos, pos);
    for (int i = n - w + 1; i <= n; i++) vecw.push_back(d[i]);
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        vece.push_back(d[x]);
    }

    sort(vecw.begin(), vecw.end()); sort(vece.begin(), vece.end());
    for (int i = 1; i < vecw.size(); i++) if (vecw[i] <= vecw[i - 1]) vecw[i] = vecw[i - 1] + 1;
    for (int i = 1; i < vece.size(); i++) if (vece[i] <= vece[i - 1]) vece[i] = vece[i - 1] + 1;;


    int ans = 0;
    for (int i = 0; i < vece.size(); i++) ans = max(ans, vecw[i] + vece[(int)vece.size() - i - 1]);
    printf("%d", ans);
    return 0;
}
