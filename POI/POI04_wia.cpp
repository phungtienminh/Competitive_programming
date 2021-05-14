#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, m;
bool found[N + N];
vector <int> g[N + N];

void dfs (int u) {
    found[u] = true;
    for (auto v: g[u]) if (!found[v]) dfs(v);
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u + n + 1].push_back(v + n + 1);
    }

    vector <int> ans;
    for (int i = 1; i <= n; i++) {
        memset(found, 0, sizeof(found));
        dfs(i + n + 1);
        for (int j = 1; j <= n; j++) {
            if (found[-j + n + 1] && found[j + n + 1]) {
                ans.push_back(i);
                break;
            }
        }
    }

    if (ans.size() == 0) printf("NIKT");
    else for (auto i: ans) printf("%d\n", i);
    return 0;
}
