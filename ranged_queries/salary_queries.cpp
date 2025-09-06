#include <bits/stdc++.h>
using namespace std;
#define int long long

//? this is a good problem, I got to know about co-ordinate compression in this problem.
//? use vector based mapping for faster results.

struct segmentTree
{
    vector<int> tree;
    segmentTree(int n)
    {
        tree.resize(4 * n + 1);
    }

    void build(int ind, int left, int right, vector<int> &arr)
    {
        if (left == right)
        {
            tree[ind] = arr[left];
            return;
        }
        int mid = left + (right - left) / 2;
        build(2 * ind + 1, left, mid, arr);
        build(2 * ind + 2, mid + 1, right, arr);
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
        vector<int> all;
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
            all.push_back(arr[i]);
        }
        // lets compress it
        vector<tuple<char, int, int>> queries(q + 1);
        for (int i = 1; i <= q; ++i)
        {
            cin >> get<0>(queries[i]) >> get<1>(queries[i]) >> get<2>(queries[i]);
            if (get<0>(queries[i]) == '?')
            {
                all.push_back(get<1>(queries[i]));
            }
            all.push_back(get<2>(queries[i]));
        }

        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        // for (int val : all)
        // {
        //     cout << val << " ";
        // }
        function<int(int)> getInd = [&](int val) -> int
        {
            return lower_bound(all.begin(), all.end(), val) - all.begin() + 1;
        };

        int size = all.size();
        vector<int> initarr(size + 1);
        for (int i = 1; i <= n; ++i)
        {
            initarr[getInd(arr[i])] += 1;
        }

        segmentTree satwik(size + 1);
        satwik.build(0, 1, size, initarr);
        for (int i = 1; i <= q; ++i)
        {
            if (get<0>(queries[i]) == '!')
            {
                int preVal = arr[get<1>(queries[i])];
                arr[get<1>(queries[i])] = get<2>(queries[i]);
                satwik.update(0, 1, size, getInd(preVal), -1);
                satwik.update(0, 1, size, getInd(get<2>(queries[i])), 1);
            }
            else
            {
                cout << satwik.query(0, 1, size, getInd(get<1>(queries[i])), getInd(get<2>(queries[i]))) << "\n";
            }
        }
    }
    return 0;
}