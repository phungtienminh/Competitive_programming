#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N], b[N], n;

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) printf("%d ", a[i] + b[n - i + 1] - a[n - i + 1]);
    return 0;
}
