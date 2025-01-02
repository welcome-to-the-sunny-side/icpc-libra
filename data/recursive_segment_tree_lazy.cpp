class monoid_chan {
public:
  int64_t sum = 0;
  monoid_chan() : sum(0) {};
  monoid_chan(int64_t x) : sum(x) {};
  monoid_chan unite(monoid_chan b) const {
    monoid_chan res(sum + b.sum);
    return res;
  }
  static monoid_chan get_default([[maybe_unused]] int l, [[maybe_unused]] int r) { return monoid_chan(); }
};
class tag_chan {
public:
  int64_t add = 0;
  tag_chan() : add(0) {}; tag_chan(int64_t x) : add(x) {};
  bool apply_to(monoid_chan &a, [[maybe_unused]] int l, [[maybe_unused]] int r) const {
    a.sum += add * (r - l + 1); return true;
  }
  void apply_to(tag_chan &t) const { t.add += add; }
  bool empty() const { return add == 0; }
};
template <typename info, typename tag>
class segment_tree_chan {
public:
  int n;
  vector<info> infos; vector<tag> tags;
  template<typename O>
  void recurse(int lb, int rb, bool update, O op) {
    auto rec = [&](int v, int l, int r, auto &&rec) -> void {
      propagate(v, l, r);
      if (l > r) return;
      if(lb <= l and r <= rb) {
        op(v, l, r); return;
      }
      int m = (l + r)/2;
      if(m >= lb) rec(2 * v, l, m, rec);
      else if(update) propagate(2 * v, l, m);
      if (m + 1 <= rb) rec(2 * v + 1, m + 1, r, rec);
      else if(update) propagate(2 * v + 1, m + 1, r);
      if(update) infos[v] = infos[2 * v].unite(infos[2 * v + 1]);
    };
    rec(1, 0, n - 1, rec);
  };
  segment_tree_chan() : segment_tree_chan(0) {};
  segment_tree_chan(int n) : segment_tree_chan(vector<info> (n)) {};
  segment_tree_chan(const vector<info> &a) :
  n((int)a.size()), infos(4 * n + 5), tags(4 * n + 5) {
    auto build = [&](int v, int l, int r, auto &&build) -> void {
      if(l > r) return;
      if(l == r) {
        infos[v] = info(a[l]); return;
      }
      int m = (l + r)/2;
      build(v * 2, l, m, build); build(v * 2 + 1, m + 1, r, build);
      infos[v] = infos[v * 2].unite(infos[v * 2 + 1]);
    };
    build(1, 0, n - 1, build);
  };
  void propagate(int v, int l, int r) {
    if(tags[v].empty()) return;
    if(l > r)   return;
    tags[v].apply_to(infos[v], l, r);
    if(l != r) {
      tags[v].apply_to(tags[2 * v]);
      tags[v].apply_to(tags[2 * v  + 1]);
    }
    tags[v] = tag();
  }
  void modify(int lb, int rb, const tag &Tag) {
    recurse(lb, rb, true, [&](int v, int l, int r) {
      Tag.apply_to(tags[v]); propagate(v, l, r);
    });
  }
  void set(int p, const info &Info) {
    recurse(p, p, true, [&](int v, int l, int r) { infos[v] = Info; });
  }
  void add(int p, const info &Info) {
    recurse(p, p, true, [&](int v, int l, int r) {
      infos[v] = infos[v].unite(Info); propagate(v, l, r); });
  }
  info query(int lb, int rb) {
    info res = info();
    recurse(lb, rb, false, [&](int v, int l, int r) { res = res.unite(infos[v]); });
    return res;
  }
  info get(int p) {
    info res = info();
    recurse(p, p, false, [&](int v, int l, int r) { res = infos[v]; });
    return res;
  }
  int max_right(int l, auto f) {
    assert(0 <= l  and l <= n - 1);
    info sum;
    int ans = l - 1;
    bool found = false;
    auto recurse = [&](int v, int lb, int rb, auto &&recurse) -> void {
        propagate(v, lb, rb);
        if(lb == rb) {
            if(f(sum.unite(infos[v]))) {
                ans = l;
                sum = sum.unite(infos[v]);
            }
            else {
                found = true;
                ans = l - 1; 
            }
            return;
        }

        int m = (lb + rb)/2;
        if(lb <= l and l <= m) {
            recurse(v * 2, lb, m, recurse);
            if(found)
                return;
            propagate(2 * v + 1, m + 1, rb);
            if(f(sum.unite(infos[2 * v + 1]))) {
                ans = rb;
                sum = sum.unite(infos[2 * v + 1]);
            }
            else {
                found = true;
                auto dfs = [&](int v, int lb, int rb, auto &&dfs) -> void {
                    if(lb > rb)
                        return;
                    propagate(v, lb, rb);
                    if(lb == rb) {
                        if(f(sum.unite(infos[v]))) {
                            ans = rb;
                            sum = sum.unite(infos[v]);
                        }
                        return;
                    }
                    int m = (lb + rb)/2;
                    propagate(2 * v, lb, m);
                    if(f(sum.unite(infos[2 * v]))) {
                        ans = m;
                        sum = sum.unite(infos[2 * v]);
                        dfs(2 * v + 1, m + 1, rb, dfs);
                    }   
                    else
                        dfs(2 * v, lb, m, dfs);                 
                };
                dfs(2 * v + 1, m + 1, rb, dfs);
            }
        }
        else {
            recurse(v * 2 + 1, m + 1, rb, recurse);
        }
    };
    recurse(1, 0, n - 1, recurse);
    return ans;
  }
};
