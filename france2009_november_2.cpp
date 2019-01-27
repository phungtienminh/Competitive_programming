#include <bits/stdc++.h>

using namespace std;

const int N = 6e5 + 5;

int n, m, a[N], cur = 1;

struct SegmentTree {
    int node[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = 0;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid); init(i << 1 | 1, mid + 1, r);
        node[i] = 0;
    }

    void update (int i, int l, int r, int pos) {
        if (l == r) {
            node[i] = 1;
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos);
        else update(i << 1 | 1, mid + 1, r, pos);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return (int)1e9;
        if (a <= l && r <= b) return node[i];

        int mid = l + r >> 1;
        return min(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
    }

    int Find (int i, int l, int r) {
        if (l == r) {
            if (node[i] == 1) return -1;
            return l > n ? -1 : l;
        }

        int mid = l + r >> 1;
        if (query(1, 1, 600000, l, mid)) return Find(i << 1 | 1, mid + 1, r);
        return Find(i << 1, l, mid);
    }
} it;

int main(){
    scanf("%d %d", &n, &m); it.init(1, 1, 600000);
    int peak = 300000;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        a[i] = min(a[i], peak);
        it.update(1, 1, 600000, a[i]);
        printf("%d\n", it.Find(1, 1, 600000));
        if (a[i] == peak) peak++;
    }
    return 0;
}
