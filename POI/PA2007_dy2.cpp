#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
char s[N], t[N];

void input(){
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%s", t);
}

void solve(){
    int ans = 0;
    for (int i = 0; i < n; i++) ans += (s[i] == t[i]);
    printf("%d", ans);
}

int main(){
    input();
    solve();
    return 0;
}
