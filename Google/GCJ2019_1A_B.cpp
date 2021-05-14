#include <bits/stdc++.h>

using namespace std;

int a[20];

int binPow (int x, int y, int mod) {
    int ans = 1;
    while (y > 0) {
        if (y & 1) ans = 1LL * ans * x % mod;
        x = 1LL * x * x % mod;
        y >>= 1;
    }

    return ans;
}

void query (int x) {
    for (int i = 1; i <= 18; i++) {
        cout << x;
        if (i != 18) cout << " ";
        else cout << endl;
    }

    int ans = 0;
    for (int i = 1; i <= 18; i++) {
        int y;
        cin >> y;
        ans += y;
    }

    a[x] = ans % x;
}

int phi (int x) {
    int ans = 0;
    for (int i = 1; i <= x; i++) if (__gcd(i, x) == 1) ans++;
    return ans;
}

void solveCRT(){
    int M = 7 * 11 * 13 * 15 * 16 * 17;
    int M1 = M / 15, M2 = M / 16, M4 = M / 7, M5 = M / 11, M6 = M / 13, M7 = M / 17;
    int y1 = binPow(M1, phi(15) - 1, 15), y2 = binPow(M2, phi(16) - 1, 16), y4 = binPow(M4, 5, 7), y5 = binPow(M5, 9, 11), y6 = binPow(M6, 11, 13), y7 = binPow(M7, 15, 17);
    int ans = a[15] * M1 * y1 + a[16] * M2 * y2 + a[7] * M4 * y4 + a[11] * M5 * y5 + a[13] * M6 * y6 + a[17] * M7 * y7;
    ans %= M;

    cout << ans << endl;
    int verd; cin >> verd;
}

int main(){
    ios::sync_with_stdio(false);
    int t, n, m;
    cin >> t >> n >> m;
    for (int i = 1; i <= t; i++) {
        query(7); query(11); query(13); query(15); query(16); query(17);
        solveCRT();
    }
    return 0;
}
