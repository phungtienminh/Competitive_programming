#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

vector <int> g[N];
int a, b, deg[N], curdeg[N], ans[N], color[N];
queue <int> q;

int main(){
    scanf("%d %d", &a, &b);
    for (int i = 1; i <= a + b; i++) {
        int num;
        scanf("%d %d", &color[i], &num);
        for (int j = 0; j < num; j++) {
            int v; scanf("%d", &v);
            g[v].push_back(i);
        }
        deg[i] = num;
    }

    while (1) {
        bool ok = true;
        for (int i = 1; i <= a + b; i++) {
            if (color[i]) ans[i] = 1, q.push(i);
            else ans[i] = 0;
            curdeg[i] = deg[i];
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v: g[u]) {
                curdeg[v]--;
                if (ans[v]) continue;
                bool f = false;
                if (v <= a) f = true;
                else if (curdeg[v] == 0) f = true;

                if (f) {
                    ans[v] = 1;
                    q.push(v);
                }
            }
        }

        for (int i = 1; i <= a + b; i++) {
            if (!color[i]) continue;
            if (i <= a && curdeg[i] == deg[i]) ok = false, color[i] = 0;
            else if (i > a && curdeg[i] > 0) ok = false, color[i] = 0;
        }

        if (ok) break;
    }

    int res = 0;
    for (int i = 1; i <= a + b; i++) res += ans[i];
    printf("%d\n", res);
    for (int i = 1; i <= a + b; i++) if (ans[i]) printf("%d\n", i);
    return 0;
}
