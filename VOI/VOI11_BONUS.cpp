#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, k, a[N][N], f[N][N];

int get (int x1, int y1, int x2, int y2) {
    return f[x2][y2] - f[x1 - 1][y2] - f[x2][y1 - 1] + f[x1 - 1][y1 - 1];
}

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];

    int ans = 0;
    for (int i = 1; i + k - 1 <= n; i++) for (int j = 1; j + k - 1 <= n; j++) ans = max(ans, get(i, j, i + k - 1, j + k - 1));
    printf("%d", ans);
    return 0;
}
