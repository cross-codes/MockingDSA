namespace _3905;

using System;
using System.Collections.Generic;

public class Solution
{
    public int[][] ColorGrid(int n, int m, int[][] sources)
    {
        int[][] grid = new int[n][];
        for (int y = 0; y < n; y++)
        {
            grid[y] = new int[m];
        }

        foreach (int[] desc in sources)
        {
            grid[desc[0]][desc[1]] = desc[2];
        }

        Queue<(int y, int x, int time)> queue = new();
        int[,] visited = new int[n, m];

        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < m; x++)
            {
                if (grid[y][x] != 0)
                {
                    queue.Enqueue((y, x, 1));
                    visited[y, x] = 1;
                }
            }
        }

        bool IsValid(int y, int x)
        {
            return y >= 0 && y < n && x >= 0 && x < m;
        }

        int[] dy = { -1, 0, 1, 0 };
        int[] dx = { 0, -1, 0, 1 };

        while (queue.Count != 0)
        {
            var (y, x, tt) = queue.Dequeue();

            int curr = grid[y][x];
            for (int i = 0; i < 4; i++)
            {
                (int Y, int X) = (y + dy[i], x + dx[i]);

                if (IsValid(Y, X))
                {
                    if (visited[Y, X] == 0)
                    {
                        grid[Y][X] = curr;
                        visited[Y, X] = tt + 1;
                        queue.Enqueue((Y, X, tt + 1));
                    }
                    else if (visited[Y, X] == tt + 1)
                    {
                        grid[Y][X] = Math.Max(grid[Y][X], curr);
                    }
                }
            }
        }

        return grid;
    }
}
