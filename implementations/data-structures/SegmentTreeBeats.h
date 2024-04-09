// Source: myself
// Ranges are inclusive [a, b]

struct Node {
    ll sum, lzAdd, mx, mx2, cntMx, mn, mn2, cntMn;
    Node(): sum(0), lzAdd(0), mx(-LLONG_MAX), mx2(-LLONG_MAX), cntMx(0), mn(LLONG_MAX), mn2(LLONG_MAX), cntMn(0) {}
    Node(ll x): sum(x), lzAdd(0), mx(x), mx2(-LLONG_MAX), cntMx(1), mn(x), mn2(LLONG_MAX), cntMn(1) {}
    Node(const Node &l, const Node &r) {
        sum = l.sum + r.sum;
        lzAdd = 0;
        mx = max(l.mx, r.mx);
        mx2 = max(l.mx2, r.mx2);
        cntMx = 0;
        if (l.mx == mx) cntMx += l.cntMx;
        else mx2 = max(mx2, l.mx);
        if (r.mx == mx) cntMx += r.cntMx;
        else mx2 = max(mx2, r.mx);
        mn = min(l.mn, r.mn);
        mn2 = min(l.mn2, r.mn2);
        cntMn = 0;
        if (l.mn == mn) cntMn += l.cntMn;
        else mn2 = min(mn2, l.mn);
        if (r.mn == mn) cntMn += r.cntMn;
        else mn2 = min(mn2, r.mn);
    }
};

struct SegmentTree { 
    int ln(int node) { return 2 * node; }
    int rn(int node) { return 2 * node + 1; }

    int n; vector<Node> st;

    void init(int _n) { n = _n; st.resize(4 * _n); }
    void init(const vector<int> &a) { init(sz(a)); build(a, 1, 0, n - 1); }

    void applyAdd(int node, int start, int end, ll x) {
        if (x == 0) return;
        st[node].sum += x * (end - start + 1);
        st[node].lzAdd += x;
        st[node].mx += x;
        if (st[node].mx2 != -LLONG_MAX) st[node].mx2 += x; 
        st[node].mn += x;
        if (st[node].mn2 != LLONG_MAX) st[node].mn2 += x; 
    }
    void applyMin(int node, int start, int end, ll x) {
        if (x >= st[node].mx) return;
        st[node].sum -= (st[node].mx - x) * st[node].cntMx;
        st[node].mx = x;
        if (x < st[node].mn) st[node].mn = x;
        else if (x < st[node].mn2) st[node].mn2 = x;
    }
    void applyMax(int node, int start, int end, ll x) {
        if (x <= st[node].mn) return;
        st[node].sum += (x - st[node].mn) * st[node].cntMn;
        st[node].mn = x;
        if (x > st[node].mx) st[node].mx = x;
        else if (x > st[node].mx2) st[node].mx2 = x;
    }

    void push(int node, int start, int end) {
        if (start == end) return;
        int mid = (start + end) / 2;
        applyAdd(ln(node), start, mid, st[node].lzAdd);
        applyAdd(rn(node), mid + 1, end, st[node].lzAdd);
        st[node].lzAdd = 0;
        applyMin(ln(node), start, mid, st[node].mx);
        applyMin(rn(node), mid + 1, end, st[node].mx);
        applyMax(ln(node), start, mid, st[node].mn);
        applyMax(rn(node), mid + 1, end, st[node].mn);
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

    void updateAdd(int node, int start, int end, int l, int r, ll x) {
        push(node, start, end);
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            applyAdd(node, start, end, x);
            return;
        }
        int mid = (start + end) / 2;
        updateAdd(ln(node), start, mid, l, r, x);
        updateAdd(rn(node), mid + 1, end, l, r, x);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }
    void updateMin(int node, int start, int end, int l, int r, ll x) {
        push(node, start, end);
        if (r < start || end < l || st[node].mx <= x) return;
        if (l <= start && end <= r && st[node].mx2 < x) {
            applyMin(node, start, end, x);
            return;
        }
        int mid = (start + end) / 2;
        updateMin(ln(node), start, mid, l, r, x);
        updateMin(rn(node), mid + 1, end, l, r, x);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }
    void updateMax(int node, int start, int end, int l, int r, ll x) {
        push(node, start, end);
        if (r < start || end < l || st[node].mn >= x) return;
        if (l <= start && end <= r && st[node].mn2 > x) {
            applyMax(node, start, end, x);
            return;
        }
        int mid = (start + end) / 2;
        updateMax(ln(node), start, mid, l, r, x);
        updateMax(rn(node), mid + 1, end, l, r, x);
        st[node] = Node(st[ln(node)], st[rn(node)]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return Node();
        if (l <= start && end <= r) return st[node];
        push(node, start, end);
        int mid = (start + end) / 2;
        return Node(query(ln(node), start, mid, l, r), query(rn(node), mid + 1, end, l, r));
    }
    
    void updateAdd(int l, int r, ll x) { updateAdd(1, 0, n - 1, l, r, x); }
    void updateMin(int l, int r, ll x) { updateMin(1, 0, n - 1, l, r, x); }
    void updateMax(int l, int r, ll x) { updateMax(1, 0, n - 1, l, r, x); }
    Node query(int l, int r) { return query(1, 0, n - 1, l, r); }
};