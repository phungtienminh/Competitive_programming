#include <bits/stdc++.h>

using namespace std;

const int N = 50005;

struct Data {
    int l, r;

    bool operator<(const Data &other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }

} a[N];

int n;
vector <pair <int, int> > ans;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1);

    int l = a[1].l;
    int r = a[1].r;

    for (int i = 2; i <= n; i++) {
        if (a[i].l > r) {
            ans.push_back(make_pair(l, r));
            l = a[i].l;
            r = a[i].r;
        }
        else r = max(r, a[i].r);
    }

    ans.push_back(make_pair(l, r));
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
