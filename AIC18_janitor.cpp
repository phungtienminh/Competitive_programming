#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m, q, a[15][N], ini[10 * N];

struct SegmentTree {
    struct Node {
        int val, sum;
        Node (int val = 0, int sum = 0): val(val), sum(sum) {}
        Node operator + (const Node &rhs) const {
            return Node(val ^ rhs.val, sum + rhs.sum);
        }
    } node[40 * N];

    void init (int i, int l, int r) {
        if (l == r) {
            node[i].val = ini[l];
            node[i].sum = (node[i].val == 0);
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void update (int i, int l, int r, int pos, int val, int type) {
        if (l == r) {
            if (type) node[i].val -= val;
            else node[i].val = val;
            node[i].sum = (node[i].val == 0);
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos, val, type);
        else update(i << 1 | 1, mid + 1, r, pos, val, type);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    int query(){
        return node[1].sum;
    }
} it;

int main(){
    freopen("janitorin.txt", "r", stdin);
    freopen("janitorout.txt", "w", stdout);
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1 && a[i - 1][j] > a[i][j]) ini[(i - 1) * m + j]++;
            if (i < n && a[i + 1][j] > a[i][j]) ini[(i - 1) * m + j]++;
            if (j > 1 && a[i][j - 1] > a[i][j]) ini[(i - 1) * m + j]++;
            if (j < m && a[i][j + 1] > a[i][j]) ini[(i - 1) * m + j]++;
        }
    }

    it.init(1, 1, n * m);
    printf("%d\n", it.query());
    while (q--) {
        int r, c, val;
        scanf("%d %d %d", &r, &c, &val);
        if (r > 1 && a[r - 1][c] < a[r][c]) it.update(1, 1, n * m, (r - 2) * m + c, 1, 1);
        if (r < n && a[r + 1][c] < a[r][c]) it.update(1, 1, n * m, r * m + c, 1, 1);
        if (c > 1 && a[r][c - 1] < a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c - 1, 1, 1);
        if (c < m && a[r][c + 1] < a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c + 1, 1, 1);
        a[r][c] = val;
        if (r > 1 && a[r - 1][c] < a[r][c]) it.update(1, 1, n * m, (r - 2) * m + c, -1, 1);
        if (r < n && a[r + 1][c] < a[r][c]) it.update(1, 1, n * m, r * m + c, -1, 1);
        if (c > 1 && a[r][c - 1] < a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c - 1, -1, 1);
        if (c < m && a[r][c + 1] < a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c + 1, -1, 1);

        it.update(1, 1, n * m, (r - 1) * m + c, 0, 0);
        if (r > 1 && a[r - 1][c] > a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c, -1, 1);
        if (r < n && a[r + 1][c] > a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c, -1, 1);
        if (c > 1 && a[r][c - 1] > a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c, -1, 1);
        if (c < m && a[r][c + 1] > a[r][c]) it.update(1, 1, n * m, (r - 1) * m + c, -1, 1);
        printf("%d\n", it.query());
    }
    return 0;
}
