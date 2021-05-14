#include <bits/stdc++.h>

using namespace std;

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    vector <pair <int, int> > v;

    for (int i = 1; i <= m - 1; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(make_pair(x, 1));
    }

    for (int i = 1; i <= n - 1; i++) {
        int x;
        scanf("%d", &x);
        v.push_back(make_pair(x, 2));
    }

    sort(v.begin(), v.end(), greater <pair <int, int> >());

    int hor = 1;
    int ver = 1;
    int ans = 0;

    for (int i = 0; i < v.size(); i++) {
        if (v[i].second == 1) {
            hor++;
            ans += ver * v[i].first;
        }
        else {
            ver++;
            ans += hor * v[i].first;
        }
    }

    printf("%d", ans);
    return 0;
}
