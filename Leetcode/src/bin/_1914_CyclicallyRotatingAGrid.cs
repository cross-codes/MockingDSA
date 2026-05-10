namespace _1914;

public class Solution
{
    public int[][] RotateGrid(int[][] grid, int k)
    {
        int n = grid.Length, m = grid[0].Length;
        int[][] res = new int[n][];
        for (int i = 0; i < n; i++) res[i] = new int[m];

        void AddLayer(int depth)
        {
            List<int> elements = new((n + m) << 1);
            for (int y = depth; y < n - depth; y++) elements.Add(grid[y][depth]);
            for (int x = depth + 1; x < m - depth; x++) elements.Add(grid[n - depth - 1][x]);
            for (int y = n - depth - 2; y >= depth; y--) elements.Add(grid[y][m - depth - 1]);
            for (int x = m - depth - 2; x > depth; x--) elements.Add(grid[depth][x]);

            RotateList(elements);

            int idx = 0;
            for (int y = depth; y < n - depth; y++) res[y][depth] = elements[idx++];
            for (int x = depth + 1; x < m - depth; x++) res[n - depth - 1][x] = elements[idx++];
            for (int y = n - depth - 2; y >= depth; y--) res[y][m - depth - 1] = elements[idx++];
            for (int x = m - depth - 2; x > depth; x--) res[depth][x] = elements[idx++];
        }

        void RotateList(List<int> elements)
        {
            int t = elements.Count, r = k % t;
            elements.Reverse();
            elements.Reverse(0, r);
            elements.Reverse(r, t - r);
        }

        int mnd = Math.Min(n, m);
        for (int depth = 0; depth < (mnd + 1) >> 1; depth++) AddLayer(depth);

        return res;
    }
}
