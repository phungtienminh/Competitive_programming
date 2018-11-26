#include <bits/stdc++.h>

using namespace std;

const int N = 5005;
const int mod = 1e9;

void add (int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int n, dp[2][N];
char a[N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) cin >> a[i];
    a[n] = '-';
    dp[0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) dp[i % 2][j] = 0;
        for (int j = n - 1; j >= 0; j--) {
            if (a[i] == a[i + 1]) {
                add(dp[i % 2][j], dp[i % 2][j + 2]);
                add(dp[i % 2][j], dp[(i - 1) % 2][j]);
            }
            else {
                add(dp[i % 2][j], dp[i % 2][j + 2]);
                if (j) add(dp[i % 2][j], dp[(i - 1) % 2][j - 1]);
            }
        }
    }

    printf("%d", dp[(n - 1) % 2][0]);
    return 0;
}
