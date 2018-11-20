#include <bits/stdc++.h>

using namespace std;

const int N = 3005;
const int maxn = 8005;

int n, m, num[N], low[N], a[N], in[N], u[maxn], v[maxn], cost[N], cnt = 0, recnt = 0;
vector <int> g[N], scc[N], g2[N];
stack <int> st;
set <pair <int, int> > pairs;

void dfs (int u) {
    num[u] = low[u] = ++cnt;
    st.push(u);
    for (auto v: g[u]) {
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (num[u] == low[u]) {
        int v;
        recnt++;
        do {
            v = st.top(); st.pop();
            num[v] = low[v] = 1e9;
            in[v] = recnt;
            scc[recnt].push_back(v);
        } while (v != u);
    }
}

int main(){
    scanf("%d %d", &n, &m); memset(a, 0x3f, sizeof(a));
    for (int i = 1; i <= m; i++) {
        int p, v;
        scanf("%d %d", &p, &v);
        a[p] = v;
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u[i], &v[i]);
        g[u[i]].push_back(v[i]);
    }

    for (int i = 1; i <= n; i++) if (!num[i]) dfs(i);
    memset(cost, 0x3f, sizeof(cost));
    for (int i = 1; i <= n; i++) cost[in[i]] = min(cost[in[i]], a[i]);
    for (int i = 1; i <= m; i++) {
        u[i] = in[u[i]];
        v[i] = in[v[i]];
        if (u[i] == v[i]) continue;
        if (pairs.find({u[i], v[i]}) == pairs.end()) {
            pairs.insert({u[i], v[i]});
            g2[v[i]].push_back(u[i]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= recnt; i++) {
        if (g2[i].size() == 0) {
            if (cost[i] > 1e9) return !printf("NIE\n%d", scc[i][0]);
            else ans += cost[i];
        }
    }

    printf("TAK\n%d", ans);
    return 0;
}
