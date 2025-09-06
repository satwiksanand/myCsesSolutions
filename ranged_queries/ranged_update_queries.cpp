#include <bits/stdc++.h>
using namespace std;
#define int long long

//* implementing segment tree with lazy propagation
class SGTree
{
    //? this is the segment tree for finding the min element in a dynamic array for any range.
private:
    vector<int> seg;  // segment tree array which contains the solution for individual node.
    vector<int> lazy; // lazy propagation array for storing pending updates.

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1, LLONG_MAX);
        lazy.resize(4 * n + 1, 0);
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

    void propagate(int ind, int low, int high)
    {
        if (lazy[ind] != 0)
        {
            seg[ind] += lazy[ind];
            if (low != high)
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
    }

    int query(int ind, int low, int high, int l, int r)
    {
        propagate(ind, low, high);

        // consider the three different overlaps.
        //? 1. no overlap:-
        if (l > high || r < low)
        {
            return LLONG_MAX;
        }

        //? 2. complete overlap:-
        if (low >= l && high <= r)
        {
            return seg[ind];
        }

        //? 3. partial overlap:-
        int mid = low + (high - low) / 2;
        return min(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }

    void rangeUpdate(int ind, int low, int high, int l, int r, int val)
    {
        propagate(ind, low, high);

        // consider the three different overlaps.
        //? 1. no overlap:-
        if (l > high || r < low)
        {
            return;
        }

        //? 2. complete overlap:-
        if (low >= l && high <= r)
        {
            seg[ind] += val;
            if (low != high)
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        //? 3. partial overlap:-
        int mid = low + (high - low) / 2;
        rangeUpdate(2 * ind + 1, low, mid, l, r, val);
        rangeUpdate(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void update(int ind, int low, int high, int pos, int val)
    {
        propagate(ind, low, high);

        if (low == high)
        {
            seg[ind] = val;
            return;
        }

        int mid = low + (high - low) / 2;
        if (pos <= mid)
        {
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
        cout << "Segment Tree: ";
        for (auto it : seg)
        {
            cout << it << " ";
        }
        cout << "\n";

        cout << "Lazy Array: ";
        for (auto it : lazy)
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
        int left, right, type, val;
        while (q--)
        {
            cin >> type;
            if (type == 1)
            {
                cin >> left >> right >> val;
                tree.rangeUpdate(0, 1, n, left, right, val);
            }
            else
            {
                cin >> left;
                cout << (tree.query(0, 1, n, left, left)) << "\n";
            }
        }
    }
    return 0;
}