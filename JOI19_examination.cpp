#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, q, ans[N], cnt = 0;
map <int, int> compress;
vector <int> vecm, veci;

struct data {
    int math, infor, sum;
    bool operator < (const data &rhs) const {
        return sum > rhs.sum;
    }
} a[N];

struct Query {
    int a, b, c, id;
    bool operator < (const Query &rhs) const {
        return c > rhs.c;
    }
} queries[N];

struct DynamicIT {
    int s, e, mid, sum;
    DynamicIT *l, *r;
    DynamicIT (int _s, int _e) {
        s = _s; e = _e; mid = (s + e) / 2; sum = 0;
        l = r = NULL;
    }

    void update (int pos) {
        if (s == e) {
            sum++;
            return;
        }

        if (pos <= mid) {
            if (l == NULL) l = new DynamicIT(s, mid);
            l -> update(pos);
        }
        else {
            if (r == NULL) r = new DynamicIT(mid + 1, e);
            r -> update(pos);
        }

        sum = 0;
        if (l != NULL) sum += l -> sum;
        if (r != NULL) sum += r -> sum;
    }

    int query (int Start, int End) {
        if (Start > e || End < s) return 0;
        if (Start <= s && e <= End) return sum;

        int res = 0;
        if (l != NULL) res += l -> query(Start, End);
        if (r != NULL) res += r -> query(Start, End);
        return res;
    }
};

DynamicIT* bit[N];

void update (int x, int y) {
    for (int i = x; i > 0; i -= i & -i) bit[i] -> update(y);
}

int get_value (int x, int y) {
    int ans = 0;
    for (int i = x; i < N; i += i & -i) ans += bit[i] -> query(y, N);
    return ans;
}

int main(){
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i].math, &a[i].infor);
        a[i].sum = a[i].math + a[i].infor;
        vecm.push_back(a[i].math);
        veci.push_back(a[i].infor);
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d %d %d", &queries[i].a, &queries[i].b, &queries[i].c);
        queries[i].id = i;
        vecm.push_back(queries[i].a);
        veci.push_back(queries[i].b);
    }

    sort(a + 1, a + n + 1);
    sort(queries + 1, queries + q + 1);
    sort(vecm.begin(), vecm.end());
    sort(veci.begin(), veci.end());

    //Compress coordinate
    compress[vecm[0]] = ++cnt;
    for (int i = 1; i < vecm.size(); i++) if (vecm[i] > vecm[i - 1]) compress[vecm[i]] = ++cnt;
    for (int i = 1; i <= n; i++) a[i].math = compress[a[i].math];
    for (int i = 1; i <= q; i++) queries[i].a = compress[queries[i].a];

    cnt = 0; compress.clear();
    compress[veci[0]] = ++cnt;
    for (int i = 1; i < veci.size(); i++) if (veci[i] > veci[i - 1]) compress[veci[i]] = ++cnt;
    for (int i = 1; i <= n; i++) a[i].infor = compress[a[i].infor];
    for (int i = 1; i <= q; i++) queries[i].b = compress[queries[i].b];
    //

    for (int i = 1; i < N; i++) bit[i] = new DynamicIT(1, N);

    int ptr = 1;
    for (int i = 1; i <= q; i++) {
        while (ptr <= n && a[ptr].sum >= queries[i].c) {
            update(a[ptr].math, a[ptr].infor);
            ptr++;
        }

        ans[queries[i].id] = get_value(queries[i].a, queries[i].b);
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
