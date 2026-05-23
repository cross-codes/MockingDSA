namespace _3922;

public class Solution
{
    // all zeroes
    // only one 1
    // only ones at the beginning and end
    // all ones
    public int MinFlips(string s)
    {
        return Math.Max(0, Math.Min((s[0] != '1' ? 1 : 0) + (s[^1] != '1' ? 1 : 0) + s.Skip(1).SkipLast(1).Count(e => e == '1'), Math.Min(s.Count(e => e == '1') - 1, s.Count(e => e == '0'))));
    }
}
