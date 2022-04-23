/**
 * Description: Performs range queries and point updates.
 * Source: http://codeforces.com/blog/entry/18051
 * Verification: https://www.spoj.com/problems/FENTREE/
 * Time: O(n) build, O(log n) query and update
 */

struct Node {
    int mn;
    Node(): mn(INT_MAX) {}
    Node(int x): mn(x) {}
    Node(const Node &l, const Node &r) {
        mn = min(l.mn, r.mn);
    }
};

struct SegmentTree {
    int n; vector<Node> st;
    
    void init(int _n) { n = _n; st.resize(2 * _n); }
    void init(const vector<int> &a) {
        init(sz(a));
        for (int i = 0; i < n; i++) st[i + n] = Node(a[i]);
        for (int i = n - 1; i > 0; i--) st[i] = Node(st[i << 1], st[i << 1 | 1]);
    }

    Node query(int l, int r) {
        Node resl, resr;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = Node(resl, st[l++]);
            if (r & 1) resr = Node(st[--r], resr);
        }
        return Node(resl, resr);
    }

    void update(int i, int x) {
        for (st[i += n] = Node(x); i >>= 1; ) st[i] = Node(st[i << 1], st[i << 1 | 1]);
    }
};
