#include <bits/stdc++.h>

using namespace std;

const int N = 505;
int n, a[N];
vector <pair <int, int> > ans;
set <pair <int, int> > pq, pq2;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) pq.insert(make_pair(a[i], i));

    while (!pq.empty()) {
        pair <int, int> u = *pq.rbegin();
        pq.erase(pq.find(u));

        pq2 = pq;

        int cur = 0;
        while (cur < u.first) {
            cur++;
            pair <int, int> v = *pq2.rbegin();
            ans.push_back(make_pair(u.second, v.second));
            pq.erase(pq.find(v));
            pq.insert(make_pair(v.first - 1, v.second));
            pq2.erase(pq2.find(v));
        }
    }

    for (int i = 0; i < ans.size(); i++) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
