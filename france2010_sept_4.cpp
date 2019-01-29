#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, m, f[N][N], g[N][N], a[N][N], p;

struct SegmentTree {
    int node[2][N << 2];
    void init (int i, int l, int r, int col) {
        if (l == r) {
            node[0][i] = g[col][l];
            node[1][i] = g[col][l] + l * p;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid, col);
        init(i << 1 | 1, mid + 1, r, col);
        for (int j = 0; j < 2; j++) node[j][i] = max(node[j][i << 1], node[j][i << 1 | 1]);
    }

    int query (int i, int l, int r, int a, int b, int type) {
        if (l > r || a > r || b < l) return -(int)1e9;
        if (a <= l && r <= b) return node[type][i];

        int mid = l + r >> 1;
        return max(query(i << 1, l, mid, a, b, type), query(i << 1 | 1, mid + 1, r, a, b, type));
    }
} it;

int main(){
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i][j - 1] + a[j][i] - p;
        }
    }

    for (int i = 0; i <= n; i++) g[1][i] = f[1][i];
    for (int i = 2; i <= m; i++) {
        it.init(1, 0, n, i - 1);
        for (int j = 0; j <= n; j++) g[i][j] = f[i][j] + max(it.query(1, 0, n, 0, j, 1), j * p + it.query(1, 0, n, j + 1, n, 0));
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) ans = max(ans, g[m][i]);
    printf("%d", ans);
    return 0;
}
