#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int a[N], n, m;
vector <int> pos[N];

void input(){
    srand(time(0));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]].push_back(i);
    }
}

void solve(){
    while (m--) {
        int l, r;
        scanf("%d %d", &l, &r);

        int cnt = 0;
        while (cnt < 25) {
            int x = rand() % (r - l + 1) + l; x = a[x];
            int dist = upper_bound(pos[x].begin(), pos[x].end(), r) - lower_bound(pos[x].begin(), pos[x].end(), l);

            if (dist * 2 > (r - l + 1)) {
                printf("%d\n", x);
                break;
            }

            cnt++;
        }

        if (cnt == 25) puts("0");
    }
}

int main(){
    input();
    solve();
    return 0;
}
