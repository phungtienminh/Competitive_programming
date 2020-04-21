#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int inf = (int)1e9;

int n, q;

struct Point {
    int x, y;
} p[N];

int dist (Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

struct SegmentTree {
    struct Node {
        int sum, mincut, lef1, lef2, rig1, rig2;
        Node (int sum = 0, int mincut = inf, int lef1 = 0, int lef2 = 0, int rig1 = 0, int rig2 = 0):
            sum(sum), mincut(mincut), lef1(lef1), lef2(lef2), rig1(rig1), rig2(rig2) {}
    } node[N << 2];

    void init (int i, int l, int r) {
        if (l == r) {
            node[i].sum = 0;
            node[i].mincut = inf;
            node[i].lef1 = node[i].lef2 = node[i].rig1 = node[i].rig2 = l;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i].lef1 = l;
        node[i].lef2 = l + 1;
        node[i].rig1 = r;
        node[i].rig2 = r - 1;
        node[i].mincut = min(node[i << 1].mincut, node[i << 1 | 1].mincut);
        node[i].mincut = min(node[i].mincut, dist(p[node[i << 1].rig2], p[node[i << 1 | 1].lef1])
                                            - dist(p[node[i << 1].rig2], p[node[i << 1].rig1])
                                            - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));
        node[i].mincut = min(node[i].mincut, dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef2])
                                            - dist(p[node[i << 1 | 1].lef2], p[node[i << 1 | 1].lef1])
                                            - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));

        if (l + 1 == r) node[i].mincut = inf;

        node[i].sum = node[i << 1].sum + node[i << 1 | 1].sum + dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]);
    }

    void update (int i, int l, int r, int pos, int x, int y) {
        if (l == r) {
            p[pos] = {x, y};
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos, x, y);
        else update(i << 1 | 1, mid + 1, r, pos, x, y);
        node[i].lef1 = l;
        node[i].lef2 = l + 1;
        node[i].rig1 = r;
        node[i].rig2 = r - 1;
        node[i].mincut = min(node[i << 1].mincut, node[i << 1 | 1].mincut);
        node[i].mincut = min(node[i].mincut, dist(p[node[i << 1].rig2], p[node[i << 1 | 1].lef1])
                                            - dist(p[node[i << 1].rig2], p[node[i << 1].rig1])
                                            - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));
        node[i].mincut = min(node[i].mincut, dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef2])
                                            - dist(p[node[i << 1 | 1].lef2], p[node[i << 1 | 1].lef1])
                                            - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));

        if (l + 1 == r) node[i].mincut = inf;

        node[i].sum = node[i << 1].sum + node[i << 1 | 1].sum + dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]);
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        if (a <= l && r <= b) return node[i].sum;
        int mid = l + r >> 1;
        int lef = query(i << 1, l, mid, a, b);
        int rig = query(i << 1 | 1, mid + 1, r, a, b);

        bool ok = true;
        if (l > mid || a > mid || b < l) ok = false;
        if (mid + 1 > r || a > r || b < mid + 1) ok = false;

        int buff = 0;
        if (ok) buff = dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]);
        return lef + rig + buff;
    }

    int query_min (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return inf;
        if (a <= l && r <= b) return node[i].mincut;

        int mid = l + r >> 1;
        int lef = query_min(i << 1, l, mid, a, b);
        int rig = query_min(i << 1 | 1, mid + 1, r, a, b);
        int buff = inf;

        bool ok = true;
        if (l == mid) ok = false;
        if (mid + 1 == r) ok = false;
        if (l > mid || a > mid || b < l) ok = false;
        if (mid + 1 > r || a > r || b < mid + 1) ok = false;

        if (ok) {
            if (node[i << 1].rig2 >= a && node[i << 1].rig2 <= b &&
                node[i << 1].rig1 >= a && node[i << 1].rig1 <= b &&
                node[i << 1 | 1].lef1 >= a && node[i << 1 | 1].lef1 <= b) {
                buff = min(buff, dist(p[node[i << 1].rig2], p[node[i << 1 | 1].lef1])
                                                - dist(p[node[i << 1].rig2], p[node[i << 1].rig1])
                                                - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));
            }

            if (node[i << 1 | 1].lef2 >= a && node[i << 1 | 1].lef2 <= b &&
                node[i << 1].rig1 >= a && node[i << 1].rig1 <= b &&
                node[i << 1 | 1].lef1 >= a && node[i << 1 | 1].lef1 <= b) {
                buff = min(buff, dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef2])
                                            - dist(p[node[i << 1 | 1].lef2], p[node[i << 1 | 1].lef1])
                                            - dist(p[node[i << 1].rig1], p[node[i << 1 | 1].lef1]));
            }
        }

        return min(buff, min(lef, rig));
    }
} it;

int main(){
    #ifndef Futymy
        freopen("marathon.in", "r", stdin);
        freopen("marathon.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;
    it.init(1, 1, n);

    while (q--) {
        char c;
        cin >> c;
        if (c == 'U') {
            int pos, x, y;
            cin >> pos >> x >> y;
            it.update(1, 1, n, pos, x, y);
        }
        else {
            int a, b;
            cin >> a >> b;
            //it.query_min(1, 1, n, a, b);
            //cout << it.query(1, 1, n, a, b) << " " << it.query_min(1, 1, n, a, b) << "\n";
            if (a == b || a + 1 == b) cout << it.query(1, 1, n, a, b) << "\n";
            else cout << it.query(1, 1, n, a, b) + it.query_min(1, 1, n, a, b) << "\n";
        }
    }
    return 0;
}
/*
5 7
-4 4
-5 -3
-1 5
-3 4
0 5
Q 1 5
U 4 0 1
U 4 -1 1
Q 2 4
Q 1 4
Q 3 4
Q 4 4
*/
