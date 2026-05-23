namespace _3918;

public class Solution
{
    public int SumOfPrimesInRange(int n)
    {
        int r = int.Parse(new string(n.ToString().Reverse().ToArray()));

        bool IsPrime(int n)
        {
            if (n < 2) return false;

            for (int i = 2; i * i <= n; i++)
            {
                if (n % i == 0) return false;
            }
            return true;
        }

        int cnt = 0, s = Math.Min(n, r), e = Math.Max(n, r);
        for (int i = s; i <= e; i++)
        {
            if (IsPrime(i))
            {
                cnt += i;
            }
        }

        return cnt;
    }
}
