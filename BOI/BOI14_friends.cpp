#include <bits/stdc++.h>

using namespace std;

const int N = 2e6 + 5;
const int base = 317;
const int mod = 1e9 + 2277;

int n, Hash[N], Pow[N], cnt[26];
char s[N];
set <int> st;

void prepare(){
    Pow[0] = 1;
    for (int i = 1; i < N; i++) Pow[i] = (1LL * Pow[i - 1] * base) % mod;
    for (int i = 1; i <= n; i++) Hash[i] = (1LL * Hash[i - 1] * base + s[i]) % mod;
}

int get (int l, int r) {
    if (l > r) return 0;
    return ((1LL * Hash[r] - 1LL * Hash[l - 1] * Pow[r - l + 1] % mod) % mod + mod) % mod;
}

int main(){
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++) cnt[s[i] - 'A']++;
    int odd = 0;
    for (int i = 0; i < 26; i++) if (cnt[i] & 1) odd++;

    if (odd != 1) return !printf("NOT POSSIBLE");
    prepare();

    int res = 0;
    int pos;

    for (int i = 1; i <= n; i++) {
        if (cnt[s[i] - 'A'] % 2 == 0) continue;
        if (i < (n + 1) / 2) {
            int cur = get(1, i - 1);
            int nxt = get(i + 1, (n + 1) / 2);
            int cur2 = get((n + 1) / 2 + 1, (n + 1) / 2 + 1 + i - 2);
            int nxt2 = get((n + 1) / 2 + 1 + i - 1, n);

            if (cur == cur2 && nxt == nxt2) {
                res++;
                st.insert(get((n + 1) / 2 + 1, n));
                if (res == 1) pos = i;
            }
        }
        else if (i == (n + 1) / 2) {
            int cur = get(1, i - 1);
            int nxt = get(i + 1, n);
            if (cur == nxt) {
                res++;
                st.insert(get(1, i - 1));
                if (res == 1) pos = i;
            }
        }
        else {
            int cur = get((n + 1) / 2, i - 1);
            int nxt = get(i + 1, n);
            int cur2 = get(1, i - (n + 1) / 2);
            int nxt2 = get(i - (n + 1) / 2 + 1, i - (n + 1) / 2 + n - (i + 1));
            if (cur == cur2 && nxt == nxt2) {
                res++;
                st.insert(get(1, (n + 1) / 2 - 1));
                if (res == 1) pos = i;
            }
        }
    }

    if (st.size() > 1) printf("NOT UNIQUE");
    else {
        int dem = 0, ptr = 1;
        while (dem < n / 2) {
            if (ptr == pos) {
                ptr++;
                continue;
            }
            dem++;
            printf("%c", s[ptr++]);
        }
    }
    return 0;
}
