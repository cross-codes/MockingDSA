namespace _2906;

using System.Numerics;

public class Solution
{
    public int[][] ConstructProductMatrix(int[][] grid)
    {
        int n = grid.Length, m = grid[0].Length;
        int[][] result = new int[n][];
        for (int y = 0; y < n; y++)
        {
            result[y] = new int[m];
        }

        long prod = 1;
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < m; x++)
            {
                result[y][x] = Convert.ToInt32(prod);
                prod = (prod * grid[y][x]) % 12345;
            }
        }

        prod = 1;
        for (int y = n - 1; y >= 0; y--)
        {
            for (int x = m - 1; x >= 0; x--)
            {
                result[y][x] = Convert.ToInt32((prod * result[y][x]) % 12345);
                prod = (prod * grid[y][x]) % 12345;
            }
        }

        return result;
    }
}
