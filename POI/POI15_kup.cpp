#include <bits/stdc++.h>

using namespace std;

const int N = 2005;

int k, n, jump[N][N], b[N][N];
long long f[N][N];

long long get (int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    return f[x2][y2] - f[x1 - 1][y2] - f[x2][y1 - 1] + f[x1 - 1][y1 - 1];
}

void go (int x1, int y1, int x2, int y2) {
	if (get(x1, y1, x2, y2) <= 2 * k) {
		printf("%d %d %d %d", y1, x1, y2, x2);
		exit(0);
	}
	if (get(x1 + 1, y1, x2, y2) >= k) go(x1 + 1, y1, x2, y2);
	else if (get(x1, y1, x2 - 1, y2) >= k) go(x1, y1, x2 - 1, y2);
	else if (get(x1, y1 + 1, x2, y2) >= k) go(x1, y1 + 1, x2, y2);
	else if (get(x1, y1, x2, y2 - 1) >= k) go(x1, y1, x2, y2 - 1);
}

void solve (int x1, int y1, int x2, int y2) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j]) jump[i][j] = jump[i - 1][j];
            else jump[i][j] = i;
        }
    }

    /*cout << "\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j] < 10) cout << b[i][j] << " ";
            else cout << "* ";
        }
        cout << "\n";
    }*/

    long long Max = 0;
    int X1, Y1, X2, Y2;

    for (int i = x1; i <= x2; i++) {
        stack <int> st;
        int r = y1, Min = 1e9;

        while (r <= y2) {
            if (st.empty() || b[i][st.top()] <= b[i][r]) Min = min(Min, b[i][r]), st.push(r++);
            else {
                int val = st.top(); st.pop();
                long long sum;

                if (st.empty()) {
                    //sum = 1LL * b[i][val] * (r - 1);
                    sum = get(jump[i][val] + 1, 1, i, r - 1);
                    if (sum > Max) {
                        Max = sum;
                        Y1 = 1; Y2 = r - 1; X2 = i; X1 = jump[i][val] + 1;
                    }
                }
                else {
                    //sum = 1LL * b[i][val] * (r - 1 - st.top());
                    sum = get(jump[i][val] + 1, st.top() + 1, i, r - 1);
                    if (sum > Max) {
                        Max = sum;
                        X2 = i; Y2 = r - 1; Y1 = st.top() + 1; X1 = jump[i][val] + 1;
                    }
                }
            }
        }

        while (!st.empty()) {
            int val = st.top(); st.pop();
            long long sum;

            if (st.empty()) {
                //sum = 1LL * b[i][val] * (r - 1);
                sum = get(jump[i][val] + 1, 1, i, r - 1);
                if (sum > Max) {
                    Max = sum;
                    Y1 = 1; Y2 = r - 1; X2 = i; X1 = jump[i][val] + 1;
                }
            }
            else {
                //sum = 1LL * b[i][val] * (r - 1 - st.top());
                sum = get(jump[i][val] + 1, st.top() + 1, i, r - 1);
                if (sum > Max) {
                    Max = sum;
                    X2 = i; Y2 = r - 1; Y1 = st.top() + 1; X1 = jump[i][val] + 1;
                }
            }
        }
    }

    Max = get(X1, Y1, X2, Y2);
    //cout << Max << "\n";
    //cout << X1 << " " << Y1 << " " << X2 << " " << Y2 << "\n";
    if (Max < k) {
        printf("NIE");
        exit(0);
    }
    if (Max <= 2 * k) {
        printf("%d %d %d %d", Y1, X1, Y2, X2);
        exit(0);
    }

    go(X1, Y1, X2, Y2);
}

int main(){
    scanf("%d %d", &k, &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &b[i][j]);
            f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + b[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j] >= k && b[i][j] <= 2 * k) {
                printf("%d %d %d %d", j, i, j, i);
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j] > 2 * k) b[i][j] = 0;
            else b[i][j] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (b[i][j]) b[i][j] += b[i - 1][j];
        }
    }

    solve(1, 1, n, n);
    printf("NIE");
    return 0;
}
/*
11 5
6 4 8 5 6
3 5 3 10 2
9 3 10 10 2
10 6 1 3 44
62 31 5 2 55
*/
