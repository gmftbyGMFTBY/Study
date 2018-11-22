class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid):
        """
        :type obstacleGrid: List[List[int]]
        :rtype: int
        """
        n, m = len(obstacleGrid), len(obstacleGrid[0])
        dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
        
        # special judge of the [[1]]
        if n == 1 and m == 1:
            if obstacleGrid[0][0] == 1: return 0
            else: return 1
            
        # special judge of the start pos is 1
        if obstacleGrid[0][0] == 1: return 0
            
        dp[1][1] = 1
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if i == 1 and j == 1: continue
                else:
                    if obstacleGrid[i - 1][j - 1] == 1: continue
                    elif obstacleGrid[i - 1 - 1][j - 1] == 1:
                        dp[i][j] = dp[i][j - 1]
                    elif obstacleGrid[i - 1][j - 1 - 1] == 1:
                        dp[i][j] = dp[i - 1][j]
                    else:
                        dp[i][j] = dp[i][j - 1] + dp[i - 1][j]
        return dp[n][m]
