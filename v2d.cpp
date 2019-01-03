#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, t, mod, a[N][N], f1[N][N], f2[N][N], f3[N][N], f4[N][N];

int readInt(){
    int ans = 0;
    char c;
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') return ans;
        ans = (ans << 3) + (ans << 1) + (c - '0');
    }
}

int main(){
    #ifndef Futymy
        freopen("v2d.in", "r", stdin);
        freopen("v2d.out", "w", stdout);
    #endif // Futymy
    n = readInt(); t = readInt(); mod = readInt();
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) a[i][j] = readInt();
    memset(f1, -0x3f, sizeof(f1)); memset(f2, -0x3f, sizeof(f2)); memset(f3, -0x3f, sizeof(f3)); memset(f4, -0x3f, sizeof(f4));
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                f1[j][k] = max(f1[j - 1][k], f1[j][k - 1]);
                f1[j][k] = max(f1[j][k], a[j][k] + j + k);
            }
        }

        for (int j = 1; j <= n; j++) {
            for (int k = n; k >= 1; k--) {
                f2[j][k] = max(f2[j - 1][k], f2[j][k + 1]);
                f2[j][k] = max(f2[j][k], a[j][k] + j - k);
            }
        }

        for (int j = n; j >= 1; j--) {
            for (int k = 1; k <= n; k++) {
                f3[j][k] = max(f3[j + 1][k], f3[j][k - 1]);
                f3[j][k] = max(f3[j][k], a[j][k] - j + k);
            }
        }

        for (int j = n; j >= 1; j--) {
            for (int k = n; k >= 1; k--) {
                f4[j][k] = max(f4[j + 1][k], f4[j][k + 1]);
                f4[j][k] = max(f4[j][k], a[j][k] - j - k);
            }
        }

        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                int val1 = max(f1[j - 1][k], f1[j][k - 1]) - j - k;
                int val2 = max(f2[j - 1][k], f2[j][k + 1]) - j + k;
                int val3 = max(f3[j + 1][k], f3[j][k - 1]) + j - k;
                int val4 = max(f4[j + 1][k], f4[j][k + 1]) + j + k;
                int val = val1; val = max(val, val2); val = max(val, val3); val = max(val, val4);
                a[j][k] += 1LL * i * val % mod;
                while (a[j][k] >= mod) a[j][k] -= mod;
                a[j][k] += (i + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans += a[i][j];
            while (ans >= mod) ans -= mod;
        }
    }
    printf("%d", ans);
    return 0;
}
