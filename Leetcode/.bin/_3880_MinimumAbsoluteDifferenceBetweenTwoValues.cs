namespace _3880;

public class Solution
{
    public int MinAbsoluteDifference(int[] nums)
    {
        int n = nums.Length;
        int mx = int.MaxValue;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (nums[i] == 1 && nums[j] == 2)
                {
                    mx = Math.Min(mx, Math.Abs(i - j));
                }
            }
        }

        return mx == int.MaxValue ? -1 : mx;
    }
}
