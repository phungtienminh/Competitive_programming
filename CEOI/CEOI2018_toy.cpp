#include <bits/stdc++.h>

using namespace std;

int n;
int cnt = 0;
vector <int> dvs;
int ans[60000000];

void input(){
    scanf("%d", &n);
}

void bt (int pos, int rem, int sum) {
    if (pos == dvs.size()) return;
    if (rem == 1) {
        ans[++cnt] = sum;
        return;
    }

    if (rem < dvs[pos]) return;
    if (rem % dvs[pos] == 0) bt(pos, rem / dvs[pos], sum + dvs[pos] - 1);
    bt(pos + 1, rem, sum);
}

void solve(){
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            dvs.push_back(i);
            if (i * i != n) dvs.push_back(n / i);
        }
    }

    dvs.push_back(n);
    sort(dvs.begin(), dvs.end());
    bt(0, n, 0);
    sort(ans + 1, ans + cnt + 1);

    int res = 0;
    ans[0] = -1;
    for (int i = 1; i <= cnt; i++) if (ans[i] > ans[i - 1]) res++;

    printf("%d\n", (int)res);
    for (int i = 1; i <= cnt; i++) if (ans[i] > ans[i - 1]) printf("%d ", ans[i]);
}

int main(){
    input();
    solve();
    return 0;
}
