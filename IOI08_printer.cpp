#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

struct Trie {
    Trie *node[26];
    int num, priority;
    bool isEnd;

    Trie() {
        for (int i = 0; i < 26; i++) node[i] = NULL;
        num = 0; priority = 100000; isEnd = false;
    }
} *root = new Trie();

int n, nNode = 0;
vector <char> ans;
vector <string> vec;

void add (string s, int id) {
    Trie *cur = root;
    for (int i = 0; i < s.length(); i++) {
        if (cur -> node[s[i] - 'a'] == NULL) {
            cur -> node[s[i] - 'a'] = new Trie();
            cur = cur -> node[s[i] - 'a'];
            cur -> num = ++nNode;
            cur -> priority = id;
        } else {
            cur = cur -> node[s[i] - 'a'];
            cur -> priority = max(cur -> priority, id);
        }
    }

    cur -> isEnd = true;
}

void dfs (Trie *cur, char c, int p) {
    if (c != '#') ans.push_back(c);
    if (cur -> isEnd) ans.push_back('P');

    vector <pair <int, int> > tmp;
    for (int i = 0; i < 26; i++) {
        if (cur -> node[i] == NULL) continue;
        if (cur -> node[i] -> num == p) continue;
        tmp.push_back(make_pair(cur -> node[i] -> priority, i));
        //dfs(cur -> node[i], (char)(i + 'a'), cur -> num);
    }

    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < tmp.size(); i++) {
        dfs(cur -> node[tmp[i].second], (char)(tmp[i].second + 'a'), cur -> num);
    }

    ans.push_back('-');
}

bool cmp (string s, string t) {
    if (s.length() != t.length()) return s.length() < t.length();
    return s < t;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vec.push_back(s);
    }

    sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < vec.size(); i++) add(vec[i], i);

    dfs(root, '#', 0);
    while (ans.size() > 0 && ans[ans.size() - 1] == '-') ans.pop_back();

    cout << (int)ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << "\n";
    return 0;
}
