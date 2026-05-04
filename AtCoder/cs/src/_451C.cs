using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;
using Evermore.Collections.Ranged;

namespace _451C
{
    public class _451C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_451C.txt"), false);
            int t = 1;
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int Q = input.NextInt();
            ExplicitTreap<int> treap = new();
            while (Q-- > 0)
            {
                int type = input.NextInt();
                if (type == 1)
                {
                    int h = input.NextInt();
                    treap.Insert(h);
                }
                else
                {
                    int h = input.NextInt();
                    if (treap.Count > 0)
                    {
                        treap.RemoveAllInRange(treap.KthSmallestZeroIndexed(0), h);
                    }
                }
                output.Append(treap.Count).AppendNewLine();
            }
        }
    }
}
