#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, m;
set <int> st;
vector <int> g[N], ans;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) st.insert(i), g[i].push_back(0), g[i].push_back(n + 1);
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
    while (!st.empty()) {
        int res = 1;
        int root = *st.begin(); st.erase(st.begin());
        queue <int> q; q.push(root);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i + 1 < g[u].size(); i++) {
                int sta = g[u][i], fin = g[u][i + 1];
                auto it = st.upper_bound(sta);
                while (it != st.end() && (*it) < fin) {
                    q.push(*it);
                    it = st.erase(it);
                    res++;
                }
            }
        }

        ans.push_back(res);
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (auto i: ans) cout << i << " ";
    return 0;
}
