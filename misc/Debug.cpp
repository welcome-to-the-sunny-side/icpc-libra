class dbg
{
public:
    template<typename T> 
    void __print(const T& x) {cerr << x;}

    template<typename T, typename V>
    void __pair_print(const pair<T, V> &x) {cerr << '{'; __handle(x.first); cerr << ','; __handle(x.second); cerr << '}';}

    template<typename T>
    void __iterate_print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __handle(i); cerr << "}";}

    template<typename T>
    void __handle(const T &t) {
        if constexpr (requires {t.size();} and !is_same_v<T, string>)   __iterate_print(t);
        else if constexpr (requires {t.first;})    __pair_print(t);
        else    __print(t);
    }

    void _print() {cerr << "]\n";}
    template <typename T, typename... V>
    void _print(T t, V... v) {
        __handle(t);
        if (sizeof...(v)) cerr << ", "; 
        _print(v...);
    }
}debugger;

#define debug(x...) cerr << "[" << #x << "] = ["; debugger._print(x)