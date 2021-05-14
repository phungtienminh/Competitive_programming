#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
char s[N];

void input(){
    scanf("%d", &n);
    scanf("%s", s + 1);
}

void solve(){
    int ans = 0;
    int l = 1;
    int r = 1;

    while (l <= n) {
        while (r <= n && s[r] == 'S') r++;
        ans = max(ans, r - l);

        r++; l = r;
    }

    printf("%d", ans);
}

int main(){
    input();
    solve();
    return 0;
}
