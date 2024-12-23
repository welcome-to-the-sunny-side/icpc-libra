static const int MOD  = 998244353;
static const int ROOT = 3; // A primitive root modulo 998244353

// Fast exponentiation
long long modexp(long long base, long long exp, int m) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % m;
        base = (base * base) % m;
        exp >>= 1;
    }
    return result;
}
// In-place Number-Theoretic Transform
// 'invert' determines whether to perform NTT (false) or inverse NTT (true)
void ntt(vector<long long>& a, bool invert) {
    int n = (int) a.size();
    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = (n >> 1);
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    // Iterative NTT
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = modexp(ROOT, (MOD - 1) / len, MOD);
        if (invert) {
            wlen = modexp(wlen, MOD - 2, MOD); // wlen = inverse(wlen) mod MOD
        }
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (a[i + j + len/2] * w) % MOD;
                a[i + j]          = (u + v) % MOD;
                a[i + j + len/2]  = (u - v + MOD) % MOD;
                w = (w * wlen) % MOD;
            }
        }
    }
    // If inverse, divide all elements by n (using modular inverse)
    if (invert) {
        long long invN = modexp(n, MOD - 2, MOD);
        for (auto &x : a) {
            x = (x * invN) % MOD;
        }
    }
}

// Polynomial multiplication using NTT
vector<long long> poly_multiply(const vector<long long>& A, const vector<long long>& B) {
    // Determine proper size for NTT (power of 2 >= deg(A) + deg(B) - 1)
    int sz = 1;
    while (sz < (int)(A.size() + B.size() - 1)) {
        sz <<= 1;
    }
    vector<long long> a(sz), b(sz);
    // Copy input coefficients
    for (int i = 0; i < (int) A.size(); i++) a[i] = A[i];
    for (int i = 0; i < (int) B.size(); i++) b[i] = B[i];
    // Forward transforms
    ntt(a, false);
    ntt(b, false);
    // Point-wise multiply
    for (int i = 0; i < sz; i++) {
        a[i] = (a[i] * b[i]) % MOD;
    }
    // Inverse transform
    ntt(a, true);
    // Resize to actual degree of resulting polynomial
    a.resize(A.size() + B.size() - 1);
    return a;
}