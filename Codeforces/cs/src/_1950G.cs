using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950G
{
    public class _1950G
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950G.txt"), false);
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
            int gcg = 0, gcw = 0;
            Dictionary<string, int> seenGenres = new(), seenWriters = new();
            (int g, int w)[] list = new (int, int)[n];
            for (int i = 0; i < n; i++)
            {
                var (g, w) = (input.NextStr(), input.NextStr());
                if (seenGenres.ContainsKey(g))
                {
                    list[i].g = seenGenres[g];
                }
                else
                {
                    seenGenres.Add(g, gcg);
                    list[i].g = gcg++;
                }

                if (seenWriters.ContainsKey(w))
                {
                    list[i].w = seenWriters[w];
                }
                else
                {
                    seenWriters.Add(w, gcw);
                    list[i].w = gcw++;
                }
            }

            // foreach ((int g, int w) in list)
            // {
            //     output.AppendAll(g, " ", w).AppendNewLine();
            // }
            bool Check(List<(int g, int w)> xs)
            {
                int n = xs.Count;
                if (n == 0)
                {
                    return true;
                }

                bool[,] possible = new bool[1 << n, n];

                for (int j = 0; j < n; j++)
                {
                    possible[1 << j, j] = true;
                }

                for (int set = 1; set < (1 << n); set++)
                {
                    for (int last = 0; last < n; last++)
                    {
                        if (!possible[set, last]) continue;
                        for (int next = 0; next < n; next++)
                        {
                            if ((set & (1 << next)) == 0)
                            {
                                if (xs[last].g == xs[next].g || xs[last].w == xs[next].w)
                                {
                                    possible[set | (1 << next), next] = true;
                                }
                            }
                        }
                    }
                }

                for (int j = 0; j < n; j++)
                {
                    if (possible[(1 << n) - 1, j]) return true;
                }

                return false;
            }

            List<int>[] buckets = new List<int>[n + 1];
            for (int i = 0; i <= n; i++)
            {
                buckets[i] = new List<int>();
            }

            int tm = 1 << n;
            for (int mask = 0; mask < tm; ++mask)
            {
                int count = BitOperations.PopCount((uint)mask);
                buckets[count].Add(mask);
            }

            for (int k = n; k >= 0; --k)
            {
                foreach (int set in buckets[k])
                {
                    List<(int, int)> include = new();
                    for (int i = 0; i < 16; i++)
                    {
                        if ((set & (1 << i)) != 0)
                        {
                            include.Add(list[i]);
                        }
                    }

                    if (Check(include))
                    {
                        output.Append(n - BitOperations.PopCount((uint)set)).AppendNewLine();
                        return;
                    }
                }
            }
        }
    }
}
