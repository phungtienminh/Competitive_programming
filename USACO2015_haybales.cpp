#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, q, a[N];

struct SegmentTree {
    struct Node {
        long long sum, Min, lz;
        Node (long long sum = 0, long long Min = 0, long long lz = 0): sum(sum), Min(Min), lz(lz) {}
        Node operator + (const Node &rhs) const {
            return Node(sum + rhs.sum, min(Min, rhs.Min), lz);
        }
    } node[N << 2];

    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = Node(a[l], a[l], 0);
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void push (int i, int l, int r) {
        if (node[i].lz) {
            node[i].sum += 1LL * (r - l + 1) * node[i].lz;
            node[i].Min += node[i].lz;
            if (l != r) {
                node[i << 1].lz += node[i].lz;
                node[i << 1 | 1].lz += node[i].lz;
            }

            node[i].lz = 0;
        }
    }

    void update (int i, int l, int r, int a, int b, int val) {
        push(i, l, r);
        if (l > r || a > r || b < l) return;
        if (a <= l && r <= b) {
            node[i].sum += 1LL * (r - l + 1) * val;
            node[i].Min += val;
            if (l != r) {
                node[i << 1].lz += val;
                node[i << 1 | 1].lz += val;
            }

            return;
        }

        int mid = l + r >> 1;
        update(i << 1, l, mid, a, b, val);
        update(i << 1 | 1, mid + 1, r, a, b, val);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    long long query_sum (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        push(i, l, r);
        if (a <= l && r <= b) return node[i].sum;

        int mid = l + r >> 1;
        return query_sum(i << 1, l, mid, a, b) + query_sum(i << 1 | 1, mid + 1, r, a, b);
    }

    long long query_min (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return (long long)1e18;
        push(i, l, r);
        if (a <= l && r <= b) return node[i].Min;

        int mid = l + r >> 1;
        return min(query_min(i << 1, l, mid, a, b), query_min(i << 1 | 1, mid + 1, r, a, b));
    }
} it;

int main(){
    #ifndef Futymy
        freopen("haybales.in", "r", stdin);
        freopen("haybales.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    it.init(1, 1, n);

    while (q--) {
        char c;
        cin >> c;
        if (c == 'P') {
            int x, y, z;
            cin >> x >> y >> z;
            it.update(1, 1, n, x, y, z);
        }
        else {
            int x, y;
            cin >> x >> y;
            if (c == 'M') cout << it.query_min(1, 1, n, x, y) << "\n";
            else cout << it.query_sum(1, 1, n, x, y) << "\n";
        }
    }
    return 0;
}
