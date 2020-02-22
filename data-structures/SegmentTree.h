/**
 * Description: Performs range queries and point updates. Bounds are zero-indexed on [l, r).
 * Source: http://codeforces.com/blog/entry/18051
 * Verification: https://www.spoj.com/problems/FENTREE/
 * Time: O(n) build, O(log n) query and update
 */

template<int SZ>
struct SegmentTree {
    int n, st[2*SZ];

    SegmentTree() {
        memset(st, 0, sizeof(st));
    }

    void build(int _n, int *a) {
        n = _n;
        for (int i=0; i<n; i++)
            st[i+n] = a[i];
        for (int i=n-1; i>0; i--)
            st[i] = st[i<<1] + st[i<<1|1];
    }

    int query(int l, int r) {
        int ret = 0;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) ret += st[l++];
            if (r&1) ret += st[--r];
        }
        return ret;
    }

    void update(int p, int val) {
        for (st[p+=n]=val; p>1; p>>=1)
            st[p>>1] = st[p] + st[p^1];
    }
};
