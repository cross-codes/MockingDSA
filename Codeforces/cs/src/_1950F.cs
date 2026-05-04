using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950F
{
    public class _1950F
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950F.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (a, b, c) = (input.NextInt(), input.NextInt(), input.NextInt());
            (int l, int r)[] adj = new (int, int)[a + b + c];
            for (int i = 0; i < adj.Length; i++)
            {
                adj[i].l = adj[i].r = -1;
            }

            int nn = 1;
            Queue<int> queue = new();
            queue.Enqueue(0);
            while (queue.Count != 0)
            {
                int u = queue.Dequeue();
                if (a != 0)
                {
                    queue.Enqueue(nn);
                    adj[u].l = nn++;
                    queue.Enqueue(nn);
                    adj[u].r = nn++;
                    a -= 1;
                }
                else if (b != 0)
                {
                    queue.Enqueue(nn);
                    adj[u].l = nn++;
                    b -= 1;
                }
                else
                {
                    c -= 1;
                }
            }

            if ((a, b, c) != (0, 0, 0))
            {
                output.Append(-1).AppendNewLine();
            }
            else
            {
                int dfs(int u)
                {
                    if (adj[u] == (-1, -1))
                    {
                        return 0;
                    }
                    else
                    {
                        int h1 = -1, h2 = -1;
                        if (adj[u].l != -1)
                        {
                            h1 = dfs(adj[u].l);
                        }

                        if (adj[u].r != -1)
                        {
                            h2 = dfs(adj[u].r);
                        }

                        return 1 + Math.Max(h1, h2);
                    }
                }

                output.Append(dfs(0)).AppendNewLine();
            }
        }

    }
}
