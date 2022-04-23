/**
 * Description: Performs range minimum queries on a static array.
 * Source: self
 * Verification: https://www.spoj.com/problems/RMQSQ/
 * Time: O(n log n) build, O(1) query
 */

template<typename T, bool MAXIMUM_MODE = false> struct RMQ {
    int n;
    vector<T> arr;
    vector<vector<int>> spt;

    // Note: when `arr[i] == arr[j]`, returns j.
    int better_index(int i, int j) const {
        return (MAXIMUM_MODE ? arr[j] < arr[i] : arr[i] < arr[j]) ? i : j;
    }

    void init(const vector<T> &a) {
        n = (int) a.size();
        arr = a;
        spt.emplace_back(n);
        for (int i = 0; i < n; i++) spt[0][i] = i;
        for (int j = 1; (1 << j) <= n; j++) {
            spt.emplace_back(n - (1 << j) + 1);
            for (int i = 0; i + (1 << j) <= n; i++) { 
                spt[j][i] = better_index(spt[j - 1][i], spt[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // Note: breaks ties by choosing the largest index.	
    int query_idx(int l, int r) const {
        int k = __lg(r - l + 1);
        return better_index(spt[k][l], spt[k][r - (1 << k) + 1]);
    }

    T query(int l, int r) const {
        return arr[query_idx(l, r)];
    }
};
