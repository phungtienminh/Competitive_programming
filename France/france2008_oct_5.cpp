#include <bits/stdc++.h>

using namespace std;

vector <vector <char> > solve (int n) {
    vector <vector <char> > ans;
    ans.assign((1 << n) + 1, vector <char>((1 << n) + 1, '.'));
    if (n == 1) {
        ans[1][1] = '@'; ans[2][1] = '*'; ans[2][2] = '#';
        return ans;
    }

    vector <vector <char> > res = solve(n - 1);
    for (int i = 1; i <= (1 << (n - 2)); i++) {
        for (int j = 1; j <= (1 << (n - 2)); j++) {
            ans[i + (1 << (n - 1))][j] = res[i][j];
            ans[i + (1 << (n - 1)) - (1 << (n - 2))][j + (1 << (n - 2))] = res[i][j];
        }
    }

    for (int i = (1 << (n - 2)) + 1; i <= (1 << (n - 1)); i++) {
        for (int j = 1; j <= (1 << (n - 1)); j++) {
            ans[i + (1 << (n - 1))][j] = res[i][j];
            ans[i + (1 << (n - 1)) - (1 << (n - 2))][j + (1 << (n - 2))] = res[i][j];
        }
    }

    for (int i = 1; i <= (1 << (n - 2)); i++) {
        for (int j = 1; j <= (1 << (n - 1)); j++) {
            ans[i][j] = res[(1 << (n - 1)) - j + 1][i];
        }
    }

    for (int i = (1 << (n - 2)) + 1; i <= (1 << (n - 1)); i++) {
        for (int j = 1; j <= (1 << (n - 2)); j++) {
            ans[i][j] = res[(1 << (n - 1)) - j + 1][i];
        }
    }

    for (int i = (1 << (n - 1)) + 1; i <= (1 << (n - 1)) + (1 << (n - 2)); i++) {
        for (int j = (1 << (n - 1)) + (1 << (n - 2)) + 1; j <= (1 << n); j++) {
            ans[i][j] = res[j - (1 << (n - 1))][(1 << (n - 1)) - (i - (1 << (n - 1)) - 1)];
        }
    }

    for (int i = (1 << (n - 1)) + (1 << (n - 2)) + 1; i <= (1 << n); i++) {
        for (int j = (1 << (n - 1)) + 1; j <= (1 << n); j++) {
            ans[i][j] = res[j - (1 << (n - 1))][(1 << (n - 1)) - (i - (1 << (n - 1)) - 1)];
        }
    }

    return ans;
}

int main(){
    int n;
    scanf("%d", &n);
    vector <vector <char> > vec = solve(n);
    for (int i = 1; i <= (1 << (n - 1)); i++) {
        for (int j = 1; j <= (1 << (n - 1)); j++) {
            printf("%c", vec[i][j]);
        }

        puts("");
    }

    for (int i = (1 << (n - 1)) + 1; i <= (1 << n); i++) {
        for (int j = 1; j <= (1 << n); j++) {
            printf("%c", vec[i][j]);
        }

        puts("");
    }
    return 0;
}
