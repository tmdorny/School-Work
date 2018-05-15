using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FormulaEvaluator //Created by Tim Dorny || u0829896
{
    /// <summary>
    /// This class handles functions in the form of strings and solves them. Variable handling can be added through a delegate function.
    /// </summary>
    public static class Evaluator
    {
        /// <summary>
        /// Function used to resolve variable values
        /// </summary>
        /// <param name="v">String variable to be resolved</param>
        /// <returns>value of variable</returns>
        public delegate int Lookup(String v);

        /// <summary>
        /// Evaluates a string function ^>^
        /// </summary>
        /// <param name="exp">String containing the function to be evaluated</param>
        /// <param name="variableEvaluator">Function that resolves variable values</param>
        /// <returns>Solution to the function</returns>
        public static int Evaluate(String exp, Lookup variableEvaluator)
        {
            //create the stacks used to store operands and numerical values
            Stack<string> operatorStack = new Stack<string>();
            Stack<double> valueStack = new Stack<double>();

            //remove whitespace from string
            exp = exp.Replace(" ", "");

            //converts string function into tokens to be analyzed
            string[] function = Regex.Split(exp, "(\\()|(\\))|(-)|(\\+)|(\\*)|(/)");

            //initialize value variables for performing computations
            //stores value of current token
            double tokenValue;
            //stores value popped from valueStack
            double stackValue;

            //loops through function array
            foreach (string token in function)
            {
                //if token is an empty string, we ignore it and continue to the next token
                if (token.Equals(""))
                {
                    continue;
                }

                //if next token is an integer, store it into value1 and proceed
                if (double.TryParse(token, out tokenValue))
                {
                    //if operator stack is empty, push tokenValue onto stack
                    if (operatorStack.Count == 0)
                    {
                        valueStack.Push(tokenValue);
                        continue;
                    }

                    //if a multiply or divide operator is at the top of operatorStack,
                    else if (operatorStack.Peek() == "*" || operatorStack.Peek() == "/")
                    {
                        //pop value and operator stacks
                        stackValue = valueStack.Pop();
                        string operand = operatorStack.Pop();

                        //determine whether to multiply or divide
                        if (operand.Equals("*"))
                        {
                            //push result back to value stack
                            valueStack.Push(stackValue * tokenValue);
                        }
                        else if (operand.Equals("/"))
                        {
                            // Throw exception if division by 0 occurs
                            if (tokenValue == 0)
                            {
                                throw new ArgumentException("Division by zero.");
                            }

                            //push result back to value stack
                            valueStack.Push(stackValue / tokenValue);
                        }
                    }
                    //if next operator is not * or /, push token onto value stack
                    else
                    {
                        valueStack.Push(tokenValue);
                    }
                    continue;
                }

                //if token is a variable
                else if (Evaluator.isVariable(token))
                {
                    //define variable value based on passed-in function
                    tokenValue = variableEvaluator(token);

                    //if operator stack is empty, add value to stack and move on
                    if (operatorStack.Count == 0)
                    {
                        valueStack.Push(tokenValue);
                        continue;
                    }

                    //if a multiply or divide operator is at the top of operatorStack,
                    if (operatorStack.Peek() == "*" || operatorStack.Peek() == "/")
                    {
                        //pop value and operator stacks
                        stackValue = valueStack.Pop();
                        string operand = operatorStack.Pop();

                        //determine whether to multiply or divide
                        if (operand.Equals("*"))
                        {
                            //push result back to value stack
                            valueStack.Push(stackValue * tokenValue);
                        }
                        else if (operand.Equals("/"))
                        {
                            // Throw exception if division by 0 occurs
                            if (tokenValue == 0)
                            {
                                throw new ArgumentException("Division by zero.");
                            }
                            // Push result back to value stack
                            valueStack.Push(stackValue / tokenValue);
                        }
                    }
                    //if next operator is not * or /, push token onto value stack
                    else
                    {
                        valueStack.Push(tokenValue);
                    }
                    continue;
                }



                //if token is plus or minus sign
                else if (token.Equals("+") || token.Equals("-"))
                {
                    //if operator stack is empty, push tokenValue onto stack
                    if (operatorStack.Count == 0)
                    {
                        operatorStack.Push(token);
                        continue;
                    }

                    //if a plus or minus operator is at the top of the stack, we must evaluate that expression first
                    //if +, pop valueStack twice and push the sum of the values back to valueStack
                    if (operatorStack.Peek().Equals("+"))
                    {
                        //pop operator stack
                        operatorStack.Pop();
                        
                        //add top 2 values on stack
                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        valueStack.Push(stackValue2 + stackValue);
                    }
                    //if -, pop valueStack twice and push the difference of the values back to valueStack
                    else if (operatorStack.Peek().Equals("-"))
                    {
                        //pop operator stack
                        operatorStack.Pop();

                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        valueStack.Push(stackValue2 - stackValue);
                    }

                    //push token onto operatorStack
                    operatorStack.Push(token);
                    continue;

                }
                //if token is * or /
                else if (token.Equals("*") || token.Equals("/"))
                {
                    //simply push the operator onto the stack
                    operatorStack.Push(token);
                    continue;
                }
                //if token is a left parenthesis
                else if (token.Equals("("))
                {
                    //simply push parenthesis onto stack
                    operatorStack.Push(token);
                    continue;
                }
                //if token is a right parenthesis
                else if (token.Equals(")"))
                {
                    // If operator stack is empty, throw exception.
                    if (operatorStack.Count == 0)
                    {
                        throw new ArgumentException("No open parenthesis found before closing parenthesis.");
                    }
                    
                    //if next operator is + or -, pop valueStack twice, apply the operator, then push the result back to valueStack

                    //if +
                    if (operatorStack.Peek().Equals("+"))
                    {
                        //pop operator
                        operatorStack.Pop();
                        
                        //find sum of popped values
                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        valueStack.Push(stackValue2 + stackValue);

                        //ensure that the next operator is a left parentesis and pop it
                        try
                        {
                            operatorStack.Peek();
                            
                        }
                        catch (InvalidOperationException)
                        {
                            // If operatorStack is empty, throw argument exception.
                            throw new ArgumentException("Invalid closing parenthesis found.");
                        }
                        //throw exception if expected symbol is not found
                        if (!operatorStack.Peek().Equals("("))
                        {
                            throw new ArgumentException("Left parenthesis not found where expected.");
                        }
                        else
                        {
                            operatorStack.Pop();
                        }
                    }
                    //if -
                    else if (operatorStack.Peek().Equals("-"))
                    {
                        //pop operator
                        operatorStack.Pop();
                        
                        //find the difference of popped values
                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        valueStack.Push(stackValue2 - stackValue);

                        //ensure that the next operator is a left parentesis and pop it
                        if (!operatorStack.Pop().Equals("("))
                        {
                            //throw exception if expected symbol is not found
                            throw new ArgumentException("Left parenthesis not found when expected.");
                        }
                    }
                    //if * or / are now at the top of the operator stack, we must pop and compute those as well

                    //first, check if operatorStack is empty to avoid exception
                    if (operatorStack.Count == 0)
                    {
                        //continue to next token
                        continue;
                    }

                    //if *
                    if (operatorStack.Peek().Equals("*"))
                    {
                        //pop operator
                        operatorStack.Pop();

                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        valueStack.Push(stackValue2 * stackValue);
                    }
                    //if /
                    else if (operatorStack.Peek().Equals("/"))
                    {
                        //pop operator
                        operatorStack.Pop();

                        stackValue = valueStack.Pop();
                        double stackValue2 = valueStack.Pop();
                        // Throw exception if dividing by 0
                        if (stackValue == 0)
                        {
                            throw new ArgumentException("Division by 0");
                        }
                        valueStack.Push(stackValue2 / stackValue);
                    }

                    continue;
                }

                //if token has not been processed by this point, it is invalid and an exception is thrown
                throw new ArgumentException("Your function contains an invalid token.");

            }

            //once all tokens have been processed

            //if operatorStack is empty, result should be the single value contained in valueStack
            if (operatorStack.Count == 0)
            {
                // If ValueStack is empty, throw exception.
                if (valueStack.Count == 0)
                {
                    throw new ArgumentException("No result found.");
                }
                
                //parse double into int and return result

                return (int)valueStack.Pop();
            }
            //if there is still one operator on the stack, it should be either a + or -
            else if (operatorStack.Count == 1)
            {
                // If ValueStack is empty or contains only 1 variable throw exception.
                if (valueStack.Count == 0 || valueStack.Count == 1)
                {
                    throw new ArgumentException("Unexpected operator remaining.");
                }

                //if +
                if (operatorStack.Peek().Equals("+"))
                {
                    
                    //valueStack must have exactly two values remaining, the sum of which is our result
                    stackValue = valueStack.Pop();
                    double stackValue2 = valueStack.Pop();
                    valueStack.Push(stackValue2 + stackValue);

                    //parse double into int and return result
                    return (int)valueStack.Pop();

                }
                //if -
                else if (operatorStack.Peek().Equals("-"))
                {
                    //valueStack must have exactly two values remaining, the difference of which is our result
                    stackValue = valueStack.Pop();
                    double stackValue2 = valueStack.Pop();
                    valueStack.Push(stackValue2 - stackValue);

                    //parse double into int and return result
                    return (int)valueStack.Pop();
                }
                // Otherwise the remaining operator is invalid and an exception is thrown.
                else
                {
                    throw new ArgumentException("Unexpected operator remaining.");
                }

            }

            //if this point is reached something went terribly wrong with the final calculation
            throw new ArgumentException("Something went terribly wrong");
        }


        /// <summary>
        /// Method to determine whether or not a given token is a valid variable (x amount of characters followed by x amount of digits) or not
        /// </summary>
        /// <param name="token">string to check variable validity</param>
        /// <returns>boolean stating whether or not the given string is a valid variable</returns>
        private static Boolean isVariable(string token)
        {
            int i = 0;

            //boolean to determine when a character is found at the beginning of the token
            Boolean firstChar = false;

            while (i <= token.Length - 1)
            {
                //if all previous characters have been valid letters, and the next character is a digit, check if all remaining characters are also digits
                if (Char.IsDigit(token[i]) && firstChar == true)
                {
                    while (i <= token.Length - 1)
                    {
                        //if a character is a non-digit beyond this point, the token is not a valid variable
                        if (!Char.IsDigit(token[i]))
                        {
                            return false;
                        }
                        i++;
                    }

                    //if the remaining characters were found to all be digits, the variable is valid and we return true
                    return true;
                }

                //if first character is not a valid letter or any subsequent characters are not valid letters or digits
                else if (!Char.IsLetter(token[i]))
                {
                    return false;
                }

                //set to true if first character of string is a valid letter
                firstChar = true;

                i++;

            }

            //making it through the initial while loop means that the string was entirely valid characters which do not constitute a valid variable
            return false;
        }


    }
}
