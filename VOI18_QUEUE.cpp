#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 5;

int t, m, n, a[N], b[N];

bool check (int mid) {
    vector <pair <int, int> > vec;
    for (int i = 1; i <= mid; i++) vec.push_back({a[i], b[i]});
    sort(vec.begin(), vec.end());
    priority_queue <int, vector <int>, greater <int> > pq;

    int ptr = 0;
    for (int i = 1; i <= m; i++) {
        while (ptr < vec.size() && vec[ptr].first <= i && vec[ptr].second >= i) pq.push(vec[ptr].second), ptr++;
        if (!pq.empty() && pq.top() < i) return false;
        if (!pq.empty()) pq.pop();
    }

    if (!pq.empty()) return false;
    return true;
}

int main(){
    #ifndef Futymy
        freopen("queue.inp", "r", stdin);
        freopen("queue.out", "w", stdout);
    #endif // Futymy
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &m, &n);
        for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &b[i]);
        int l = 1, r = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) l = mid + 1;
            else r = mid - 1;
        }

        printf("%d\n", r);
    }
    return 0;
}
