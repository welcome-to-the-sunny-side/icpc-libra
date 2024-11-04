template<typename T> 
void __print(const T& x) {
    if constexpr (is_arithmetic_v<T> or is_same_v<T, string>)   cerr << x;
    else {
        cerr << '{';
        for(auto i : x) __print(i), cerr << ',';
        cerr << '}';
    }
}

template <typename... A>
void _print(const A&... a) {((__print(a), cerr << ", "), ...);}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__); cerr << "]\n";