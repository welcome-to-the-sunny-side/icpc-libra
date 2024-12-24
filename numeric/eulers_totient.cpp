int phi(int n) { // O(sqrt(n))
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}
vector<int> phi; // phi[1] is 1
void phi_1_to_n(int n) { // 1 to n in O(nloglogn)
    phi.resize(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
        }
    }
}