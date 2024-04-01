/**
 * Description: A tree data structure for efficient string and binary number queries.
 * Source: https://codeforces.com/blog/entry/55782
 * Verification: https://www.spoj.com/problems/SUBXOR/
 * Time: O(length) insertion and query
 */

#define MAX_N 100000
#define MAX_C 26

int id = 1, trie[MAX_N][MAX_C], cnt[MAX_N];

void add(const string &s) {
    int u = 0;
    cnt[u]++;
    for (char c : s) {
        c -= 'a';
        if (!trie[u][c])
            trie[u][c] = id++;
        u = trie[u][c];
        cnt[u]++;
    }
}

int query(const string &s) {
    int u = 0;
    for (char c : s) {
        c -= 'a';
        if (!trie[u][c])
            return 0;
        u = trie[u][c];
    }
    return cnt[u];
}
