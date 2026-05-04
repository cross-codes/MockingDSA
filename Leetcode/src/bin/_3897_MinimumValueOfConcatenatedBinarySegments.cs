namespace _3897;

using System;
using System.Runtime.CompilerServices;

public class Solution
{
    const int MOD = (int)1e9 + 7;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public static int ModPow(long n, long p, int m)
    {
        long result = 1L;
        for (long i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
        {
            if ((i & p) != 0)
            {
                result = result * j % m;
            }
        }
        return (int)result;
    }

    public int MaxValue(int[] nums1, int[] nums0)
    {
        int n = nums1.Length;
        (int o, int z)[] nums = new (int, int)[n];
        for (int i = 0; i < n; i++)
        {
            nums[i] = (nums1[i], nums0[i]);
        }

        Array.Sort(nums, (e1, e2) =>
        {
            if (e1.z == 0 && e2.z == 0) return 0;
            if (e1.z == 0) return -1;
            if (e2.z == 0) return 1;

            if (e1.o != e2.o)
            {
                return e2.o.CompareTo(e1.o);
            }

            return e1.z.CompareTo(e2.z);
        });

        Array.Reverse(nums);

        long Sum2Range(long x, long y)
        {
            if (x > y) return 0;
            return ((ModPow(2, y + 1, MOD) - ModPow(2, x, MOD)) + MOD) % MOD;
        }

        long pow = 0, res = 0;
        for (int i = 0; i < n; i++)
        {
            long pow_start = pow + nums[i].z;
            long pow_end = pow_start + nums[i].o - 1;

            res = (res + Sum2Range(pow_start, pow_end)) % MOD;
            pow += nums[i].z + nums[i].o;
        }

        return (int)res;
    }
}
