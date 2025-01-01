/*
- only need to modify the monoid functions
- be sure to reroot tree to intended root before calling lca or similar, as there a lot of internal reroots
- after calling access(v), T[v] will contain path from current root to v, and subtree of v when tree is rooted at current root
- subtree aggregate queries require invertibility
- subtree aggregate is T[v].self + T[v].vir (NOT T[v].sub!!!)  
- for the updates, just pass a lambda like:
    lct.update(1, [&](auto &x) {x.self += 10;});
*/
struct splay_tree_chan
{
    //monoid
    struct monoid_chan
    {
        int ch[2] = {0, 0}, p = 0;
        long long self = 0, path = 0; // Path aggregates
        long long sub = 0, vir = 0;   // Subtree aggregates
        bool flip = 0;                // Lazy tags
    };
    vector<monoid_chan> T;
    void push(int x)
    {
        if (!x || !T[x].flip)
            return;
        int l = T[x].ch[0], r = T[x].ch[1];

        T[l].flip ^= 1, T[r].flip ^= 1;

        swap(T[x].ch[0], T[x].ch[1]);
        T[x].flip = 0;
    }
    void pull(int x)
    {
        int l = T[x].ch[0], r = T[x].ch[1];
        push(l);
        push(r);

        T[x].path = T[l].path + T[x].self + T[r].path;
        T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
    }
    //pull/remove subtree of v from virtual subtree of u
    void pull_virtual (int u, int v)
    {
        T[u].vir += T[v].sub;
    }
    void remove_virtual (int u, int v)
    {
        T[u].vir -= T[v].sub;
    }

    //untouched
    splay_tree_chan(int n) : T(n + 1) {}
    void set(int x, int d, int y)
    {
        T[x].ch[d] = y;
        T[y].p = x;
        pull(x);
    }
    void splay(int x)
    {
        auto dir = [&](int x)
        {
            int p = T[x].p;
            if (!p)
                return -1;
            return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
        };
        auto rotate = [&](int x)
        {
            int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
            set(y, dx, T[x].ch[!dx]);
            set(x, !dx, y);
            if (~dy)
                set(z, dy, x);
            T[x].p = z;
        };
        for (push(x); ~dir(x);)
        {
            int y = T[x].p, z = T[y].p;
            push(z);
            push(y);
            push(x);
            int dx = dir(x), dy = dir(y);
            if (~dy)
                rotate(dx != dy ? x : y);
            rotate(x);
        }
    }
};
struct link_cut_chan : splay_tree_chan
{
    link_cut_chan(int n) : splay_tree_chan(n) {}

    int access(int x)
    {
        int u = x, v = 0;
        for (; u; v = u, u = T[u].p)
        {
            splay(u);
            int &ov = T[u].ch[1];
            pull_virtual(u, ov);
            remove_virtual(u, v);
            ov = v;
            pull(u);
        }
        return splay(x), v;
    }

    void reroot(int x)
    {
        access(x);
        T[x].flip ^= 1;
        push(x);
    }

    void link(int u, int v)
    {
        reroot(u);
        access(v);
        pull_virtual(v, u);
        T[u].p = v;
        pull(v);
    }

    void cut(int u, int v)
    {
        reroot(u);
        access(v);
        T[v].ch[0] = T[u].p = 0;
        pull(v);
    }

    // Rooted tree LCA. Returns 0 if u and v arent connected.
    int lca(int u, int v)
    {
        if (u == v)
            return u;
        access(u);
        int ret = access(v);
        return T[u].p ? ret : 0;
    }

    // Query subtree of u where v is outside the subtree.
    // The final answer is found by combining T[u].self and T[u].vir
    monoid_chan subtree(int u, int v)
    {
        reroot(v);
        access(u);
        return T[u];
    }

    // Query path [u..v]
    monoid_chan path(int u, int v)
    {
        reroot(u);
        access(v);
        return T[v];
    }

    // Update vertex u with value v
    void update(int u, auto upd)
    {
        access(u);
        upd(T[u]);
        pull(u);
    }
};