#include <bits/stdc++.h>

using namespace std;

int t, n;
string s;

void solve (int test) {
    cin >> n >> s;
    int a = 0, b = 0;
    for (int i = 0; i < s.length(); i++) {
        a += (s[i] == 'A');
        b += (s[i] == 'B');
    }

    cout << "Case #" << test << ":\n";
    cout << (abs(a - b) == 1 ? "Y\n" : "N\n");
}

int main(){
    freopen("alchemy_input.txt", "r", stdin);
    freopen("alchemy_output.txt", "w", stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t;
    for (int test = 1; test <= t; test++) solve(test);
    return 0;
}
