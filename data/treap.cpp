struct treap {
    struct node {
        ll val, sum, lazy, priority;
        int size;
        node *left, *right;
        node(ll v) : val(v), sum(v), lazy(0), priority(rand()), size(1), left(nullptr), right(nullptr) {}
    };

    node* root = nullptr;

    int size(node* t) { return t ? t->size : 0; }
    ll sum(node* t) { return t ? t->sum : 0; }

    void apply(node* t, ll lazy) {
        if (!t) return;
        t->val += lazy;
        t->sum += lazy * t->size;
        t->lazy += lazy;
    }

    void push(node* t) {
        if (!t || t->lazy == 0) return;
        apply(t->left, t->lazy);
        apply(t->right, t->lazy);
        t->lazy = 0;
    }

    void pull(node* t) {
        if (!t) return;
        t->size = 1 + size(t->left) + size(t->right);
        t->sum = t->val + sum(t->left) + sum(t->right);
    }

    void split(node* t, int key, node*& left, node*& right) {
        if (!t) return void(left = right = nullptr);
        push(t);
        if (size(t->left) < key) {
            split(t->right, key - size(t->left) - 1, t->right, right);
            left = t;
        } else {
            split(t->left, key, left, t->left);
            right = t;
        }
        pull(t);
    }

    node* merge(node* left, node* right) {
        if (!left || !right) return left ? left : right;
        push(left), push(right);
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            pull(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            pull(right);
            return right;
        }
    }

    void insert(int pos, ll val) {
        node *left, *right;
        split(root, pos, left, right);
        root = merge(merge(left, new node(val)), right);
    }

    void erase(int pos) {
        node *left, *mid, *right;
        split(root, pos, left, mid);
        split(mid, 1, mid, right);
        root = merge(left, right);
        delete mid;
    }

    void range_update(int l, int r, ll delta) {
        node *left, *mid, *right;
        split(root, l, left, mid);
        split(mid, r - l + 1, mid, right);
        apply(mid, delta);
        root = merge(merge(left, mid), right);
    }

    ll range_query(int l, int r) {
        node *left, *mid, *right;
        split(root, l, left, mid);
        split(mid, r - l + 1, mid, right);
        ll res = sum(mid);
        root = merge(merge(left, mid), right);
        return res;
    }
};
