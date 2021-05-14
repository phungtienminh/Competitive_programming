#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int n, child[N], dp[N], par[N];
vector <int> g[N], vec;

void dfs (int u, int p) {
    vec.push_back(u);
    for (auto v: g[u]) {
        if (v == p) continue;
        child[u]++;
        par[v] = u;
        dfs(v, u);
    }
}

bool check2 (vector <int> v, int mid, int val) {
    int l = 0, r = (int)v.size() - 1;
    for (int i = 0; i < v.size() / 2; i++) {
        if (l == mid) l++;
        if (r == mid) r--;
        if (v[l] + v[r] > val) return false;
        l++; r--;
    }

    return true;
}

bool check (int mid) {
    for (auto i: vec) {
        if (i == 1) break;
        vector <int> v;
        for (auto j: g[i]) if (j != par[i]) v.push_back(dp[j] + 1);
        sort(v.begin(), v.end());
        if (v.size() % 2 == 0) v.insert(v.begin(), 0);

        int l = 0, r = (int)v.size() - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (check2(v, m, mid)) r = m - 1;
            else l = m + 1;
        }

        if (l == v.size() || v[l] >= mid) return 0;
        dp[i] = v[l];
    }

    vector <int> v;
    for (auto j: g[1]) v.push_back(dp[j] + 1);
    sort(v.begin(), v.end());
    if (v[v.size() - 1] > mid) return false;
    if (v.size() % 2) v.pop_back();
    for (int i = 0; i < v.size(); i++) if (v[i] + v[v.size() - i - 1] > mid) return false;
    return true;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }

    dfs(1, 1);
    int ans = n - 1;
    for (int i = 1; i <= n; i++) ans -= ((i != 1) + child[i]) / 2;

    reverse(vec.begin(), vec.end());
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }

    printf("%d %d", ans, l);
    return 0;
}
