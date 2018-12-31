#include <bits/stdc++.h>

using namespace std;

const int N = 65;
const int maxn = 6e4 + 5;

int n, a[N], trace[N][maxn][2];
bool dp[N][maxn][2];
vector <int> v[2];

int main(){
    #ifndef Futymy
        freopen("balin.txt", "r", stdin);
        freopen("balout.txt", "w", stdout);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < 2; k++) {
                if (dp[i][j][k]) {
                    if (k == 0) {
                        dp[i + 1][j + a[i + 1]][k] = true;
                        trace[i + 1][j + a[i + 1]][k] = 1;
                        if (j >= a[i + 1]) {
                            dp[i + 1][j - a[i + 1]][k] = true;
                            trace[i + 1][j - a[i + 1]][k] = 2;
                        }
                        else {
                            dp[i + 1][a[i + 1] - j][k ^ 1] = true;
                            trace[i + 1][a[i + 1] - j][k ^ 1] = 2;
                        }
                    }
                    else {
                        dp[i + 1][j + a[i + 1]][k] = true;
                        trace[i + 1][j + a[i + 1]][k] = 2;
                        if (j >= a[i + 1]) {
                            dp[i + 1][j - a[i + 1]][k] = true;
                            trace[i + 1][j - a[i + 1]][k] = 1;
                        }
                        else {
                            dp[i + 1][a[i + 1] - j][k ^ 1] = true;
                            trace[i + 1][a[i + 1] - j][k ^ 1] = 1;
                        }
                    }
                }
            }
        }
    }

    int Min = 2e9, state = 0;
    for (int i = 0; i < maxn; i++) for (int j = 0; j < 2; j++) if (dp[n][i][j] && i < Min) Min = i, state = j;
    int cur = n;
    while (cur > 0) {
        v[trace[cur][Min][state] - 1].push_back(cur);
        if (trace[cur][Min][state] == 1) {
            if (state == 1) Min += a[cur];
            else {
                if (Min >= a[cur]) Min -= a[cur];
                else Min = a[cur] - Min, state ^= 1;
            }
        }
        else {
            if (state == 0) Min += a[cur];
            else {
                if (Min >= a[cur]) Min -= a[cur];
                else Min = a[cur] - Min, state ^= 1;
            }
        }
        cur--;
    }

    sort(v[0].begin(), v[0].end()); sort(v[1].begin(), v[1].end());
    if (v[0].empty()) v[0].push_back(0);
    if (v[1].empty()) v[1].push_back(0);
    for (auto i: v[0]) printf("%d ", i);
    puts("");
    for (auto i: v[1]) printf("%d ", i);
    return 0;
}
