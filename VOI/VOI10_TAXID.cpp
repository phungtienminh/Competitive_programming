#include <bits/stdc++.h>

using namespace std;

const int N = 70;

long long n, f[N][2][2], q;
int m, p, a[N];

void add (long long &x, long long y) {
    x += y;
}

char toChar (int x) {
    if (x < 10) return (char)(x + '0');
    return (char)(x + 87);
}

string getString (long long x, int base) {
    string ans = "";
    while (x > 0) {
        char c = toChar(x % base);
        ans = c + ans;
        x /= base;
    }

    return ans;
}

int toInt (char c) {
    if (c >= '0' && c <= '9') return (int)(c - '0');
    return (int)(c - 87);
}

long long solve (int base, long long n) {
    string s = getString(n, 36);
    //cout << s << " " << base << " " << s.length() << "\n";
    memset(f, 0, sizeof(f));
    f[0][1][0] = 1;
    for (int i = 0; i < s.length(); i++) {
        for (int high = 0; high < 2; high++) {
            for (int ok = 0; ok < 2; ok++) {
                if (f[i][high][ok]) {
                    int lim = base - 1;
                    if (high) lim = min(lim, toInt(s[i]));
                    //cout << s[i] << " " << lim << " LIM\n";
                    for (int dig = 0; dig <= lim; dig++) {
                        int nhigh = high && dig == toInt(s[i]);
                        int nok = ok || dig > 0;
                        add(f[i + 1][nhigh][nok], f[i][high][ok]);
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < 2; i++) add(ans, f[(int)s.length()][i][1]);
    //cout << " " << ans << "\n";
    //cout << ans << "\n";
    return ans;
}

int main(){
    scanf("%lld %d %d %lld", &n, &m, &p, &q);
    for (int i = 1; i <= (m - 1) / 2; i++) scanf("%d", &a[i]); a[(m - 1) / 2 + 1] = 36;
    long long low = solve(a[(p + 1) / 2 - 1], n), high = solve(a[(p + 1) / 2], n);
    //cout << low << " " << high << "\n";
    long long numth = (p % 2 == 1 ? q : high - low - q + 1);

    long long l = 1, r = n;
    while (l <= r) {
        long long mid = (l + r) / 2;
        //cout << i << " " << solve(a[(p + 1) / 2], i) << " " << solve(a[(p + 1) / 2 - 1], i) << "\n";
        if (solve(a[(p + 1) / 2], mid) - solve(a[(p + 1) / 2 - 1], mid) < numth) l = mid + 1;
        else r = mid - 1;
    }

    //cout << l << "\n";
    //cout << getString(2334887LL, 36) << " " << getString(2334888LL, 36) << "\n";

    string ans = getString(l, 36);
    cout << ans;
    return 0;
}
/*
12398018236861 3 1 10000000000
35
*/
