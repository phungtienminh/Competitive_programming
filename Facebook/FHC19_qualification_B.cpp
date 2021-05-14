#include <bits/stdc++.h>

using namespace std;

int t;
string s;

int main(){
    //freopen("leapfrog_ch2_.txt", "r", stdin);
    //freopen("contestant.out", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int T = 1; T <= t; T++) {
        cout << "Case #" << T << ": ";
        cin >> s;
        int cnt = 0;
        for (int j = 0; j < s.length(); j++) cnt += (s[j] == 'B');
        cout << ((cnt >= s.length() / 2 || cnt >= 2) && cnt != s.length() - 1 ? "Y\n" : "N\n");
    }
    return 0;
}
