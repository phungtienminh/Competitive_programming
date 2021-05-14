#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, a[N], q, dp[N];
deque <int> dq;

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &q);
}

void solve(){
    while (q--) {
        int k; scanf("%d", &k);
        dq.clear();
        dp[1] = 0; dq.push_back(1);

        for (int i = 2; i <= n; i++) {
            while (!dq.empty() && dq.front() < max(1, i - k)) dq.pop_front();
            dp[i] = dp[dq.front()] + (a[dq.front()] <= a[i]);
            while (!dq.empty() && ((dp[dq.back()] > dp[i]) || (dp[dq.back()] == dp[i] && a[dq.back()] <= a[i]))) dq.pop_back();
            dq.push_back(i);
        }

        printf("%d\n", dp[n]);
    }
}

int main(){
    input();
    solve();
    return 0;
}
