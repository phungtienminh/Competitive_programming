#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;
int a[N], dp[N], n, left_most[N];

int main(){
    scanf("%d", &n);
    a[0] = dp[0] = 0;
    getchar();

    for (int i = 1; i<=n; i++) {
        char c;
        c = getchar();
        if (c == 'j') a[i] = -1;
        else a[i] = 1;

        dp[i] = dp[i - 1] + a[i];
    }

    stack <int> st;
    for (int i = 0; i<=n; i++) left_most[i] = i;
    for (int i = 0; i<=n; i++) {
        while (!st.empty() && dp[st.top()] <= dp[i]) {
            int k = left_most[st.top()];
            if (dp[k] <= dp[left_most[i]]) left_most[i] = k;
            st.pop();
        }

        st.push(i);
    }

    int ans = 0;
    for (int i = 1; i<=n; i++) ans = max(ans, i - left_most[i]);
    printf("%d", ans);
    return 0;
}
