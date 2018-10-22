#include <bits/stdc++.h>

using namespace std;

const int N = 4105;

int n, m, k, col[N][4];
char a[N][N];

int toint (char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%s", a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            col[j][toint(a[i][j])]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (int j = 0; j < m; j++) cur += (n - col[j][toint(a[i][j])]);
        if (cur == k * (n - 1)) return !printf("%d", i);
    }
    return 0;
}
