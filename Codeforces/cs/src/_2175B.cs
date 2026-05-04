using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _2175B
{
    public class _2175B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2175B.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (n, l, r) = ((uint)input.NextInt(), (uint)input.NextInt(), (uint)input.NextInt());
            uint[] b = new uint[n + 1];
            for (uint i = 1; i <= n; i++)
            {
                b[i] = i;
                if (i == r)
                {
                    b[i] = l - 1;
                }
            }

            for (int i = 1; i <= n; i++)
            {
                output.Append(b[i] ^ b[i - 1]).Append(" ");
            }

            output.AppendNewLine();
        }
    }
}
