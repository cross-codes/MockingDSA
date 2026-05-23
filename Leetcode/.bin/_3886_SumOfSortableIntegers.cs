namespace _3886;

public class Solution
{
    public int SortableIntegers(int[] nums)
    {
        int n = nums.Length;
        List<int> factors = new();
        for (int k = 1; k * k <= n; k++)
        {
            if (n % k == 0)
            {
                factors.Add(k);
                if (k * k != n)
                {
                    factors.Add(n / k);
                }
            }
        }

        bool CyclicallySortable(List<int> elements)
        {
            int n = elements.Count;
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (elements[i] > elements[(i + 1) % n])
                {
                    cnt += 1;
                }
            }

            return cnt <= 1;
        }

        bool Ok(int k)
        {
            int gmx = int.MinValue;
            for (int i = 0; i < n; i += k)
            {
                List<int> subarr = new();
                for (int j = i; j < i + k; j++)
                {
                    subarr.Add(nums[j]);
                }

                if (subarr.Min() < gmx || !CyclicallySortable(subarr))
                {
                    return false;
                }

                gmx = subarr.Max();
            }

            return true;
        }

        int sum = 0;
        foreach (int k in factors)
        {
            sum += Ok(k) ? k : 0;
        }

        return sum;
    }
}
