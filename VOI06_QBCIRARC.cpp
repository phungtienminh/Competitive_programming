#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int maxn = 2e4 + 5;

vector <pair <int, int> > g[N], ans;
pair <int, int> edge[maxn];
bool ban[maxn], visited[N], instack[N];
int n, m;

bool dfs (int u) {
    visited[u] = instack[u] = true;
    for (auto v: g[u]) {
        if (ban[v.second]) continue;
        if (!visited[v.first] && dfs(v.first)) return true;
        else if (instack[v.first]) return true;
    }

    instack[u] = false;
    return false;
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back({v, i});
        edge[i] = {u, v};
    }

    bool f = 0;
    for (int i = 1; i <= n; i++) if (!visited[i]) f |= dfs(i);
    if (!f) printf("%d", -1);
    else {
        for (int i = 1; i <= m; i++) {
            ban[i] = true;
            f = 0; memset(visited, 0, sizeof(visited));
            for (int j = 1; j <= n; j++) if (!visited[j]) f |= dfs(j);

            if (!f) ans.push_back({edge[i].first, edge[i].second});
            ban[i] = false;
        }

        sort(ans.begin(), ans.end());
        if (ans.size() == 0) printf("%d", -1);
        else {
            printf("%d\n", (int)ans.size());
            for (auto i: ans) printf("%d %d\n", i.first, i.second);
        }
    }
    return 0;
}
