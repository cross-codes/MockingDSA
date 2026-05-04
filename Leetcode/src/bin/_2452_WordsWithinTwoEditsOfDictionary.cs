namespace _2452;

public class Solution
{
    public IList<string> TwoEditWords(string[] queries, string[] dictionary)
    {
        int n = queries[0].Length;

        List<string> res = new();
        foreach (string query in queries)
        {
            foreach (string word in dictionary)
            {
                int diff = 0;
                for (int i = 0; i < n; i++)
                {
                    if (query[i] != word[i])
                    {
                        diff += 1;
                    }
                }

                if (diff <= 2)
                {
                    res.Add(query);
                    break;
                }
            }
        }

        return res;
    }
}
