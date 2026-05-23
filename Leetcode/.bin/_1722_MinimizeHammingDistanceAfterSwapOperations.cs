namespace _1722;

public class Solution
{
    public int MinimumHammingDistance(int[] source, int[] target, int[][] allowedSwaps)
    {
        int n = source.Length;
        List<List<int>> adj = new();
        for (int i = 0; i < n; i++)
        {
            adj.Add(new());
        }


        for (int i = 0; i < allowedSwaps.Length; i++)
        {
            int a = allowedSwaps[i][0], b = allowedSwaps[i][1];
            adj[a].Add(b);
            adj[b].Add(a);
        }

        bool[] visited = new bool[n];
        void dfs(List<int> cc, int u)
        {
            cc.Add(u);
            visited[u] = true;
            foreach (int e in adj[u])
            {
                if (!visited[e])
                {
                    dfs(cc, e);
                }
            }
        }

        List<List<int>> ccs = new();
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                List<int> cc = new();
                dfs(cc, i);
                ccs.Add(cc);
            }
        }


        int cnt = 0;
        foreach (List<int> cc in ccs)
        {
            Dictionary<int, int> srcElements = new(), targetElements = new();
            foreach (int idx in cc)
            {
                if (srcElements.ContainsKey(source[idx]))
                {
                    srcElements[source[idx]] += 1;
                }
                else
                {
                    srcElements.Add(source[idx], 1);
                }

                if (targetElements.ContainsKey(target[idx]))
                {
                    targetElements[target[idx]] += 1;
                }
                else
                {
                    targetElements.Add(target[idx], 1);
                }
            }

            foreach ((int k, int v) in targetElements)
            {
                if (srcElements.ContainsKey(k))
                {
                    cnt += Math.Max(0, v - srcElements[k]);
                }
                else
                {
                    cnt += v;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (source[i] != target[i])
                {
                    cnt += 1;
                }
            }
        }

        return cnt;
    }
}
