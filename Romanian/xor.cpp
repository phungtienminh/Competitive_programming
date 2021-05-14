#include <bits/stdc++.h>

using namespace std;

const int N = 35;

int t, mod, r1, c1, r2, c2, row[N], col[N];

int main(){
    #ifndef Futymy
        freopen("xor.in", "r", stdin);
        freopen("xor.out", "w", stdout);
    #endif // Futymy
    scanf("%d %d", &t, &mod);
    while (t--) {
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        int ans = 0;

        for (int i = 30; i >= 0; i--) {
            int pos = 0;
            for (int j = i; j <= 30; j++) {
                if (r1 & (1 << j)) continue;
                pos = j;
                break;
            }

            int temp = r1 | (1 << pos);
            for (int j = pos - 1; j >= 0; j--) temp &= ~(1 << j);
            int tmp = temp;
            temp |= (1 << i);
            if (temp > r2) {
                //cout << tmp << "\n";
                if (pos == i) {
                    row[i] = 0;
                    continue;
                }
                if (tmp <= r2) row[i] = tmp - r1;
                else row[i] = r2 + 1 - r1;
            }
            else {
                int val = (r2 - temp) / (1 << (i + 1));
                int last = temp + val * (1 << (i + 1));
                row[i] = (last - temp) / (1 << (i + 1)) * (1 << i) + min(r2 - last + 1, 1 << i) + (pos != i ? tmp - r1 : 0);
            }
        }

        //for (int i = 0; i <= 30; i++) cout << row[i] << " ";
        //cout << "\n";
        for (int i = 30; i >= 0; i--) {
            int pos = 0;
            for (int j = i; j <= 30; j++) {
                if (c1 & (1 << j)) continue;
                pos = j;
                break;
            }

            int temp = c1 | (1 << pos);
            for (int j = pos - 1; j >= 0; j--) temp &= ~(1 << j);
            int tmp = temp;
            temp |= (1 << i);
            if (temp > c2) {
                if (pos == i) {
                    col[i] = 0;
                    continue;
                }

                if (tmp <= c2) col[i] = tmp - c1;
                else col[i] = c2 + 1 - c1;
            }
            else {
                int val = (c2 - temp) / (1 << (i + 1));
                int last = temp + val * (1 << (i + 1));
                col[i] = (last - temp) / (1 << (i + 1)) * (1 << i) + min(c2 - last + 1, 1 << i) + (pos != i ? tmp - c1 : 0);
            }
        }

        //for (int i = 0; i <= 30; i++) cout << col[i] << " ";
        //cout << "\n";
        for (int i = 30; i >= 0; i--) {
            ans += (1LL << i) % mod * (1LL * row[i] * (c2 - c1 + 1 - col[i]) % mod + 1LL * col[i] * (r2 - r1 + 1 - row[i]) % mod) % mod;
            if (ans >= mod) ans -= mod;
            //cout << ans << "\n";
        }

        printf("%d\n", ans);
    }
    return 0;
}
/*
5 29473 1 3 2 4 2 2 12 15 10000 10000 11000 11000 123 51 54667341 1878099 1234567 1234567 1234678 1234678

1 3000
1 1 3 5

1 29473
123 51 54667341 1878099
*/
