#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

struct Query {
    int u, v, a, b, id, type;
    Query (int u = 0, int v = 0, int a = 0, int b = 0, int id = 0, int type = 0): u(u), v(v), a(a), b(b), id(id), type(type) {}
};

int n, m, q, num[N], low[N], ans[N], cnt = 0;
vector <int> g[N];
vector <Query> queries[N];

bool check (int st, int en, int pos) {
    return (st <= pos && pos <= en);
}

pair <int, int> proc (vector <pair <int, int> > vec, int pos) {
    int cur = upper_bound(vec.begin(), vec.end(), make_pair(pos + 1, 0)) - vec.begin();
    if (cur == 0) return {-1, -1};
    cur--;
    if (vec[cur].second < pos) return {-1, -1};
    return vec[cur];
}

void dfs (int u, int p) {
    num[u] = low[u] = ++cnt;
    vector <pair <int, int> > vec;
    for (auto v: g[u]) {
        if (v == p) continue;
        if (num[v]) low[u] = min(low[u], num[v]);
        else {
            int st = cnt + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (num[u] <= low[v]) vec.push_back({st, cnt});
            if (num[v] == low[v]) {
                pair <int, int> cur = {min(u, v), max(u, v)};
                for (auto i: queries[u]) {
                    if (i.type == 1) {
                        if (cur == make_pair(i.a, i.b)) {
                            if (check(st, cnt, num[i.u]) != check(st, cnt, num[i.v])) ans[i.id] = true;
                        }
                    }
                }
            }
        }
    }

    sort(vec.begin(), vec.end());
    for (auto i: queries[u]) {
        if (i.type == 2) {
            if (proc(vec, num[i.u]) != proc(vec, num[i.v])) ans[i.id] = true;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int u, v, a, b;
            scanf("%d %d %d %d", &u, &v, &a, &b);
            if (a > b) swap(a, b);
            queries[a].push_back(Query(u, v, a, b, i, type));
            queries[b].push_back(Query(u, v, a, b, i, type));
        }
        else {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            queries[c].push_back(Query(u, v, c, c, i, type));
        }
    }

    dfs(1, 1);
    for (int i = 1; i <= q; i++) puts(!ans[i] ? "yes" : "no");
    return 0;
}
/*
13 15
1 2
2 3
3 5
2 4
4 6
2 6
1 4
1 7
7 8
7 9
7 10
8 11
8 12
9 12
12 13
5
1 5 13 1 2
1 6 2 1 4
1 13 6 7 8
2 13 6 7
2 13 6 8
*/
