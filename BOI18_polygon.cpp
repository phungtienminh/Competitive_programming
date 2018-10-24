#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, deg[N], nxt[N], ans = 0, res = 0, cnt = 0;
map <string, int> mm;
vector <int> g[N];
stack <int> st;
bool used[N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s, t;
        cin >> s >> t;
        if (!mm.count(s)) mm[s] = ++cnt;
        if (!mm.count(t)) mm[t] = ++cnt;
        g[mm[s]].push_back(mm[t]);
        deg[mm[t]]++;
        nxt[mm[s]] = mm[t];
    }

    if (n & 1) return cout << -1, 0;
    for (int i = 1; i <= n; i++) if (!used[i] && nxt[i] != i && nxt[nxt[i]] == i) used[i] = used[nxt[i]] = true;
    for (int i = 1; i <= n; i++) if (!deg[i] && !used[i]) st.push(i);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (used[nxt[u]]) {
            nxt[u] = u;
            continue;
        }

        ans++;
        used[u] = used[nxt[u]] = true;
        if (!used[nxt[nxt[u]]]) {
            deg[nxt[nxt[u]]]--;
            if (!deg[nxt[nxt[u]]]) st.push(nxt[nxt[u]]);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        int cur = 1;
        for (int v = nxt[i]; v != i; v = nxt[v]) {
            used[v] = true;
            cur++;
        }

        if (cur & 1) res++;
        ans += cur / 2;
    }

    ans += res;
    cout << ans;
    return 0;
}
