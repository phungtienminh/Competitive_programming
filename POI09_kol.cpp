#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 6e4 + 5;

int c, s, q, node[4 * N], lazy[4 * N];

void init (int i, int l, int r) {
    if (l > r) return;
    if (l == r) {
        node[i] = lazy[i] = 0;
        return;
    }

    lazy[i] = 0;
    int m = (l + r) >> 1;
    init(i << 1, l, m);
    init(i << 1 | 1, m + 1, r);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

void dolazy (int i, int l, int r) {
    if (lazy[i]) {
        node[i] += lazy[i];
        if (l != r) {
            lazy[i << 1] += lazy[i];
            lazy[i << 1 | 1] += lazy[i];
        }
        lazy[i] = 0;
    }
}

void update (int i, int l, int r, int a, int b, int val) {
    dolazy(i, l, r);
    if (l > r || a > r || b < l) return;
    if (a <= l && r <= b) {
        node[i] += val;
        if (l != r) {
            lazy[i << 1] += val;
            lazy[i << 1 | 1] += val;
        }

        return;
    }

    int m = (l + r) >> 1;
    update(i << 1, l, m, a, b, val);
    update(i << 1 | 1, m + 1, r, a, b, val);

    node[i] = max(node[i << 1], node[i << 1 | 1]);
}

int get (int i, int l, int r, int a, int b) {
    if (l > r || a > r || b < l) return 0;
    dolazy(i, l, r);

    if (a <= l && r <= b) return node[i];
    int m = (l + r) >> 1;
    return max(get(i << 1, l, m, a, b), get(i << 1 | 1, m + 1, r, a, b));
}

signed main(){
    scanf("%lld %lld %lld", &c, &s, &q);
    init(1, 1, c);

    while (q--) {
        int l, r, val;
        scanf("%lld %lld %lld", &l, &r, &val);
        if (get(1, 1, c, l, r - 1) + val <= s) {
            update(1, 1, c, l, r - 1, val);
            puts("T");
        }
        else puts("N");
    }
    return 0;
}
