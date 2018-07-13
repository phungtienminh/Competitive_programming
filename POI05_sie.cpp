#include <bits/stdc++.h>

using namespace std;

const int N = 205;
int a[N][N];

int main(){
    vector <pair <int, int> > ans;
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            bool ok = true;
            for (int k = 1; k <= n; k++) {
                if (k != i && k != j && a[i][k] + a[k][j] == a[i][j]) {
                    ok = false;
                    break;
                }
            }

            if (ok) ans.push_back(make_pair(i, j));
        }
    }

    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
