#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], nxt[N], ans = 0;
vector <int> g[N];
bool visited[N], instack[N];

void dfs (int u) {
    visited[u] = instack[u] = true;
    for (auto v: g[u]) {
        if (!visited[v]) dfs(v);
        else if (instack[v]) {
            int cur = nxt[v]; ans++;
            while (cur != v) {
                ans++;
                cur = nxt[cur];
            }
        }
    }

    instack[u] = false;
}

int main(){
    #ifndef Futymy
        freopen("shuffle.in", "r", stdin);
        freopen("shuffle.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), g[i].push_back(a[i]), nxt[i] = a[i];
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
    printf("%d", ans);
    return 0;
}
/*
9
4 3 4 8 2 4 5 3 5
*/
