#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int a[N];

int main(){
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int grundy = 0;
        a[0] = 0;

        for (int i = n - 1; i >= 0; i = i - 2) grundy ^= (a[i + 1] - a[i]);

        if (grundy != 0 || n == 1) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
