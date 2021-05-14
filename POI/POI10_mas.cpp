#include <bits/stdc++.h>
using namespace std;

bool ok = false;
int num[10];
bool used[10];
int n;
int a[10][12];

void bt (int pos) {
    if (ok) return;
    if (pos == n + 1) {
        bool f = true;
        for (int i = 1; i <= n; i++) {
            f = false;
            int sum = 0;
            int res = 0;

            for (int j = 1; j <= n; j++) {
                for (int k = 3; k <= n + 2; k++) {
                    if (num[j] == a[i][k]) {
                        if (k == j + 2) sum += num[j];
                        else res += num[j];
                    }
                }
            }

            if (sum == a[i][1] && res == a[i][2]) f = true;

            if (!f) return;
        }

        if (f) {
            ok = true;
            for (int i = 1; i <= n; i++) {
                if (i > 1) cout << " ";
                cout << num[i];
            }
            cout << "\n";

            return;
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = true;
            num[pos] = i;
            bt(pos + 1);
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 2; j++) {
            cin >> a[i][j];
        }
    }

    memset(used, 0, sizeof(used));
    bt(1);
    return 0;
}
