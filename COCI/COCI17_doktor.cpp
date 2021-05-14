#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, a[N], f[N], p[N];
vector <pair <int, int> > vec[N + N];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        int x = i - a[i];
        p[a[i]] = i;
        vec[2 * i - 1 - x].push_back({min(i, a[i]), max(i, a[i])});
        f[i] = f[i - 1] + (a[i] == i);
    }

    int Max = -1, ans1 = 0, ans2 = 0;
    for (int i = 1; i <= 2 * n - 1; i++) {
        sort(vec[i].begin(), vec[i].end(), greater <pair <int, int> >());
        for (int j = 0; j < vec[i].size(); j++) {
            int res = j + 1 - (f[vec[i][j].second] - f[vec[i][j].first - 1]);
            if (res > Max) {
                Max = res;
                ans1 = a[vec[i][j].first];
                ans2 = a[vec[i][j].second];
            }
        }
    }

    if (p[ans1] > p[ans2]) swap(ans1, ans2);
    cout << ans1 << " " << ans2;
    return 0;
}
