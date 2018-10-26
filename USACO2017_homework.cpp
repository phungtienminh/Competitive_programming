#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, a[N], rmq[N][20], f[N];
vector <int> vec;

int get (int u, int v) {
    int k = log2(v - u + 1);
    return min(rmq[u][k], rmq[v - (1 << k) + 1][k]);
}

int main(){
    #ifndef Futymy
        freopen("homework.in", "r", stdin);
        freopen("homework.out", "w", stdout);
    #endif // Futymy

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), rmq[i][0] = f[i] = a[i];
    for (int i = 1; i <= n; i++) f[i] += f[i - 1];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            rmq[i][k] = min(rmq[i][k - 1], rmq[i + (1 << (k - 1))][k - 1]);
        }
    }

    double ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        double res = (double)(f[n] - f[i] - get(i + 1, n)) / (double)(n - i - 1);
        if (res > ans) {
            ans = res;
            vec.clear(); vec.push_back(i);
        }
        else if (res == ans) vec.push_back(i);
    }

    for (auto i: vec) printf("%d\n", i);
    return 0;
}
