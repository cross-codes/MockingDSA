using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using Evermore.IO;

namespace _1950C
{
    public class _1950C
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950C.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            string time = input.NextStr();
            string inputfmt = "HH:mm";
            string outputfmt = "hh:mm tt";

            if (DateTime.TryParseExact(time, inputfmt, CultureInfo.InvariantCulture, DateTimeStyles.None, out DateTime dateTime))
            {
                string res = dateTime.ToString(outputfmt, CultureInfo.InvariantCulture);
                output.Append(res).AppendNewLine();
            }
            else
            {
                output.Append("NOOOOO").AppendNewLine();
            }
        }
    }
}
