class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        dp = [0 for i in nums]
        for i in range(len(nums)):
            dp[i] = max(nums[i], dp[i - 1] + nums[i])
        
        return max(dp)
