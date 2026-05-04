using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950B
{
    public class _1950B
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950B.txt"), false);
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
            char[,] grid = new char[n << 1, n << 1];
            bool flip = true;
            for (int y = 0; y < (n << 1); y += 2)
            {
                for (int x = 0; x < (n << 1); x += 2)
                {
                    grid[y, x] = flip ? '#' : '.';
                    grid[y, x + 1] = flip ? '#' : '.';
                    grid[y + 1, x] = flip ? '#' : '.';
                    grid[y + 1, x + 1] = flip ? '#' : '.';
                    flip = !flip;
                }
                if ((n & 1) == 0)
                {
                    flip = !flip;
                }
            }

            for (int y = 0; y < (n << 1); y++)
            {
                for (int x = 0; x < (n << 1); x++)
                {
                    output.Append(grid[y, x]);
                }

                output.AppendNewLine();
            }
        }
    }
}
