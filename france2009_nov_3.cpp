#include <bits/stdc++.h>

using namespace std;

const int N = 2005;
const int mod = 1e9 + 7;
const int base = 317;

string s, t;
int Hashs[N], Hasht[N], Pow[N];

int get_hash_s (int l, int r) {
    return (Hashs[r] - 1LL * Hashs[l - 1] * Pow[r - l + 1] % mod + mod) % mod;
}

int get_hash_t (int l, int r) {
    return (Hasht[r] - 1LL * Hasht[l - 1] * Pow[r - l + 1] % mod + mod) % mod;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> s; t = s; reverse(t.begin(), t.end());
    Pow[0] = 1;
    for (int i = 1; i < N; i++) Pow[i] = 1LL * Pow[i - 1] * base % mod;
    s = "#" + s; t = "#" + t;
    for (int i = 1; i < s.length(); i++) Hashs[i] = (1LL * Hashs[i - 1] * base + s[i]) % mod;
    for (int i = 1; i < t.length(); i++) Hasht[i] = (1LL * Hasht[i - 1] * base + t[i]) % mod;

    //cout << s << "\n" << t << "\n";
    int ans = 0;
    for (int i = 1; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            int mid = (i + j) / 2;
            int Start = t.length() - j;
            int End = t.length() - i;
            int Midrev = t.length() - mid;

            if (get_hash_s(i, mid) == get_hash_t(Start, Midrev - ((j - i + 1) % 2 == 0))) ans = max(ans, j - i + 1);
        }
    }

    cout << ans;
    return 0;
}
