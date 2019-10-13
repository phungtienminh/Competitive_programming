#include <bits/stdc++.h>

using namespace std;

const int nbit = 17;
const int N = 1 << nbit;
const double pi = acos(-1);

typedef complex <double> base;
typedef vector <base> vb;

base W[N];

int revbit (int mask) {
    for (int i = 0, j = nbit - 1; i <= j; i++, j--) {
        if ((mask >> i & 1) != (mask >> j & 1)) {
            mask ^= (1 << i);
            mask ^= (1 << j);
        }
    }

    return mask;
}

void fft (int n, vb &a, bool inv) {
    if (n == 1) return;
    for (int i = 0; i < n; i++) {
        int j = revbit(i);
        if (i < j) swap(a[i], a[j]);
    }

    vb anext(n);
    for (int step = 1; step < n; step <<= 1) {
        double ang = pi / step;
        if (inv) ang = -ang;

        base w(1), wn(cos(ang), sin(ang));
        for (int i = 0; i < step; i++) {
            W[i] = w;
            w *= wn;
        }

        int start_even = 0, start_odd = start_even + step;
        while (start_even < n) {
            for (int i = 0; i < step; i++) {
                anext[start_even + i] = a[start_even + i] + a[start_odd + i] * W[i];
                anext[start_odd + i] = a[start_even + i] - a[start_odd + i] * W[i];
            }

            start_even += 2 * step;
            start_odd += 2 * step;
        }

        for (int i = 0; i < n; i++) a[i] = anext[i];
    }

    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
}

int n, m, res[N], buff = 0;
string s, t;
vb vs(N), vt(N);

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> s >> t;
    for (int i = n - 1; i >= 0; i--) vs[n - 1 - i] = s[i] - '0';
    for (int i = m - 1; i >= 0; i--) vt[m - 1 - i] = t[i] - '0';
    fft(N, vs, false); fft(N, vt, false);
    for (int i = 0; i < N; i++) vs[i] = vs[i] * vt[i];
    fft(N, vs, true);
    for (int i = 0; i < N; i++) {
        res[i] = (int)(vs[i].real() + 0.5 + buff);
        buff = res[i] / 10;
        res[i] %= 10;
    }

    bool ok = false;
    for (int i = N - 1; i >= 0; i--) {
        if (res[i]) ok = true;
        if (!ok) continue;
        cout << res[i];
    }

    if (!ok) cout << 0;
    return 0;
}
