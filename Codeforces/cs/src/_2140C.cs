using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _2140C
{
    public class _2140C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2140C.txt"), false);
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
            long[] a = input.ReadLongArray(n);
            if (n == 1)
            {
                output.Append(a[0]).AppendNewLine();
                return;
            }

            if (n == 2)
            {
                output.Append(Math.Max(a[0] - a[1], a[1] - a[0] + 1)).AppendNewLine();
                return;
            }

            long S = 0;
            bool flip = true;
            foreach (int e in a)
            {
                if (flip)
                {
                    S += e;
                }
                else
                {
                    S -= e;
                }
                flip = !flip;
            }
            long gmx = long.MinValue, mel = long.MaxValue, mol = long.MaxValue;

            for (int i = 0; i < n; i++)
            {
                long vp = i + (2L * a[i]);
                long vm = i - (2L * a[i]);

                if ((i & 1) == 0)
                {
                    if (mol != long.MaxValue)
                    {
                        gmx = Math.Max(gmx, vm - mol);
                    }
                    mel = Math.Min(mel, vp);
                }
                else
                {
                    if (mel != long.MaxValue)
                    {
                        gmx = Math.Max(gmx, vp - mel);
                    }

                    mol = Math.Min(mol, vm);
                }
            }

            if ((n & 1) != 0)
            {
                gmx = Math.Max(gmx, n - 1);
            }
            else
            {
                gmx = Math.Max(gmx, n - 2);
            }

            output.Append(gmx + S).AppendNewLine();
        }
    }
}
