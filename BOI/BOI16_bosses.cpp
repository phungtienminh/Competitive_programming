#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 5;

vector <int> g[N];
bool visited[N];
int val[N], n, ans = 1e9;

void bfs (int s) {
    queue <int> q; q.push(s); visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                val[v] = val[u] + 1;
            }
        }
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int num; scanf("%d", &num);
        for (int j = 0; j < num; j++) {
            int v; scanf("%d", &v);
            g[v].push_back(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        memset(visited, 0, sizeof(visited));
        val[i] = 1;
        bool f = true;

        bfs(i);

        for (int j = 1; j <= n; j++) {
            if (!visited[j]) {
                f = false;
                break;
            }
        }

        if (!f) continue;

        int sum = 0;
        for (int j = 1; j <= n; j++) sum += val[j];
        ans = min(ans, sum);
    }

    printf("%d", ans);
    return 0;
}
