using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _2211A
{
    public class _2211A
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2211A.txt"), false);
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
            int[] p = input.ReadIntegerArray(n);
            if (n == 1) {
                output.Append(1).AppendNewLine();
            } else {
                for (int i = 0; i < n; i++) {
                    output.Append(2).Append(" ");
                }

                output.AppendNewLine();
            }
        }
    }
}
