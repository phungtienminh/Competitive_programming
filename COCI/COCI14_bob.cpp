#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int n, m, a[N][N], h[N][N];
long long ans = 0;

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; i++) h[1][i] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == a[i - 1][j]) h[i][j] = h[i - 1][j] + 1;
            else h[i][j] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        vector <pair <int, int> > vec; vec.push_back({0, 0});
        int pos = 0;
        for (int j = 1; j <= m; j++) {
            if (j - 1 && a[i][j] != a[i][j - 1]) {
                pos++;
                while (!vec.empty() && vec.back().first >= 0) vec.pop_back();
                vec.push_back({0, pos});
            }

            pos++;
            while (!vec.empty() && vec.back().first >= h[i][j]) vec.pop_back();
            vec.push_back({h[i][j], pos});
            long long res = 0;

            for (int k = 1; k < vec.size(); k++) res += 1LL * (vec[k].first - vec[k - 1].first) * (pos - vec[k - 1].second);
            ans += res;
        }
    }

    printf("%lld", ans);
    return 0;
}
