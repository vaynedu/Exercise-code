//动态规划求一条路径最小的路（二位数组中）

int minPathSum(vector<vector int> > &grid){
    int i = 0;
    int j = 0;
    int m = grid.size();
    int n = grid[0].size();
    vector<vector int > > dp(m,vector<int>(n));
    dp[0][0] = grid[0][0];

    for(i = 1; i < m; i++){
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for(j = 1; j < n; j++){
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }

    for(i = 1; i < m; i++){
        for(j = 1; j < n; j++){
            dp[i][j] = min(dp[i][j-1],dp[i-1][j]) + a[i][j];
        }
    }
     
    return dp[m-1][n-1];

}
