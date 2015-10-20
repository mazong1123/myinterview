using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpInterviews
{
    /// <summary>
    /// What is the output of the program below? Explain your answer.
    /// Also, would the answer change if we were to replace await Task.Delay(5); with Thread.Sleep(5)? Why or why not?
    /// <see cref="http://www.toptal.com/c-sharp/interview-questions"/>
    /// </summary>
    public static class AsyncTaskOutput
    {
        private static string result;

        public static async Task<string> SaySomething()
        {
            await Task.Delay(5);
            result = "Hello world!";

            return "Something";
        }

        public static void Run()
        {
            SaySomething();

            Console.WriteLine(result);
        }
    }
}
