namespace _3904;

public class Solution
{
    public int FirstStableIndex(int[] nums, int k)
    {
        int n = nums.Length;
        int[] mxs = new int[n], mns = new int[n];

        int curmx = nums[0];
        for (int i = 0; i < n; i++)
        {
            curmx = Math.Max(curmx, nums[i]);
            mxs[i] = curmx;
        }

        int curmn = nums[^1];
        for (int i = n - 1; i >= 0; i--)
        {
            curmn = Math.Min(curmn, nums[i]);
            mns[i] = curmn;
        }

        for (int i = 0; i < n; i++)
        {
            if (mxs[i] - mns[i] <= k)
            {
                return i;
            }
        }

        return -1;
    }
}
