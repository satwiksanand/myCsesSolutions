#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node
{
    int minVal = INT_MAX;
    int maxVal = INT_MIN;

    node(int a, int b) : minVal(a), maxVal(b) {}
    node() = default;
};

struct segmentTree
{
    vector<node> tree;

    segmentTree(int n)
    {
        tree.resize(4 * n + 1, node());
    }

    void build(int ind, int left, int right, vector<int> &arr)
    {
        if (left == right)
        {
            tree[ind] = node(arr[left], arr[left]);
            return;
        }
        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid, arr);
        build(2 * ind + 2, mid + 1, right, arr);
        tree[ind] = node(min(tree[2 * ind + 1].minVal, tree[2 * ind + 2].minVal), max(tree[2 * ind + 1].maxVal, tree[2 * ind + 2].maxVal));
    }

    void update(int ind, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            tree[ind] = node(val, val);
            return;
        }
        int mid = left + (right - left) / 2;
        if (pos >= left && pos <= mid)
        {
            update(2 * ind + 1, left, mid, pos, val);
        }
        else
        {
            update(2 * ind + 2, mid + 1, right, pos, val);
        }
        tree[ind] = node(min(tree[2 * ind + 1].minVal, tree[2 * ind + 2].minVal), max(tree[2 * ind + 1].maxVal, tree[2 * ind + 2].maxVal));
    }

    int query(int ind, int left, int right, int val)
    { // this query code is different in the sense that we don't need low and high to define the segment since everytime we are looking on the whole array.
        if (left == right)
        {
            return tree[ind].minVal >= val ? left : -1;
        }
        int mid = left + (right - left) / 2;
        if (tree[2 * ind + 1].maxVal >= val)
        {
            return query(2 * ind + 1, left, mid, val);
        }
        else if (tree[2 * ind + 2].maxVal >= val)
        {
            return query(2 * ind + 2, mid + 1, right, val);
        }
        return -1;
    }
};

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    // cin>>tt;
    while (tt--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
        }
        segmentTree satwik(n + 1);
        satwik.build(0, 1, n, arr);
        int val = -1;
        while (m--)
        {
            cin >> val;
            int ans = satwik.query(0, 1, n, val);
            if (ans == -1)
            {
                cout << 0 << " ";
                continue;
            }
            cout << ans << " ";
            arr[ans] -= val;
            satwik.update(0, 1, n, ans, arr[ans]);
        }
    }
    return 0;
}