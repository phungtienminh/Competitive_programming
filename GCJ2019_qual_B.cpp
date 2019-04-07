#include <bits/stdc++.h>

using namespace std;

int t, n;
string s;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int T = 1; T <= t; T++) {
        cin >> n >> s;
        cout << "Case #" << T << ": ";
        for (int i = 0; i < 2 * n - 2; i++) {
            if (s[i] == 'E') cout << "S";
            else cout << "E";
        }

        cout << "\n";
    }

    return 0;
}
