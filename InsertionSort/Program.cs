using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InsertionSort
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] input = new int[] { 31, 41, 59, 26, 41, 58 };

            InsertionSortAscending((int[])input.Clone());
            InsertionSortDescending((int[])input.Clone());
        }

        static void InsertionSortAscending(int[] input)
        {
            for (int i = 1; i < input.Length; i++)
            {
                int k = input[i];
                int j = i - 1;
                while (j > -1 && input[j] > k)
                {
                    input[j + 1] = input[j];
                    j--;
                }

                input[j + 1] = k;
            }

            Console.WriteLine(string.Join(" ", input.Select(x => x.ToString())));
        }

        static void InsertionSortDescending(int[] input)
        {
            for (int i = 1; i < input.Length; i++)
            {
                int k = input[i];
                int j = i - 1;
                while (j > -1 && input[j] < k)
                {
                    input[j + 1] = input[j];
                    j--;
                }

                input[j + 1] = k;
            }

            Console.WriteLine(string.Join(" ", input.Select(x => x.ToString())));
        }
    }
}
