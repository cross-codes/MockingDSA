using System.IO;
using System.Diagnostics;
using System;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;
using Evermore.Collections.Ranged;

namespace _2192C
{
    internal class _2192C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new StandardInputReader();
        private static readonly StandardOutputWriter output = new StandardOutputWriter();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2192C.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (n, h, k) = (input.NextInt(), input.NextInt(), input.NextInt());
            int[] a = new int[n];
            long S = 0;
            for (int i = 0; i < n; i++)
            {
                a[i] = input.NextInt();
                S += a[i];
            }

            var table = new IdempotentSparseTable<int>(a, Math.Max);
            long x = h / S;
            if (h - (x * S) == 0)
            {
                output.Append(x * n + (x - 1) * k).AppendNewLine();
                return;
            }
            else
            {
                long tt = x * (n + k), acc = 0, rem = h - (x * S);
                int mn = int.MaxValue;

                for (int L = 1; L <= n; L++)
                {
                    acc += a[L - 1];
                    mn = Math.Min(mn, a[L - 1]);

                    if (acc >= rem)
                    {
                        output.Append(tt + L).AppendNewLine();
                        return;
                    }

                    if (L < n)
                    {
                        int mx = table.RangeQuery(L, n);
                        long bss = acc - mn + mx;

                        if (bss >= rem)
                        {
                            output.Append(tt + L).AppendNewLine();
                            return;
                        }
                    }
                }
            }
        }
    }
}
