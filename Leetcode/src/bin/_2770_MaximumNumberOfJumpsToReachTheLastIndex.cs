namespace _2770;

public class Solution
{
    public int MaximumJumps(int[] nums, int target)
    {
        int n = nums.Length;

        int[] mxj = new int[n];
        Array.Fill(mxj, int.MinValue);
        int dfs(int i)
        {
            if (i == n - 1) return 0;
            if (mxj[i] != int.MinValue) return mxj[i];

            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] >= (long)nums[i] - target && nums[j] <= (long)nums[i] + target)
                {
                    mxj[i] = Math.Max(mxj[i], 1 + dfs(j));
                }
            }

            return mxj[i];
        }

        dfs(0);
        return (mxj[0] <= 0 ? -1 : mxj[0]);
    }
}
