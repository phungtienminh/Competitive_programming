#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

bool adj[N][N];
int n, m, red[N], black[N];

void input(){
    memset(adj, 0, sizeof(adj));
    memset(red, 0, sizeof(red));
    memset(black, 0, sizeof(black));

    scanf("%d", &n);
    scanf("%d", &m);

    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = true;
    }
}

void solve(){
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (adj[i][j]) {
                red[i]++;
                red[j]++;
            }
            else {
                black[i]++;
                black[j]++;
            }
        }
    }

    long long res = 1LL * n * (n - 1) * (n - 2) / 6; //nC3 - total number of triangles
    for (int i = 1; i <= n; i++) res = res - 1LL * red[i] * black[i] / 2; //subtract from triangles have different colors on sides. Because we will count two times, then we must divide by 2.
    printf("%lld", res);
}

int main(){
    input();
    solve();
    return 0;
}
