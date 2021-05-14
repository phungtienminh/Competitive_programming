#include <bits/stdc++.h>

using namespace std;

const int N = 5005;
vector <int> g[N], depth[N], buff, pre[N];

void dfs (int u, int p, int root, int depth, int subtree) {
    pre[depth].push_back(subtree);
    for (int i = 0; i<g[u].size(); i++) {
        int v = g[u][i];
        if (v == p || v == root) continue;

        dfs(v, u, root, depth + 1, subtree);
    }
}

long long calc (vector <int> v) {
    long long ans = 0;
    long long res = 0;
    long long sum = 0;

    for (int i = 0; i<v.size(); i++) {
        ans = ans + res * v[i];
        res = res + sum * v[i];
        sum = sum + v[i];
    }

    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i<n-1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    long long ans = 0;
    for (int i = 1; i<=n; i++) {
        for (int j = 0; j<=n; j++) pre[j].clear();
        for (int j = 0; j<g[i].size(); j++) {
            dfs(g[i][j], -1, i, 1, j);
        }

        for (int j = 0; j<=n; j++) {
            if (!pre[j].empty()) {
                sort(pre[j].begin(), pre[j].end());

                int l = 0;
                int r = 0;
                int k = 0;

                while (k < pre[j].size()) {
                    k = r + 1;
                    r++;
                    for (; k<pre[j].size(); k++) {
                        if (pre[j][k] == pre[j][l]) r++;
                        else break;
                    }

                    buff.push_back(r - l);
                    l = r;
                }

                ans += calc(buff);
                buff.clear();
            }
        }
    }

    printf("%lld", ans);
    return 0;
}
