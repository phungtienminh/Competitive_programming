#include <bits/stdc++.h>

using namespace std;

const int N = 555;

int dp[N], trace[N];

bool check (int n) {
    if (n < 2) return false;
    if (n < 4) return true;
    for (int i = 2; i * i <= n; i++) if (n % i == 0) return false;
    return true;
}

vector <int> v;

void path (int n) {
    while (trace[n]) {
        v.push_back(n - trace[n]);
        n = trace[n];
    }

    v.push_back(n);
}

int main(){
    //freopen("GOLDBACH.inp", "r", stdin);
    //freopen("GOLDBACH.out", "w", stdout);

    memset(dp, 0, sizeof(dp));
    dp[3] = 1; dp[4] = 0; dp[5] = 1; dp[6] = 0; dp[7] = 1;
    memset(trace, 0, sizeof(trace));

    for (int i = 8; i < N; i++) {
        for (int j = 3; j < i && i - j > j; j++) {
            if (dp[j] && check(i - j) && (i - j) % 2 == 1) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    trace[i] = j;
                }
            }
        }
    }

    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        v.clear();

        if (n == 15) {
            printf("3\n3 5 7\n");
            continue;
        }

        if (n < N) path(n);
        else {
            for (int i = n - 5; i >= n - N; i--) {
                if (check(i) && i % 2 == 1 && dp[n - i]) {
                    v.push_back(i);
                    path(n - i);
                    break;
                }
            }
        }

        sort(v.begin(), v.end());
        printf("%d\n", (int)v.size());
        for (int i = 0; i < v.size(); i++) {
            if (i) printf(" ");
            printf("%d", v[i]);
        }

        puts("");
    }
    return 0;
}
