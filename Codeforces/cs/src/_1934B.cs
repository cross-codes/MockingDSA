using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1934B
{
    public class _1934B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1934B.txt"), false);
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
            int mn = int.MaxValue;
            for (int a = 0; a <= 2; a++)
            {
                for (int b = 0; b <= 1; b++)
                {
                    for (int c = 0; c <= 2; c++)
                    {
                        for (int d = 0; d <= 2; d++)
                        {
                            int S = a * 1 + b * 3 + c * 6 + d * 10;
                            if (S <= n && (n - S) % 15 == 0)
                            {
                                int e = (n - S) / 15;
                                mn = Math.Min(mn, a + b + c + d + e);
                            }
                        }
                    }
                }
            }

            output.Append(mn).AppendNewLine();
        }
    }
}
