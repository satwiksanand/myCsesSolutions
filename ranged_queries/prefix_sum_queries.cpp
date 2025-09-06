#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node
{
    int totalSum = 0LL;
    int maxPrefixSum = 0LL;
    node(int a, int b)
    {
        this->maxPrefixSum = b;
        this->totalSum = a;
    }
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
            tree[ind].totalSum = arr[left];
            tree[ind].maxPrefixSum = max(0LL, arr[left]);
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid, arr);
        build(2 * ind + 2, mid + 1, right, arr);
        tree[ind].totalSum = tree[2 * ind + 1].totalSum + tree[2 * ind + 2].totalSum;
        tree[ind].maxPrefixSum = max(tree[2 * ind + 1].maxPrefixSum, tree[2 * ind + 1].totalSum + tree[2 * ind + 2].maxPrefixSum);
        tree[ind].maxPrefixSum = max(0LL, tree[ind].maxPrefixSum);
    }

    void update(int ind, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            tree[ind].totalSum = val;
            tree[ind].maxPrefixSum = max(0LL, val);
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
        tree[ind].totalSum = tree[2 * ind + 1].totalSum + tree[2 * ind + 2].totalSum;
        tree[ind].maxPrefixSum = max(tree[2 * ind + 1].maxPrefixSum, tree[2 * ind + 1].totalSum + tree[2 * ind + 2].maxPrefixSum);
        tree[ind].maxPrefixSum = max(0LL, tree[ind].maxPrefixSum);
    }

    node query(int ind, int left, int right, int low, int high)
    {
        if (low > right || high < left)
        {
            return node();
        }
        if (left >= low && right <= high)
        {
            return tree[ind];
        }

        int mid = left + (right - left) / 2;
        node leftResult = query(2 * ind + 1, left, mid, low, high);
        node rightResult = query(2 * ind + 2, mid + 1, right, low, high);
        node currResult(0, 0);
        currResult.totalSum = leftResult.totalSum + rightResult.totalSum;
        currResult.maxPrefixSum = max(leftResult.maxPrefixSum, leftResult.totalSum + rightResult.maxPrefixSum);
        currResult.maxPrefixSum = max(0LL, currResult.maxPrefixSum);
        return currResult;
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
        int n, q;
        cin >> n >> q;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
        }
        segmentTree satwik(n + 1);
        satwik.build(0, 1, n, arr);
        int type, a, b;
        for (int i = 1; i <= q; ++i)
        {
            cin >> type >> a >> b;
            if (type == 1)
            {
                satwik.update(0, 1, n, a, b);
            }
            else
            {
                cout << satwik.query(0, 1, n, a, b).maxPrefixSum << "\n";
            }
        }
    }
    return 0;
}