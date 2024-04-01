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