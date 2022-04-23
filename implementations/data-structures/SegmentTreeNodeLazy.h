/**
 * Description: Performs range queries and range updates. Stores tree nodes as structs.
 * Source: self
 * Verification: https://www.codechef.com/problems/FLIPCOIN
 * Time: O(n) build, O(log n) query and update
 */

struct Node {
    ll sum, lzSet;
    Node(): sum(0), lzSet(LLONG_MAX) {}
    Node(ll x): sum(x), lzSet(LLONG_MAX) {}
    Node(const Node &l, const Node &r) {
        sum = l.sum + r.sum;
        lzSet = LLONG_MAX;
    }
};

struct SegmentTree { 
    int ln(int node) { return 2 * node; }
    int rn(int node) { return 2 * node + 1; }

    int n; vector<Node> st;

    void init(int _n) { n = _n; st.resize(4 * _n); }
    void init(const vector<int> &a) { init(sz(a)); build(a, 1, 0, n - 1); }

    void apply(int node, int start, int end, ll x) {
        if (x == LLONG_MAX) return;
        st[node].sum = x * (end - start + 1);
        st[node].lzSet = x;
    }

    void push(int node, int start, int end) {
        if (start == end) return;
        int mid = (start + end) / 2;
        apply(ln(node), start, mid, st[node].lzSet);
        apply(rn(node), mid + 1, end, st[node].lzSet);
        st[node].lzSet = LLONG_MAX;
    }

    void build(const vector<int> &a, int node, int start, int end) {
        if (start == end) {
            st[node] = Node(a[start]);
            return;
        }
        int mid = (start + end) / 2;
        build(a, ln(node), start, mid);
        build(a, rn(node), mid + 1, end);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }

    void update(int node, int start, int end, int l, int r, ll x) {
        push(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply(node, start, end, x);
            return;
        }
        int mid = (start + end) / 2;
        update(ln(node), start, mid, l, r, x);
        update(rn(node), mid + 1, end, l, r, x);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }

    Node query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || end < l) return Node();
        if (l <= start && end <= r) return st[node];
        int mid = (start + end) / 2;
        return Node(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    
    void update(int l, int r, ll x) { update(1, 0, n - 1, l, r, x); }
    Node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
