namespace _3895;

public class Solution
{
    public int CountDigitOccurrences(int[] nums, int digit)
    {
        int CountOccurences(int e)
        {
            int cnt = 0;
            while (e != 0)
            {
                int d = e % 10;
                if (d == digit)
                {
                    cnt += 1;
                }

                e /= 10;
            }

            return cnt;
        }

        int gcnt = 0;
        foreach (int e in nums)
        {
            gcnt += CountOccurences(e);
        }

        return gcnt;
    }
}
