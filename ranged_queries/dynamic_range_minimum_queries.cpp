#include <bits/stdc++.h>
using namespace std;
#define int long long

//* implementing segment tree
class SGTree
{
    //? this is the segment tree for finding the min element in a dynamic array for any range.
private:
    vector<int> seg; // segment tree array which contains the solution for individual node.
public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }

        int mid = low + (high - low) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r)
    {
        // consider the three different overlaps.
        //? 1. no overlap:->
        if (l > high || r < low)
        {
            return INT_MAX;
        }

        //? 2. complete overlap:->
        if (low >= l && high <= r)
        {
            return seg[ind];
        }

        //? 3. partial overlap:->
        int mid = low + (high - low) / 2;
        return min(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }

    void update(int ind, int low, int high, int pos, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }

        int mid = low + (high - low) / 2;
        if (pos <= mid)
        {
            // the index to be updated is in the left side of the recursion tree.
            update(2 * ind + 1, low, mid, pos, val);
        }
        else
        {
            update(2 * ind + 2, mid + 1, high, pos, val);
        }
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void printSGTree()
    {
        // just print the segment array.
        for (auto it : seg)
        {
            cout << it << " ";
        }
        cout << "\n";
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
        int n, q;
        cin >> n >> q;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
            // arr[i] += arr[i - 1];
        }
        SGTree tree(n + 1);
        tree.build(0, 1, n, arr);
        int left, right, type;
        while (q--)
        {
            cin >> type >> left >> right;
            if (type == 1)
            {
                tree.update(0, 1, n, left, right);
            }
            else
            {
                cout << (tree.query(0, 1, n, left, right)) << "\n";
            }
        }
    }
    return 0;
}