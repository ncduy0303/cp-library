/**
 * Description: Stores vectors in nodes of segment tree. Change vector to ordered_set to support point updates.
 * Source: https://codeforces.com/blog/entry/15890
 * Verification: https://www.spoj.com/problems/KQUERYO/
 * Time: O(n log n) build, O(log^2 n) query
 */

#define MAX_N 100000

int a[MAX_N];
vector<int> st[4 * MAX_N];

void build(int p, int l, int r) {
    if (l == r) {
        st[p].push_back(a[l]);
        return;
    }

    int m = (l + r) / 2;
    build(2*p, l, m);
    build(2*p+1, m+1, r);
    merge(st[2*p].begin(), st[2*p].end(), st[2*p+1].begin(), st[2*p+1].end(), back_inserter(st[p]));
}

// number of elements greater than a specified number
int query(int p, int l, int r, int i, int j, int k) {
    if (i > r || j < l)
        return 0;
    if (i <= l && r <= j)
        return st[p].end() - upper_bound(st[p].begin(), st[p].end(), k);

    int m = (l + r) / 2;
    return query(2*p, l, m, i, j, k) + query(2*p+1, m+1, r, i, j, k);
}

// smallest number greater or equal to a specified number
int query(int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return INF;
    if (l == tl && r == tr) {
        vector<int>::iterator pos = lower_bound(t[v].begin(), t[v].end(), x);
        if (pos != t[v].end())
            return *pos;
        return INF;
    }
    int tm = (tl + tr) / 2;
    return min(query(v*2, tl, tm, l, min(r, tm), x), 
               query(v*2+1, tm+1, tr, max(l, tm+1), r, x));
}
