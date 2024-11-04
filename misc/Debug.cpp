template<typename T> 
void __print(const T& x) {
    if constexpr (requires { x.size(); } && !requires { x.length(); }) {
        cerr << '{';
        for (auto i : x) __print(i), cerr << ',';
        cerr << '}';
    }
    else if constexpr (requires { x.first; })
        cerr << '{', __print(x.first), cerr << ',', __print(x.second), cerr << '}';
    else    cerr << x;
}

template <typename... Args>
void _print(const Args&... args) {((__print(args), cerr << ", "), ...);}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__); cerr << "]\n";