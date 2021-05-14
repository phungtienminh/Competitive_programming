#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int n, m, q;
char a[N][N];
string s;
int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
string dir[8] = {"NW", "N", "NE", "E", "SE", "S", "SW", "W"};

int main(){
    #ifndef Futymy
        freopen("huntin.txt", "r", stdin);
        freopen("huntout.txt", "w", stdout);
    #endif // Futymy
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> a[i][j];
    cin >> q;
    while (q--) {
        cin >> s;
        int ans1 = 0, ans2 = 0;
        string ans3 = "";
        int len = s.length();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int k = 0; k < 8; k++) {
                    if (i + (len - 1) * dx[k] >= 1 && i + (len - 1) * dx[k] <= n && j + (len - 1) * dy[k] >= 1 && j + (len - 1) * dy[k] <= m) {
                        bool f = true;
                        for (int l = 0; l < len; l++) {
                            if (a[i + l * dx[k]][j + l * dy[k]] != s[l]) {
                                f = false;
                                break;
                            }
                        }

                        if (f) {
                            ans1 = i; ans2 = j; ans3 = dir[k];
                            break;
                        }
                    }
                }

                if (ans1) break;
            }

            if (ans1) break;
        }

        cout << ans1 << " " << ans2 << " " << ans3 << "\n";
    }
    return 0;
}
