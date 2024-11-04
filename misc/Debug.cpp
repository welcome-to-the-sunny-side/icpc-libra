template<typename T> void __print(const T& x) {cerr << x;}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}

template<typename T>
void __iterate_print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}

void _print() {cerr << "]\n";}

template <typename T, typename... V>
void _print(T t, V... v) {
    if constexpr (requires {t.size();} and !is_same_v<T, string>)   __iterate_print(t);
    else    __print(t);
    if (sizeof...(v)) cerr << ", "; 
    _print(v...);
}

#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)