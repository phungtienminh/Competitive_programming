#include <bits/stdc++.h>

#define int long long

using namespace std;

vector <int> dvs;

signed main(){
    //freopen("ANTIPRIME.inp", "r", stdin);
    //freopen("ANTIPRIME.out", "w", stdout);

    int n;
    scanf("%lld", &n);
    dvs.push_back(1); dvs.push_back(2); dvs.push_back(4); dvs.push_back(6); dvs.push_back(12); dvs.push_back(24);
    dvs.push_back(36); dvs.push_back(48); dvs.push_back(60); dvs.push_back(120); dvs.push_back(180); dvs.push_back(240);
    dvs.push_back(360); dvs.push_back(720); dvs.push_back(840); dvs.push_back(1260); dvs.push_back(1680); dvs.push_back(2520);
    dvs.push_back(5040); dvs.push_back(7560); dvs.push_back(10080); dvs.push_back(15120); dvs.push_back(20160); dvs.push_back(25200);
    dvs.push_back(27720); dvs.push_back(45360); dvs.push_back(50400); dvs.push_back(55440); dvs.push_back(83160); dvs.push_back(110880);
    dvs.push_back(166320); dvs.push_back(221760); dvs.push_back(277200); dvs.push_back(332640); dvs.push_back(498960); dvs.push_back(554400);
    dvs.push_back(665280); dvs.push_back(720720); dvs.push_back(1081080); dvs.push_back(1441440); dvs.push_back(2162160); dvs.push_back(2882880);
    dvs.push_back(3603600); dvs.push_back(4324320); dvs.push_back(6486480); dvs.push_back(7207200); dvs.push_back(8648640); dvs.push_back(10810800);
    dvs.push_back(14414400); dvs.push_back(17297280); dvs.push_back(21621600); dvs.push_back(32432400); dvs.push_back(36756720); dvs.push_back(43243200);
    dvs.push_back(61261200); dvs.push_back(73513440); dvs.push_back(110270160); dvs.push_back(122522400); dvs.push_back(147026880); dvs.push_back(183783600);
    dvs.push_back(245044800); dvs.push_back(294053760); dvs.push_back(367567200); dvs.push_back(551350800); dvs.push_back(698377680); dvs.push_back(735134400);
    dvs.push_back(1102701600); dvs.push_back(1396755360); dvs.push_back(2000000001);
    int pos = lower_bound(dvs.begin(), dvs.end(), n) - dvs.begin();
    if (dvs[pos] > n) pos--;
    printf("%lld", dvs[pos]);
    return 0;
}
