#include <bits/stdc++.h>
using namespace std;
#define int long long

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
            arr[i] += arr[i - 1];
        }
        int left, right;
        while (q--)
        {
            cin >> left >> right;
            cout << (arr[right] - arr[left - 1]) << "\n";
        }
    }
    return 0;
}