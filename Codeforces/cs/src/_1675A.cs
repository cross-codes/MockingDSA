using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1675A
{
    public class _1675A
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1675A.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (a, b, c, x, y) = (input.NextInt(), input.NextInt(), input.NextInt(), input.NextInt(), input.NextInt());

            int tot = 0;
            tot += Math.Max(x - a, 0);
            tot += Math.Max(y - b, 0);
            if (tot <= c) {
                output.Append("YES").AppendNewLine();
            } else {
                output.Append("NO").AppendNewLine();
            }
        }
    }
}
