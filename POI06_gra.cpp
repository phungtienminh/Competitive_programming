#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

map <pair <int, int>, int> mm;
int n, deg[N], d[N], dp[N], odd = 0;
vector <int> g[N];

int readInt(){
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + c - '0';
    }
}

void bfs (int s) {
    memset(d, 0x3f, sizeof(d)); d[s] = 0;
    queue <int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

void dfs (int u, int p) {
    dp[u] = 1;
    for (auto v: g[u]) {
        if (v == p) continue;
        if (d[v] != d[u] + 1) continue;
        dfs(v, u);
        dp[u] += dp[v];
    }
}

int main(){
    n = readInt();
    for (int i = 1; i <= n - 2; i++) {
        int a, b, c;
        a = readInt(); b = readInt(); c = readInt();
        if (!mm.count({min(a, b), max(a, b)})) mm[{min(a, b), max(a, b)}] = i;
        else {
            int cur = mm[{min(a, b), max(a, b)}];
            g[cur].push_back(i); g[i].push_back(cur);
            deg[cur]++; deg[i]++;
        }

        if (!mm.count({min(a, c), max(a, c)})) mm[{min(a, c), max(a, c)}] = i;
        else {
            int cur = mm[{min(a, c), max(a, c)}];
            g[cur].push_back(i); g[i].push_back(cur);
            deg[cur]++; deg[i]++;
        }

        if (!mm.count({min(b, c), max(b, c)})) mm[{min(b, c), max(b, c)}] = i;
        else {
            int cur = mm[{min(b, c), max(b, c)}];
            g[cur].push_back(i); g[i].push_back(cur);
            deg[cur]++; deg[i]++;
        }
    }

    if (deg[1] == 1) return !printf("TAK");
    bfs(1);
    dfs(1, 1);
    for (auto v: g[1]) odd += (dp[v] % 2 == 1);
    printf(odd % 2 == 0 ? "NIE" : "TAK");
    return 0;
}
