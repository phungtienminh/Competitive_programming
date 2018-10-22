#include <bits/stdc++.h>

using namespace std;

const int N = 4105;

int n, m, k, sum[N], val[N], f[4][N];
char a[N][N];

int toint (char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int main(){
    mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%s", a[i]);
    for (int i = 1; i <= n; i++) val[i] = rd() % 100000 + 1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            f[toint(a[j][i])][i] += val[j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                if (k != toint(a[i][j])) sum[i] += f[k][j];
            }
        }

        int cur = 0;
        for (int j = 1; j <= n; j++) if (i != j) cur += val[j];
        if (sum[i] == k * cur) return !printf("%d", i);
    }
    return 0;
}
