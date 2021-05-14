#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

int n, k;
pair <int, int> a[N];

struct seg {
    int node[N << 2], lazy[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = 1;
            lazy[i] = 0;
            return;
        }

        int m = (l + r) >> 1;
        init(i << 1, l, m);
        init(i << 1 | 1, m + 1, r);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void dolazy (int i, int l, int r) {
        if (lazy[i]) {
            node[i] = lazy[i] * (r - l + 1);
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
            node[i] = val * (r - l + 1);
            if (l != r) {
                lazy[i << 1] = val;
                lazy[i << 1 | 1] = val;
            }

            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, a, b, val);
        update(i << 1 | 1, m + 1, r, a, b, val);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    int get (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        dolazy(i, l, r);
        if (a <= l && r <= b) return node[i];

        int m = (l + r) >> 1;
        return get(i << 1, l, m, a, b) + get(i << 1 | 1, m + 1, r, a, b);
    }
} it;

int dist (pair <int, int> x) {
    return min(max(x.first, x.second) - min(x.first, x.second), min(x.first, x.second) + n - max(x.first, x.second));
}

bool cmp (pair <int, int> p1, pair <int, int> p2) {
    return dist(p1) < dist(p2);
}

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) scanf("%d %d", &a[i].first, &a[i].second);
    sort(a + 1, a + k + 1, cmp); it.init(1, 1, n);
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        int curd = dist(a[i]);
        int d1 = max(a[i].first, a[i].second) - min(a[i].first, a[i].second);
        int d2 = min(a[i].first, a[i].second) + n - max(a[i].first, a[i].second);
        if (d1 == curd) {
            ans = max(ans, it.get(1, 1, n, min(a[i].first, a[i].second), max(a[i].first, a[i].second)));
            it.update(1, 1, n, min(a[i].first, a[i].second) + 1, max(a[i].first, a[i].second) - 1, 0);
        }
        else {
            int cur = it.get(1, 1, n, max(a[i].first, a[i].second), n) + it.get(1, 1, n, 1, min(a[i].first, a[i].second));
            ans = max(ans, cur);
            it.update(1, 1, n, max(a[i].first, a[i].second) + 1, n, 0);
            it.update(1, 1, n, 1, min(a[i].first, a[i].second) - 1, 0);
        }

        if (i == k) {
            ans = max(ans, it.get(1, 1, n, min(a[i].first, a[i].second), max(a[i].first, a[i].second)));
            ans = max(ans, it.get(1, 1, n, max(a[i].first, a[i].second), n) + it.get(1, 1, n, 1, min(a[i].first, a[i].second)));
        }
    }

    printf("%d", ans);
    return 0;
}
