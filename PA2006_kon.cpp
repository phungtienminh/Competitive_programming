#include <bits/stdc++.h>

using namespace std;

const int mod = 10;

int n;

struct Matrix {
    int a[2][2];

    Matrix(){
        memset(a, 0, sizeof(a));
    }

    Matrix (int b, int c, int d, int e) {
        this->a[0][0] = b;
        this->a[1][0] = c;
        this->a[0][1] = d;
        this->a[1][1] = e;
    }

    Matrix mul (Matrix a, Matrix b) {
        Matrix c = Matrix();
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
                }
            }
        }

        return c;
    }

    Matrix Pow (Matrix a, int n) {
        if (n == 1) return a;

        Matrix temp = Pow(a, n / 2);
        temp = mul(temp, temp);
        if (n & 1) return mul(temp, a);
        return temp;
    }
} mt;

void input(){
    scanf("%d", &n);
}

void solve(){
    Matrix base = Matrix(0, 1, 1, 1);
    Matrix ans = mt.Pow(base, n);
    printf("%d", ans.a[1][1]);
}

int main(){
    input();
    solve();
    return 0;
}
