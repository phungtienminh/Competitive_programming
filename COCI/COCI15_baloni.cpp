#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, a[N], ans = 0;
set <int> pos[N];
bool used[N];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), pos[a[i]].insert(i);
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        ans++;
        int pt = a[i], lst = i;
        while (pt >= 1) {
            auto it = pos[pt].lower_bound(lst);
            if (it == pos[pt].end()) break;
            lst = *it;
            pos[pt].erase(it);
            used[lst] = true;
            pt--;
        }
    }

    printf("%d", ans);
    return 0;
}
