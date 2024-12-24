template<typename T = long long>
struct Line {
    T m, b;
    mutable T x_end;
    bool operator<(const Line& o) const { return m < o.m; }
    bool operator<(T x) const { return x_end < x; }
    T eval(T x) const { return m * x + b; }
};

template<typename T = long long>
struct LineContainer : multiset<Line<T>, less<>> {
    bool maximum;
    LineContainer(bool is_maximum = true) : maximum(is_maximum) {}
    
    using Iterator = typename multiset<Line<T>, less<>>::iterator;
    static T div(T a, T b) { return a / b - ((a ^ b) < 0 && a % b); }
    
    bool isect(Iterator x, Iterator y) {
        if (y == this->end()) { x->x_end = numeric_limits<T>::max(); return false; }
        if (x->m == y->m) x->x_end = x->b > y->b ? numeric_limits<T>::max() : -numeric_limits<T>::max();
        else x->x_end = div(y->b - x->b, x->m - y->m);
        return x->x_end >= y->x_end;
    }
    
    void add(T m, T b) {
        if (!maximum) m = -m, b = -b;
        auto z = this->insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = this->erase(z);
        if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));
        while ((y = x) != this->begin() && (--x)->x_end >= y->x_end)
            isect(x, this->erase(y));
    }
    
    T query(T x) {
        assert(!this->empty());
        auto l = *this->lower_bound(x);
        T res = l.eval(x);
        return maximum ? res : -res;
    }
};