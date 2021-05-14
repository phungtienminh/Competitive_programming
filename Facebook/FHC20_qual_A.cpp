#include <bits/stdc++.h>

using namespace std;

const int N = 55;

int T, n, ans[N][N];
string s, t;
vector <int> g[N];
bool visited[N];

void dfs (int u) {
    visited[u] = true;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!visited[v]) dfs(v);
    }
}

void solve (int test) {
    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) g[i].clear();
    memset(visited, 0, sizeof(visited));
    memset(ans, 0, sizeof(ans));

    for (int i = 0; i < n - 1; i++) {
        if (t[i] == 'Y' && s[i + 1] == 'Y') {
            g[i].push_back(i + 1);
        }
        if (t[i + 1] == 'Y' && s[i] == 'Y') {
            g[i + 1].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i);
        for (int j = 0; j < n; j++) {
            if (visited[j]) {
                ans[i][j] = 1;
            }
        }
    }

    cout << "Case #" << test << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (ans[i][j] == 1 ? "Y" : "N");
        }
        cout << "\n";
    }
}

int main(){
    freopen("travel_restrictions_input.txt", "r", stdin);
    freopen("travel_restrictions_output.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    for (int test = 1; test <= T; test++) solve(test);
    return 0;
}
