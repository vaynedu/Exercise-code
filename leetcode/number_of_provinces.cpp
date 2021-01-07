class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if(isConnected.empty()) return 0;
        
        int n = isConnected.size();
        int cnt = 0;
        vector<bool> visited(n, false);
        
        for(int i = 0; i < n; i++){
            if(!visited[i]){
                cnt++;
                dfs(i, isConnected, visited);
            }
        }
        return cnt;
    }

    void dfs(int i, vector<vector<int>>& isConnected, vector<bool> &visited){
        visited[i] = true;

        for(int j = 0; j < isConnected.size(); j++){
            if(isConnected[i][j] == 1 && !visited[j]){
                dfs(j, isConnected, visited);
            }
        }
    }
   
};

// 三种方法
//https://leetcode-cn.com/problems/number-of-provinces/solution/dfs-bfs-bing-cha-ji-3-chong-fang-fa-ji-s-edkl/
