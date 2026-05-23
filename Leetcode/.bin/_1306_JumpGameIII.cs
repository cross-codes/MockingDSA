namespace _1306;

public class Solution
{
    public bool CanReach(int[] arr, int start)
    {
        int n = arr.Length;
        List<int>[] G = new List<int>[n];
        for (int i = 0; i < n; i++) G[i] = new();

        bool InBounds(int idx)
        {
            return idx >= 0 && idx < n;
        }

        for (int i = 0; i < n; i++)
        {
            if (arr[i] == 0) continue;
            if (InBounds(i - arr[i])) G[i].Add(i - arr[i]);
            if (InBounds(i + arr[i])) G[i].Add(i + arr[i]);
        }

        bool[] visited = new bool[n];
        void dfs(int u)
        {
            visited[u] = true;
            foreach (int v in G[u]) if (!visited[v]) dfs(v);
        }

        dfs(start);

        bool ok = false;
        for (int i = 0; i < n; i++) ok |= (arr[i] == 0 && visited[i]);
        return ok;
    }
}
