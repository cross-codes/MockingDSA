namespace Evermore.Graphs;

public class DisjointSetForest
{
    public int[] sizes, parents;

    public DisjointSetForest(int n)
    {
        this.sizes = new int[n];
        this.parents = new int[n];

        for (int i = 0; i < n; i++)
        {
            MakeSet(i);
        }
    }

    private void MakeSet(int u)
    {
        parents[u] = u;
        sizes[u] = 1;
    }

    public int FindSet(int u)
    {
        if (parents[u] == u)
        {
            return u;
        }
        else
        {
            return parents[u] = FindSet(parents[u]);
        }
    }

    bool Unite(int x, int y)
    {
        int xRoot = FindSet(x), yRoot = FindSet(y);

        if (xRoot == yRoot)
        {
            return false;
        }

        if (sizes[xRoot] < sizes[yRoot])
        {
            int temp = xRoot;
            xRoot = yRoot;
            yRoot = temp;
        }

        sizes[xRoot] += sizes[yRoot];
        parents[yRoot] = xRoot;

        return true;
    }
}
