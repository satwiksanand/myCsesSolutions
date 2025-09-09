#include <bits/stdc++.h>
using namespace std;

struct SegTree
{
    int n;
    vector<int> tree;

    SegTree(int n)
    {
        this->n = n;
        tree.assign(4 * n, -1);
    }

    void update(int idx, int val, int node, int l, int r)
    {
        if (l == r)
        {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(idx, val, 2 * node, l, mid);
        else
            update(idx, val, 2 * node + 1, mid + 1, r);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int idx, int val)
    {
        update(idx, val, 1, 1, n);
    }

    int query(int ql, int qr, int node, int l, int r)
    {
        if (qr < l || r < ql)
            return -1;
        if (ql <= l && r <= qr)
            return tree[node];
        int mid = (l + r) / 2;
        return max(query(ql, qr, 2 * node, l, mid),
                   query(ql, qr, 2 * node + 1, mid + 1, r));
    }

    int query(int l, int r)
    {
        return query(l, r, 1, 1, n);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    // store last occurrences
    vector<int> lastOcc(n + 1, -1);
    unordered_map<int, set<int>> occ;

    SegTree st(n);

    // initialize
    for (int i = 1; i <= n; i++)
    {
        auto &S = occ[arr[i]];
        auto it = S.insert(i).first;

        int prevIdx = (it == S.begin() ? -1 : *std::prev(it));
        lastOcc[i] = prevIdx;
        st.update(i, prevIdx);

        // also fix the "next occurrence" after i
        auto nxt = std::next(it);
        if (nxt != S.end())
        {
            lastOcc[*nxt] = i;
            st.update(*nxt, i);
        }
    }

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int pos, val;
            cin >> pos >> val;
            if (arr[pos] == val)
                continue; // no change

            int oldVal = arr[pos];
            // erase pos from old value's set
            auto &S = occ[oldVal];
            auto it = S.find(pos);
            auto nxt = std::next(it);

            S.erase(it);

            // fix the "next occurrence"
            if (nxt != S.end())
            {
                int prevIdx = (nxt == S.begin() ? -1 : *std::prev(nxt));
                lastOcc[*nxt] = prevIdx;
                st.update(*nxt, prevIdx);
            }

            // insert pos into new value's set
            auto &T = occ[val];
            auto it2 = T.insert(pos).first;

            int prevIdx = (it2 == T.begin() ? -1 : *std::prev(it2));
            lastOcc[pos] = prevIdx;
            st.update(pos, prevIdx);

            auto nxt2 = std::next(it2);
            if (nxt2 != T.end())
            {
                lastOcc[*nxt2] = pos;
                st.update(*nxt2, pos);
            }

            arr[pos] = val;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            int mx = st.query(l, r);
            if (mx >= l)
                cout << "NO\n";
            else
                cout << "YES\n";
        }
    }
}

//! the above is the correct code(ChatGPT version), apparently the idea that i came up with was correct but
//! it gave tle for one of the test cases, what was missing is that i had to manage the indexes better

// TODO I will leave the code here, maybe fix it later.

// #include <bits/stdc++.h>
// using namespace std;
// // #define int long long

// // the node in the segment tree is supposed to contain the last index where it occured and if it is the first index then use -1 instead;

// // TODO: fix the TLE, i need a better way of finding the last occurance or we need to use an entirely different idea.

// struct segmentTree
// {
//     vector<int> tree;
//     segmentTree(int n)
//     {
//         tree.resize(4 * n + 1);
//     }
//     void build(int ind, int left, int right, vector<int> &arr)
//     {
//         if (left == right)
//         {
//             tree[ind] = arr[left];
//             return;
//         }
//         int mid = left + (right - left) / 2;
//         build(2 * ind + 1, left, mid, arr);
//         build(2 * ind + 2, mid + 1, right, arr);
//         tree[ind] = max(tree[2 * ind + 1], tree[2 * ind + 2]);
//     }

//     void update(int ind, int left, int right, int pos, int val)
//     {
//         if (left == right)
//         {
//             tree[ind] = val;
//             return;
//         }
//         int mid = left + (right - left) / 2;
//         if (pos <= mid)
//         {
//             update(2 * ind + 1, left, mid, pos, val);
//         }
//         else
//         {
//             update(2 * ind + 2, mid + 1, right, pos, val);
//         }
//         tree[ind] = max(tree[2 * ind + 1], tree[2 * ind + 2]);
//     }

//     int query(int ind, int left, int right, int low, int high)
//     {
//         if (low > right || high < left)
//         {
//             return -1;
//         }
//         if (left >= low && right <= high)
//         {
//             return tree[ind];
//         }
//         int mid = left + (right - left) / 2;
//         return max(query(2 * ind + 1, left, mid, low, high), query(2 * ind + 2, mid + 1, right, low, high));
//     }
// };

// int32_t main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     int tt = 1;
//     // cin>>tt;
//     while (tt--)
//     {
//         int n, q;
//         cin >> n >> q;
//         vector<int> arr(n + 1);
//         map<int, set<int>> ind;
//         for (int i = 1; i <= n; ++i)
//         {
//             cin >> arr[i];
//             ind[arr[i]].insert(i);
//         }
//         vector<int> initarr(n + 1);
//         for (int i = 1; i <= n; ++i)
//         {
//             auto last = ind[arr[i]].lower_bound(i);
//             if (last == ind[arr[i]].begin())
//             {
//                 initarr[i] = -1;
//             }
//             else
//             {
//                 last--;
//                 initarr[i] = *last;
//             }
//         }

//         // print the array
//         // for (int i = 1; i <= n; ++i)
//         // {
//         //     cout << initarr[i] << " \n"[i == n];
//         // }

//         segmentTree satwik(n + 1);
//         satwik.build(0, 1, n, initarr);
//         int type;
//         for (int i = 1; i <= q; ++i)
//         {
//             cin >> type;
//             if (type == 1)
//             {
//                 int pos, val;
//                 cin >> pos >> val;
//                 int preVal = arr[pos];
//                 arr[pos] = val;
//                 ind[preVal].erase(pos);
//                 // erasing the preval;
//                 auto nextPreVal = ind[preVal].upper_bound(pos);
//                 if (nextPreVal != ind[preVal].end())
//                 {
//                     int nextPreInd = *nextPreVal;
//                     if (nextPreVal == ind[preVal].begin())
//                     {
//                         satwik.update(0, 1, n, nextPreInd, -1);
//                     }
//                     else
//                     {
//                         nextPreVal--;
//                         int lastPreVal = *nextPreVal;
//                         satwik.update(0, 1, n, nextPreInd, lastPreVal);
//                     }
//                 }

//                 // inserting the newval
//                 auto nextNewVal = ind[val].upper_bound(pos);
//                 if (nextNewVal == ind[val].end())
//                 {
//                     if (ind[val].size() == 0)
//                     {
//                         satwik.update(0, 1, n, pos, -1);
//                     }
//                     else
//                     {
//                         nextNewVal--;
//                         int lastNewInd = *nextNewVal;
//                         satwik.update(0, 1, n, pos, lastNewInd);
//                     }
//                 }
//                 else
//                 {
//                     int nextNewInd = *nextNewVal;
//                     if (nextNewVal == ind[val].begin())
//                     {
//                         satwik.update(0, 1, n, nextNewInd, pos);
//                         satwik.update(0, 1, n, pos, -1);
//                     }
//                     else
//                     {
//                         nextNewVal--;
//                         int lastNewInd = *nextNewVal;
//                         satwik.update(0, 1, n, pos, lastNewInd);
//                         satwik.update(0, 1, n, nextNewInd, pos);
//                     }
//                 }
//                 ind[val].insert(pos);
//             }
//             else
//             {
//                 int left, right;
//                 cin >> left >> right;
//                 int currHighest = satwik.query(0, 1, n, left, right);
//                 if (currHighest >= left)
//                 {
//                     cout << "NO\n";
//                 }
//                 else
//                 {
//                     cout << "YES\n";
//                 }
//             }
//         }
//     }
//     return 0;
// }