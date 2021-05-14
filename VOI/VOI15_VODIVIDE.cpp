#include <bits/stdc++.h>

using namespace std;

const int N = 5005;

int n, ans = 0;
pair <int, pair <int, int> > a[N];
priority_queue <pair <int, int> > pq;
stack <int> st;
bool used[N];

int main(){
    #ifdef Futymy
        //freopen("all.in", "r", stdin);
    #endif // Futymy
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), a[i].second.second = i;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i].second.first);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        pq.push({a[i].second.first, a[i].second.second});
        if (i & 1) {
            pair <int, int> val = pq.top(); pq.pop();
            ans += val.first;
            used[val.second] = true;
        }
    }

    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
        if (used[a[i].second.second]) st.push(a[i].second.second);
        else printf("%d %d\n", st.top(), a[i].second.second), st.pop();
    }
    return 0;
}
/*
6
6 10 11 18 5 14
1 7 6 12 15 1
*/
