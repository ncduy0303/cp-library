/**
 * Description: A data structure for solving a variety of string problems.
 * Source: https://cp-algorithms.com/string/suffix-array.html
 * Verification: https://www.spoj.com/problems/ADASTRNG/
 * Time: O(n log n) build
 */

template<char MIN_CHAR = '$', int ALPHA = 256> struct SuffixArray {
    int n;
    string s;
    vector<int> pos, rnk, lcp;
 
    SuffixArray(const string &_s) : n((int) _s.size() + 1), s(_s), pos(n), rnk(n), lcp(n - 1) {
        s += MIN_CHAR;
        buildSA();
        buildLCP();
    }
 
    void buildSA() {
        vector<int> cnt(max(ALPHA, n));
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < ALPHA; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) pos[--cnt[s[i]]] = i;
        for (int i = 1; i < n; i++) rnk[pos[i]] = rnk[pos[i - 1]] + (s[pos[i]] != s[pos[i - 1]]);
 
        for (int k = 0; (1 << k) < n; k++) {
            vector<int> npos(n), nrnk(n), ncnt(n);
            for (int i = 0; i < n; i++) pos[i] = (pos[i] - (1 << k) + n) % n;
            for (int i = 0; i < n; i++) ncnt[rnk[i]]++;
            for (int i = 1; i < n; i++) ncnt[i] += ncnt[i - 1];
            for (int i = n - 1; i >= 0; i--) npos[--ncnt[rnk[pos[i]]]] = pos[i];
            for (int i = 1; i < n; i++) {
                pair<int,int> cur = {rnk[npos[i]], rnk[(npos[i] + (1 << k)) % n]};
                pair<int,int> pre = {rnk[npos[i - 1]], rnk[(npos[i - 1] + (1 << k)) % n]};
                nrnk[npos[i]] = nrnk[npos[i - 1]] + (cur != pre);
            }
            pos = npos; rnk = nrnk;
        }
    }
 
    void buildLCP() {
        for (int i = 0, k = 0; i < n - 1; i++, k = max(k - 1, 0)) {
            int j = pos[rnk[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[rnk[i] - 1] = k;
        }
    }
 
    int cntMatching(const string &t) {
        int m = sz(t);
        if (m > n) return 0;
 
        int lo, hi, lb, ub;
 
        lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.substr(pos[mid], m) >= t) hi = mid;
            else lo = mid + 1;
        }
        lb = lo;
 
        lo = 0, hi = n - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (s.substr(pos[mid], m) <= t) lo = mid;
            else hi = mid - 1;
        }
        ub = lo;
        
        return s.substr(pos[lb], m) == t ? ub - lb + 1 : 0;
    }

    ll cntSubstr() {
        ll res = (ll) n * (n - 1) / 2;
        for (int x : lcp) res -= x;
        return res;
    }

    string kthSubstr(ll k) {
        for (int i = 1; i < n; i++) {
            int nxt = n - 1 - pos[i] - lcp[i - 1];
            if (k > nxt) {
                k -= nxt;
            } else {
                return s.substr(pos[i], k + lcp[i - 1]);
            }
        }
    }
};
