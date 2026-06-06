namespace _3121;

public class Solution
{
    public int NumberOfSpecialChars(string word)
    {
        int cnt = 0;
        for (char c = 'a'; c <= 'z'; c++)
            cnt += word.Contains(c) && word.Contains(Char.ToUpper(c)) && (word.LastIndexOf(c) < word.IndexOf(Char.ToUpper(c))) ? 1 : 0;

        return cnt;
    }
}
