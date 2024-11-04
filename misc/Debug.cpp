// Integral Types
template<typename T>
requires is_arithmetic_v<T>
void __print(const T& x) { cerr << x; }

// Char
void __print(char x) { cerr << '\'' << x << '\''; }

// String
void __print(const std::string& x) { cerr << '\"' << x << '\"'; }

// Boolean
void __print(const bool& x) { cerr << (x ? "true" : "false"); }

// Handle pairs
template<typename T, typename V>
void __print(const std::pair<T, V>& x) {
    std::cerr << '{';
    __print(x.first);
    std::cerr << ',';
    __print(x.second);
    std::cerr << '}';
}

// Handle any iterable container
template<typename T>
requires (!std::is_arithmetic_v<T> && requires(T x) { std::begin(x); std::end(x); })
void __print(const T& x) {
    int f = 0;
    std::cerr << '{';
    for (const auto& i : x) {
        std::cerr << (f++ ? "," : "");
        __print(i);
    }
    std::cerr << "}";
}

// Variadic template for multiple arguments
template<typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) std::cerr << ", ";
    if constexpr (sizeof...(v) > 0) {
        _print(v...);
    }
}

#define debug(x...) { std::cerr << "[" << #x << "] = ["; _print(x); std::cerr << "]\n"; }