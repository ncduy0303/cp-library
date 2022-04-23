/**
 * Description: Performs range queries and point updates. Stores tree nodes as structs.
 * Source: self
 * Verification: https://www.spoj.com/problems/GSS3/
 * Time: O(n) build, O(log n) query and update
 */

struct Node {
    ll mn;
    Node(): mn(LLONG_MAX) {}
    Node(ll x): mn(x) {}
    Node(const Node &l, const Node &r) {
        mn = min(l.mn, r.mn);
    }
};

struct SegmentTree { 
    int ln(int node) { return 2 * node; }
    int rn(int node) { return 2 * node + 1; }
    
    int n; vector<Node> st;

    void init(int _n) { n = _n; st.resize(4 * _n); }
    void init(vector<int> &a) { init(sz(a)); build(a, 1, 0, n - 1); }
    
    void apply(int node, ll x) {
        st[node].mn = x;
    }

    void build(vector<int> &a, int node, int start, int end) {
        if (start == end) {
            st[node] = Node(a[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(a, ln(node), start, mid);
        build(a, rn(node), mid + 1, end);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }

    void update(int node, int start, int end, int i, ll x) {
        if (start == end) {
            apply(node, x);
            return;
        }
        int mid = (start + end) / 2;
        if (i <= mid) update(ln(node), start, mid, i, x);
        else update(rn(node), mid + 1, end, i, x);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return Node(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }

    void update(int i, ll x) { update(1, 0, n - 1, i, x); }
    Node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
    struct Node {
        int ans = 0;

        void leaf(int val) {
            ans += val;
        }

        void pull(const Node &a, const Node &b) {
            ans = min(a.ans, b.ans);
        }
    };

    int n;
    vector<int> a;
    vector<Node> st;

    SegmentTree(int _n) : n(_n), a(n), st(4*n) {
        build(1, 0, n-1);
    }

    SegmentTree(const vector<int> &_a) : n((int) _a.size()), a(_a), st(4*n) {
        build(1, 0, n-1);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            st[p].leaf(a[l]);
            return;
        }
        int m = (l + r) / 2;
        build(2*p, l, m);
        build(2*p+1, m+1, r);
        st[p].pull(st[2*p], st[2*p+1]);
    }

    Node query(int p, int l, int r, int i, int j) {
        if (l == i && r == j)
            return st[p];
        int m = (l + r) / 2;
        if (j <= m)
            return query(2*p, l, m, i, j);
        else if (i > m)
            return query(2*p+1, m+1, r, i, j);
        Node ret, ls = query(2*p, l, m, i, m), rs = query(2*p+1, m+1, r, m+1, j);
        ret.pull(ls, rs);
        return ret;
    }

    int query(int i, int j) {
        return query(1, 0, n-1, i, j).ans;
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p].leaf(val);
            return;
        }
        int m = (l + r) / 2;
        if (idx <= m)
            update(2*p, l, m, idx, val);
        else
            update(2*p+1, m+1, r, idx, val);
        st[p].pull(st[2*p], st[2*p+1]);
    }

    void update(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }
};
