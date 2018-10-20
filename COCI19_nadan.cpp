#include <bits/stdc++.h>

using namespace std;

int main(){
    int k, n;
    scanf("%d %d", &k, &n);
    int sum = n * (n - 1) / 2;
    for (int i = 1; i < n; i++) printf("%d\n", i);
    printf("%d", k - sum);
    return 0;
}
