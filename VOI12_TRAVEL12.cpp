#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, m;
vector <int> g[N];
bitset <10001> bs[N];

void dfs (int u, int len, int fi, int se, int th, int fo) {
    if (len == 3) {
        if (bs[fo].test(fi)) {
            printf("%d %d %d %d", fi, se, th, fo);
            exit(0);
        }

        return;
    }

    for (auto v: g[u]) {
        if (v == fi || v == se || v == th || v == fo) continue;
        if (len == 0) dfs(v, len + 1, fi, v, th, fo);
        else if (len == 1) dfs(v, len + 1, fi, se, v, fo);
        else dfs(v, len + 1, fi, se, th, v);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (bs[u].test(v)) continue;
        g[u].push_back(v); g[v].push_back(u);
        bs[u].set(v); bs[v].set(u);
    }

    for (int i = 1; i <= n; i++) dfs(i, 0, i, -1, -1, -1);
    printf("%d", -1);
    return 0;
}
