template<typename T> 
void __print(const T& x) {
    if constexpr (requires { x.size(); } && !requires { x.length(); })
        for (auto i : x) __print(i), cerr << ',';
    else if constexpr (requires { x.first; })
        __print(x.first), cerr << ',', __print(x.second);
    else    cerr << x;
}

template <typename... Args>
void _print(const Args&... args) {((cerr << '{', __print(args), cerr << "}, "), ...);}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__); cerr << "]\n";