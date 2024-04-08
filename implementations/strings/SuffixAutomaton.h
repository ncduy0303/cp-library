/**
 * Description: Every distinct substring corresponds to an execution in the automaton.
 * All substrings ending at the same state end at the same set of positions in the string (same equiv class).
 * The suffix link of state of substring w leads to the state of longest suffix of w with larger equiv class.
 * The suffix links form a tree, and we can compute equiv class sizes bottom-up on this tree.
 * Source: https://cp-algorithms.com/string/suffix-automaton.html
 * Verification: https://cses.fi/problemset/task/2108, https://www.spoj.com/problems/SUBLEX/
 * Time: O(n) build
 */

template<char MIN_CHAR = 'a', int ALPHA = 26> struct SuffixAutomaton {
    int last;
    vector<int> len, link, firstPos;
    vector<ll> dp, ending;
    vector<array<int, ALPHA>> nxt;
    vector<int> pos;
 
    SuffixAutomaton() : last(0), len(1), link(1, -1), firstPos(1), nxt(1), ending(1) {}
 
    SuffixAutomaton(const string &s) : SuffixAutomaton() {
        for (char c : s)
            extend(c);
        topo();
        dp.assign(sz(len), 0);
        dfs(0);
    }

    void dfs(int u) {
        dp[u] = ending[u];
        for (int i = 0; i < ALPHA; ++i) {
            if (!nxt[u][i]) continue;
            int v = nxt[u][i];
            if (!dp[v]) dfs(v);
            dp[u] += dp[v];
        }
    }
 
    int getIndex(char c) {
        return c - MIN_CHAR;
    }

    void topo() {
        // couting sort by len() to get the topological order from bottom to root
        int n = (int) len.size();
        vector<int> cnt(n);
        for (int i = 0; i < n; i++) cnt[len[i]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
        pos.assign(n, 0);
        for (int i = n - 1; i >= 0; i--) pos[--cnt[len[i]]] = i;

        for (int i = n - 1; i >= 0; i--) {
            int cur = pos[i];
            if (link[cur] != -1) {
                ending[link[cur]] += ending[cur];
            }
        }
    }
 
    void extend(char c) {
        int cur = (int) len.size(), i = getIndex(c), p = last;
        len.push_back(len[last] + 1);
        link.emplace_back();
        firstPos.emplace_back(len[last] + 1);
        nxt.emplace_back();
        while (p != -1 && !nxt[p][i]) {
            nxt[p][i] = cur;
            p = link[p];
        }
        if (p != -1) {
            int q = nxt[p][i];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                int clone = (int) len.size();
                len.push_back(len[p] + 1);
                link.push_back(link[q]);
                firstPos.push_back(firstPos[q]);
                nxt.push_back(nxt[q]);
                while (p != -1 && nxt[p][i] == q) {
                    nxt[p][i] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
 
    int firstMatching(const string &t) {
        int cur = 0;
        for (char c : t) {
            int cc = getIndex(c);
            if (!nxt[cur][cc]) return -1;
            cur = nxt[cur][cc];
        }
        return firstPos[cur] - sz(t) + 1;
    }

    ll cntSubstr() {
        ll res = 0;
        for (int i = 1; i < sz(len); i++) {
            res += len[i] - len[link[i]];
        }
        return res;
    }

    void lcs(const string &t, vector<int> &dp) {
        // dp[i] = length of the lcs with state i
        int n = (int) len.size();
        dp.assign(n, 0);
        int cur = 0, match = 0;
        for (char c : t) {
            int cc = getIndex(c);
            while (cur && !nxt[cur][cc]) {
                cur = link[cur];
                match = len[cur];
            }
            if (nxt[cur][cc]) {
                cur = nxt[cur][cc];
                match++;
            }
            dp[cur] = max(dp[cur], match);
        }
        for (int i = n - 1; i >= 0; i--) {
            int cur = pos[i];
            if (link[cur] != -1) {
                dp[link[cur]] = max(dp[link[cur]], min(len[link[cur]], dp[cur]));
            }
        }
    }

    string kthSubstr(ll k) {
        // k-th non-distinct substring
        int n = (int) len.size();
        int cur = 0;
        string res = "";
        while (k > 0) {
            for (int i = 0; i < ALPHA; i++) {
                if (!nxt[cur][i]) continue;
                int v = nxt[cur][i];
                if (dp[v] < k) {
                    k -= dp[v];
                } else {
                    res += (char) (MIN_CHAR + i);
                    k -= ending[v];
                    cur = v;
                    break;
                }
            }
        }
        return res;
    }
};
