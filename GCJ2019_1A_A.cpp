#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

struct Trie {
    Trie *child[30];
    int subt;
    bool endHere;

    Trie() {
        for (int i = 0; i < 30; i++) child[i] = NULL;
        subt = 0; endHere = false;
    }
} *root = new Trie();

void update (string s) {
    Trie *cur = root;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (cur -> child[s[i] - 'A'] == NULL) cur -> child[s[i] - 'A'] = new Trie();
        cur = cur -> child[s[i] - 'A'];
    }

    cur -> subt = 1; cur -> endHere = true;
}

void reupdate (Trie *u) {
    for (int i = 0; i < 30; i++) {
        if (u -> child[i] != NULL) {
            reupdate(u -> child[i]);
            u -> subt += u -> child[i] -> subt;
        }
    }
}

int t, n, ans = 0;
string a[N];

void dfs (Trie *u, bool ok) {
    bool leaf = true;
    for (int i = 0; i < 30; i++) if (u -> child[i] != NULL) leaf = false;
    if (!leaf) {
        u -> subt = 0;
        if (u -> endHere) u -> subt = 1;
        for (int i = 0; i < 30; i++) if (u -> child[i] != NULL) dfs(u -> child[i], true), u -> subt += u -> child[i] -> subt;
    }

    //cout << c << " DEBUG " << " " << ans << " " << (u -> subt) << "\n";
    if (ok) {
        int taken = min(2, (u -> subt) / 2 * 2);
        ans += taken;
        u -> subt -= taken;
    }
}

void solve(){
    cin >> n; root = new Trie(); ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], update(a[i]);
    reupdate(root);
    dfs(root, false);
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
