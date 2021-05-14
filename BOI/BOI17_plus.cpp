#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

void add (int &x, int y) {
    x = (x + y) % mod;
}

int binPow (int x, int y) {
    int ans = 1;
    while (y > 0) {
        if (y & 1) ans = (1LL * ans * x) % mod;
        x = (1LL * x * x) % mod;
        y >>= 1;
    }

    return ans;
}

struct data {
    int x, y, sign;
    bool operator < (const data &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
} a[N];

int n, m, k;
bool coincide = true;

int solve(){
    sort(a + 1, a + k + 1);
    int pt = 1, row = 0;
    for (int i = 1; i <= k; i = pt) {
        while (pt <= k && a[pt].x == a[i].x) pt++;
        for (int j = i + 1; j < pt; j++) {
            if ((a[j].y + a[j].sign) % 2 != (a[i].y + a[i].sign) % 2) {
                coincide = false;
                return 0;
            }
        }
        row++; i = pt;
    }

    return binPow(2, n - row);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        char c;
        cin >> c >> a[i].x >> a[i].y;
        if (c == '+') a[i].sign = 1;
        else a[i].sign = 0;
    }

    int ans = 0;
    add(ans, solve());
    swap(n, m);
    for (int i = 1; i <= k; i++) swap(a[i].x, a[i].y);
    add(ans, solve());

    if (coincide) {
        if (k) add(ans, mod - 1);
        else add(ans, mod - 2);
    }

    cout << ans;
    return 0;
}
