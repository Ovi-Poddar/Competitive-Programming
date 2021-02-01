#include<bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long

const int N = 2e5 + 5;

struct Node
{
	int seg, pref, suf, sum; //Node Property
};

struct segtree
{
	int siz;
	vector<Node> tree;

	Node NEUTRAL_ELEMENT = {0, 0, 0, 0}; //modify it

	Node merge(Node &a, Node &b) //modify it 
	{
		return {
			max(a.seg, max(b.seg, a.suf + b.pref)),
			max(a.pref, a.sum + b.pref),
			max(b.suf, a.suf + b.sum),
			a.sum + b.sum
		};
	}

	Node single(int val) //modify it
	{
		if (val > 0) {
			return {val, val, val, val};
		}
		else {
			return {0, 0, 0, val};
		}
	}

	void init(int n) 
	{
		siz = 1;
		while (siz < n) siz *= 2;
		tree.resize(2 * siz);
	}
	void build(vector<int> &a, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < (int)a.size())
			{
				tree[x] = single(a[lx]);
			}
			return;
		}
		int mid = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, mid);
		build(a, 2 * x + 2, mid, rx);
		tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
	}
	void build(vector<int> &a)
	{
		build(a, 0, 0, siz);
	}
	void update(int i, int val, int x, int lx, int rx) //[lx, rx)
	{
		if (rx - lx == 1)
		{
			tree[x] = single(val);
			return;
		}
		int mid = (lx + rx) / 2;
		if ( i < mid) {
			update(i, val, 2 * x + 1, lx, mid);
		}
		else {
			update(i, val, 2 * x + 2, mid, rx);
		}
		tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
	}

	void update(int i, int val) //sets index i to val
	{
		update(i, val, 0, 0, siz);
	}
	Node query(int l, int r, int x, int lx, int rx) //[lx, rx), [l, r) 
	{
		if ( lx >= r || rx <= l) return NEUTRAL_ELEMENT;
		if (lx >= l && rx <= r) return tree[x];
		int mid = (lx + rx) / 2;
		Node s1 = query(l, r, 2 * x + 1, lx, mid);
		Node s2 = query(l, r, 2 * x + 2, mid, rx);
		return merge(s1, s2);
	}
	Node query(int l, int r) //[l, r)
	{
		return query(l, r, 0, 0, siz);
	}

};
	
//Problem Link :-
//https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

int32_t main()
{
	IOS;

	int n, m;
	cin >> n >> m;

	segtree st;
	st.init(n);
	
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	st.build(a);
	cout << st.query(0, n).seg << endl;
	while (m--)
	{
		int i, val;
		cin >> i >> val;
		st.update(i, val);
		cout << st.query(0, n).seg << endl;

	}

	return 0;
}

