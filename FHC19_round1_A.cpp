#include <bits/stdc++.h>

using namespace std;

const int N = 55;

int t, n, m, d[N][N];

void solve (int Test) {
    scanf("%d %d", &n, &m);
    memset(d, 0x3f, sizeof(d));
    vector <pair <int, pair <int, int> > > vec;
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        d[u][v] = d[v][u] = w;
        vec.push_back({w, {u, v}});
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    printf("Case #%d: ", Test);
    for (auto i: vec) {
        if (d[i.second.first][i.second.second] != i.first) {
            puts("Impossible");
            return;
        }
    }

    printf("%d\n", (int)vec.size());
    for (auto i: vec) printf("%d %d %d\n", i.second.first, i.second.second, i.first);
}

int main(){
    //freopen("graphs_as_a_service.txt", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    scanf("%d", &t);
    for (int T = 1; T <= t; T++) solve(T);
    return 0;
}
