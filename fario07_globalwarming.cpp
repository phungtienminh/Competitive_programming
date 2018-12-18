#include <bits/stdc++.h>

using namespace std;

int t, n, q, l, r, k;

struct Query {
    int l, r, k;

    bool operator<(const Query &other) const {
        return k > other.k;
    }
} query[100005];

const int N = 100005;
int node[4 * N], lazy[4 * N];

void build_tree (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = lazy[i] = 0;
        return;
    }

    int m = (l + r) >> 1;
    build_tree(i << 1, l, m);
    build_tree(i << 1 | 1, m + 1, r);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
    lazy[i] = max(lazy[i << 1], lazy[i << 1 | 1]);
}

void dolazy (int i, int l, int r) {
    if (lazy[i] != 0) {
        node[i] = lazy[i];
        if (l != r) {
            lazy[i << 1] = lazy[i];
            lazy[i << 1 | 1] = lazy[i];
        }

        lazy[i] = 0;
    }
}

void update (int i, int l, int r, int a, int b, int val) {
    dolazy(i, l, r);
    if (l > r || a > r || b < l) return;
    if (a <= l && r <= b) {
        node[i] = val;
        if (l != r) {
            lazy[i << 1] = val;
            lazy[i << 1 | 1] = val;
        }

        return;
    }

    int m = (l + r) >> 1;
    update(i << 1, l, m, a, b, val);
    update(i << 1 | 1, m + 1, r, a, b, val);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return -0x3f3f3f3f;
    dolazy(i, l, r);
    if (a <= l && r <= b) return node[i];

    int m = (l + r) >> 1;
    return max(get(i << 1, l, m, a, b), get(i << 1 | 1, m + 1, r, a, b));
}

int main(){
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &q);
        build_tree(1, 1, n);
        for (int i = 0; i<q; i++) {
            scanf("%d %d %d", &query[i].l, &query[i].r, &query[i].k);
        }

        sort(query, query + q);
        for (int i = 0; i<q; i++) {
            update(1, 1, n, query[i].l, query[i].r, query[i].k);
        }

        bool f = true;
        for (int i = 0; i<q; i++) {
            int res = get(1, 1, n, query[i].l, query[i].r);
            if (res != query[i].k) f = false;
        }

        if (f) printf("%d\n", 1);
        else printf("%d\n", 0);
    }
    return 0;
}
