#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

vector <int> vec[N];
int n, q, cnt[N], Max = 0;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        vec[a].push_back(b);
        Max = max(Max, a);
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        cnt[a] += b;
        Max = max(Max, a);
    }

    int ans = 0;
    for (int i = 0; i <= Max; i++) {
        sort(vec[i].begin(), vec[i].end());
        if (vec[i].size() < cnt[i]) return !printf("NIE");
        else {
            for (int j = 0; j < cnt[i]; j++) ans += vec[i][j];
            for (int j = cnt[i]; j < (int)vec[i].size() - 1; j += 2) vec[i + 1].push_back(vec[i][j] + vec[i][j + 1]);
        }
    }

    printf("%d", ans);
    return 0;
}
