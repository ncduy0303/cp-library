/**
 * Description: Policy-based data structure to support queries for kth largest and number of elements less than given number.
 * Source: https://codeforces.com/blog/entry/11080
 * Verification: https://www.spoj.com/problems/ORDERSET/
 * Time: O(log n) for both queries
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// find_by_order(k) - returns iterator to kth largest element (0-indexed) or an iterator to end if it doesn't exist
// order_of_key(x) - returns the number of elements in the set strictly smaller than x
