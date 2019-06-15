#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, q;

int readInt(){
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

struct SegmentTree {
    int node[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = 1e9 + 2277;
            return;
        }

        int mid = l + r >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
    }

    void update (int i, int l, int r, int pos, int val) {
        if (l == r) {
            node[i] = val;
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid) update(i << 1, l, mid, pos, val);
        else update(i << 1 | 1, mid + 1, r, pos, val);
        node[i] = min(node[i << 1], node[i << 1 | 1]);
    }

    int Find (int i, int l, int r, int a, int b, int val) {
        if (l > r || a > r || b < l) return -1;
        if (l == r) {
            if (node[i] <= val) return l;
            return -1;
        }

        if (a <= l && r <= b) {
            if (node[i] > val) return -1;
        }

        int mid = l + r >> 1;
        int res = Find(i << 1, l, mid, a, b, val);
        if (res != -1) return res;
        return Find(i << 1 | 1, mid + 1, r, a, b, val);
    }
} it;

int main(){
    n = readInt(); q = readInt(); it.init(1, 1, n);
    for (int i = 1; i <= q; i++) {
        char c;
        c = getchar(); getchar();

        if (c == 'M') {
            int x, a;
            x = readInt(); a = readInt();
            it.update(1, 1, n, a, x);
        }
        else {
            int y, b;
            y = readInt(); b = readInt();
            printf("%d\n", it.Find(1, 1, n, b, n, y));
        }
    }
    return 0;
}
