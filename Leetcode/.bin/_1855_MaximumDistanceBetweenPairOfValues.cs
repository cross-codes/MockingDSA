namespace _1855;

public class Solution
{
    public int MaxDistance(int[] nums1, int[] nums2)
    {
        int n = nums1.Length, m = nums2.Length;

        List<(int v, int i)> supp = new();
        HashSet<int> seen = new();
        for (int i = 0; i < n; i++)
        {
            if (!seen.Contains(nums1[i]))
            {
                supp.Add((nums1[i], i));
                seen.Add(nums1[i]);
            }
        }

        supp.Reverse();
        int FirstEqualOrLesser(int e)
        {
            int L = -1, R = supp.Count;
            while (R - L > 1)
            {
                int M = (L + R) >>> 1;
                if (supp[M].v >= e)
                {
                    R = M;
                }
                else
                {
                    L = M;
                }
            }

            if (R == supp.Count)
            {
                return supp[^1].i;
            }
            return (supp[R].v > e) ? (L >= 0 ? supp[L].i : -1) : supp[R].i;
        }

        int mx = 0;
        for (int j = 0; j < m; j++)
        {
            int i = FirstEqualOrLesser(nums2[j]);
            if (i != -1 && i <= j)
            {
                mx = Math.Max(mx, j - i);
            }
        }

        return mx;
    }
}
