#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;

int readInt() {
    int ans = 0;
    char c;

    while (1) {
        c = getchar();
        if (c == ' ' || c == '\n') break;

        ans = ans * 10 + (c - '0');
    }

    return ans;
}

int a[N], b[N], t, n;

int main(){
    t = readInt();

    //1 2 3 3 4 5
    //1 3 2 4 3 5
    while (t--) {
        n = readInt();
        for (int i = 1; i <= n; i++) a[i] = readInt();
        for (int i = 1; i <= n; i++) b[i] = a[i];
        sort(b + 1, b + n + 1);

        int pos = 0;
        for (int i = 1; i * 2 - 1 <= n; i++) {
            a[i * 2 - 1] = b[i];

            if ((i + 1) * 2 - 1 > n) pos = i;
        }

        int cur = 2;
        for (int i = pos + 1; i <= n; i++) {
            a[cur] = b[i];
            cur += 2;
        }

        bool ok = true;
        for (int i = 1; i <= n - 2; i++) {
            if (a[i] == a[i + 1] || a[i + 1] == a[i + 2]) ok = false;
            if (a[i] < a[i + 1] && a[i + 1] < a[i + 2]) ok = false;
            if (a[i] > a[i + 1] && a[i + 1] > a[i + 2]) ok = false;

            if (!ok) break;
        }

        if (a[n - 1] == a[n]) ok = false;

        if (ok) puts("TAK");
        else {
            int pos = 0;
            for (int i = 1; i * 2 <= n; i++) {
                a[i * 2] = b[i];

                if ((i + 1) * 2 > n) pos = i;
            }

            int cur = 1;
            for (int i = pos + 1; i <= n; i++) {
                a[cur] = b[i];
                cur += 2;
            }

            ok = true;
            for (int i = 1; i <= n - 2; i++) {
                if (a[i] == a[i + 1] || a[i + 1] == a[i + 2]) ok = false;
                if (a[i] < a[i + 1] && a[i + 1] < a[i + 2]) ok = false;
                if (a[i] > a[i + 1] && a[i + 1] > a[i + 2]) ok = false;

                if (!ok) break;
            }

            if (a[n - 1] == a[n]) ok = false;

            if (ok) puts("TAK");
            else puts("NIE");
        }
    }
    return 0;
}
