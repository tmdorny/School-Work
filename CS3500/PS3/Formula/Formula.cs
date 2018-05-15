// Skeleton written by Joe Zachary for CS 3500, September 2013
// Read the entire skeleton carefully and completely before you
// do anything else!

// Version 1.1 (9/22/13 11:45 a.m.)

// Change log:
//  (Version 1.1) Repaired mistake in GetTokens
//  (Version 1.1) Changed specification of second constructor to
//                clarify description of how validation works


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace SpreadsheetUtilities    //PS3 Tim Dorny u0829896
{      
    /// <summary>
    /// Represents formulas written in standard infix notation using standard precedence
    /// rules.  The allowed symbols are non-negative numbers written using double-precision 
    /// floating-point syntax; variables that consist of a letter or underscore followed by 
    /// zero or more letters, underscores, or digits; parentheses; and the four operator 
    /// symbols +, -, *, and /.  
    /// 
    /// Spaces are significant only insofar that they delimit tokens.  For example, "xy" is
    /// a single variable, "x y" consists of two variables "x" and y; "x23" is a single variable; 
    /// and "x 23" consists of a variable "x" and a number "23".
    /// 
    /// Associated with every formula are two delegates:  a normalizer and a validator.  The
    /// normalizer is used to convert variables into a canonical form, and the validator is used
    /// to add extra restrictions on the validity of a variable (beyond the standard requirement 
    /// that it consist of a letter or underscore followed by zero or more letters, underscores,
    /// or digits.)  Their use is described in detail in the constructor and method comments.
    /// </summary>
    public class Formula
    {
        // Private variable containing the formula in string form.
        private string FormulaString;

        // Private variables containing the normalizer and validator functions.
        private Func<string, string> Normalizer;
        private Func<string, bool> Validator;

        // Private List containing the parsed tokens from the GetTokens method.
        private List<string> FormulaTokens;

        // Private List containing all valid variables within the function.
        private List<string> FormulaVariables;

        // Private variable to keep track of the list index when iterating through foreach loop.
        private int ListIndex;

        // Private StringBuilder used to create string representation of normalized function
        StringBuilder FormulaBuilder;



        /// <summary>
        /// Creates a Formula from a string that consists of an infix expression written as
        /// described in the class comment.  If the expression is syntactically invalid,
        /// throws a FormulaFormatException with an explanatory Message.
        /// 
        /// The associated normalizer is the identity function, and the associated validator
        /// maps every string to true.  
        /// </summary>
        public Formula(String formula) :
            this(formula, s => s, s => true)
        {
            
        }

        /// <summary>
        /// Creates a Formula from a string that consists of an infix expression written as
        /// described in the class comment.  If the expression is syntactically incorrect,
        /// throws a FormulaFormatException with an explanatory Message.
        /// 
        /// The associated normalizer and validator are the second and third parameters,
        /// respectively.  
        /// 
        /// If the formula contains a variable v such that normalize(v) is not a legal variable, 
        /// throws a FormulaFormatException with an explanatory message. 
        /// 
        /// If the formula contains a variable v such that isValid(normalize(v)) is false,
        /// throws a FormulaFormatException with an explanatory message.
        /// 
        /// Suppose that N is a method that converts all the letters in a string to upper case, and
        /// that V is a method that returns true only if a string consists of one letter followed
        /// by one digit.  Then:
        /// 
        /// new Formula("x2+y3", N, V) should succeed
        /// new Formula("x+y3", N, V) should throw an exception, since V(N("x")) is false
        /// new Formula("2x+y3", N, V) should throw an exception, since "2x+y3" is syntactically incorrect.
        /// </summary>
        public Formula(String formula, Func<string, string> normalize, Func<string, bool> isValid)
        {
            FormulaString = formula;
            Normalizer = normalize;
            Validator = isValid;
            
            // Store formula tokens in list to check validity.
            FormulaTokens = GetTokens(FormulaString).ToList();

            // Initialize list to contain all valid variables.
            FormulaVariables = new List<string>();

            // Initialize StringBuilder to contain string representation with normalized variables.
            FormulaBuilder = new StringBuilder();

            // Ensure that the provided formula contains at least one token.
            if (!FormulaTokens.GetEnumerator().MoveNext())
            {
                // If the formula contains no tokens, throw an exception.
                throw new FormulaFormatException("The given formula contained no tokens. Check that the formula has been entered correctly.");
            }

            // Check the the first and last tokens are valid.
            // Variable used for storing the output of TryParse (not used)
            double temp;

            // First token must be a left parenthesis, variable, or number.
            
            if (!(FormulaTokens.First() == "(") && FormulaTokens.First().IsValidVariable() && Double.TryParse(FormulaTokens.First(), out temp))
            {
                // If first token is not valid, throw exception.
                throw new FormulaFormatException("The first token in the given formula is invalid. Ensure that your formula begins correctly.");
            }
            // Last token must be a right parenthesis, variable, or number.
            if (!(FormulaTokens.Last() == ")") && FormulaTokens.Last().IsValidVariable() && Double.TryParse(FormulaTokens.Last(), out temp))
            {
                // If last token is not valid, throw exception.
                throw new FormulaFormatException("The last token in the given formula is invalid. Ensure that your formula ends correctly.");
            }
            
            // Variables to keep track of parenthesis for syntactical checking
            int LeftParenthesis = 0;
            int RightParenthesis = 0;
            // List index tracker for loop.
            ListIndex = 0;

            // Look through each token.
            foreach (string token in FormulaTokens)
            {            
                // Ensure that each token in FormulaTokens is a valid operator/variable/number.
                if (!token.CheckValidToken())
                {
                    throw new FormulaFormatException("Formula contained an invalid token. Check that your formula is syntactically correct.");
                }

                // If token is an operator, ensure that the proceeding token is valid.
                else if (token == "+" || token == "-" || token == "*" || token == "/")
                {
                    ParenthesisFollowingRule();
                }

                //***Parenthesis Syntax Checking***
                // If token is a right or left parenthesis, increment the corresponding variable.
                else if (token == "(")
                {
                    LeftParenthesis++;
                    // Also ensure that the left parenthesis is followed by a correct token. (Number, variable, or left parenthesis)
                    ParenthesisFollowingRule();
                }
                else if (token == ")")
                {
                    RightParenthesis++;
                    // Also ensure that the right parenthesis is followed by a correct token. (operator or right parenthesis)
                    ExtraFollowingRule();
                }               
                
                // ***Variable Handling***
                // If the token is a valid variable, ensure that it meets the specified criteria.
                else if (token.IsValidVariable())
                {
                    // Ensure that when normalized, the variable remains syntactically correct.
                    if (!(Normalizer(token).IsValidVariable()))
                    {
                        // If variable is no longer syntactically correct, throw a FormulaFormatException.
                        throw new FormulaFormatException("Normailzed variable is no longer a valid variable. Ensure that your normalizer is working as expected.");
                    }
                    // Ensure that when normalized, the variable is valid according to the validator.
                    if (!(Validator(Normalizer(token))))
                    {
                        // If variable is not valid according to the validator, throw a FormulaFormatException.
                        throw new FormulaFormatException("Variable failed validation. Check your variables and validator method.");
                    }
                    // Check that the variable is proceeded by a valid token. (Operator or right parenthesis)
                    ExtraFollowingRule();

                    // Add the normalized variable to our FormulaBuilder
                    FormulaBuilder.Append(Normalizer(token));
                    // If variable is valid before and after the normalizer and validator are applied, and doesn't already exist in FormulaVariables,
                    //     add it to the variables list with the normalizer applied.
                    if (!FormulaVariables.Contains(Normalizer(token)))
                    {
                        FormulaVariables.Add(Normalizer(token));
                        // Increment ListIndex and move onto next token.
                        ListIndex++;
                        continue;
                    }                  
                }

                // If token is a number, simply ensure that the proceeding token is valid.
                else if (Double.TryParse(token, out temp))
                {
                    ExtraFollowingRule();
                }

                // If at any point, RightParenthesis is greater than LeftParenthesis, the formula's syntax is incorrect and an exception is thrown.
                if (RightParenthesis > LeftParenthesis)
                {
                    throw new FormulaFormatException("Formula contains incorrect parenthesis usage. Check that all parenthesis pairs have been properly opened.");
                }
                // Add token to FormulaBuilder
                FormulaBuilder.Append(token);

                // Increment ListIndex
                ListIndex++;
            }

            // Check that the total number of right and left parenthesis are equal. If not, throw an exception.
            if (!(RightParenthesis == LeftParenthesis))
            {
                throw new FormulaFormatException("Formula contains incorrect parenthesis usage. Ensure that all parenthesis pairs are properly closed.");
            }
        }


        /// <summary>
        /// Helper method that checks if left parentheses and operators are followed by correct tokens as specified in the PS3 documentation.
        ///     Throws a FormulaFormatException if invalid token is found.
        ///     Uses the private variable ListIndex to check the proceeding token in a list.
        /// </summary>
        private void ParenthesisFollowingRule()
        {
            double temp;
            int NextIndex = ListIndex + 1;
            // If NextIndex is out of bounds, simply return
            if (NextIndex >= FormulaTokens.Count)
            {
                return;
            }
            // Check that the next element is a left parenthesis, variable, or number.
            if (!((FormulaTokens[NextIndex] == "(") || FormulaTokens[NextIndex].IsValidVariable() || Double.TryParse(FormulaTokens[NextIndex], out temp)))
            {
                // If left parentheseis/operator is not followed by a valid token, throw exception.
                throw new FormulaFormatException("Unexpected token proceeding left parenthesis or operator. Ensure that your formula is entered correctly.");
            }
        }

        /// <summary>
        /// Helper method that checks if numbers, variables, and right parenthesis are followed by correct tokens as specified in the PS3 documentation.
        ///     Throws a FormulaFormatException if invalid token is found.
        ///     Uses the private variable ListIndex to check the proceeding token in a list. 
        /// </summary>
        private void ExtraFollowingRule()
        {
            int NextIndex = ListIndex + 1;
            // If NextIndex is out of bounds, simply return
            if (NextIndex >= FormulaTokens.Count)
            {
                return;
            }
            if (!((FormulaTokens[NextIndex] == "+" || FormulaTokens[NextIndex] == "-" || FormulaTokens[NextIndex] == "*" || FormulaTokens[NextIndex] == "/" || FormulaTokens[NextIndex] == ")")))
            {
                // If right parentheseis/number/variable is not followed by a valid token, throw exception.
                throw new FormulaFormatException("Unexpected token proceeding right parenthesis, number, or variable. Ensure that your formula is entered correctly.");
            }
        }


        /// <summary>
        /// Evaluates this Formula, using the lookup delegate to determine the values of
        /// variables.  When a variable symbol v needs to be determined, it should be looked up
        /// via lookup(normalize(v)). (Here, normalize is the normalizer that was passed to 
        /// the constructor.)
        /// 
        /// For example, if L("x") is 2, L("X") is 4, and N is a method that converts all the letters 
        /// in a string to upper case:
        /// 
        /// new Formula("x+7", N, s => true).Evaluate(L) is 11
        /// new Formula("x+7").Evaluate(L) is 9
        /// 
        /// Given a variable symbol as its parameter, lookup returns the variable's value 
        /// (if it has one) or throws an ArgumentException (otherwise).
        /// 
        /// If no undefined variables or divisions by zero are encountered when evaluating 
        /// this Formula, the value is returned.  Otherwise, a FormulaError is returned.  
        /// The Reason property of the FormulaError should have a meaningful explanation.
        ///
        /// This method should never throw an exception.
        /// </summary>
        public object Evaluate(Func<string, double> lookup)
        {
            // Create the stacks used to store operands and numerical values.
            Stack<string> OperatorStack = new Stack<string>();
            Stack<double> ValueStack = new Stack<double>();          

            // Imports the provided tokens from constructor.
            List<string> function = FormulaTokens;

            // Initialize value variables for performing computations.
            // Stores value of current token.
            double TokenValue;
            // Stores value popped from valueStack.
            double StackValue;

            // Iterates through the function tokens.
            foreach (string token in function)
            {
                
                //*****INTEGER TOKEN*****

                // If next token is an integer, store it into TokenValue and proceed.
                if (double.TryParse(token, out TokenValue))
                {
                    // If operator stack is empty, push TokenValue onto stack.
                    if (OperatorStack.Count == 0)
                    {
                        ValueStack.Push(TokenValue);
                        continue;
                    }

                    // If a multiply or divide operator is at the top of operatorStack;
                    else if (OperatorStack.Peek() == "*" || OperatorStack.Peek() == "/")
                    {
                        // Pop value and operator stacks;
                        StackValue = ValueStack.Pop();
                        string operand = OperatorStack.Pop();

                        // Determine whether to multiply or divide;
                        if (operand.Equals("*"))
                        {
                            // Push result back to value stack
                            ValueStack.Push(StackValue * TokenValue);
                        }
                        else if (operand.Equals("/"))
                        {
                            // Return formula error if division by 0 occurs
                            if (TokenValue == 0)
                            {
                                return new FormulaError("Division by 0");
                            }

                            // Push result back to ValueStack.
                            ValueStack.Push(StackValue / TokenValue);
                        }
                    }
                    // If next operator is not * or /, push token onto value stack.
                    else
                    {
                        ValueStack.Push(TokenValue);
                    }
                    continue;
                }

                
                //*****VARIABLE TOKEN*****

                // If token is a variable;
                else if (token.IsValidVariable())
                {
                    // Define variable value based on passed-in delegate function using normalized variable names.
                    try
                    {
                        TokenValue = lookup(Normalizer(token));
                    }
                    catch(Exception)
                    {
                        return new FormulaError("Variable lookup failed.");
                    }

                    // If operator stack is empty, add TokenValue to stack and move on to the next token.
                    if (OperatorStack.Count == 0)
                    {
                        ValueStack.Push(TokenValue);
                        continue;
                    }

                    // If a multiply or divide operator is at the top of OperatorStack;
                    if (OperatorStack.Peek() == "*" || OperatorStack.Peek() == "/")
                    {
                        //pop value and operator stacks
                        StackValue = ValueStack.Pop();
                        string operand = OperatorStack.Pop();

                        // Determine whether to multiply or divide;
                        if (operand.Equals("*"))
                        {
                            // Push result back to value stack.
                            ValueStack.Push(StackValue * TokenValue);
                        }
                        else if (operand.Equals("/"))
                        {
                            // Return formula error if division by 0 occurs.
                            if (TokenValue == 0)
                            {
                                return new FormulaError("Division by zero.");
                            }
                            // Push result back to ValueStack.
                            ValueStack.Push(StackValue / TokenValue);
                        }
                    }
                    // If next operator is not * or /, push token onto ValueStack.
                    else
                    {
                        ValueStack.Push(TokenValue);
                    }
                    continue;
                }

                
                //*****PLUS OR MINUS OPERATOR TOKEN*****

                // If token is plus or minus operator.
                else if (token.Equals("+") || token.Equals("-"))
                {
                    // If OperatorStack is empty, push TokenValue onto stack.
                    if (OperatorStack.Count == 0)
                    {
                        OperatorStack.Push(token);
                        continue;
                    }

                    //if a plus or minus operator is at the top of the stack, we must evaluate that expression first
                    //if +, pop valueStack twice and push the sum of the values back to valueStack
                    if (OperatorStack.Peek().Equals("+"))
                    {
                        //pop operator stack
                        OperatorStack.Pop();

                        //add top 2 values on stack
                        StackValue = ValueStack.Pop();
                        double stackValue2 = ValueStack.Pop();
                        ValueStack.Push(stackValue2 + StackValue);
                    }
                    //if -, pop valueStack twice and push the difference of the values back to valueStack
                    else if (OperatorStack.Peek().Equals("-"))
                    {
                        //pop operator stack
                        OperatorStack.Pop();

                        StackValue = ValueStack.Pop();
                        double stackValue2 = ValueStack.Pop();
                        ValueStack.Push(stackValue2 - StackValue);
                    }

                    //push token onto operatorStack
                    OperatorStack.Push(token);
                    continue;

                }


                //*****MULTIPLY OR DIVIDE TOKEN*****

                // If token is * or /.
                else if (token.Equals("*") || token.Equals("/"))
                {
                    // Simply push the operator onto OperatorStack.
                    OperatorStack.Push(token);
                    continue;
                }


                //*****LEFT PARENTHESIS TOKEN*****

                // If token is a left parenthesis;
                else if (token.Equals("("))
                {
                    // Simply push parenthesis onto OperatorStack.
                    OperatorStack.Push(token);
                    continue;
                }


                //*****RIGHT PARENTHESIS TOKEN*****

                // If token is a right parenthesis;
                else if (token.Equals(")"))
                {                  
                    // If next operator is + or -, pop ValueStack twice, apply the operator, then push the result back to ValueStack.

                    // If next operator is +;
                    if (OperatorStack.Peek().Equals("+"))
                    {
                        // Pop OperatorStack;
                        OperatorStack.Pop();

                        // Find sum of popped values;
                        StackValue = ValueStack.Pop();
                        double StackValue2 = ValueStack.Pop();
                        ValueStack.Push(StackValue2 + StackValue);

                        
                    }

                    // If next operator is -;
                    else if (OperatorStack.Peek().Equals("-"))
                    {
                        // Pop OperatorStack
                        OperatorStack.Pop();

                        // Find the difference of popped values;
                        StackValue = ValueStack.Pop();
                        double stackValue2 = ValueStack.Pop();
                        ValueStack.Push(stackValue2 - StackValue);

                        
                    }

                    // Pop left parenthesis off of the OperatorStack.                      
                    OperatorStack.Pop();

                    // If * or / are now at the top of the operator stack, we must pop and compute those as well

                    // If OperatorStack is empty, continue to next token.
                    if (OperatorStack.Count == 0)
                    {
                        // Continue to next token
                        continue;
                    }

                    // If * operator is at the top of OperatorStack;
                    if (OperatorStack.Peek().Equals("*"))
                    {
                        // Pop operator;
                        OperatorStack.Pop();

                        // Pop ValueStack twice, apply operator, and push result onto ValueStack.
                        StackValue = ValueStack.Pop();
                        double StackValue2 = ValueStack.Pop();
                        ValueStack.Push(StackValue2 * StackValue);

                    }
                    // If / operator is at the top of OperatorStack;
                    else if (OperatorStack.Peek().Equals("/"))
                    {
                        // Pop operator;
                        OperatorStack.Pop();

                        // Pop ValueStack twice, apply operator, and push result onto ValueStack.
                        StackValue = ValueStack.Pop();
                        double stackValue2 = ValueStack.Pop();
                        // Throw exception if dividing by 0
                        if (StackValue == 0)
                        {
                            return new FormulaError("Division by zero.");
                        }
                        ValueStack.Push(stackValue2 / StackValue);
                      
                    }
                    
                    continue;
                }

            }

            // Once all tokens have been processed;

            // If OperatorStack is empty, result should be the single value contained in ValueStack.
            if (OperatorStack.Count == 0)
            {               
                // Return result.
                return ValueStack.Pop();
            }
            // If there is still one operator on the OperatorStack, it should be either a + or - operator,
            else if (OperatorStack.Count == 1)
            {
                // If ValueStack is empty or contains only 1 variable return a formula error.
                if (ValueStack.Count == 0 || ValueStack.Count == 1)
                {
                    return new FormulaError("Invalid syntax.");
                }

                // If remaining operator is +;
                if (OperatorStack.Peek().Equals("+"))
                {

                    // ValueStack must have exactly two values remaining, the sum of which is our result;
                    StackValue = ValueStack.Pop();
                    double stackValue2 = ValueStack.Pop();
                    ValueStack.Push(stackValue2 + StackValue);

                    // Return the result.
                    return ValueStack.Pop();

                }
                // If remaining operator is -;
                else if (OperatorStack.Peek().Equals("-"))
                {
                    // ValueStack must have exactly two values remaining, the difference of which is our result.
                    StackValue = ValueStack.Pop();
                    double stackValue2 = ValueStack.Pop();
                    ValueStack.Push(stackValue2 - StackValue);

                    // Return result.
                    return ValueStack.Pop();
                }
                // Otherwise the remaining operator is invalid and an exception is thrown.
                else
                {
                    return new FormulaError("Unexpected operator remaining.");
                }

            }
            else
            {
                return new FormulaError("R.I.P");
            }
        }

        /// <summary>
        /// Enumerates the normalized versions of all of the variables that occur in this 
        /// formula.  No normalization may appear more than once in the enumeration, even 
        /// if it appears more than once in this Formula.
        /// 
        /// For example, if N is a method that converts all the letters in a string to upper case:
        /// 
        /// new Formula("x+y*z", N, s => true).GetVariables() should enumerate "X", "Y", and "Z"
        /// new Formula("x+X*z", N, s => true).GetVariables() should enumerate "X" and "Z".
        /// new Formula("x+X*z").GetVariables() should enumerate "x", "X", and "z".
        /// </summary>
        public IEnumerable<String> GetVariables()
        {
            return FormulaVariables;
        }

        /// <summary>
        /// Returns a string containing no spaces which, if passed to the Formula
        /// constructor, will produce a Formula f such that this.Equals(f).  All of the
        /// variables in the string should be normalized.
        /// 
        /// For example, if N is a method that converts all the letters in a string to upper case:
        /// 
        /// new Formula("x + y", N, s => true).ToString() should return "X+Y"
        /// new Formula("x + Y").ToString() should return "x+Y"
        /// </summary>
        public override string ToString()
        {
            return FormulaBuilder.ToString();
        }

        /// <summary>
        /// If obj is null or obj is not a Formula, returns false.  Otherwise, reports
        /// whether or not this Formula and obj are equal.
        /// 
        /// Two Formulae are considered equal if they consist of the same tokens in the
        /// same order.  To determine token equality, all tokens are compared as strings 
        /// except for numeric tokens, which are compared as doubles, and variable tokens,
        /// whose normalized forms are compared as strings.
        /// 
        /// For example, if N is a method that converts all the letters in a string to upper case:
        ///  
        /// new Formula("x1+y2", N, s => true).Equals(new Formula("X1  +  Y2")) is true
        /// new Formula("x1+y2").Equals(new Formula("X1+Y2")) is false
        /// new Formula("x1+y2").Equals(new Formula("y2+x1")) is false
        /// new Formula("2.0 + x7").Equals(new Formula("2.000 + x7")) is true
        /// </summary>
        public override bool Equals(object obj)
        {
            // If obj is null, return false.
            if (obj == null)
            {
                return false;
            }
            // If obj cannot be cast to Formula, return false.
            Formula Formula2 = obj as Formula;
            if ((System.Object)Formula2 == null)
            {
                return false;
            }
            // Retrieve each Formula object's tokens.
            List<string> Formula1Tokens = this.GetFormulaTokens();
            List<string> Formula2Tokens = Formula2.GetFormulaTokens();
            // If Formulas contain a non-equal amount of variables, then they are not equal.
            if (!(Formula1Tokens.Count == Formula2Tokens.Count))
            {
                return false;
            }
            // Compare the variables from each formula object.
            List<string> Formula1Variables = this.GetFormulaVariables();
            List<string> Formula2Variables = Formula2.GetFormulaVariables();

            // Check that formulas have same number of variables
            if (!(Formula1Variables.Count == Formula2Variables.Count))
            {
                return false;
            }
            // Check that all variables are equal.
            for (int i = 0; i < Formula1Variables.Count; i++)
            {
                if (!(Formula1Variables[i] == Formula2Variables[i]))
                {
                    return false;
                }
            }

            // Variables to contain parsed doubles from tokens for comparison.
            double Formula1Double = 0;
            double Formula2Double = 0;

            for (int i = 0; i < Formula1Tokens.Count; i++)
            {
                // If current token is a double, attempt to parse the corresponding token from each list.
                if (Double.TryParse(Formula1Tokens[i], out Formula1Double))
                {
                    // If the other object's corresponding token is not also a parsable double, return false.
                    if (!Double.TryParse(Formula2Tokens[i], out Formula2Double))
                    {
                        return false;
                    }
                    // If the parsed doubles are not equal, return false.
                    else if (!(Formula2Double == Formula1Double))
                    {
                        return false;
                    }
                }
                // Skip over any variables. (They have already been compared)
                if (Formula1Tokens[i].IsValidVariable())
                {
                    continue;
                }


                // The rest of the tokens should be normalized variables and operators, so we simply compare them.
                else if (!(Formula1Tokens[i] == Formula2Tokens[i]))
                {
                    // If tokens are not equal, return false.
                    return false;
                }
            }
            // If the for loop completes, the Formula objects are equal by the provided definition.
            return true;
        }

        /// <summary>
        /// Returns a list containing the tokens that make up the given formula object.
        /// </summary>
        /// <returns></returns>
        public List<string> GetFormulaTokens()
        {
            return FormulaTokens;
        }

        /// <summary>
        /// Returns a list containing all of the normalized variables in the function.
        /// </summary>
        /// <returns></returns>
        public List<String> GetFormulaVariables()
        {
            return FormulaVariables;
        }
        /// <summary>
        /// Reports whether f1 == f2, using the notion of equality from the Equals method.
        /// Note that if both f1 and f2 are null, this method should return true.  If one is
        /// null and one is not, this method should return false.
        /// </summary>
        public static bool operator ==(Formula f1, Formula f2)
        {
            // If f1 and f2 are null, return true.
            if (Object.ReferenceEquals(f1, null) && Object.ReferenceEquals(f2, null))
            {
                return true;
            }
            // If only one of the two is null, return false.
            else if (Object.ReferenceEquals(f1, null) || Object.ReferenceEquals(f2, null))
            {
                return false;
            }
            // Otherwise simply return the result of Formula's Equals method.
            return f1.Equals(f2);
        }

        /// <summary>
        /// Reports whether f1 != f2, using the notion of equality from the Equals method.
        /// Note that if both f1 and f2 are null, this method should return false.  If one is
        /// null and one is not, this method should return true.
        /// </summary>
        public static bool operator !=(Formula f1, Formula f2)
        {
            // If f1 and f2 are null, return false.
            if (Object.ReferenceEquals(f1, null) && Object.ReferenceEquals(f2, null))
            {
                return false;
            }
            // If only one of the two is null, return false.
            else if (Object.ReferenceEquals(f1, null) || Object.ReferenceEquals(f2, null))
            {
                return true;
            }
            // Otherwise simply return the opposite result of Formula's Equals method.
            return !f1.Equals(f2);
        }

        /// <summary>
        /// Returns a hash code for this Formula.  If f1.Equals(f2), then it must be the
        /// case that f1.GetHashCode() == f2.GetHashCode().  Ideally, the probability that two 
        /// randomly-generated unequal Formulae have the same hash code should be extremely small.
        /// </summary>
        public override int GetHashCode()
        {
            // Stores string representation of formula into HashString
            string HashString = this.ToString();
            // Prime number to be used in calculations
            int prime = 31;
            // Int to store the eventual value of the hash code.
            int HashCode = 0;
            for (int i = 0; i < HashString.Length; i++)
            {
                // Multiply each character by the prime number to the power of i plus i.
                HashCode += HashString[i] * (prime ^ i) + i;
            }
            // Return the resulting hash code.
            return HashCode;
        }

        /// <summary>
        /// Given an expression, enumerates the tokens that compose it.  Tokens are left paren;
        /// right paren; one of the four operator symbols; a string consisting of a letter or underscore
        /// followed by zero or more letters, digits, or underscores; a double literal; and anything that doesn't
        /// match one of those patterns.  There are no empty tokens, and no token contains white space.
        /// </summary>
        private static IEnumerable<string> GetTokens(String formula)
        {
            // Patterns for individual tokens
            String lpPattern = @"\(";
            String rpPattern = @"\)";
            String opPattern = @"[\+\-*/]";
            String varPattern = @"[a-zA-Z_](?: [a-zA-Z_]|\d)*";
            String doublePattern = @"(?: \d+\.\d* | \d*\.\d+ | \d+ ) (?: [eE][\+-]?\d+)?";
            String spacePattern = @"\s+";

            // Overall pattern
            String pattern = String.Format("({0}) | ({1}) | ({2}) | ({3}) | ({4}) | ({5})",
                                            lpPattern, rpPattern, opPattern, varPattern, doublePattern, spacePattern);

            // Enumerate matching tokens that don't consist solely of white space.
            foreach (String s in Regex.Split(formula, pattern, RegexOptions.IgnorePatternWhitespace))
            {
                if (!Regex.IsMatch(s, @"^\s*$", RegexOptions.Singleline))
                {
                    yield return s;
                }
            }

        }
    }
    /// <summary>
    /// Class containing extensions related to the Formula class.
    /// </summary>
    public static class FormulaExtensions
    {
        /// <summary>
        /// Checks if a variable is valid under the default conditions. 
        ///     (Begins with letter or underscore followed by any number of letters/underscores/digits).
        /// </summary>
        /// <param name="token">Variable to be checked.</param>
        /// <returns>True if the variable is valid, false otherwise.</returns>
        public static bool IsValidVariable(this String token)
        {
            if (!(Char.IsLetter(token[0]) || token[0] == '_'))
            {
                return false;
            }
            for (int i = 0; i < token.Length; i++)
            {
                if ((!(Char.IsLetterOrDigit(token[i]))) && token[i] != '_')
                {
                    return false;
                }
            }
            return true;

        }
        /// <summary>
        /// Checks if a given token is valid for a Formula object.
        ///     [Valid characters: '+' '-' '*' '/' '(' ')' '_' variables and digits]
        /// </summary>
        /// <returns>True if token is valid, false if not.</returns>
        public static bool CheckValidToken(this String token)
        {
            bool test = token == "+";
            double temp;

            if (!(token == "+" || token == "-" || token == "*" || token == "/" || token == "(" || token == ")" || token == "_"))
            {
                if (!(token.IsValidVariable() || Double.TryParse(token, out temp)))
                {
                    return false;
                }
            }
            return true;
        }
    }

    /// <summary>
    /// Used to report syntactic errors in the argument to the Formula constructor.
    /// </summary>
    public class FormulaFormatException : Exception
    {
        /// <summary>
        /// Constructs a FormulaFormatException containing the explanatory message.
        /// </summary>
        public FormulaFormatException(String message)
            : base(message)
        {
        }
    }

    /// <summary>
    /// Used as a possible return value of the Formula.Evaluate method.
    /// </summary>
    public struct FormulaError
    {
        /// <summary>
        /// Constructs a FormulaError containing the explanatory reason.
        /// </summary>
        /// <param name="reason"></param>
        public FormulaError(String reason)
            : this()
        {
            Reason = reason;
        }

        /// <summary>
        ///  The reason why this FormulaError was created.
        /// </summary>
        public string Reason { get; private set; }
    }
}

