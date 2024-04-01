/**
 * Description: A finite state automaton containing a dictionary of words, can efficiently find occurrence of words in a given string.
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Light/ACfixed.h
 * Verification: https://open.kattis.com/problems/stringmultimatching
 * Time: O(sum of lengths) build time
 */

#define MAX_N 100000
#define MAX_C 26

int id = 1, trie[MAX_N][MAX_C], slink[MAX_N], elink[MAX_N];
vector<ar<int,2>> ids[MAX_N];
vector<int> ans[MAX_N];

void add(const string &s, int i) {
    int u = 0;
    for (char c : s) {
        if (!trie[u][c])
            trie[u][c] = id++;
        u = trie[u][c];
    }
    elink[u] = u;
    ids[u].push_back({i, sz(s)});
}

void gen() {
    slink[0] = -1;
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (!elink[u]) elink[u] = elink[slink[u]];
        for (int c = 0; c < MAX_C; c++) {
            int v = trie[u][c];
            if (v) {
                slink[v] = (slink[u] == -1 ? 0 : trie[slink[u]][c]);
                que.push(v);
            } else if (u) {
                trie[u][c] = trie[slink[u]][c];
            }
        }
    }
}

int feed(int u, char c, int i) {
    u = trie[u][c];
    for (int v = elink[u]; v; v = elink[slink[v]]) {
        for (auto [id, len] : ids[v]) {
            ans[id].push_back(i - len + 1);
        }
    }
    return u;
}
