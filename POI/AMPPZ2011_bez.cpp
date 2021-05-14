#include <bits/stdc++.h>

using namespace std;

int t;
long long a, b;

int main(){
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", a + b);
    }
    return 0;
}
