#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, s, d, a, b, ans1 = 0, ans2 = 0, d1[N], d2[N], d3[N], d4[N];
vector <int> g[N];

void bfs1(){
    memset(d1, 0x3f, sizeof(d1)); queue <int> q;
    d1[a] = 0; q.push(a);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (d1[v] > 1e9) {
                d1[v] = d1[u] + 1;
                q.push(v);
            }
        }
    }
}

void bfs2(){
    memset(d2, 0x3f, sizeof(d2)); queue <int> q;
    d2[b] = 0; q.push(b);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (d2[v] > 1e9) {
                d2[v] = d2[u] + 1;
                q.push(v);
            }
        }
    }
}

void bfs3(){
    memset(d3, 0x3f, sizeof(d3));
    queue <int> q; q.push(s); d3[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans1 = max(ans1, d3[u]);
        for (auto v: g[u]) {
            if (d3[v] > 1e9 && (d1[v] == d1[u] - 1 && d2[v] == d2[u] - 1)) {
                d3[v] = d3[u] + 1;
                q.push(v);
            }
        }
    }
}

void bfs4(){
    memset(d4, 0x3f, sizeof(d4));
    queue <int> q; q.push(d); d4[d] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans2 = max(ans2, d4[u]);
        for (auto v: g[u]) {
            if (d4[v] > 1e9 && (d1[v] == d1[u] - 1 && d2[v] == d2[u] - 1)) {
                d4[v] = d4[u] + 1;
                q.push(v);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &s, &d, &a, &b);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    bfs1(); bfs2();
    if (d1[d] - d1[s] != d2[d] - d2[s]) printf("%d", max(min(d1[d] - d1[s], d2[d] - d2[s]), -1));
    else {
        bfs3(); bfs4();
        printf("%d", max(d1[d] - d1[s] - ((d1[d] - d1[s] + ans1) < ans2), -1));
    }
    return 0;
}
/*
6 6
1 2 3 4
1 5
5 6
6 3
6 4
1 2
3 4

6 7
5 6 1 2
6 3
1 2
1 3
2 3
1 5
2 4
5 4
*/
