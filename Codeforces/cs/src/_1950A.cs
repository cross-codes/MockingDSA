using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950A
{
    public class _1950A
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950A.txt"), false);
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
            if (a < b && b < c)
            {
                output.Append("STAIR").AppendNewLine();
            }
            else if (a < b && b > c)
            {
                output.Append("PEAK").AppendNewLine();
            }
            else
            {
                output.Append("NONE").AppendNewLine();
            }
        }
    }
}
