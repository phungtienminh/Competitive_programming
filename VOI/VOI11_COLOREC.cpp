#include <bits/stdc++.h>

using namespace std;

const int N = 405;
const int maxn = 1e5 + 5;
const int offset = 201;

int f[N][N][5][5], n, x[maxn], y[maxn], c[maxn], col[N][N];
vector <int> vec[N];

int main(){
    #ifdef Futymy
        freopen("testgen.inp", "r", stdin);
        //freopen("testgen.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &x[i], &y[i], &c[i]);
        x[i] += offset; y[i] += offset;
        col[x[i]][y[i]] = c[i];
        vec[x[i]].push_back(y[i]);
    }

    for (int i = 1; i <= 401; i++) sort(vec[i].begin(), vec[i].end());
    for (int i = 1; i <= 401; i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            for (int k = j + 1; k < vec[i].size(); k++) {
                f[vec[i][j]][vec[i][k]][col[i][vec[i][j]]][col[i][vec[i][k]]]++;
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= 401; i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            for (int k = j + 1; k < vec[i].size(); k++) {
                if (col[i][vec[i][j]] != col[i][vec[i][k]]) {
                    int nc1 = 0, nc2 = 0;
                    if (col[i][vec[i][j]] != 1 && col[i][vec[i][k]] != 1) nc1 = 1;
                    if (col[i][vec[i][j]] != 2 && col[i][vec[i][k]] != 2) {
                        if (nc1) nc2 = 2;
                        else nc1 = 2;
                    }

                    if (col[i][vec[i][j]] != 3 && col[i][vec[i][k]] != 3) {
                        if (nc1) nc2 = 3;
                        else nc1 = 3;
                    }

                    if (col[i][vec[i][j]] != 4 && col[i][vec[i][k]] != 4) nc2 = 4;
                    ans = ans + f[vec[i][j]][vec[i][k]][nc1][nc2] + f[vec[i][j]][vec[i][k]][nc2][nc1];
                }
            }
        }
    }

    printf("%lld", ans / 2);
    /*#ifdef Futymy
        cout << "\n" << fixed << setprecision(6) << (double)clock() / (double)CLOCKS_PER_SEC;
    #endif*/
    return 0;
}
