#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 5;
const int mod = 1e9 + 9;

char s[N];
int n, dp[2][N];

void add (int &x, int y) {
    x = (x + y) % mod;
}

int main(){
    scanf("%d", &n);
    scanf("%s", s);
    memset(dp, 0, sizeof(dp)); dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) dp[(i + 1) % 2][j] = 0;
        for (int j = 0; j <= n; j++) {
            if (dp[i % 2][j]) {
                if (s[i] == ')') {
                    if (j) add(dp[(i + 1) % 2][j - 1], dp[i % 2][j]);
                }
                else {
                    add(dp[(i + 1) % 2][j + 1], dp[i % 2][j]);
                    if (j) add(dp[(i + 1) % 2][j - 1], dp[i % 2][j]);
                }
            }
        }
    }
    printf("%d", dp[n % 2][0]);
    return 0;
}
