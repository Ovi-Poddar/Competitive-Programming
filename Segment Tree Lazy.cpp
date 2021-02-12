const int N = 2e5 + 5;
int a[N];

struct data
{
    //Use required attributes
    int sum;

    //Default Values
    data() : sum(0) {};
};

struct SegTree
{
    int N;
    vector<data> st;
    vector<bool> cLazy;
    vector<int> lazy;

    void init(int n)
    {
        N = n;
        st.resize(4 * N + 5);
        cLazy.assign(4 * N + 5, false);
        lazy.assign(4 * N + 5, 0);
    }

    //Write required merge functions
    void merge(data &cur, data &l, data &r)
    {
        cur.sum = l.sum + r.sum;
    }

    void build(int node, int L, int R)
    {
        if (L == R)
        {
            st[node].sum = a[L];
            return;
        }
        int M = (L + R) / 2;
        build(node * 2, L, M);
        build(node * 2 + 1, M + 1, R);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    //Handle lazy propagation appropriately
    void propagate(int node, int L, int R)
    {
        if (!cLazy[node]) return;

        if (L != R)
        {
            cLazy[node * 2] = 1;
            cLazy[node * 2 + 1] = 1;
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        st[node].sum = (R - L + 1) * lazy[node];
        cLazy[node] = 0;
    }

    data Query(int node, int L, int R, int i, int j)
    {
        propagate(node, L, R);
        if (j < L || i > R)
            return data();
        if (i <= L && R <= j)
            return st[node];
        int M = (L + R) / 2;
        data left = Query(node * 2, L, M, i, j);
        data right = Query(node * 2 + 1, M + 1, R, i, j);
        data cur;
        merge(cur, left, right);
        return cur;
    }

    data pQuery(int node, int L, int R, int pos)
    {
        if (cLazy[node])
            propagate(node, L, R);
        if (L == R)
            return st[node];
        int M = (L + R) / 2;
        if (pos <= M)
            return pQuery(node * 2, L, M, pos);
        else
            return pQuery(node * 2 + 1, M + 1, R, pos);
    }

    void Update(int node, int L, int R, int i, int j, int val)
    {
        propagate(node, L, R);
        if (j < L || i > R)
            return;
        if (i <= L && R <= j)
        {
            cLazy[node] = 1;
            lazy[node] = val;
            propagate(node, L, R);
            return;
        }
        int M = (L + R) / 2;
        Update(node * 2, L, M, i, j, val);
        Update(node * 2 + 1, M + 1, R, i, j, val);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    void pUpdate(int node, int L, int R, int pos, int val)
    {
        propagate(node, L, R);
        if (L == R)
        {
            cLazy[node] = 1;
            lazy[node] = val;
            propagate(node, L, R);
            return;
        }
        int M = (L + R) / 2;
        if (pos <= M)
            pUpdate(node * 2, L, M, pos, val);
        else
            pUpdate(node * 2 + 1, M + 1, R, pos, val);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    data query(int pos)
    {
        return pQuery(1, 1, N, pos);
    }

    data query(int l, int r)
    {
        return Query(1, 1, N, l, r);
    }

    void update(int pos, int val)
    {
        pUpdate(1, 1, N, pos, val);
    }

    void update(int l, int r, int val)
    {
        Update(1, 1, N, l, r, val);
    }
};

------------------------------------------------------------------------

// const int N = 2e5 + 5;
// int tree[4 * N], lazy[4 * N], a[N];

// void init(int n) {
//     for (int i = 1; i <= 4 * n; i++) lazy[i] = -1;
// }

// void build (int cn, int b, int e) {
//     if (b == e) {
//         tree[cn] = a[b];
//         return;
//     }
//     int lc = 2 * cn, rc = lc + 1, mid = (b + e) / 2;
//     build(lc, b, mid);
//     build(rc, mid + 1, e);
//     tree[cn] = tree[lc] + tree[rc];
// }

// void relax (int cn, int b, int e) {
//     if (lazy[cn] == -1) return;
//     tree[cn] = (e - b + 1) * lazy[cn];
//     if (b != e) {
//         lazy[2 * cn] = lazy[cn] ;
//         lazy[2 * cn + 1] = lazy[cn] ;
//     }
//     lazy[cn] = -1;
// }

// void upd (int cn, int b, int e, int i, int j, int add) {
//     relax(cn, b, e);
//     if (b > j or e < i) {
//         return;
//     }
//     int lc = 2 * cn , rc = lc + 1 , mid = (b + e) / 2;
//     if (b >= i and e <= j) {
//         lazy[cn] = add;
//         relax(cn, b, e);
//         return;
//     }
//     upd(lc, b, mid, i, j, add);
//     upd(rc, mid + 1, e, i, j, add);
//     tree[cn] = tree[lc] + tree[rc];
// }

// int query (int cn, int b, int e, int i, int j) {
//     relax(cn, b, e);
//     if (b > j or e < i) return 0;
//     if (b >= i and e <= j) {
//         return tree[cn];
//     }
//     int lc = 2 * cn, rc = lc + 1, mid = (b + e) / 2;
//     return query(lc, b, mid, i, j) + query(rc, mid + 1, e, i, j);
// }

