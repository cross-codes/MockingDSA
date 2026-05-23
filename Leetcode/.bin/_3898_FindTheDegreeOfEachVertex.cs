namespace _3898;

public class Solution
{
    public int[] FindDegrees(int[][] matrix)
    {
        int n = matrix.Length;
        int[] res = new int[n];
        for (int y = 0; y < n; y++)
        {
            res[y] = matrix[y].Sum();
        }

        return res;
    }
}
