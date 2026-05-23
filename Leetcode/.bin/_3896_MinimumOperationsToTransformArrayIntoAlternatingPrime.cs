namespace _3896;

using System;

public class Solution
{
    static int[] evenCost = new int[100001];
    static int[] oddCost = new int[100001];

    static Solution()
    {
        Array.Fill(evenCost, -1);
        Array.Fill(oddCost, -1);
    }

    private static bool IsPrime(int n)
    {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    private static int NextPrime(int n)
    {
        if (n <= 1) return 2;
        int prime = n + 1;
        while (!IsPrime(prime))
        {
            prime++;
        }
        return prime;
    }

    public int MinOperations(int[] nums)
    {
        int cnt = 0;

        for (int i = 0; i < nums.Length; i++)
        {
            int val = nums[i];

            if ((i & 1) == 0)
            {
                if (evenCost[val] == -1)
                {
                    if (!IsPrime(val))
                    {
                        evenCost[val] = NextPrime(val) - val;
                    }
                    else
                    {
                        evenCost[val] = 0;
                    }
                }
                cnt += evenCost[val];
            }
            else
            {
                if (oddCost[val] == -1)
                {
                    if (IsPrime(val))
                    {
                        oddCost[val] = (val == 2) ? 2 : 1;
                    }
                    else
                    {
                        oddCost[val] = 0;
                    }
                }
                cnt += oddCost[val];
            }
        }

        return cnt;
    }
}
