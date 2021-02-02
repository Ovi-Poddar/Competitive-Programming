#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long

const int N = 2e5 + 5;

int n;
int a[N];

struct Node
{
	int sum; //modify it
};

struct segtree
{
	int siz;
	vector<Node> tree;

	Node NEUTRAL_ELEMENT = {0}; //modify it

	Node merge(Node &a, Node &b) //modify it
	{
		return {a.sum + b.sum};
	}

	Node single(int val) //modify it
	{
		return {val};
	}

	void init(int n)
	{
		siz = 1;
		while (siz < n) siz *= 2;
		tree.resize(2 * siz + 100);
	}
	void build( int x, int lx, int rx)
	{
		if (rx == lx )
		{
			if(lx <= n)
				tree[x] = single(a[lx]);
			return;
		}
		int mid = (lx + rx) / 2;
		build( 2 * x , lx, mid);
		build( 2 * x + 1, mid + 1, rx);
		tree[x] = merge(tree[2 * x ], tree[2 * x + 1]);
	}
	void build()
	{
		build( 1, 1, siz);
	}
	void update(int i, int val, int x, int lx, int rx)
	{
		if (rx == lx )
		{
			tree[x] = single(val);
			return;
		}
		int mid = (lx + rx) / 2;
		if ( i <= mid) {
			update(i, val, 2 * x , lx, mid);
		}
		else {
			update(i, val, 2 * x + 1, mid + 1, rx);
		}
		tree[x] = merge(tree[2 * x ], tree[2 * x + 1]);
	}
	void update(int i, int val) //sets index i to val
	{
		update(i, val, 1, 1, siz);
	}
	Node query(int l, int r, int x, int lx, int rx)
	{
		if ( lx > r || rx < l) return NEUTRAL_ELEMENT;
		if (lx >= l && rx <= r) return tree[x];
		int mid = (lx + rx) / 2;
		Node s1 = query(l, r, 2 * x , lx, mid);
		Node s2 = query(l, r, 2 * x + 1, mid + 1, rx);
		return merge(s1, s2);
	}
	Node query(int l, int r)
	{
		return query(l, r, 1, 1, siz);
	}
};

int32_t main()
{
	IOS;

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	segtree st;
	st.init(n);
	st.build();

	cout<<st.query(1, n).sum;

	return 0;
}

