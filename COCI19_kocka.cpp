#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, l[N], r[N], a[5][N], u[N], d[N];
bool has[N];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= 4; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) {
        if (a[1][i] == -1 && a[2][i] != -1) return !printf("NE");
        if (a[1][i] != -1 && a[2][i] == -1) return !printf("NE");
        if (a[1][i] + a[2][i] >= n) return !printf("NE");
        if (a[3][i] == -1 && a[4][i] != -1) return !printf("NE");
        if (a[3][i] != -1 && a[4][i] == -1) return !printf("NE");
        if (a[3][i] + a[4][i] >= n) return !printf("NE");
    }
    for (int i = 1; i <= n; i++) {
        int lef = a[1][i], rig = a[2][i];
        if (lef == -1) lef = -1;
        if (rig == -1) rig = -1;
        l[i] = lef + 1, r[i] = n - rig;
        has[l[i]] = true; has[r[i]] = true;
    }

    //for (int i = 1; i <= n; i++) cout << l[i] << " " << r[i] << "\n";
    for (int i = 1; i <= n; i++) {
        if (a[3][i] == -1 || a[4][i] == -1) {
            if (has[i]) return !printf("NE");
            continue;
        }
        int frow = a[3][i] + 1, lrow = n - a[4][i];
        if (i < l[frow] || i > r[frow] || i < l[lrow] || i > r[lrow]) return !printf("NE");
    }

    memset(has, 0, sizeof(has));
    for (int i = 1; i <= n; i++) {
        int up = a[3][i], down = a[4][i];
        if (up == -1) up = -1;
        if (down == -1) down = -1;
        u[i] = up + 1, d[i] = n - down;
        has[u[i]] = true; has[d[i]] = true;
    }

    //for (int i = 1; i <= n; i++) cout << u[i] << " " << d[i] << "\n";
    for (int i = 1; i <= n; i++) {
        if (a[1][i] == -1 || a[2][i] == -1) {
            if (has[i]) return !printf("NE");
            continue;
        }
        int lcol = a[1][i] + 1, rcol = n - a[2][i];
        if (i < u[lcol] || i > d[lcol] || i < u[rcol] || i > d[rcol]) return !printf("NE");
    }

    printf("DA");
    return 0;
}
