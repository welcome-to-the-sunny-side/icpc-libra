// Integral Types
template<typename T>
requires is_arithmetic_v<T>
void __print(const T& x) { cerr << x; }

// Char
void __print(char x) { cerr << '\'' << x << '\''; }

// String
void __print(const string& x) { cerr << '\"' << x << '\"'; }

// Boolean
void __print(const bool& x) { cerr << (x ? "true" : "false"); }

// Handle pairs
template<typename T, typename V>
void __print(const pair<T, V>& x) {
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}

// Handle any iterable container
template<typename T>
requires (!is_arithmetic_v<T> && requires(T x) { begin(x); end(x); })
void __print(const T& x) {
    int f = 0;
    cerr << '{';
    for (const auto& i : x) {
        cerr << (f++ ? "," : "");
        __print(i);
    }
    cerr << "}";
}

// Variadic template for multiple arguments
template<typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) cerr << ", ";
    if constexpr (sizeof...(v) > 0) {
        _print(v...);
    }
}

#define debug(x...) { cerr << "[" << #x << "] = ["; _print(x); cerr << "]\n"; }