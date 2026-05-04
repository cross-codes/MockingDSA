namespace _1599;

public class Solution
{
    public bool ContainsCycle(char[][] grid)
    {
        int n = grid.Length, m = grid[0].Length;

        int[] dx = { -1, 0, 1, 0 };
        int[] dy = { 0, 1, 0, -1 };

        Color[,] color = new Color[n, m];
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < m; x++)
            {
                color[y, x] = Color.WHITE;
            }
        }

        bool valid(int y, int x)
        {
            return y >= 0 && y < n && x >= 0 && x < m;
        }

        bool cycleFound = false;
        void dfs(int y, int x, int py, int px)
        {
            color[y, x] = Color.GRAY;
            for (int i = 0; i < 4; i++)
            {
                int Y = y + dy[i], X = x + dx[i];
                if (valid(Y, X) && grid[Y][X] == grid[y][x])
                {
                    if (color[Y, X] == Color.GRAY && (Y, X) != (py, px))
                    {
                        cycleFound = true;
                    }

                    if (color[Y, X] == Color.WHITE)
                    {
                        dfs(Y, X, y, x);
                    }
                }
            }

            color[y, x] = Color.BLACK;
        }

        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < m; x++)
            {
                if (color[y, x] == Color.WHITE)
                {
                    dfs(y, x, -1, -1);
                }
            }
        }

        return cycleFound;
    }

    private enum Color
    {
        WHITE, GRAY, BLACK
    }
}
