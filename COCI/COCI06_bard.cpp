#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int maxn = 55;

bitset <N> bs[maxn];
int n, q;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        int num; cin >> num;
        bool one = false;
        vector <int> vec;

        for (int j = 0; j < num; j++) {
            int x;
            cin >> x;
            one |= (x == 1);
            vec.push_back(x);
        }

        if (one) for (auto k: vec) bs[k].set(i);
        else {
            bitset <N> temp;
            for (auto k: vec) temp |= bs[k];
            for (auto k: vec) bs[k] = temp;
        }
    }

    for (int i = 1; i <= n; i++) if (bs[i].count() == bs[1].count()) cout << i << "\n";
    return 0;
}
