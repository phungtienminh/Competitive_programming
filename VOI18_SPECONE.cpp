#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, k, s, m, cnt = 0, deg[N];
map <string, int> mm;
map <int, string> names;
map <pair <int, int>, int> edge;
vector <int > g[N];

int main(){
    #ifndef Futymy
        freopen("specone.inp", "r", stdin);
        freopen("specone.out", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k >> s >> m;
    for (int i = 1; i <= n; i++) deg[i] = k;
    for (int i = 1; i <= s; i++) {
        string cur;
        cin >> cur;
        if (!mm.count(cur)) mm[cur] = ++cnt, names[cnt] = cur;
    }

    for (int i = 1; i <= cnt; i++) deg[i] = 0;
    for (int i = 1; i <= m; i++) {
        string curu, curv;
        cin >> curu >> curv;
        if (!mm.count(curu)) mm[curu] = ++cnt, names[cnt] = curu;
        if (!mm.count(curv)) mm[curv] = ++cnt, names[cnt] = curv;
        int u = mm[curu], v = mm[curv];
        if (!edge.count({u, v})) {
            edge[{u, v}] = edge[{v, u}] = 1;
            g[u].push_back(v); g[v].push_back(u);
        }
    }

    vector <string> ans;
    queue <int> q;
    for (int i = 1; i <= s; i++) {
        q.push(i);
        ans.push_back(names[i]);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: g[u]) {
            if (deg[v] == 0) continue;
            if (--deg[v] == 0) {
                q.push(v);
                ans.push_back(names[v]);
            }
        }
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto i: ans) cout << i << " ";
    return 0;
}
