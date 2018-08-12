#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    scanf("%d", &n);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n / i; j++) {
            ans++;
        }
    }

    printf("%d", ans);
    return 0;
}
