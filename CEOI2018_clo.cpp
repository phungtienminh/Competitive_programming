#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

struct Data {
    int core, speed, cost, type;

    bool operator<(const Data &other) const {
        if (speed != other.speed) return speed > other.speed;
        return type > other.type;
    }
} a[2 * N];

double dp[2][100 * N];
int n, m;

int readInt(){
    char c;
    int ans = 0;

    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') break;
        ans = ans * 10 + (c - '0');
    }

    return ans;
}

void input(){
    n = readInt();
    for (int i = 1; i <= n; i++) {
        a[i].core = readInt(); a[i].speed = readInt(); a[i].cost = readInt();
        a[i].type = 1;
    }

    m = readInt();
    for (int i = 1; i <= m; i++) {
        a[i + n].core = readInt(); a[i + n].speed = readInt(); a[i + n].cost = readInt();
        a[i + n].type = 0;
    }
}

void maximize (double &x, double y) {
    x = max(x, y);
}

void solve(){
    sort(a + 1, a + n + m + 1);
    int p = 1;
    int q = 0;
    int ncore = 0;

    for (int i = 0; i < N * 100; i++) dp[0][i] = dp[1][i] = -1e18 - 2277;
    dp[0][0] = 0;

    for (int i = 1; i <= n + m; i++) {
        for (int j = 0; j <= ncore; j++) dp[p][j] = -1e18 - 2277;
        for (int j = 0; j <= ncore; j++) {
            if (dp[q][j] > -1e18) {
                maximize(dp[p][j], dp[q][j]);
                if (a[i].type) {
                    maximize(dp[p][j + a[i].core], dp[q][j] - a[i].cost);
                }
                else {
                    if (j >= a[i].core) maximize(dp[p][j - a[i].core], dp[q][j] + a[i].cost);
                }
            }
        }

        if (a[i].type) ncore += a[i].core;

        p ^= 1;
        q ^= 1;
    }

    long long ans = 0;
    for (int i = 0; i < N * 100; i++) ans = max(ans, (long long)dp[q][i]);
    printf("%lld", ans);
}

int main(){
    input();
    solve();
    return 0;
}
