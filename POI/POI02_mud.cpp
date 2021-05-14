#include <bits/stdc++.h>

using namespace std;

const int N = 355;
const int maxn = 105;

int pref_cost[N][maxn], pref_dist[N][maxn], len[N], cost[N], cost_way[N][maxn];
int n, m;

int main(){
    //freopen("mudfest.inp", "r", stdin);
    //freopen("mudfest.out", "w", stdout);

    scanf("%d %d", &n, &m);
    memset(cost, 0, sizeof(cost));
    memset(pref_cost, 0, sizeof(pref_cost));
    memset(pref_dist, 0, sizeof(pref_dist));

    int ans = 0;
    for (int i = 1; i<=n; i++) {
        scanf("%d", &len[i]);
        for (int j = 1; j<=len[i]; j++) {
            int x, y;
            scanf("%d %d", &x, &y);
            cost_way[i][j] = y;
            pref_dist[i][j] = pref_dist[i][j - 1] + x;
            cost[i] = cost[i] + y * pref_dist[i][j];
            pref_cost[i][j] = pref_cost[i][j - 1] + y;
        }
        ans += cost[i];
    }

    int pos1 = 0;
    int pos2 = 0;

    for (int i = 1; i<=n; i++) {
        int res = 0;
        int temp = 0;

        for (int j = 1; j<=n; j++) temp = temp + (j != i ? pref_cost[j][len[j]] : 0);
        for (int j = 1; j<=len[i]; j++) {
            res = 0;

            for (int k = 1; k<=n; k++) res = res + (k != i ? cost[k] : 0);
            res = res + m * pref_dist[i][j] + temp * pref_dist[i][j];
            for (int k = 1; k<=len[i]; k++) {
                if (k <= j) res = res + (pref_dist[i][j] - pref_dist[i][k]) * cost_way[i][k];
                else res = res + (pref_dist[i][k] - pref_dist[i][j]) * cost_way[i][k];
            }

            if (res < ans) {
                ans = res;
                pos1 = i;
                pos2 = j;
            }

            //cout << i << " " << j << " " << res << "\n";
        }
    }

    printf("%d\n%d %d\n", ans, pos1, pos2);
    return 0;
}
