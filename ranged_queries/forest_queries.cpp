#include <bits/stdc++.h>
using namespace std;
// #define int long long

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
        vector<string> mat(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> mat[i];
        }
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] = mat[i - 1][j - 1] == '*';
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 2; j <= n; ++j)
            {
                dp[i][j] += dp[i][j - 1];
            }
        }
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                dp[i][j] += dp[i - 1][j];
            }
        }

        // for(int i = 1; i <= n; ++i){
        //     for(int j = 1; j <= n; ++j){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }

        int x1, y1, x2, y2;

        while (q--)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << (dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1]) << "\n";
        }
    }
    return 0;
}