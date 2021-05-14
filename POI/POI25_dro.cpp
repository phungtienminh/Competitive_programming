#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

int n, m, num[N], low[N], sz[N], ans[N], belong[N], cnt = 0, cntcc = 0;
stack <int> st;
vector <int> g[N], dag[N];
bool instack[N], visited[N];

void dfs (int u) {
    num[u] = low[u] = ++cnt;
    st.push(u);
    instack[u] = true;
    for (auto v: g[u]) {
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v]) low[u] = min(low[u], num[v]);
    }

    if (num[u] == low[u]) {
        cntcc++;
        int v;
        do {
            v = st.top(); st.pop();
            num[v] = low[v] = 1e9;
            sz[cntcc]++;
            belong[v] = cntcc;
        } while (v != u);
    }
}

void solve (int u) {
    ans[u] = sz[u];
    visited[u] = true;
    for (auto v: dag[u]) {
        if (!visited[v]) solve(v);
        ans[u] += ans[v];
    }
}

int main(){
    //freopen("testgen.inp", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
    }

    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= n; i++) if (!num[i]) dfs(i);
    for (int i = 1; i <= n; i++) for (auto j: g[i]) if (belong[i] != belong[j]) dag[belong[i]].push_back(belong[j]);
    for (int i = 1; i <= cntcc; i++) if (!visited[i]) solve(i);
    for (int i = 1; i <= n; i++) printf("%d\n", ans[belong[i]] - 1);
    return 0;
}
