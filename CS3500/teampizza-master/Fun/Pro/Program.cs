using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Threading;

namespace Pro
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                int NumberOfVariables = 0;
                

                while (true)
                {
                    Console.Write("Enter the desired number of variables: ");
                    string Var = Console.ReadLine();
                    
                    try
                    {
                        NumberOfVariables = Int32.Parse(Var);
                        break;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("\n Invalid entry! Thanks Obama!!! \n");
                    }
                }
                HashSet<StringBuilder> Results = GetPossibleCombinations(NumberOfVariables);
                // Print Results
                foreach(StringBuilder numString in Results)
                {
                    string ToConsole = numString.ToString();
                    Console.WriteLine("\n" + ToConsole);
                    //Thread.Sleep(10);
                }
                Console.WriteLine("\n There were " + Results.Count + " combinations for the given number of variables.\n");
                
                
            }


        }

        public static HashSet<StringBuilder> GetPossibleCombinations(int vars)
        {
            if (vars == 1)
            {
                HashSet <StringBuilder> Base = new HashSet<StringBuilder>();
                StringBuilder Base0 = new StringBuilder();
                StringBuilder Base1 = new StringBuilder();
                Base0.Append("0 ");
                Base1.Append("1 ");
                Base.Add(Base0);
                Base.Add(Base1);
                return Base;
            }
            else
            {
                HashSet<StringBuilder> PrevSet = GetPossibleCombinations(vars - 1);
                HashSet<StringBuilder> NewSet = new HashSet<StringBuilder>();
                // Append 0's
                foreach (StringBuilder numString in PrevSet)
                {
                    StringBuilder NewString = new StringBuilder();
                    NewString.Append(numString);
                    NewString.Append("0 ");
                    NewSet.Add(NewString);
                }
                // Append 1's
                foreach (StringBuilder numString in PrevSet)
                {
                    StringBuilder NewString = new StringBuilder();
                    NewString.Append(numString);
                    NewString.Append("1 ");
                    NewSet.Add(NewString);
                }
                return NewSet;
            }
        }
    }
}
