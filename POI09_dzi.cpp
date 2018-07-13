#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int a[N][N], n;

int main(){
    scanf("%d", &n);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            a[i][j] ^= 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j]) a[i][j] += a[i - 1][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        stack <int> st;
        int max_area = 0;
        int top_val = 0;
        int area = 0;
        int r = 1;

        while (r <= n) {
            if (st.empty() || a[i][st.top()] <= a[i][r]) st.push(r++);
            else {
                top_val = a[i][st.top()]; st.pop();
                area = top_val * (r - 1);
                if (!st.empty()) area = top_val * (r - st.top() - 1);

                max_area = max(max_area, area);
            }
        }

        while (!st.empty()) {
            top_val = a[i][st.top()]; st.pop();
            area = top_val * (r - 1);
            if (!st.empty()) area = top_val * (r - st.top() - 1);

            max_area = max(max_area, area);
        }

        ans = max(ans, max_area);
    }

    printf("%d", ans);
    return 0;
}
