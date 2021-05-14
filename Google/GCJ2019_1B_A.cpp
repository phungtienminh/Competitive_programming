#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int x[N], y[N], p, q, t;

void solve(){
    memset(x, 0, sizeof(x)); memset(y, 0, sizeof(y));
    for (int i = 1; i <= p; i++) {
        int X, Y;
        char c;
        cin >> X >> Y >> c;
        if (c == 'N') y[Y + 1]++;
        else if (c == 'S') y[0]++, y[Y]--;
        else if (c == 'W') x[0]++, x[X]--;
        else x[X + 1]++;
    }

    for (int i = 1; i <= q; i++) x[i] += x[i - 1], y[i] += y[i - 1];

    int ansx = 0, ansy = 0, posx = 0, posy = 0;
    for (int i = 0; i <= q; i++) {
        if (x[i] > ansx) {
            ansx = x[i];
            posx = i;
        }

        if (y[i] > ansy) {
            ansy = y[i];
            posy = i;
        }
    }

    cout << posx << " " << posy << "\n";
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> p >> q;
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
