#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 5;

int pref[N], last[N], t, n, m, mod;

struct Matrix {
    int a[2][2];

    Matrix(){
        memset(a, 0, sizeof(a));
    }

    Matrix (int b, int c, int d, int e) {
        this->a[0][0] = b;
        this->a[1][0] = c;
        this->a[0][1] = d;
        this->a[1][1] = e;
    }

    Matrix mul (Matrix a, Matrix b) {
        Matrix c = Matrix();
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
                }
            }
        }

        return c;
    }

    Matrix Pow (Matrix a, int n) {
        if (n == 1) return a;

        Matrix temp = Pow(a, n / 2);
        temp = mul(temp, temp);

        if (n & 1) return mul(temp, a);
        return temp;
    }
} mt;

void fropen(){
    freopen("FIBSEQ.INP", "r", stdin);
    freopen("FIBSEQ.OUT", "w", stdout);
}

void solve(){
    Matrix base = Matrix(0, 1, 1, 1);
    base = mt.Pow(base, m - 1);

    pref[0] = base.a[0][1];
    pref[1] = base.a[1][1];
    for (int i = 2; i <= n; i++) pref[i] = (pref[i - 1] + pref[i - 2]) % mod;
    for (int i = 2; i <= n; i++) pref[i] = (pref[i] + pref[i - 1]) % mod;
    memset(last, 0, sizeof(last));

    for (int i = 1; i <= n; i++) {
        if (!pref[i] || last[pref[i]]) {
            printf("%lld ", i - last[pref[i]]);
            for (int j = last[pref[i]] + 1; j <= i; j++) printf("%lld ", m + j - 1);
            break;
        }

        last[pref[i]] = i;
    }

    puts("");
}

void input(){
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld %lld %lld", &n, &m, &mod);
        solve();
    }
}

signed main(){
    fropen();
    input();
    return 0;
}
