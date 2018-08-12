#include <bits/stdc++.h>

using namespace std;

int t, n;

void solve(){
    int cnt = 0;
    while (n % 2 == 0) {
        cnt++;
        n /= 2;
    }

    puts(cnt % 2 == 0 ? "NIE" : "TAK");
}

void input(){
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        solve();
    }
}

int main(){
    input();
    return 0;
}
