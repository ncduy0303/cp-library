/**
 * Description: Performs 2D range prefix sum queries and point updates. Bounds are one-indexed on [1, x][1, y].
 * Source: own
 * Verification: https://www.spoj.com/problems/MATSUM/
 * Time: O(log^2 n) query and update
 */

template<typename T> struct FenwickTree2D {
    int n, m; vector<vector<T>> ft;
    
    void init(int _n, int _m) { n = _n; m = _m; ft.resize(_n + 1, vector<T>(_m + 1)); }

    void update(int x, int y, T v) {
        for (int tx = x; tx <= n; tx += tx&-tx)
            for (int ty = y; ty <= m; ty += ty&-ty)
                ft[tx][ty] += v;
    }

    T query(int x, int y) {
        T res = 0;
        for (int tx = x; tx; tx -= tx&-tx) 
            for (int ty = y; ty; ty -= ty&-ty)
                res += ft[tx][ty];
        return res;
    }
    T query(int x1, int y1, int x2, int y2) { return (x1 <= x2 && y1 <= y2) ? query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1) : 0; }
};
