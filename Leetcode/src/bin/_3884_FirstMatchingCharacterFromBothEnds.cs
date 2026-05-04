namespace _3884;

public class Solution
{
    public int FirstMatchingIndex(string s)
    {
        int n = s.Length;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == s[n - i - 1])
            {
                return i;
            }
        }

        return -1;
    }
}
