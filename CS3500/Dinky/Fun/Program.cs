using Fun;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Fun
{
    class Program
    {

        static void Main(string[] args)
        {
            while (true)
            {
                int NumberOfValues = 0;
                int count = 0;
                while (true)
                {
                    Console.Write("Enter the number of variables you want to view: ");
                    string NumberOfValuesString = Console.ReadLine();

                    try
                    {
                        NumberOfValues = Int32.Parse(NumberOfValuesString);
                        break;
                    }
                    catch
                    {
                        Console.WriteLine("\n" + "Invalid entry idiot.");
                    }
                }



                bool SecondToLast = false;
                int[] printa = new int[NumberOfValues];
                // Init array to 0
                for (int i = 0; i < NumberOfValues; i++)
                {
                    printa[i] = 0;

                }
                //Console.WriteLine(printa.makeString());
                // body
                for (int i = 0; i < NumberOfValues; i++)
                {
                    if ( i == 1 && NumberOfValues == 2)
                    {
                        printa[1] = 1;
                        break;
                    }
                    
                        printa[i] = 1;
                    
                    


                    if ((i == NumberOfValues - 2) && !(NumberOfValues == 2))
                    {
                        SecondToLast = true;
                    }
                    else
                    {
                        Console.WriteLine(printa.makeString());
                        count++;
                    }

                    if (!SecondToLast)
                    {
                        for (int j = i + 1; j < NumberOfValues; j++)
                        {
                            printa[j] = 1;
                            Console.WriteLine(printa.makeString());
                            count++;
                            printa[j] = 0;
                        }
                        // reset base
                        for (int j = i + 1; j < NumberOfValues; j++)
                        {
                            printa[j] = 0;
                        }
                    }
                    else
                    {

                    }
                }
                SecondToLast = false;
                // body reverse
                for (int i = 0; i < NumberOfValues; i++)
                {
                    if (i == 1 && NumberOfValues == 2)
                    {
                        break;
                    }

                    printa[i] = 0;


                    if (i == NumberOfValues - 2 && !(NumberOfValues == 2))
                    {
                        SecondToLast = true;
                    }
                    else
                    {
                        Console.WriteLine(printa.makeString());
                        count++;
                    }

                    if (!SecondToLast)
                    {
                        for (int j = i + 1; j < NumberOfValues; j++)
                        {
                            printa[j] = 0;
                            Console.WriteLine(printa.makeString());
                            count++;
                            printa[j] = 1;
                        }
                        // reset base
                        for (int j = i + 1; j < NumberOfValues; j++)
                        {
                            printa[j] = 1;
                        }
                    }
                    else
                    {

                    }
                }
                Console.WriteLine("\n" + "Number of combinations: " + count + ".\n");
            }



        }
    }
    public static class Extensions
    {
        public static string makeString(this int[] array)
        {
            StringBuilder stringy = new StringBuilder();
            for (int i = 0; i < array.Length; i++)
            {
                string nice = array[i] + " ";
                stringy.Append(nice);
            }
            return stringy.ToString();
        }
    }

}
