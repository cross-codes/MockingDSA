namespace _3924;

public class Solution
{
    public int MinimumThreshold(int n, int[][] edges, int source, int target, int k)
    {
        if (source == target) return 0;

        int mxw = int.MinValue;
        List<(int, int)>[] G = new List<(int, int)>[n];
        for (int i = 0; i < n; i++) G[i] = new();

        foreach (var edge in edges)
        {
            mxw = Math.Max(mxw, edge[2]);
            G[edge[0]].Add((edge[1], edge[2]));
            G[edge[1]].Add((edge[0], edge[2]));
        }

        bool pred(int M)
        {
            int[] minCosts = new int[n];
            Array.Fill(minCosts, int.MaxValue);
            minCosts[source] = 0;

            var deque = new LinkedList<int>();
            deque.AddFirst(source);

            while (deque.Count > 0)
            {
                int u = deque.First!.Value;
                deque.RemoveFirst();

                if (u == target) return minCosts[u] <= k;

                foreach ((int v, int w) in G[u])
                {
                    int weight = (w > M ? 1 : 0);
                    if (minCosts[u] + weight < minCosts[v])
                    {
                        minCosts[v] = minCosts[u] + weight;
                        if (weight == 0) deque.AddFirst(v);
                        else deque.AddLast(v);
                    }
                }
            }

            return false;
        }

        int L = -1, R = mxw + 1;
        while (R - L > 1)
        {
            int M = (L + R) >>> 1;
            if (pred(M)) R = M; else L = M;
        }

        return (R == mxw + 1) ? -1 : R;
    }
}
