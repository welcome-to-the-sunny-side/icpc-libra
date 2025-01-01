#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define endl "\n"
using namespace std;
struct {
    template<typename T, typename V>
    void __print(const pair<T, V> &x) {
        cerr << '{';
        __print(x.first);
        cerr << ',';
        __print(x.second);
        cerr << '}';
    }
    template<typename T>
    void __print(const T &x) {
        if constexpr (is_arithmetic_v<T> or is_same_v<T, string>)   cerr << x;
        else {
            int f = 0;
            cerr << '{';
            for (auto &i : x) {
                cerr << (f++ ? "," : "");
                __print(i);
            }
            cerr << "}";
        }
    }
    void _print() {
        cerr << "]\n";
    }
    template <typename T, typename... V>
    void _print(T t, V... v) {
        __print(t);
        if (sizeof...(v)) cerr << ", ";
        _print(v...);
    }
} debugger;
#define debug(x...) { cerr << "[" << #x << "] = ["; debugger._print(x); }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
signed main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    int t = 1;
    cin >> t;
    while(t --)
    {

    }
}