#include <bits/stdc++.h>

using namespace std;

const int N = 505;

vector <int> g[N];
int cnt[N], n, deg[N];
bool visited[N];

void dfs (int u) {
    visited[u] = true; cnt[u]++;
    for (auto v: g[u]) if (!visited[v]) dfs(v);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int num; scanf("%d", &num);
        for (int j = 1; j <= num; j++) {
            int x; scanf("%d", &x);
            g[x].push_back(i);
            deg[i]++;
        }
    }

    vector <int> buff;
    for (int i = 1; i <= n; i++) if (!deg[i]) buff.push_back(i);
    for (auto i: buff) {
        memset(visited, 0, sizeof(visited));
        dfs(i);
    }

    vector <int> ans;
    for (int i = 1; i <= n; i++) if (deg[i] && cnt[i] < 2) ans.push_back(i);
    if (ans.size() == 0) printf("BRAK");
    else for (auto i: ans) printf("%d\n", i);
    return 0;
}
