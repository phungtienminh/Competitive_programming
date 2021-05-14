#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, p, dp[N], trace[N];
pair <int, int> segments[N];
char a[N][N];

int main(){
    //freopen("testgen.inp", "r", stdin);
    //freopen("contestant.out", "w", stdout);

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= m; i++) {
        segments[i].first = segments[i].second = i;
        for (int j = 2; j <= p; j++) {
            int fin = m + 1;
            for (int k = segments[i].first - (i != 1); k <= m; k++) {
                if (a[j][k] == '.') {
                    fin = k;
                    break;
                }
            }

            segments[i].first = fin;

            fin = 0;
            for (int k = segments[i].second + (i != m); k >= 1; k--) {
                if (a[j][k] == '.') {
                    fin = k;
                    break;
                }
            }

            segments[i].second = fin;
        }
    }

    //for (int i = 1; i <= m; i++) cout << segments[i].first << " " << segments[i].second << "\n";

    memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
    for (int i = 1; i <= m; i++) {
        if (a[p][i] == '#') {
            dp[i] = dp[i - 1];
            trace[i] = trace[i - 1];
            continue;
        }

        for (int j = 1; j <= m; j++) {
            int l = segments[j].first, r = segments[j].second;
            if (i > r || i < l) continue;
            l = max(l, 1);
            if (dp[i] > dp[l - 1] + 1) {
                dp[i] = dp[l - 1] + 1;
                trace[i] = j;
            }
        }
    }

    cout << dp[m] << "\n";
    stack <int> st;
    int cur = m;
    while (cur > 0) {
        int segid = trace[cur];
        if (segid) st.push(segid);
        cur = segments[segid].first - 1;
    }

    while (!st.empty()) cout << st.top() << " ", st.pop();
    return 0;
}
/*
6 3 3
###
.#.
#.#
...
.#.
...
*/
