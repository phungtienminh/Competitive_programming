#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int mod = 1e9;

int n, h, a[N], lp[N], expo[N];

void sieve(){
    for (int i = 2; i < N; i++) {
        if (!lp[i]) {
            for (int j = i; j < N; j += i) lp[j] = i;
        }
    }
}

int mul (int x, int y) {
    return 1LL * x * y % mod;
}

int binPow (int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1) ans = (1LL * ans * x) % mod;
        x = (1LL * x * x) % mod;
        y >>= 1;
    }

    return ans;
}

void factorize (int val, int type) {
    while (val > 1) {
        int cur = lp[val];
        while (val % cur == 0) {
            val /= cur;
            expo[cur] += type;
        }
    }
}

int solve(){
    n++;
    int ans = 1;
    for (int i = n + 2; i <= 2 * n; i++) factorize(i, 1);
    for (int i = 1; i <= n; i++) factorize(i, -1);
    for (int i = 1; i < N; i++) ans = mul(ans, binPow(i, expo[i]));
    return ans;
}

int main(){
    scanf("%d %d", &n, &h);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sieve();

    int ans = 2;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] < a[i + 1]) ans++;
        else break;
    }
    printf("%d\n%d", ans, solve());
    return 0;
}
