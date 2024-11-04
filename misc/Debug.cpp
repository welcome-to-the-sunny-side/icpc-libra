template<typename T> 
void __print(const T& x) {
    cerr << '{';
    if constexpr (requires {x.size();} and !is_same_v<T, string>){
        int f = 0;
        for(auto i : x) cerr << (f ++ ? "," : ""), __print(i);
    }
    else if constexpr (requires {x.first;})
        __print(x.first), cerr << ',', __print(x.second);
    else
        cerr << x;
    cerr << '}';
}

void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) cerr << ", "; 
    _print(v...);
}

#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)