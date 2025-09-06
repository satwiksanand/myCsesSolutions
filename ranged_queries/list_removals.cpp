#include <bits/stdc++.h>
using namespace std;
#define int long long

struct segmentTree
{
    vector<int> tree;
    segmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    void build(int ind, int left, int right)
    {
        if (left == right)
        {
            tree[ind] = 1;
            return;
        }
        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid);
        build(2 * ind + 2, mid + 1, right);
        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }

    void update(int ind, int left, int right, int pos)
    {
        if (left == right)
        {
            tree[ind] = 0;
            return;
        }

        int mid = left + (right - left) / 2;
        if (pos <= mid)
        {
            update(2 * ind + 1, left, mid, pos);
        }
        else
        {
            update(2 * ind + 2, mid + 1, right, pos);
        }
        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }

    int query(int ind, int left, int right, int pos)
    {
        if (left == right)
        {
            return left;
        }
        int mid = left + (right - left) / 2;
        if (pos <= tree[2 * ind + 1])
        {
            return query(2 * ind + 1, left, mid, pos);
        }
        return query(2 * ind + 2, mid + 1, right, pos - tree[2 * ind + 1]);
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
        int n;
        cin >> n;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
        }
        segmentTree satwik(n + 1);
        satwik.build(0, 1, n);
        int ind = 0;
        for (int i = 1; i <= n; ++i)
        {
            cin >> ind;
            int ans = satwik.query(0, 1, n, ind);
            cout << arr[ans] << " ";
            satwik.update(0, 1, n, ans);
        }
    }
    return 0;
}