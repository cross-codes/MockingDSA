namespace _2883;

using System.Linq;

public class Solution
{
    public int FurthestDistanceFromOrigin(string moves)
    {
        int left = moves.Count(c => c == 'L');
        int right = moves.Count(c => c == 'R');
        moves = moves.Replace('_', left > right ? 'L' : 'R');


        int x = 0;
        foreach (char c in moves)
        {
            x += c == 'L' ? -1 : 1;
        }

        return Math.Abs(x);
    }
}
