#include <bits/stdc++.h>
using namespace std;
// #define int long long

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
            tree[ind] = 0;
            return;
        }
        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid);
        build(2 * ind + 2, mid + 1, right);
        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }

    void update(int ind, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            tree[ind] += val;
            return;
        }
        int mid = left + (right - left) / 2;
        if (pos <= mid)
        {
            update(2 * ind + 1, left, mid, pos, val);
        }
        else
        {
            update(2 * ind + 2, mid + 1, right, pos, val);
        }
        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }

    int query(int ind, int left, int right, int low, int high)
    {
        if (low > right || high < left)
        {
            return 0;
        }
        if (left >= low && right <= high)
        {
            return tree[ind];
        }
        int mid = left + (right - left) / 2;
        return query(2 * ind + 1, left, mid, low, high) + query(2 * ind + 2, mid + 1, right, low, high);
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tt = 1;
    // cin >> tt;
    while (tt--)
    {
        int n = 0, q = 0;
        cin >> n >> q;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
        }
        map<int, int> last;
        vector<vector<array<int, 2>>> all(n + 1);
        for (int i = 1; i <= q; ++i)
        {
            int left, right;
            cin >> left >> right;
            all[right].push_back({left, i});
        }
        segmentTree satwik(n + 1);
        satwik.build(0, 1, n);

        vector<int> res(q + 1);

        for (int i = 1; i <= n; ++i)
        {
            if (last.count(arr[i]))
            {
                satwik.update(0, 1, n, last[arr[i]], -1);
            }
            last[arr[i]] = i;
            satwik.update(0, 1, n, i, 1);
            for (array<int, 2> &curr : all[i])
            {
                res[curr[1]] = satwik.query(0, 1, n, curr[0], i);
            }
        }

        for (int i = 1; i <= q; ++i)
        {
            cout << res[i] << "\n";
        }
    }
    return 0;
}