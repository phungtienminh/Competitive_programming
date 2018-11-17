#include <bits/stdc++.h>

using namespace std;

const int N = 3005;

int n, m;
vector <pair <int, int> > vec;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        vec.push_back({x, 1});
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        vec.push_back({x, 2});
    }

    sort(vec.begin(), vec.end());
    int ans = 0;
    for (auto i: vec) if (i.first <= 1440) ans++;
    printf("%d\n", ans);

    bool f1 = false, f2 = false;
    int cur1 = 0, cur2 = 0, res = 0;
    for (auto i: vec) {
        if (i.second == 1) {
            if (f2 && cur1 == cur2) res++, f2 = false;
            cur1++;

            if (cur1 > cur2) f1 = true;
        }
        else {
            if (f1 && cur2 == cur1) res++, f1 = false;
            cur2++;

            if (cur2 > cur1) f2 = true;
        }
    }
    printf("%d", res);
    return 0;
}
