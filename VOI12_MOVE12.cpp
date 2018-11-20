#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;

int n, a[N], t[N];

bool check (int mid) {
    vector <pair <int, int> > vec;
    for (int i = 1; i <= n; i++) vec.push_back({max(1, a[i] - mid / t[i]), min(n, a[i] + mid / t[i])});
    sort(vec.begin(), vec.end());

    int pt = 0;
    priority_queue <int, vector <int>, greater <int> > pq;
    for (int i = 1; i <= n; i++) {
        while (pt < vec.size() && vec[pt].first <= i && vec[pt].second >= i) pq.push(vec[pt].second), pt++;
        while (!pq.empty() && pq.top() < i) pq.pop();
        if (pq.empty()) return false;
        pq.pop();
    }

    return true;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i], &t[i]);
    int l = 0, r = 1e9;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }

    printf("%d", l);
    return 0;
}
