namespace _3921;

public class Solution
{
    public int[] ScoreValidator(string[] events)
    {
        int[] res = new int[2];
        foreach (string s in events)
        {
            if (res[1] == 10) break;
            if (s.Equals("W")) res[1] += 1;
            else if (s.Equals("WD") || s.Equals("NB")) res[0] += 1;
            else res[0] += int.Parse(s);
        }

        return res;
    }
}
