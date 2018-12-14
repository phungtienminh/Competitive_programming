#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

typedef pair <int, int> ii;
typedef pair <ii, ii> iiii;
typedef pair <iiii, int> i5;

int n, a[N][5], temp[5];
map <i5, int> mm[6];
long long ans = 0;

int main(){
    #ifndef Futymy
        freopen("cowpatibility.in", "r", stdin);
        freopen("cowpatibility.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) for (int j = 0; j < 5; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++) sort(a[i], a[i] + 5);
    for (int cnt = 1; cnt <= 5; cnt++) {
        for (int mask = 1; mask < 32; mask++) {
            if (__builtin_popcount(mask) != cnt) continue;
            for (int i = 1; i <= n; i++) {
                memset(temp, 0, sizeof(temp));
                for (int j = 0; j < 5; j++) {
                    if (mask & (1 << j)) {
                        temp[j] = a[i][j];
                    }
                }

                sort(temp, temp + 5, greater <int>());
                mm[cnt][{{{temp[0], temp[1]}, {temp[2], temp[3]}}, temp[4]}]++;
            }
        }

        long long res = 0;
        for (auto i: mm[cnt]) res += 1LL * i.second * (i.second - 1) / 2;
        if (cnt % 2 == 1) ans += res;
        else ans -= res;
    }

    printf("%lld", 1LL * n * (n - 1) / 2 - ans);
    return 0;
}
