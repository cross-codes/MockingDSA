using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Evermore.IO;

namespace _1934D
{
    public class _1934D
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1934D.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            ulong n = (ulong)input.NextLong(), m = (ulong)input.NextLong();
            if (BitOperations.PopCount(n) == 1)
            {
                output.Append(-1).AppendNewLine();
            }
            else
            {
                int a = 63 - BitOperations.LeadingZeroCount(n);
                int b = 63 - BitOperations.LeadingZeroCount(n ^ (1UL << a));
                int msbm = 63 - BitOperations.LeadingZeroCount(m);
                if ((n ^ m) < n)
                {
                    output.Append(1).AppendNewLine();
                    output.AppendAll(n, " ", m).AppendNewLine();
                }
                else if (msbm <= b)
                {
                    output.Append(2).AppendNewLine();
                    output.AppendAll(n, " ", (1UL << (b + 1)) - 1, " ", m).AppendNewLine();
                }
                else
                {
                    output.Append(-1).AppendNewLine();
                }
            }
        }
    }
}
