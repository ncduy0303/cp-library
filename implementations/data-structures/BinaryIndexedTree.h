/**
 * Description: Performs range prefix sum queries and point updates. kth returns first index with prefix query >= k.
 * Source: own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time: O(log n) query and update
 */

template<typename T> struct FenwickTree {
    int n; vector<T> ft;
    
    void init(int _n) { n = _n; ft.resize(_n); }
    void init(const vector<int> &a) { init(sz(a)); for (int i = 0; i < n; i++) update(i, a[i]); }

    void update(int x, T v) { for (; x < n; x = x | (x + 1)) ft[x] += v; }
    void update(int l, int r, T v) { update(l, v); update(r + 1, -v); }

    T query(int x) {
        T res = 0;
        for (; x >= 0; x = (x & (x + 1)) - 1) res += ft[x];
        return res;
    }
    T query(int l, int r) { return (l <= r) ? query(r) - query(l - 1) : 0; }
};

// more functions
template<typename T> struct FenwickTree {
    int n, lg; vector<T> ft;
    
    void init(int _n) { n = _n; lg = __lg(_n); ft.resize(_n + 1); }
    void init(const vector<int> &a) { init(sz(a)); for (int i = 0; i < n; i++) update(i + 1, a[i]); }
    
    void update(int x, T v) { for (; x <= n; x += x&-x) ft[x] += v; }
    void update(int l, int r, T v) { update(l, v); update(r + 1, -v); }
    
    T query(int x) {
        T res = 0;
        for (; x; x -= x&-x) res += ft[x];
        return res;
    }
    T query(int l, int r) { return (l <= r) ? query(r) - query(l - 1) : 0; }
    
    int find_by_order(int k) { // return 1 if k < 1 and returns N if k > N
        int sum = 0, pos = 0;
        for (int i = lg; i >= 0; i--) {
            if (pos + (1 << i) < n && sum + ft[pos + (1 << i)] < k) {
                sum += ft[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1; 
    }
    int order_of_key(int k) { return query(k); }
};

// range update, range query
template<typename T> struct FenwickTree {
    int n; vector<T> ft1, ft2;
    
    void init(int _n) { n = _n; ft1.resize(_n + 1); ft2.resize(_n + 1); }
    void init(const vector<int> &a) { init(sz(a)); for (int i = 0; i < n; i++) update(i + 1, i + 1, a[i]); }
    
    void update(vector<T> &ft, int x, T v) { for (; x <= n; x += x&-x) ft[x] += v; }
    void update(int l, int r, T v) { 
        update(ft1, l, v);
        update(ft1, r + 1, -v);
        update(ft2, l, v * (l - 1));
        update(ft2, r + 1, -v * r);
    }
    
    T query(vector<T> &ft, int x) {
        T res = 0;
        for (; x; x -= x&-x) res += ft[x];
        return res;
    }
    T query(int x) { return query(ft1, x) * x - query(ft2, x); }
    T query(int l, int r) { return (l <= r) ? query(r) - query(l - 1) : 0; }
};
