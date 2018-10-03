#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, q, a[N];

struct seg {
    struct Node {
        int Min, Max;
    } node[4 * N];

    int lazy[4 * N];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i].Min = node[i].Max = a[l];
            lazy[i] = 0;
            return;
        }

        int m = (l + r) >> 1;
        init(i << 1, l, m);
        init(i << 1 | 1, m + 1, r);

        node[i].Min = min(node[i << 1].Min, node[i << 1 | 1].Min);
        node[i].Max = max(node[i << 1].Max, node[i << 1 | 1].Max);
        lazy[i] = 0;
    }

    void dolazy (int i, int l, int r) {
        if (lazy[i]) {
            node[i].Min += lazy[i];
            node[i].Max += lazy[i];
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
            node[i].Min += val;
            node[i].Max += val;
            if (l != r) {
                lazy[i << 1] += val;
                lazy[i << 1 | 1] += val;
            }

            return;
        }

        int m = (l + r) >> 1;
        update(i << 1, l, m, a, b, val);
        update(i << 1 | 1, m + 1, r, a, b, val);

        node[i].Min = min(node[i << 1].Min, node[i << 1 | 1].Min);
        node[i].Max = max(node[i << 1].Max, node[i << 1 | 1].Max);
    }

    int get_min (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return (int)2e9 + 2277;
        dolazy(i, l, r);
        if (a <= l && r <= b) return node[i].Min;

        int m = (l + r) >> 1;
        return min(get_min(i << 1, l, m, a, b), get_min(i << 1 | 1, m + 1, r, a, b));
    }

    int get_max (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        dolazy(i, l, r);
        if (a <= l && r <= b) return node[i].Max;

        int m = (l + r) >> 1;
        return max(get_max(i << 1, l, m, a, b), get_max(i << 1 | 1, m + 1, r, a, b));
    }

    int Find_min (int i, int l, int r, int val) {
        dolazy(i, l, r);
        if (l == r) {
            if (node[i].Min >= val) return l;
            return -1;
        }

        int m = (l + r) >> 1;
        int lef = get_max(1, 1, n, 1, m);
        if (lef >= val) return Find_min(i << 1, l, m, val);
        return Find_min(i << 1 | 1, m + 1, r, val);
    }

    int Find_max (int i, int l, int r, int val) {
        dolazy(i, l, r);
        if (l == r) {
            if (node[i].Max <= val) return l;
            return -1;
        }

        int m = (l + r) >> 1;
        int rig = get_min(1, 1, n, m + 1, n);
        if (rig <= val) return Find_max(i << 1 | 1, m + 1, r, val);
        return Find_max(i << 1, l, m, val);
    }
} it;

int main(){
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    it.init(1, 1, n);

    while (q--) {
        getchar();
        char c = getchar();
        int l, r;
        scanf("%d %d", &l, &r);

        if (c == 'F') {
            int pos = it.Find_min(1, 1, n, r);
            if (pos == -1) continue;
            if (pos + l - 1 >= n) {
                it.update(1, 1, n, pos, n, 1);
                continue;
            }

            int lastval = it.get_max(1, 1, n, pos, pos + l - 1);
            int lastpos = it.Find_min(1, 1, n, lastval);
            int nxtpos = it.Find_max(1, 1, n, lastval);
            int diff = lastpos - pos;

            it.update(1, 1, n, pos, lastpos - 1, 1);
            it.update(1, 1, n, nxtpos - (l - diff) + 1, nxtpos, 1);
        }
        else {
            int pos = it.Find_min(1, 1, n, l);
            int lastpos = it.Find_max(1, 1, n, r);

            if (pos == -1 || lastpos == -1) printf("%d\n", 0);
            else printf("%d\n", lastpos - pos + 1);
        }
    }
    return 0;
}

/*
5 7
1 3 2 5 2
F 2 1
C 3 6
F 2 3
C 6 8
F 2 1
F 2 2
C 3 5
*/
