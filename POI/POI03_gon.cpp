#include <bits/stdc++.h>

using namespace std;

const int N = 505;

vector <int> g[N], ans;
bool used[N], used2[N];
int n, m;

int redfs (int u) {
    int res = 1;
    used2[u] = true;

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!used2[v]) res += redfs(v);
    }

    return res;
}

bool check (int u) {
    memset(used2, 0, sizeof(used2));
    for (int i = 1; i <= n; i++) {
        if (used[i]) used2[i] = true;
    }

    used2[u] = true;
    int res = redfs(1);

    return (res == n - ans.size() - 1);
}

void dfs (int u) {
    if (u > 1) {
        used[u] = true;
        ans.push_back(u);
    }

    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!used[v] && check(v)) dfs(v);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(used, 0, sizeof(used));
    dfs(1);
    printf("1");
    for (int i = 0; i < ans.size(); i++) printf(" %d", ans[i]);
    puts("");
    printf("1");
    for (int i = ans.size() - 1; i >= 0; i--) printf(" %d", ans[i]);
    puts("");
    return 0;
}
