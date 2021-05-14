#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N], n, col[N], cur[N], ans = 0;
vector <int> g[N];
map <pair <int, int>, vector <int> > temp;
map <int, int> mm[N];

void dfs (int u, int p) {
    mm[u][a[u]]++;
    if (col[a[u]] == 1) cur[u]++;
    for (auto v: g[u]) {
        if (v == p) continue;
        dfs(v, u);

        if (mm[u].size() < mm[v].size()) {
            mm[u].swap(mm[v]);
            cur[u] = cur[v];
        }

        for (auto it: mm[v]) {
            mm[u][it.first] += it.second;
            if (mm[u][it.first] == col[it.first]) cur[u]++;
        }
    }

    if (cur[u] == mm[u].size()) ans++;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 2; i++) {
        int x, y, z, d;
        scanf("%d %d %d %d", &x, &y, &z, &d);
        a[i] = d; col[d]++;
        temp[{x, y}].push_back(i); temp[{y, x}].push_back(i); temp[{x, z}].push_back(i);
        temp[{z, x}].push_back(i); temp[{y, z}].push_back(i); temp[{z, y}].push_back(i);
    }

    for (auto it: temp) {
        if (it.second.size() == 1) continue;
        g[it.second[0]].push_back(it.second[1]);
        g[it.second[1]].push_back(it.second[0]);
    }

    for (int i = 1; i <= n - 2; i++) sort(g[i].begin(), g[i].end()), g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
    dfs(1, 1);
    printf("%d", ans - 1);
    return 0;
}
