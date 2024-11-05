template<typename T>
void __p(const T& x);
template<typename X, typename Y>
void __p(const pair<X, Y>& x){
    cerr << '{', __p(x.first), cerr << ", ", __p(x.second), cerr << '}';
}
template<typename T> 
void __p(const T& x) {
    if constexpr (is_arithmetic_v<T> or is_same_v<T, string>)   cerr << x;
    else {
        cerr << '{';
        int f = 0; for(auto i : x) cerr << (f ++ ? ", " : ""), __p(i);
        cerr << '}';
    }
}
template <typename... A>
void _p(const A&... a) {((__p(a), cerr << ", "), ...);}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _p(__VA_ARGS__); cerr << "]\n";