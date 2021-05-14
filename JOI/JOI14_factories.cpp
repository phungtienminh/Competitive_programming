#include <bits/stdc++.h>
#include "factories.h"

using namespace std;

const int N = 5e5 + 5;
vector <pair <int, int> > g[N];
int h[N], child[N], par[N];
bool visited[N];
long long dist[20][N], ans[N];

void dfs (int u, int p) {
    child[u] = 1;
    for (auto v: g[u]) {
        if (v.first != p && !visited[v.first]) {
            dfs(v.first, u);
            child[u] += child[v.first];
        }
    }
}

int findcen (int u, int p, int sz) {
    for (auto v: g[u]) {
        if (v.first != p && !visited[v.first] && child[v.first] >= sz / 2) return findcen(v.first, u, sz);
    }

    return u;
}

void redfs (int level, int u, int p, int cost) {
    if (p != -1) dist[level][u] = dist[level][p] + cost;
    for (auto v: g[u]) {
        if (v.first != p && !visited[v.first]) {
            redfs(level, v.first, u, v.second);
        }
    }
}

void centroid (int root, int p) {
    dfs(root, -1);
    int cen = findcen(root, -1, child[root]);
    visited[cen] = true; par[cen] = p;
    if (p != -1) h[cen] = h[p] + 1;

    redfs(h[cen], cen, -1, 0);
    for (auto v: g[cen]) if (v.first != p && !visited[v.first]) centroid(v.first, cen);
}

void update (int u) {
    for (int v = u; v != -1; v = par[v])
        ans[v] = min(ans[v], dist[h[v]][u]);
}

long long query (int u) {
    long long res = 1e18;
    for (int v = u; v != -1; v = par[v])
        res = min(res, ans[v] + dist[h[v]][u]);

    return res;
}

void Init (int N, int A[], int B[], int D[]) {
    for (int i = 0; i < N - 1; i++) {
        g[A[i]].push_back(make_pair(B[i], D[i]));
        g[B[i]].push_back(make_pair(A[i], D[i]));
    }

    for (int i = 0; i < N; i++) ans[i] = 1e18;
    centroid(0, -1);
}

long long Query (int S, int X[], int T, int Y[]) {
    if (S < T) {
        for (int i = 0; i < S; i++) update(X[i]);
        long long res = 1e18;
        for (int i = 0; i < T; i++) res = min(res, query(Y[i]));
        for (int i = 0; i < S; i++)
            for (int v = X[i]; v != -1; v = par[v])
                ans[v] = 1e18;

        return res;
    }
    else {
        for (int i = 0; i < T; i++) update(Y[i]);
        long long res = 1e18;
        for (int i = 0; i < S; i++) res = min(res, query(X[i]));
        for (int i = 0; i < T; i++)
            for (int v = Y[i]; v != -1; v = par[v])
                ans[v] = 1e18;

        return res;
    }
}
