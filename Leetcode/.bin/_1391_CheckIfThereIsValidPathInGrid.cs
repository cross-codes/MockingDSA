namespace _1391;

using System.Diagnostics;

public class Solution {
    public bool HasValidPath(int[][] grid) {
        int n = grid.Length, m = grid[0].Length;

        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, 1, 0, -1};

        bool Valid (int y, int x) {
            return y >= 0 && y < n && x >= 0 && x < m;
        }

        bool ValidTransition(int fromType, int toType, Direction dir) {
            switch(fromType) {
                case 1:
                    switch (dir) {
                        case Direction.UP:
                            return false;
                        case Direction.DOWN:
                            return false;
                        case Direction.LEFT:
                            return toType is 1 or 4 or 6;
                        case Direction.RIGHT:
                            return toType is 1 or 3 or 5;
                    }
                    break;

                case 2:
                    switch (dir) {
                        case Direction.UP:
                            return toType is 2 or 3 or 4;
                        case Direction.DOWN:
                            return toType is 2 or 5 or 6;
                        case Direction.LEFT:
                            return false;
                        case Direction.RIGHT:
                            return false;
                    }
                    break;

                case 3:
                    switch (dir) {
                        case Direction.UP:
                            return false;
                        case Direction.DOWN:
                            return toType is 2 or 5 or 6;
                        case Direction.LEFT:
                            return toType is 1 or 4 or 6;
                        case Direction.RIGHT:
                            return false;
                    }
                    break;

                case 4:
                    switch (dir) {
                        case Direction.UP:
                            return false;
                        case Direction.DOWN:
                            return toType is 2 or 5 or 6;
                        case Direction.LEFT:
                            return false;
                        case Direction.RIGHT:
                            return toType is 1 or 3 or 5;
                    }
                    break;

                case 5:
                    switch (dir) {
                        case Direction.UP:
                            return toType is 2 or 3 or 4;
                        case Direction.DOWN:
                            return false;
                        case Direction.LEFT:
                            return toType is 1 or 4 or 6;
                        case Direction.RIGHT:
                            return false;
                    }
                    break;

                case 6:
                    switch (dir) {
                        case Direction.UP:
                            return toType is 2 or 3 or 4;
                        case Direction.DOWN:
                            return false;
                        case Direction.LEFT:
                            return false;
                        case Direction.RIGHT:
                            return toType is 1 or 3 or 5;
                    }
                    break;

                default:
                    throw new UnreachableException();
            }

            throw new UnreachableException();
        }

        Direction GetDir((int y, int x) from, (int y, int x) to) {
            if (from.y - to.y == -1) {
                return Direction.DOWN;
            } else if (from.y - to.y == 1) {
                return Direction.UP;
            } else if (from.x - to.x == 1) {
                return Direction.LEFT;
            } else {
                return Direction.RIGHT;
            }
        }

        bool[,] visited = new bool[n, m];
        void Dfs(int y, int x) {
            visited[y, x] = true;
            for (int i = 0; i < 4; i++) {
                var (Y, X) = (y + dy[i], x + dx[i]);
                Direction dir = GetDir((y, x), (Y, X));
                if (Valid(Y, X) && !visited[Y,X] && ValidTransition(grid[y][x], grid[Y][X], dir)) {
                    Dfs(Y, X);
                }
            }
        }

        Dfs(0, 0);
        return visited[n - 1, m - 1];
    }

    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }
}
