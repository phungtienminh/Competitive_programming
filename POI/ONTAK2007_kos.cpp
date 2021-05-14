#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int M = 25;

int n, m;
long long k, a[N][M], ans[M];

void input(){
    scanf("%d %d %lld", &m, &n, &k);
}

void precalc(){
    for (int i = 1; i < N; i++) a[i][1] = i;
    for (int i = 2; i < M; i++) a[1][i] = 1;
    for (int i = 2; i < N; i++) {
        for (int j = 2; j < M; j++) {
            a[i][j] = a[i - 1][j] + a[i][j - 1];
        }
    }
}

void solve(){
    precalc();
    for (int i = 1; i <= m; i++) ans[i] = 1;

    int cur = n;
    while (k > cur) {
        for (int i = 1; i < M; i++) {
            if (a[cur][i] >= k) {
                k = k - a[cur][i - 1];
                ans[i]++;
                for (int j = i - 1; j >= 1; j--) ans[j] = ans[i];
                cur--;
                break;
            }
        }
    }

    ans[1] = ans[1] + k - 1;
    for (int i = m; i >= 1; i--) printf("%lld ", ans[i]);
}

int main(){
    input();
    solve();
    return 0;
}
