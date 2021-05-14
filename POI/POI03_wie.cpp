#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, a[2][N], b[2][N], res[2][N];
bool placed[2][N];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d %d %d", &a[0][i], &b[0][i], &a[1][i], &b[1][i]);
    for (int t = 1; t <= n; t++) {
        bool ok = false;
        int Min = 1e9, pos;
        for (int i = 1; i <= n; i++) {
            if (placed[0][i]) continue;
            if (t > a[1][i]) return !printf("NIE");
            if (t >= a[0][i]) {
                ok = true;
                if (a[1][i] - t < Min) {
                    Min = a[1][i] - t;
                    pos = i;
                }
            }
        }

        if (!ok) return !printf("NIE");
        placed[0][pos] = true;
        res[0][pos] = t;
    }

    for (int t = 1; t <= n; t++) {
        bool ok = false;
        int Min = 1e9, pos;
        for (int i = 1; i <= n; i++) {
            if (placed[1][i]) continue;
            if (t > b[1][i]) return !printf("NIE");
            if (t >= b[0][i]) {
                ok = true;
                if (b[1][i] - t < Min) {
                    Min = b[1][i] - t;
                    pos = i;
                }
            }
        }

        if (!ok) return !printf("NIE");
        placed[1][pos] = true;
        res[1][pos] = t;
    }

    for (int i = 1; i <= n; i++) printf("%d %d\n", res[0][i], res[1][i]);
    return 0;
}
