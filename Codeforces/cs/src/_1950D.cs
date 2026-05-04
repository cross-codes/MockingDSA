using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950D
{
    public class _1950D
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950D.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int[] binaryDec = {
                // 00000,
                // 00001,
                00010,
                00011,
                00100,
                00101,
                00110,
                00111,
                01000,
                01001,
                01010,
                01011,
                01100,
                01101,
                01110,
                01111,
                10000,
                10001,
                10010,
                10011,
                10100,
                10101,
                10110,
                10111,
                11000,
                11001,
                11010,
                11011,
                11100,
                11101,
                11110,
                11111
            };

            Array.Reverse(binaryDec);

            int n = input.NextInt();

            if (n == 1)
            {
                output.Append("YES").AppendNewLine();
            }
            else
            {
                foreach (int bd in binaryDec)
                {
                    if (n % bd == 0)
                    {
                        // output.Append("BD: ").Append(bd).AppendNewLine();
                        while (n % bd == 0)
                        {
                            n /= bd;
                        }
                    }
                }

                output.Append(n == 1 ? "YES" : "NO").AppendNewLine();
            }
        }
    }
}
