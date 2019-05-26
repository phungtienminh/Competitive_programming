#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x, y, x2, y2;
    Rect (int x = 0, int y = 0, int x2 = 0, int y2 = 0): x(x), y(y), x2(x2), y2(y2) {}
};

int n, k;
vector <Rect> vec;
long long ans = 1e18;

int round_up (int n, int r) {
    return n % r == 0 ? n + 1 : n + r - n % r + 1;
}

int round_down (int n, int r) {
    return n % r == 0 ? n - r : n - n % r;
}

bool is_black (int x, int y, int len) {
    int cellx = (x % len == 0 ? x / len : x / len + 1) % 2;
    int celly = (y % len == 0 ? y / len : y / len + 1) % 2;
    return cellx == celly;
}

int getcellx (int x, int len) {
    return x % len == 0 ? x / len : x / len + 1;
}

int getcelly (int y, int len) {
    return y % len == 0 ? y / len : y / len + 1;
}

long long solve (int len) {
    int nsquare = n / len; //Number of square in each row and each column
    long long res = (1LL * nsquare * nsquare + 1) / 2 * len * len; //initialize result as number of needed black squares
    //if (len == 2) cout << res << "\n";
    for (auto rect: vec) {
        int x = rect.x, y = rect.y, x2 = rect.x2, y2 = rect.y2;
        int upx = round_up(x, len), upy = round_up(y, len), downx = round_down(x2, len), downy = round_down(y2, len);
        //if (len == 2) cout << upx << " " << upy << " " << downx << " " << downy << "\n";
        if (downx >= upx && downy >= upy) {
            long long sq = 1LL * (downx - upx + 1) * (downy - upy + 1) / len / len;
            long long nblack = is_black(x, y, len) ? (sq + 1) / 2 : sq / 2;
            long long nwhite = sq - nblack;
            res -= nblack * len * len, res += nwhite * len * len;
        }
        //if (len == 2) cout << res << "\n";
        if (downx >= upx) {
            long long sq = 1LL * (downx - upx + 1) / len;
            long long nblack = is_black(x, y, len) ? sq / 2 : (sq + 1) / 2;
            long long nwhite = sq - nblack;
            res -= nblack * len * (min(upy - 1, y2) - y + 1);
            res += nwhite * len * (min(upy - 1, y2) - y + 1);
            if (getcelly(y, len) != getcelly(y2, len)) {
                nblack = is_black(x, y2, len) ? sq / 2 : (sq + 1) / 2;
                nwhite = sq - nblack;
                res -= nblack * len * (y2 - max(y, downy + 1) + 1);
                res += nwhite * len * (y2 - max(y, downy + 1) + 1);
            }
        }
        //if (len == 2) cout << res << "\n";
        if (downy >= upy) {
            long long sq = 1LL * (downy - upy + 1) / len;
            long long nblack = is_black(x, y, len) ? sq / 2 : (sq + 1) / 2;
            long long nwhite = sq - nblack;
            res -= nblack * len * (min(upx - 1, x2) - x + 1);
            res += nwhite * len * (min(upx - 1, x2) - x + 1);
            if (getcellx(x, len) != getcellx(x2, len)) {
                nblack = is_black(x2, y, len) ? sq / 2 : (sq + 1) / 2;
                nwhite = sq - nblack;
                res -= nblack * len * (x2 - max(x, downx + 1) + 1);
                res += nwhite * len * (x2 - max(x, downx + 1) + 1);
            }
        }

        if (getcellx(x, len) == getcellx(x2, len) && getcelly(y, len) == getcelly(y2, len)) {
            if (is_black(x, y, len)) res -= 1LL * (x2 - x + 1) * (y2 - y + 1);
            else res += 1LL * (x2 - x + 1) * (y2 - y + 1);
        }
        else if (getcellx(x, len) == getcellx(x2, len)) {
            if (is_black(x, y, len)) res -= 1LL * (x2 - x + 1) * (upy - y);
            else res += 1LL * (x2 - x + 1) * (upy - y);

            if (is_black(x, y2, len)) res -= 1LL * (x2 - x + 1) * (y2 - downy);
            else res += 1LL * (x2 - x + 1) * (y2 - downy);
        }
        else if (getcelly(y, len) == getcelly(y2, len)) {
            if (is_black(x, y, len)) res -= 1LL * (upx - x) * (y2 - y + 1);
            else res += 1LL * (upx - x) * (y2 - y + 1);

            if (is_black(x2, y, len)) res -= 1LL * (x2 - downx) * (y2 - y + 1);
            else res += 1LL * (x2 - downx) * (y2 - y + 1);
        }
        else {
            if (is_black(x, y, len)) res -= 1LL * (upx - x) * (upy - y);
            else res += 1LL * (upx - x) * (upy - y);

            if (is_black(x2, y, len)) res -= 1LL * (x2 - downx) * (upy - y);
            else res += 1LL * (x2 - downx) * (upy - y);

            if (is_black(x, y2, len)) res -= 1LL * (upx - x) * (y2 - downy);
            else res += 1LL * (upx - x) * (y2 - downy);

            if (is_black(x2, y2, len)) res -= 1LL * (x2 - downx) * (y2 - downy);
            else res += 1LL * (x2 - downx) * (y2 - downy);
        }
    }

    return res;
}

long long calc() {
    long long res = (1LL * n * n + 1) / 2;
    for (auto rect: vec) {
        int x = rect.x, y = rect.y, x2 = rect.x2, y2 = rect.y2;
        long long sq = 1LL * (x2 - x + 1) * (y2 - y + 1);
        long long nblack = is_black(x, y, 1) ? (sq + 1) / 2 : sq / 2;
        long long nwhite = sq - nblack;
        res -= nblack; res += nwhite;
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        int x, y, x2, y2;
        cin >> x >> y >> x2 >> y2;
        vec.push_back(Rect(x, y, x2, y2));
    }

    long long res = calc();
    ans = min(ans, min(res, 1LL * n * n - res));
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            long long temp = solve(i);
            ans = min(ans, min(temp, 1LL * n * n - temp));
            temp = solve(n / i);
            ans = min(ans, min(temp, 1LL * n * n - temp));
        }
    }

    cout << ans;
    return 0;
}
/*
6 8
3 3 3 3
1 2 1 2
3 4 3 4
5 5 5 5
4 3 4 3
4 4 4 4
2 1 2 1
3 6 3 6
*/
