#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <set>
#include <stack>
#include <queue>
#include <map>
#include <cstring>
#include <string>
#include <memory.h>
#include <list>
#include <deque>
#include <cstdlib>

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define INF 1000000009
#define N 500005
#define maxn 1000005

using namespace std;

typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef pair <int, ii> iii;
typedef vector <iii> viii;
typedef long long LL;

struct Words {
    string name;
    LL sum;
    LL mul;
    LL sub;

    Words (string name, LL sum, LL mul, LL sub)
    {
        this->name = name;
        this->sum = sum;
        this->mul = mul;
        this->sub = sub;
    }
};

int main(){
    //freopen("main.inp", "r", stdin);
    //freopen("main.out", "w", stdout);
    freopen("words.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    vector <Words> v;
    while (getline(cin, s))
    {
        if (s == "#") break;
        LL sum = 0;
        LL mul = 1;
        LL sub = 0;
        for (LL i = 0; i<s.length(); i++)
        {
            sum += (s[i] - 95);
            mul *= (s[i] - 95);
            sub -= (s[i] - 95);
        }
        Words w = Words(s, sum, mul, sub);
        v.pb(w);
        //if (s == "hairstyle") cout << sum << " " << mul << " " << sub << "\n";
    }

    cin.clear();
    freopen("anagin.txt", "r", stdin);
    freopen("anagout.txt", "w", stdout);

    while (getline(cin, s))
    {
        if (s == "#") break;

        LL sum = 0;
        LL mul = 1;
        LL sub = 0;
        for (LL i = 0; i<s.length(); i++)
        {
            if (s[i] == ' ') continue;
            sum += (s[i] - 95);
            mul *= (s[i] - 95);
            sub -= (s[i] - 95);
        }

        bool flag = false;
        for (LL i = 0; i<v.size(); i++)
        {
            if (v[i].sum == sum && v[i].mul == mul && v[i].sub == sub)
            {
                cout << v[i].name << " ";
                flag = true;
            }
        }
        if (!flag) cout << "No anagram found";
        cout << "\n";
        //if (s == "relay this") cout << sum << " " << mul << " " << sub << "\n";
    }
    return 0;
}
