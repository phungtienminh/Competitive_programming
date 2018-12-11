#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 5;

struct dolls {
    int x, y;
    dolls (int x = 0, int y = 0): x(x), y(y) {}
    bool operator < (const dolls &rhs) const {
        if (x != rhs.x) return x > rhs.x;
        return y < rhs.y;
    }
} a[N];

struct query {
    int x, y, id;
    query (int x = 0, int y = 0, int id = 0): x(x), y(y), id(id) {}
    bool operator < (const query &rhs) const {
        if (x != rhs.x) return x > rhs.x;
        return y < rhs.y;
    }
} b[N];

int n, q;

struct fenwick {
    int fenw[N];
    void update (int x, int val) {
        for (int i = x; i < N; i += i & -i) fenw[i] = max(fenw[i], val);
    }

    int get (int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= i & -i) ans = max(ans, fenw[i]);
        return ans;
    }
} bit[2];

int readInt(){
    char c;
    int ans = 0;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int ans[N], cnt = 0;
map <int, int> comp;
vector <int> vec;

int main(){
    n = readInt(); q = readInt();
    for (int i = 1; i <= n; i++) a[i].x = readInt(), a[i].y = readInt(), vec.push_back(a[i].y);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= q; i++) {
        b[i].x = readInt(), b[i].y = readInt(); b[i].id = i;
        vec.push_back(b[i].y);
    }

    sort(b + 1, b + q + 1);
    sort(vec.begin(), vec.end());
    comp[vec[0]] = ++cnt;
    for (int i = 1; i < vec.size(); i++) if (vec[i] > vec[i - 1]) comp[vec[i]] = ++cnt;

    int ptr = 1;
    for (int i = 1; i <= q; i++) {
        while (ptr <= n && a[ptr].x >= b[i].x) {
            int val = 1 + bit[0].get(comp[a[ptr].y]);
            bit[0].update(comp[a[ptr].y], val);
            bit[1].update(comp[a[ptr].y], val);
            ptr++;
        }

        ans[b[i].id] = bit[1].get(comp[b[i].y]);
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}
/*
7 3
9 5
3 7
10 6
5 10
2 6
10 10
4 1
10 5
3 5
3 9
*/
