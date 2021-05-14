#include <bits/stdc++.h>

using namespace std;

const int N = 505;

bitset <N> org[N], cur[N], nxt[N];
int n, m, k;
string s;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.') org[i].set(j);
        }

        cur[i] = org[i];
    }

    cin >> s;
    for (char c: s) {
        for (int i = 0; i < n; i++) nxt[i].reset();

        if (c == 'W' || c == '?') {
            for (int i = 0; i < n; i++) nxt[i] |= (cur[i] >> 1);
        }

        if (c == 'E' || c == '?') {
            for (int i = 0; i < n; i++) nxt[i] |= (cur[i] << 1);
        }

        if (c == 'N' || c == '?') {
            for (int i = 0; i + 1 < n; i++) nxt[i] |= cur[i + 1];
        }

        if (c == 'S' || c == '?') {
            for (int i = 1; i < n; i++) nxt[i] |= cur[i - 1];
        }

        for (int i = 0; i < n; i++) cur[i] = nxt[i] & org[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) ans += cur[i].count();
    cout << ans;
    return 0;
}
