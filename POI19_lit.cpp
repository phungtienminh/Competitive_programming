#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
const int maxn = 30;

int n, tree[N], a[N];
char s[N], t[N];
vector <int> pos[30];

void update (int x, int val) {
    while (x <= n) {
        tree[x] += val;
        x += x & -x;
    }
}

int get (int x) {
    int ans = 0;
    while (x > 0) {
        ans += tree[x];
        x -= x & -x;
    }

    return ans;
}

void input(){
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    memset(tree, 0, sizeof(tree));
}

void solve(){
    for (int i = n; i >= 1; i--) pos[t[i] - 'A'].push_back(i);
    for (int i = 1; i <= n; i++) {
        int cur = pos[s[i] - 'A'][pos[s[i] - 'A'].size() - 1];
        a[cur] = i;
        pos[s[i] - 'A'].pop_back();
    }

    long long ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += get(a[i] - 1);
        update(a[i], 1);
    }

    printf("%lld", ans);
}

int main(){
    input();
    solve();
    return 0;
}
