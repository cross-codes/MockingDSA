using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1675D
{
    public class _1675D
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1675D.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int n = input.NextInt();
            List<int>[] succ = new List<int>[n];
            for (int i = 0; i < n; i++)
            {
                succ[i] = new();
            }

            int[] par = new int[n];
            for (int i = 0; i < n; i++)
            {
                int p = input.NextInt() - 1;
                succ[p].Add(i);
                par[i] = p;
            }

            bool[] visited = new bool[n];

            int DisjointTR(int v)
            {
                while (!visited[par[v]] && par[v] != v)
                {
                    v = par[v];
                }
                return v;
            }

            List<int> MaximalHeight(int u)
            {
                visited[u] = true;
                List<int> lcp = new();
                foreach (int v in succ[u])
                {
                    if (!visited[v])
                    {
                        List<int> path = MaximalHeight(v);
                        if (path.Count > lcp.Count)
                        {
                            lcp = path;
                        }
                    }
                }

                visited[u] = false;
                List<int> best = new();
                best.Add(u);
                best.AddRange(lcp);

                return best;
            }

            List<List<int>> paths = new();
            for (int i = 0; i < n; i++)
            {
                if (!visited[i])
                {
                    int v = DisjointTR(i);
                    List<int> lp = MaximalHeight(v);
                    foreach (int u in lp)
                    {
                        visited[u] = true;
                    }
                    paths.Add(lp);
                }
            }

            output.Append(paths.Count).AppendNewLine();
            foreach (var path in paths)
            {
                output.Append(path.Count).AppendNewLine();
                foreach (int u in path)
                {
                    output.Append(u + 1).Append(" ");
                }

                output.AppendNewLine();
            }
        }
    }
}
