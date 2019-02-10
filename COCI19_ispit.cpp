#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
const int N = 505;

int n, m, cnt[26];
char a[N][N];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            memset(cnt, 0, sizeof(cnt));
            int f = -1, last = -1;
            for (int k = 1; k <= n; k++) {
                cnt[a[i][k] - 'a']++;
                cnt[a[j][k] - 'a']--;
                if (a[i][k] != a[j][k]) {
                    if (f == -1) f = k;
                    last = k;
                }
            }

            if (last - f + 1 <= m && count(cnt, cnt + 26, 0) == 26) return cout << "DA", 0;
        }
    }

    cout << "NE";
    return 0;
}
/*
10 4
bkppucotbt
pctkuobbtp
tpktuobcbp
cpubotnptb
btpcupobnt
tbctponbpu
ktcpbpuotb
ctubpnpbot
bcnotutppb
ttcbppuobk
*/
