namespace _3912;

public class Solution
{
    public IList<int> FindValidElements(int[] nums)
    {
        int n = nums.Length;
        bool isGreaterRight(int idx)
        {
            int curr = nums[idx];
            for (int i = idx + 1; i < n; i++)
            {
                if (nums[i] >= curr)
                {
                    return false;
                }
            }

            return true;
        }

        bool isGreaterLeft(int idx)
        {
            int curr = nums[idx];
            for (int i = idx - 1; i >= 0; i--)
            {
                if (nums[i] >= curr)
                {
                    return false;
                }
            }

            return true;
        }

        List<int> valid = new();
        valid.Add(nums[0]);
        for (int i = 1; i < n - 1; i++)
        {
            if (isGreaterRight(i) || isGreaterLeft(i))
            {
                valid.Add(nums[i]);
            }
        }

        if (n != 1)
        {
            valid.Add(nums[^1]);
        }
        return valid;
    }
}
