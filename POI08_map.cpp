#include <bits/stdc++.h>

using namespace std;

const int N = 255;
int n, r, a[N][N], w[N][N], pref[N][N];

int get (int a, int b, int c, int d) {
    return pref[c][d] - pref[c][b - 1] - pref[a - 1][d] + pref[a - 1][b - 1];
}

int main(){
    scanf("%d %d", &n, &r);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    memset(pref, 0, sizeof(pref));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            w[i][j] = get(max(i - r, 1), max(j - r, 1), min(i + r, n), min(j + r, n));
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) printf(" ");
            printf("%d", w[i][j]);
        }

        puts("");
    }
    return 0;
}
