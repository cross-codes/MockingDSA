namespace _3923;

public class Solution
{
    public int MinGenerations(int[][] points, int[] target)
    {
        (int x, int y, int z) tgt = (target[0], target[1], target[2]);
        List<(int x, int y, int z)> prevGen = new();
        HashSet<(int, int, int)> seen = new();
        foreach (int[] point in points)
        {
            prevGen.Add((point[0], point[1], point[2]));
            seen.Add(prevGen[^1]);
        }

        if (seen.Contains(tgt)) return 0;

        for (int k = 1; k < 20; k++)
        {
            seen = new();
            List<(int x, int y, int z)> nextGen = new();
            foreach ((int x, int y, int z) point in prevGen)
            {
                seen.Add(point);
                nextGen.Add(point);
            }

            int n = prevGen.Count;
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (prevGen[i] == prevGen[j]) continue;
                    var nx = (prevGen[i].x + prevGen[j].x) >> 1;
                    var ny = (prevGen[i].y + prevGen[j].y) >> 1;
                    var nz = (prevGen[i].z + prevGen[j].z) >> 1;
                    if (!seen.Contains((nx, ny, nz)))
                    {
                        seen.Add((nx, ny, nz));
                        nextGen.Add((nx, ny, nz));
                    }
                }
            }

            if (seen.Contains(tgt)) return k;
            prevGen = nextGen;
        }

        return -1;
    }
}
