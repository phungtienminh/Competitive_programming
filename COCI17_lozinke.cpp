#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 5;

int n, ans = 0;
map <string, bitset <N> > mm;
string a[N];
bitset <N> temp;
map <string, int> mm2;

bool cmp (string s, string t) {
    if (s.length() != t.length()) return s.length() < t.length();
    return s < t;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], mm2[a[i]]++;
    sort(a + 1, a + n + 1, cmp);
    //for (int i = 1; i <= n; i++) cout << a[i] << "\n";
    for (int i = 1; i <= n; i++) {
        temp.reset();
        for (int l = 0; l < a[i].length(); l++) {
            for (int r = 0; r < a[i].length(); r++) {
                string t = a[i].substr(l, r - l + 1);
                if (mm.count(t)) temp |= mm[t];
            }
        }

        ans += temp.count();
        mm[a[i]].set(i);
    }

    for (auto i: mm2) ans += i.second * (i.second - 1) / 2;
    cout << ans;
    return 0;
}
