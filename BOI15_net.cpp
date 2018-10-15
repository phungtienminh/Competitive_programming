#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n;
vector <int> vec, g[N];

void dfs (int u, int p) {
    bool leaf = true;
    for (auto v: g[u]) {
        if (v == p) continue;
        leaf = false;
        dfs(v, u);
    }

    if (leaf) vec.push_back(u);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v; scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (g[i].size() > 1) {
            dfs(i, i);
            break;
        }
    }

    printf("%d\n", ((int)vec.size() + 1) / 2);
    for (int i = 0; i < ((int)vec.size() + 1) / 2; i++) printf("%d %d\n", vec[i], vec[i + vec.size() / 2]);
    return 0;
}
