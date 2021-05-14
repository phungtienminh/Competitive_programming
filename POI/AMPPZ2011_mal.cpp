#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int a[N], n;

void input(){
    scanf("%d", &n);
}

void solve(){
    if (n % 2 == 0) {
        a[1] = n / 2; a[n] = n / 2 + 1;

        int cur = n / 2 + 2;
        for (int i = 2; i <= n / 2; i = i + 2) {
            a[i] = cur;
            cur += 2;
        }

        cur = n / 2 - 2;
        for (int i = 3; i <= n / 2; i = i + 2) {
            a[i] = cur;
            cur -= 2;
        }

        cur = n / 2 - 1;
        for (int i = n - 1; i > n / 2; i = i - 2) {
            a[i] = cur;
            cur -= 2;
        }

        cur = n / 2 + 3;
        for (int i = n - 2; i > n / 2; i = i - 2) {
            a[i] = cur;
            cur += 2;
        }
    }
    else {
        if (n % 4 == 3) {
            a[1] = n / 2; a[n] = n / 2 + 1;

            int cur = n / 2 + 2;
            for (int i = 2; i <= (n + 1) / 2; i = i + 2) {
                a[i] = cur;
                cur += 2;
            }

            cur = n / 2 - 2;
            for (int i = 3; i <= (n + 1) / 2; i = i + 2) {
                a[i] = cur;
                cur -= 2;
            }

            cur = n / 2 + 3;
            for (int i = n - 1; i > (n + 1) / 2; i = i - 2) {
                a[i] = cur;
                cur += 2;
            }

            cur = n / 2 - 1;
            for (int i = n - 2; i > (n + 1) / 2; i = i - 2) {
                a[i] = cur;
                cur -= 2;
            }
        }
        else {
            a[1] = n / 2; a[n] = n / 2 + 1;

            int cur = n / 2 + 2;
            for (int i = 2; i < (n + 1) / 2; i = i + 2) {
                a[i] = cur;
                cur += 2;
            }

            cur = n / 2 - 2;
            for (int i = 3; i < (n + 1) / 2; i = i + 2) {
                a[i] = cur;
                cur -= 2;
            }

            cur = n / 2 + 3;
            for (int i = n - 1; i >= (n + 1) / 2; i = i - 2) {
                a[i] = cur;
                cur += 2;
            }

            cur = n / 2 - 1;
            for (int i = n - 2; i >= (n + 1) / 2; i = i - 2) {
                a[i] = cur;
                cur -= 2;
            }
        }
    }

    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
}

int main(){
    input();
    solve();
    return 0;
}
