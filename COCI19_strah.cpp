#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int n, m, h[N][N], l[N], r[N], ans[N][N];
char a[N][N];
long long res = 0;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = 1; i <= m; i++) h[1][i] = (a[1][i] == '#' ? 0 : 1);
    for (int i = 2; i <= n; i++) for (int j = 1; j <= m; j++) h[i][j] = (a[i][j] == '#' ? 0 : h[i - 1][j] + 1);
    for (int i = 1; i <= n; i++) {
        deque <int> dq;
        for (int j = 1; j <= m; j++) {
            while (!dq.empty() && h[i][dq.front()] > h[i][j]) dq.pop_front();
            if (dq.empty()) l[j] = 0;
            else l[j] = dq.front();

            dq.push_front(j);
        }

        while (!dq.empty()) dq.pop_back();
        for (int j = m; j >= 1; j--) {
            while (!dq.empty() && h[i][dq.front()] >= h[i][j]) dq.pop_front();
            if (dq.empty()) r[j] = m + 1;
            else r[j] = dq.front();

            dq.push_front(j);
        }

        for (int j = 1; j <= m; j++) {
            ans[h[i][j]][r[j] - l[j]]--;
            ans[h[i][j]][r[j] - j]++;
            ans[h[i][j]][j - l[j]]++;
            ans[h[i][j]][0]--;
            //cout << l[j] << " " << r[j] << "\n";
        }
    }

    for (int i = 1; i <= n + 1; i++) for (int j = 1; j <= m + 1; j++) ans[i][j] += ans[i][j - 1];
    for (int i = n; i >= 1; i--) for (int j = m; j >= 1; j--) ans[i][j] += ans[i + 1][j] + ans[i][j + 1] - ans[i + 1][j + 1];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) res += 1LL * ans[i][j] * i * j;
    cout << res;
    return 0;
}
