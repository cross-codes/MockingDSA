using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _451B
{
    public class _451B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_451B.txt"), false);
            int t = 1;
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (N, M) = (input.NextInt(), input.NextInt());
            (int prev, int next)[] dept = new (int, int)[M];
            for (int i = 0; i < N; i++)
            {
                var (A, B) = (input.NextInt(), input.NextInt());
                dept[A - 1].prev += 1;
                dept[B - 1].next += 1;
            }

            foreach ((int prev, int next) in dept)
            {
                output.Append(next - prev).AppendNewLine();
            }
        }
    }
}
