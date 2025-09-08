#include <bits/stdc++.h>
using namespace std;
#define int long long

//! update function was not needed for this problem, but if it was required the solution would be this.

struct node
{
    int maxPrefixSum = 0;
    int maxSuffixSum = 0;
    int maxSubarraySum = 0;
    int totalSum = 0;
    node(int a, int b, int c, int d)
    {
        this->maxPrefixSum = a;
        this->maxSuffixSum = b;
        this->maxSubarraySum = c;
        this->totalSum = d;
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
            tree[ind].maxPrefixSum = max(0LL, arr[left]);
            tree[ind].maxSuffixSum = max(0LL, arr[left]);
            tree[ind].maxSubarraySum = max(0LL, arr[left]);
            tree[ind].totalSum = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid, arr);
        build(2 * ind + 2, mid + 1, right, arr);

        // max prefix sum:->
        tree[ind].maxPrefixSum = max(tree[2 * ind + 1].maxPrefixSum, tree[2 * ind + 1].totalSum + tree[2 * ind + 2].maxPrefixSum);
        tree[ind].maxPrefixSum = max(tree[ind].maxPrefixSum, 0LL);

        // max suffix sum:->
        tree[ind].maxSuffixSum = max(tree[2 * ind + 2].maxSuffixSum, tree[2 * ind + 2].totalSum + tree[2 * ind + 1].maxSuffixSum);
        tree[ind].maxSuffixSum = max(0LL, tree[ind].maxSuffixSum);

        // total sum:->
        tree[ind].totalSum = tree[2 * ind + 1].totalSum + tree[2 * ind + 2].totalSum;

        // max subarray sum:->
        tree[ind].maxSubarraySum = max({0LL, tree[2 * ind + 1].maxSubarraySum, tree[2 * ind + 2].maxSubarraySum, tree[2 * ind + 1].maxSuffixSum + tree[2 * ind + 2].maxPrefixSum});
    }

    void update(int ind, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            tree[ind].maxPrefixSum = max(0LL, val);
            tree[ind].maxSubarraySum = max(0LL, val);
            tree[ind].maxSuffixSum = max(0LL, val);
            tree[ind].totalSum = val;
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

        // max prefix sum:->
        tree[ind].maxPrefixSum = max(tree[2 * ind + 1].maxPrefixSum, tree[2 * ind + 1].totalSum + tree[2 * ind + 2].maxPrefixSum);
        tree[ind].maxPrefixSum = max(tree[ind].maxPrefixSum, 0LL);

        // max suffix sum:->
        tree[ind].maxSuffixSum = max(tree[2 * ind + 2].maxSuffixSum, tree[2 * ind + 2].totalSum + tree[2 * ind + 1].maxSuffixSum);
        tree[ind].maxSuffixSum = max(0LL, tree[ind].maxSuffixSum);

        // total sum:->
        tree[ind].totalSum = tree[2 * ind + 1].totalSum + tree[2 * ind + 2].totalSum;

        // max subarray sum:->
        tree[ind].maxSubarraySum = max({0LL, tree[2 * ind + 1].maxSubarraySum, tree[2 * ind + 2].maxSubarraySum, tree[2 * ind + 1].maxSuffixSum + tree[2 * ind + 2].maxPrefixSum});
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
        node currResult(0, 0, 0, 0);

        // max prefix sum:->
        currResult.maxPrefixSum = max(leftResult.maxPrefixSum, leftResult.totalSum + rightResult.maxPrefixSum);
        currResult.maxPrefixSum = max(currResult.maxPrefixSum, 0LL);

        // max suffix sum:->
        currResult.maxSuffixSum = max(rightResult.maxSuffixSum, rightResult.totalSum + leftResult.maxSuffixSum);
        currResult.maxSuffixSum = max(0LL, currResult.maxSuffixSum);

        // total sum:->
        currResult.totalSum = leftResult.totalSum + rightResult.totalSum;

        // max subarray sum:->
        currResult.maxSubarraySum = max({0LL, leftResult.maxSubarraySum, rightResult.maxSubarraySum, leftResult.maxSuffixSum + rightResult.maxPrefixSum});
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
        int ind, val;
        for (int i = 1; i <= q; ++i)
        {
            cin >> ind >> val;
            // satwik.update(0, 1, n, ind, val);
            cout << satwik.query(0, 1, n, ind, val).maxSubarraySum << "\n";
        }
    }
    return 0;
}