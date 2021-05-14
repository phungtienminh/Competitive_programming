#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, a[N], b[N], f[N], cnt = 1000;
map <string, int> mm;

struct disj {
    int par[N];
    void init (int n) {
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    int Find (int x) {
        return par[x] == x ? x : par[x] = Find(par[x]);
    }

    bool same (int x, int y) {
        return Find(x) == Find(y);
    }

    void join (int x, int y) {
        x = Find(x); y = Find(y);
        if (x == y) return;
        par[y] = x;
    }
} dsu;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        if (s[0] >= '0' && s[0] <= '9') {
            int sum = 0;
            for (int j = 0; j < s.length(); j++) sum = sum * 10 + (s[j] - '0');
            a[i] = sum;
        }
        else {
            if (!mm.count(s)) mm[s] = ++cnt;
            a[i] = mm[s];
        }
    }

    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        if (s[0] >= '0' && s[0] <= '9') {
            int sum = 0;
            for (int j = 0; j < s.length(); j++) sum = sum * 10 + (s[j] - '0');
            b[i] = sum;
        }
        else {
            if (!mm.count(s)) mm[s] = ++cnt;
            b[i] = mm[s];
        }
    }

    dsu.init(200000);
    for (int i = 1; i <= n; i++) dsu.join(a[i], b[i]);
    for (int i = 0; i <= 1000; i++) f[dsu.Find(i)]++;
    for (int i = 0; i < N; i++) if (f[i] >= 2) return cout << "NE", 0;
    cout << "DA";
    return 0;
}
