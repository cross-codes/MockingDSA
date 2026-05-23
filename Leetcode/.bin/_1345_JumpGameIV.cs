namespace _1345;

public class Solution
{
    public int MinJumps(int[] arr)
    {
        int n = arr.Length;
        Dictionary<int, List<int>> positions = new();
        for (int i = 0; i < n; i++)
        {
            int e = arr[i];
            if (positions.ContainsKey(e)) positions[e].Add(i);
            else positions.Add(e, new List<int> { i });
        }

        bool InBounds(int idx)
        {
            return idx < n && idx >= 0;
        }

        Queue<int> queue = new();
        bool[] visited = new bool[n];
        int[] distance = new int[n];

        visited[0] = true;
        distance[0] = 0;
        queue.Enqueue(0);
        while (queue.Count != 0)
        {
            void visit(int u, int s)
            {
                visited[u] = true;
                distance[u] = distance[s] + 1;
                queue.Enqueue(u);
            }

            int i = queue.Dequeue();
            if (i == n - 1) break;

            if (InBounds(i - 1) && !visited[i - 1]) visit(i - 1, i);
            if (InBounds(i + 1) && !visited[i + 1]) visit(i + 1, i);
            foreach (int idx in positions[arr[i]])
                if (idx != i && !visited[idx]) visit(idx, i);

            positions[arr[i]].Clear();
        }

        return distance[n - 1];
    }
}
