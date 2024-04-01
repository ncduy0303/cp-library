/**
 * Description: Multiplies two polynomials quickly.
 * Source: https://cp-algorithms.com/algebra/fft.html, CP4
 * Verification: https://www.spoj.com/problems/POLYMUL/
 * Time: O(n log n)
 */

using cd = complex<double>;

const double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    for (int i=1, j=0; i<n; i++) {
        int bit = n >> 1;
        for (; j&bit; bit>>=1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len=2; len<=n; len*=2) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            cd w(1);
            for (int j=0; j<len/2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv)
        for (cd &x : a)
            x /= n;
}

vector<long long> mul(const vector<long long> &a, const vector<long long> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int) a.size() + (int) b.size())
        n *= 2;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i=0; i<n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> ret(n);
    for (int i=0; i<n; i++)
        ret[i] = llround(fa[i].real());
    return ret;
}

using cd = complex<double>;
const double PI = acos(-1.0);

int reverseBit(int x, int m) {  // m is the binary length of A.size()-1
    int ret = 0;
    for (int k = 0; k < m; k++) {
        if (x & (1 << k)) ret |= (1 << (m - 1 - k));
    }
    return ret;
}

void FFT(vector<cd> &A) {  // evaulates A at the nth roots of unity for n = 2^k >= A.size()
    int m = 0;
    while ((1 << m) < (int)A.size()) m++;
    A.resize(1 << m, 0);                       // size of A should be a power of 2, resizes A
    for (int k = 0; k < (int)A.size(); k++) {  // sort to bit-reversal permutation
        if (k < reverseBit(k, m)) swap(A[k], A[reverseBit(k, m)]);
    }

    for (int n = 2; n <= (int)A.size(); n <<= 1) {
        for (int k = 0; 2 * k < n; k++) {
            // we are going to get the kth and k+n/2th element of each length n block
            cd x = cd(cos(2 * PI * k / n), sin(2 * PI * k / n));  // nth root of unity
            for (int j = 0; j < (int)A.size(); j += n) {  // apply to every sub-array of length n
                cd A0k = A[k + j];                        // previously computed
                cd A1k = A[k + j + n / 2];                // previously computed
                A[k + j] = A0k + x * A1k;
                A[k + j + n / 2] = A0k - x * A1k;
            }
        }
    }
}

void IFFT(vector<cd> &A) {  // Size of A should be a power of 2
    for (auto &p : A) p = conj(p);
    FFT(A);
    // for (auto &p : A) p = conj(p);  // not needed if IFFT only used for multiplication
    for (auto &p : A) p /= (int) A.size();
}

vector<ll> multiply(vector<ll> p1, vector<ll> p2) {
    int n = 1;
    while (n < (int) p1.size() + (int) p2.size() - 1) n <<= 1;  // n is a power of 2
    vector<cd> A(p1.begin(), p1.end());
    vector<cd> B(p2.begin(), p2.end());
    A.resize(n, 0);
    B.resize(n, 0);

    FFT(A);  // Evaluate A at the nth roots of unity
    FFT(B);  // Evaluate B at the nth roots of unity

    vector<cd> C(n, 0);
    for (int i = 0; i < n; i++)
        C[i] = A[i] * B[i];  // C = A * B, we get C at the nth roots of unity
    IFFT(C);                 // convert back to coefficient form

    n = (int) p1.size() + (int) p2.size() - 1;
    vector<ll> ans(n, 0);
    for (int i = 0; i < n; i++) ans[i] = round(C[i].real());

    return ans;
}