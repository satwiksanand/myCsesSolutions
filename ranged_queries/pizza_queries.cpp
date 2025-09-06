#include <bits/stdc++.h>
using namespace std;
#define int long long

// the querying logic honestly was pretty difficult to see but i guess with practice we just get better.

struct node
{
    int leftMinCost;  // min cost if i was ordering from left house for any range [left ... right]
    int rightMinCost; // min cost if i was ordering from right house for any range [left ... right]
    node(int a, int b)
    {
        this->leftMinCost = a;
        this->rightMinCost = b;
    }
    node() = default;
};

struct segmentTree
{
    vector<node> tree;
    segmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    void build(int ind, int left, int right, vector<int> &arr)
    {
        if (left == right)
        {
            tree[ind].leftMinCost = arr[left];
            tree[ind].rightMinCost = arr[left];
            return;
        }
        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid, arr);
        build(2 * ind + 2, mid + 1, right, arr);
        tree[ind].leftMinCost = min(tree[2 * ind + 1].leftMinCost, tree[2 * ind + 2].leftMinCost + (mid - left + 1));
        tree[ind].rightMinCost = min(tree[2 * ind + 2].rightMinCost, tree[2 * ind + 1].rightMinCost + (right - mid));
    }

    void update(int ind, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            tree[ind].leftMinCost = val;
            tree[ind].rightMinCost = val;
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
        tree[ind].leftMinCost = min(tree[2 * ind + 1].leftMinCost, tree[2 * ind + 2].leftMinCost + (mid - left + 1));
        tree[ind].rightMinCost = min(tree[2 * ind + 2].rightMinCost, tree[2 * ind + 1].rightMinCost + (right - mid));
    }

    node query(int ind, int left, int right, int low, int high)
    {
        if (low > right || high < left)
        {
            return node(1e16, 1e16);
        }
        if (left >= low && right <= high)
        {
            return tree[ind];
        }
        int mid = left + (right - left) / 2;
        node leftResult = query(2 * ind + 1, left, mid, low, high);
        node rightResult = query(2 * ind + 2, mid + 1, right, low, high);
        node currResult(1e16, 1e16);
        int leftCost = 0;
        int rightCost = 0;
        if (high <= mid)
        {
            // the required segment in the left part.
            leftCost = high - max(left, low) + 1;
            rightCost = 0;
        }
        else if (low > mid)
        {
            // the required segment in the right part.
            leftCost = 0;
            rightCost = min(right, high) - max(mid + 1, low) + 1;
        }
        else
        {
            leftCost = mid - max(left, low) + 1;
            rightCost = min(right, high) - mid;
        }
        currResult.leftMinCost = min(leftResult.leftMinCost, rightResult.leftMinCost + leftCost);
        currResult.rightMinCost = min(rightResult.rightMinCost, leftResult.rightMinCost + rightCost);
        return currResult;
    }

    void printStree()
    {
        for (node curr : tree)
        {
            cout << curr.leftMinCost << " " << curr.rightMinCost << "\n";
        }
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tt = 1;
    // cin>>tt;
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
        int which, ind, val;
        for (int i = 1; i <= q; ++i)
        {
            cin >> which >> ind;
            if (which == 1)
            {
                cin >> val;
                satwik.update(0, 1, n, ind, val);
            }
            else
            {
                // satwik.printStree(); //bad way of doing things but I will figure it out soon.
                node leftResult = satwik.query(0, 1, n, 1, ind);
                node rightResult = satwik.query(0, 1, n, ind, n);
                // cout << leftResult.leftMinCost << " " << leftResult.rightMinCost << "\n";
                // cout << rightResult.leftMinCost << " " << rightResult.rightMinCost << "\n";
                cout << min(leftResult.rightMinCost, rightResult.leftMinCost) << "\n";
            }
        }
    }
    return 0;
}