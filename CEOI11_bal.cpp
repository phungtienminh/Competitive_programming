#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, x[N], r[N];
double ans[N];
deque <int> dq;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &x[i], &r[i]);
    for (int i = 1; i <= n; i++) {
        ans[i] = r[i];
        while (!dq.empty()) {
            ans[i] = min(ans[i], (double)(x[i] - x[dq.back()]) * (double)(x[i] - x[dq.back()]) / (4.0 * (double)ans[dq.back()]));
            if (ans[i] > ans[dq.back()]) dq.pop_back();
            else break;
        }
        dq.push_back(i);
    }

    for (int i = 1; i <= n; i++) cout << fixed << setprecision(3) << ans[i] << "\n";
    return 0;
}
