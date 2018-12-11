#include <bits/stdc++.h>

using namespace std;

const int N = 8e5 + 5;

int n, q, a[N];

struct SegmentTree {
    int node[N << 2], lazy[N << 2];
    void init (int i, int l, int r) {
        if (l == r) {
            node[i] = lazy[i] = 0;
            return;
        }

        int mid = (l + r) >> 1;
        init(i << 1, l, mid);
        init(i << 1 | 1, mid + 1, r);
        node[i] = node[i << 1] + node[i << 1 | 1];
        lazy[i] = 0;
    }

    void dolazy (int i, int l, int r) {
        if (l > r) return;
        node[i] += lazy[i] * (r - l + 1);
        if (l != r) {
            lazy[i << 1] += lazy[i];
            lazy[i << 1 | 1] += lazy[i];
        }

        lazy[i] = 0;
    }

    void update (int i, int l, int r, int a, int b, int val) {
        dolazy(i, l, r);
        if (l > r || a > r || b < l) return;
        if (a <= l && r <= b) {
            node[i] += val * (r - l + 1);
            if (l != r) {
                lazy[i << 1] += val;
                lazy[i << 1 | 1] += val;
            }

            return;
        }

        int mid = (l + r) >> 1;
        update(i << 1, l, mid, a, b, val); update(i << 1 | 1, mid + 1, r, a, b, val);
        node[i] = node[i << 1] + node[i << 1 | 1];
    }

    int query (int i, int l, int r, int a, int b) {
        if (l > r || a > r || b < l) return 0;
        dolazy(i, l, r);
        if (a <= l && r <= b) return node[i];

        int mid = (l + r) >> 1;
        return query(i << 1, l, mid, a, b) + query(i << 1 | 1, mid + 1, r, a, b);
    }
} it;

vector <int> vec;
pair <int, int> queries[N];
int cnt = 0;
map <int, int> comp;

int readInt() {
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    #ifdef Futymy
        freopen("all.in", "r", stdin);
        freopen("all.out", "w", stdout);
    #endif // Futymy
    n = readInt(); q = readInt();
    for (int i = 1; i <= n; i++) a[i] = readInt();
    for (int i = 1; i <= q; i++) {
        int type;
        type = readInt();
        if (type == 1) {
            int x;
            x = readInt();
            queries[i] = {-1, x};
        }
        else {
            int c, d;
            c = readInt(); d = readInt();
            queries[i] = {c, d};
        }
    }

    for (int i = 0; i <= n; i++) vec.push_back(a[i]), vec.push_back(a[i] + 1);
    for (int i = 1; i <= q; i++) vec.push_back(queries[i].second), vec.push_back(queries[i].second + 1);
    sort(vec.begin(), vec.end()); vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    comp[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[i - 1]) comp[vec[i]] = ++cnt;
    it.init(1, 1, cnt);

    //for (auto i: vec) cout << i << " ";
    //cout << "\n";

    for (int i = 0; i < n; i++) it.update(1, 1, cnt, comp[a[i] + 1], comp[a[i + 1]], 1);
    for (int i = 1; i <= q; i++) {
        if (queries[i].first == -1) printf("%d\n", it.query(1, 1, cnt, comp[queries[i].second], comp[queries[i].second]));
        else {
            //for (int j = 1; j <= cnt; j++) cout << it.query(1, 1, cnt, j, j) << " ";
            //cout << "\n";
            if (queries[i].first < n) it.update(1, 1, cnt, comp[a[queries[i].first] + 1], comp[a[queries[i].first + 1]], -1);
            it.update(1, 1, cnt, comp[a[queries[i].first - 1] + 1], comp[a[queries[i].first]], -1);
            //cout << "POS " << comp[a[queries[i].first - 1] + 1] << " " << comp[a[queries[i].first]] << "\n";
            //for (int j = 1; j <= cnt; j++) cout << it.query(1, 1, cnt, j, j) << " "; cout << "\n";
            a[queries[i].first] = queries[i].second;
            it.update(1, 1, cnt, comp[a[queries[i].first - 1] + 1], comp[a[queries[i].first]], 1);
            //cout << "POS2 " << comp[a[queries[i].first - 1] + 1] << " " << comp[a[queries[i].first]] << "\n";
            //for (int j = 1; j <= cnt; j++) cout << it.query(1, 1, cnt, j, j) << " "; cout << "\n";
            if (queries[i].first < n) it.update(1, 1, cnt, comp[a[queries[i].first] + 1], comp[a[queries[i].first + 1]], 1);
            //cout << "POS3 " << comp[a[queries[i].first] + 1] << " " << comp[a[queries[i].first + 1]] << "\n";
            //for (int j = 1; j <= cnt; j++) cout << it.query(1, 1, cnt, j, j) << " ";
            //cout << "\n";
        }
    }
    return 0;
}
/*
3 10
934 587 780
2 1 697
2 3 327
2 2 640
2 1 454
2 1 663
2 3 381
2 2 199
2 1 714
2 2 976
1 267

3 3
934 587 780
1 267
2 1 714
1 267
*/
