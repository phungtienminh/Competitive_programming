#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int p, n, a[N], b[N], f[N];

int main(){
    scanf("%d %d", &p, &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]), f[i] = f[i - 1] + b[i];

    int ans = 0;
    deque <int> dq;
    for (int i = 1; i <= n; i++) {
        dq.push_back(i);
        while (!dq.empty() && f[i] - f[dq.front() - 1] > p) dq.pop_front();
        if (!dq.empty()) ans += a[dq.front()] * b[i];
        while (!dq.empty() && a[dq.back()] > a[i + 1]) dq.pop_back();
    }

    printf("%d", ans);
    return 0;
}
