class Solution:
    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n, m = len(grid), len(grid[0])
        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        dp[1][1] = grid[0][0]
        
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                # need to special judge of the bound
                if i == 1 and j == 1: continue
                if i == 1: dp[i][j] = grid[i - 1][j - 1] + dp[i][j - 1]
                elif j == 1: dp[i][j] = grid[i - 1][j - 1] + dp[i - 1][j]
                else: dp[i][j] = grid[i - 1][j - 1] + min(dp[i - 1][j], dp[i][j - 1])
                
        return dp[n][m]
