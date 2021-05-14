#include <bits/stdc++.h>

using namespace std;

int n, ans = 0;
vector <pair <int, int> > vec;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        vec.push_back({x, 0});
    }

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        vec.push_back({x, 1});
    }

    sort(vec.begin(), vec.end());
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i - 1].second ^ vec[i].second) {
            ans++;
            i++;
        }
    }

    printf("%d", ans);
    return 0;
}
