#include <bits/stdc++.h>

using namespace std;

int n;
deque <pair <int, int> > dq;

void solve(){
    scanf("%d", &n);
    int last = 0;
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        while (!dq.empty() && dq.back().first <= l) dq.pop_back();
        while (!dq.empty() && dq.front().first > r) {
            last = dq.front().second;
            dq.pop_front();
        }

        ans = max(ans, i - last);
        dq.push_back(make_pair(l, i));
    }

    printf("%d", ans);
}

int main(){
    solve();
    return 0;
}
