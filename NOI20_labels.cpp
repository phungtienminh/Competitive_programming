#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int n, d[N], a[N];
long long f[N];
map <long long, int> mm;

void solve(){
    mm[f[0]] = 0;
    pair <int, int> temp = make_pair(-1, -1);

    for (int i = 1; i <= n - 1; i++) {
        if (mm.count(f[i] - (n - 1))) {
            temp = make_pair(mm[f[i] - (n - 1)] + 1, i + 1);
            break;
        }

        mm[f[i]] = i;
    }

    if (temp.first == -1) { return; }
    a[temp.first] = 1, a[temp.second] = n;
    for (int i = temp.first + 1; i < temp.second; i++) a[i] = d[i - 1] + a[i - 1];
    for (int i = temp.first - 1; i >= 1; i--) a[i] = a[i + 1] - d[i];
    for (int i = temp.second + 1; i <= n; i++) a[i] = a[i - 1] + d[i - 1];
    for (int i = 1; i <= n - 1; i++) if (a[i + 1] - a[i] != d[i]) return;
    for (int i = 1; i <= n; i++) if (a[i] < 1 || a[i] > n) return;
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
    exit(0);
}

void solve2(){
    mm.clear();
    mm[f[0]] = 0;
    pair <int, int> temp = make_pair(-1, -1);

    for (int i = 1; i <= n - 1; i++) {
        if (mm.count(f[i] + (n - 1))) {
            temp = make_pair(mm[f[i] + (n - 1)] + 1, i + 1);
            break;
        }

        mm[f[i]] = i;
    }

    if (temp.first == -1) { cout << -1 << "\n", exit(0); }
    a[temp.first] = n, a[temp.second] = 1;
    for (int i = temp.first + 1; i < temp.second; i++) a[i] = d[i - 1] + a[i - 1];
    for (int i = temp.first - 1; i >= 1; i--) a[i] = a[i + 1] - d[i];
    for (int i = temp.second + 1; i <= n; i++) a[i] = a[i - 1] + d[i - 1];
    for (int i = 1; i <= n - 1; i++) if (a[i + 1] - a[i] != d[i]) cout << -1 << "\n", exit(0);
    for (int i = 1; i <= n; i++) if (a[i] < 1 || a[i] > n) cout << -1 << "\n", exit(0);
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
    exit(0);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) cin >> d[i], f[i] = f[i - 1] + d[i];
    solve();
    solve2();
    return 0;
}
