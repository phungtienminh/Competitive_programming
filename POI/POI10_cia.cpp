#include <bits/stdc++.h>

using namespace std;

vector <char> v;

int main(){
    int n;
    scanf("%d", &n);

    if (n == 1) printf("%d\na\n", 1);
    else if (n == 2) printf("%d\nab\n", 2);
    else if (n == 3) printf("%d\naba\n", 2);
    else {
        printf("%d\n", 3);

        v.push_back('0');
        int cnt = 1;

        while (cnt < n) {
            if (cnt * 2 <= n) {
                for (int i = 0; i < cnt; i++) v.push_back((v[i] == '0' ? '1' : '0'));
                cnt *= 2;
            }
            else {
                for (int i = 0; i < n - cnt; i++) v.push_back((v[i] == '0' ? '1' : '0'));
                cnt *= 2;
            }
        }

        char last = '0';
        v[0] = 'a';
        for (int i = 1; i < v.size(); i++) {
            char c;
            if (v[i] == '0') c = 'a';
            else c = 'b';

            if (v[i] == last) c = 'c';
            last = v[i];
            v[i] = c;
        }

        for (int i = 0; i < v.size(); i++) printf("%c", v[i]);
        puts("");
    }
    return 0;
}
