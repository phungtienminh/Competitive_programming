#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, k, d;

struct SegmentTree {
    struct Node {
        long long left, right, val, sum;
    } node[4 * N];

    Node combine (Node l, Node r) {
        Node ans;
        ans.sum = l.sum + r.sum;
        ans.left = max(l.left, l.sum + r.left);
        ans.right = max(r.right, l.right + r.sum);
        ans.val = max(max(l.val, r.val), l.right + r.left);
        return ans;
    }

    void init (int i, int l, int r, int k) {
        if (l > r) return;
        if (l == r) {
            node[i] = {0, 0, 0, -k};
            return;
        }

        int m = (l + r) >> 1;
        init(i << 1, l, m, k);
        init(i << 1 | 1, m + 1, r, k);

        node[i] = combine(node[i << 1], node[i << 1 | 1]);
    }

    void update (int i, int l, int r, int pos, int val) {
        if (l > r || pos > r || pos < l) return;
        if (l == r) {
            if (l == pos) {
                node[i].sum += val;
                node[i].left = node[i].right = node[i].val = max(0LL, node[i].sum);
            }

            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, pos, val);
        update(i << 1 | 1, m + 1, r, pos, val);

        node[i] = combine(node[i << 1], node[i << 1 | 1]);
    }

    long long query() {
        return node[1].val;
    }
} it;

void input(){
    scanf("%d %d %d %d", &n, &m, &k, &d);
}

void solve(){
    it.init(1, 1, n, k);
    while (m--) {
        int pos, val;
        scanf("%d %d", &pos, &val);
        it.update(1, 1, n, pos, val);
        puts(it.query() <= 1LL * k * d ? "TAK" : "NIE");
    }
}

int main(){
    input();
    solve();
    return 0;
}
