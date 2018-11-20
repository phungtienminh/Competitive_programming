#include <bits/stdc++.h>

using namespace std;

char a[7] = {'B', 'C', 'D', 'E', 'F', 'G', 'A'};
string magic = "CDEGCABAAGFDACBC";

int main(){
    int t;
    scanf("%d", &t);
    while (t--) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (v - u + 1 >= 32) printf("%d\n", (v - u + 1) / 16 * 16);
        else {
            int cnt = 0, cnt2 = 0;
            bool f1 = false, f2 = false;
            for (int i = u; i <= v; i++) {
                if ((i - 1) % 16 == 7 || (i - 1) % 16 == 8) {
                    if ((i - 1) % 16 == 7) f1 = true, cnt++;
                    else if (f1) cnt++;
                }

                if ((i - 1) % 16 == 0 || (i - 1) % 16 == 15) {
                    if ((i - 1) % 16 == 15) f2 = true, cnt2++;
                    else if (f2) cnt2++;
                }
            }
            if (cnt >= 2 || cnt2 >= 2) printf("%d\n", 2);
            else printf("%d\n", -1);
        }
    }
    return 0;
}
