#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector <pair <int, int> > g[N], v[N];
int n, one = 0, two = 0, a[N], b[N], ans = 0;
bool visited[N];

void dfs (int u, int val) {
    visited[u] = true;
    if (val) two++;
    else one++;

    for (auto v: g[u]) {
        if (!visited[v.first]) dfs(v.first, val ^ v.second);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) {
        v[a[i]].push_back(make_pair(i, 1));
        v[b[i]].push_back(make_pair(i, 2));
    }

    for (int i = 1; i <= N - 5; i++) {
        if (v[i].size() != 2) continue;
        if (v[i][0].second == v[i][1].second) {
            if (v[i][0].first != v[i][1].first) {
                g[v[i][0].first].push_back(make_pair(v[i][1].first, 1));
                g[v[i][1].first].push_back(make_pair(v[i][0].first, 1));
            }
        }
        else {
            if (v[i][0].first != v[i][1].first) {
                g[v[i][0].first].push_back(make_pair(v[i][1].first, 0));
                g[v[i][1].first].push_back(make_pair(v[i][0].first, 0));
            }
        }
    }

    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
            ans = ans + min(one, two);
            one = 0; two = 0;
        }
    }

    printf("%d", ans);
    return 0;
}
