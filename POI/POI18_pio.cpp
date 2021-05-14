#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, hmax, hmin;
vector <int> h;

void input(){
    scanf("%d", &n);
    hmax = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        h.push_back(x);
        hmax = max(hmax, x);
    }

    hmin = hmax - 1000;
}

vector <int> calc (vector <int> v) {
    vector <int> ans(n, -1);
    int mx = hmin;
    for (int i = n - 1; i >= 0; i--) {
        if (v[i] > mx) {
            mx = v[i];
            for (int x = 1; x <= 1000; x++) {
                int pos = i - (x - 1) * (x - 1) - 1;
                if (pos >= 0 && pos < n) ans[pos] = max(ans[pos], h[i] + x);
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) ans[i] = max(ans[i], ans[i + 1]);
    return ans;
}

void solve(){
    vector <int> ans1 = calc(h);
    reverse(h.begin(), h.end());
    vector <int> ans2 = calc(h);
    reverse(h.begin(), h.end());
    reverse(ans2.begin(), ans2.end());

    for (int i = 0; i < n; i++) printf("%d\n", max(max(ans1[i], ans2[i]), h[i]) - h[i]);
}

int main(){
    input();
    solve();
    return 0;
}
