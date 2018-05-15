using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using SpreadsheetUtilities;
using System.Collections.Generic;
using System.Linq;

namespace FormulaTester
{
    /// <summary>
    /// Tests various features of the Formula Class. Written by Tim Dorny u0829896
    /// </summary>
    [TestClass]
    public class FormulaTester
    {
        // *******Delegate methods for normalizer/validator.*******

        /// <summary>
        /// Simple normalizer; converts string to uppercase.
        /// </summary>
        /// <param name="formula"></param>
        /// <returns></returns>
        private string GoodNormalizer1(String formula)
        {
            return formula.ToUpper();
        }

        /// <summary>
        /// Bad normalizer; returns an invalid variable.
        /// </summary>
        /// <param name="formula"></param>
        /// <returns></returns>
        private string BadNormalizer1(String formula)
        {
            return "b@d_v@ri@ble";
        }

        /// <summary>
        /// Bad normalizer; adds invalid variable syntax to the beginning of variable.
        /// </summary>
        /// <param name="formula"></param>
        /// <returns></returns>
        private string BadNormalizer2(String formula)
        {
            return formula.Insert(0, "()()()()");
        }

        /// <summary>
        /// Variable is only valid if it contains "oppa"
        /// </summary>
        /// <param name="variable"></param>
        /// <returns></returns>
        private bool Validator1(String variable)
        {
            if (!variable.Contains("oppa"))
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Variable is invalid if i contains "a" or "b"
        /// </summary>
        /// <param name="variable"></param>
        /// <returns></returns>
        private bool Validator2(String variable)
        {
            if (variable.Contains("a") || variable.Contains("b"))
            {
                return false;
            }
            return true;
        }


        // ****************************************PUBLIC TESTS****************************************
        /// <summary>
        /// Tests normalizing variables with a simple ToUpper normalizer.
        /// </summary>
        [TestMethod]
        public void PublicTestSimpleNormalizer()
        {
            Formula f = new Formula("labba + dabba + nice + benny + 5", GoodNormalizer1, s => true);
            IEnumerator<string> variables = f.GetVariables().GetEnumerator();

            Assert.IsTrue(variables.MoveNext());
            Assert.IsTrue(variables.Current == "LABBA");
            Assert.IsTrue(variables.MoveNext());
            Assert.IsTrue(variables.Current == "DABBA");
            Assert.IsTrue(variables.MoveNext());
            Assert.IsTrue(variables.Current == "NICE");
            Assert.IsTrue(variables.MoveNext());
            Assert.IsTrue(variables.Current == "BENNY");
            Assert.IsFalse(variables.MoveNext());
        }

        /// <summary>
        /// Tests that an exception is thrown when no tokens are parsed from the given formula.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "The given formula contained no tokens. Check that the formula has been entered correctly.")]
        public void PublicTestConstructorNoTokensException()
        {
            Formula f = new Formula("                       ", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the first token in a formula is invalid. (Right parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "The first token in the given formula is invalid. Ensure that your formula begins correctly.")]
        public void PublicTestConstructorBadFirstTokenException()
        {
            Formula f = new Formula(") 3 + 2", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the last token in a formula is invalid. (Left parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "The last token in the given formula is invalid. Ensure that your formula ends correctly.")]
        public void PublicTestConstructorBadLastTokenException()
        {
            Formula f = new Formula("3 + 2 (", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when a given token is invalid. This test tests the invalid variable ")greenman"
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Formula contained an invalid token. Check that your formula is syntactically correct.")]
        public void PublicTestConstructorBadTokenException1()
        {
            Formula f = new Formula("1 + 1 - 1 * 1 / 1 + )greenman", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when a given token is invalid. This test tests the invalid variable "123JOHNCENA"
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Formula contained an invalid token. Check that your formula is syntactically correct.")]
        public void PublicTestConstructorBadTokenException2()
        {
            Formula f = new Formula("1 + 1 - 1 * 1 + 123JOHNCENA / 1", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when a given token is invalid. This test tests an invalid variable "abc12@#$%$#@$%@#%"
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Formula contained an invalid token. Check that your formula is syntactically correct.")]
        public void PublicTestConstructorBadTokenException3()
        {
            Formula f = new Formula("1 + 1 + abc12@#$%$#@$%@#% - 1 * 1 / 1", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the parenthesis following rule is broken. Tests with left parenthesis.
        ///     (token immediately following left parenthesis or operator must be a number, variable, or left parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Unexpected token proceeding left parenthesis or operator. Ensure that your formula is entered correctly.")]
        public void PublicTestConstructorParenthesisFollowingRule1()
        {
            Formula f = new Formula("1 + 2 + ( - 5) * 5", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the parenthesis following rule is broken. Tests with operator.
        ///     (token immediately following left parenthesis or operator must be a number, variable, or left parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Unexpected token proceeding left parenthesis or operator. Ensure that your formula is entered correctly.")]
        public void PublicTestConstructorParenthesisFollowingRule2()
        {
            Formula f = new Formula("1 + + + + + + + 1", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the extra following rule is broken. Tests with right parenthesis.
        ///     (token immediately following right parenthesis, variable, or number must be an operator or closing parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Unexpected token proceeding right parenthesis, number, or variable.Ensure that your formula is entered correctly.")]
        public void PublicTestConstructorExtraFollowingRule1()
        {
            Formula f = new Formula("2 + (3 - 1) 6", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the extra following rule is broken. Tests with variable.
        ///     (token immediately following right parenthesis, variable, or number must be an operator or closing parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Unexpected token proceeding right parenthesis, number, or variable.Ensure that your formula is entered correctly.")]
        public void PublicTestConstructorExtraFollowingRule2()
        {
            Formula f = new Formula("2 + X2 6 + (2 - 2)", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the extra following rule is broken. Tests with number.
        ///     (token immediately following right parenthesis, variable, or number must be an operator or closing parenthesis)
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Unexpected token proceeding right parenthesis, number, or variable.Ensure that your formula is entered correctly.")]
        public void PublicTestConstructorExtraFollowingRule3()
        {
            Formula f = new Formula("2 + 9 9 + (2 - 2)", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the number of right parenthesis exceeds the number of left parenthesis.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Formula contains incorrect parenthesis usage. Check that all parenthesis pairs have been properly opened.")]
        public void PublicTestConstructorImbalancedParenthesis1()
        {
            Formula f = new Formula("1 + (1 + 1) ) +-1", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when the number of left parenthesis exceeds the number of right parenthesis.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Formula contains incorrect parenthesis usage. Ensure that all parenthesis pairs are properly closed.")]
        public void PublicTestConstructorImbalancedParenthesis2()
        {
            Formula f = new Formula("2 + ((( 3 * 4 )) - 1", s => s, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when normalization results in an invalid variable.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Normailzed variable is no longer a valid variable.")]
        public void PublicTestConstructorNormalizationException1()
        {
            Formula f = new Formula("2 + _a + 2", BadNormalizer1, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when normalization results in an invalid variable.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Normailzed variable is no longer a valid variable.")]
        public void PublicTestConstructorNormalizationException2()
        {
            Formula f = new Formula("2 + _a + b + _c + dad22", BadNormalizer2, s => true);
        }

        /// <summary>
        /// Tests that an exception is thrown when a variable fails the passed-in validator.
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException), "Variable failed validation.")]
        public void PublicTestConstructorValidationException()
        {
            Formula f = new Formula("2 + _abshaqha + 2", s => s, Validator1);
        }

        /// <summary>
        /// Tests that no exceptions are thrown when a valid normalizer and validator are passed in.
        /// </summary>
        [TestMethod]
        public void PublicTestConstructorSuccessfulInitialization()
        {
            Formula f = new Formula("5 + a - 2 * b - ab / ba", GoodNormalizer1, Validator2);
            List<string> variables = f.GetVariables().ToList();
            Assert.IsTrue(variables[0] == "A");
            Assert.IsTrue(variables[1] == "B");
            Assert.IsTrue(variables[2] == "AB");
            Assert.IsTrue(variables[3] == "BA");
        }

        //**********FORMULA EVALUATION TESTING*********

        /// <summary>
        /// Tests evaluating a simple formula to ensure basic code is running smoothly.
        /// </summary>
        [TestMethod]
        public void PublicTestSimpleEvaluation1()
        {
            Formula f = new Formula("2 * (5 + 5)", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == 20);
        }

        /// <summary>
        /// Tests evaluating a simple formula to ensure basic code is running smoothly.
        /// </summary>
        [TestMethod]
        public void PublicTestSimpleEvaluation2()
        {
            Formula f = new Formula("5 + 10 / 2", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == 10);
        }

        /// <summary>
        /// Tests evaluating a simple formula to ensure basic code is running smoothly.
        /// </summary>
        [TestMethod]
        public void PublicTestSimpleEvaluation3()
        {
            Formula f = new Formula("1 + 2 - 1 * (2 + 2)", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == -1);
        }
        /// <summary>
        /// Lookup basic variables
        /// </summary>
        /// <param name="variable"></param>
        /// <returns></returns>
        public double BasicLookup(String variable)
        {
            if (variable == "X")
            {
                return 7;
            }
            else if (variable == "Y")
            {
                return 3;
            }
            else if (variable == "Z")
            {
                return 17;
            }
            else
            {
                throw new ArgumentException();
            }
        }
        private double BasicLookup2(String variable)
        {
            if (variable == "A")
            {
                return 5;
            }
            if (variable == "B")
            {
                return 10;
            }
            else
            {
                throw new ArgumentException();
            }
        }

        /// <summary>
        /// Tests evaluating a simple formula (with variables) to ensure basic code is running smoothly.
        /// </summary>
        [TestMethod]
        public void PublicTestSimpleVariableEvaluation1()
        {
            Formula f = new Formula("X * Y - Z", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(BasicLookup));
            Assert.IsTrue(result == 4);
        }

        /// <summary>
        /// Tests proper handling of failed variable lookup.
        /// </summary>
        [TestMethod]
        public void PublicTestVariableLookupFailure()
        {
            Formula f = new Formula("((X * Y) - ZOOANIMALS)", s => s, s => true);
            Object result = f.Evaluate(BasicLookup);
            Object expected = new FormulaError("Variable lookup failed.");
            Assert.AreEqual(expected, result);
        }

        /// <summary>
        /// Tests proper handling of division by 0.
        /// </summary>
        [TestMethod]
        public void PublicTestDivisionByZero()
        {
            Formula f = new Formula("(1 + 2) / (3 - 3)", s => s, s => true);
            Object result = f.Evaluate(BasicLookup);
            Object expected = new FormulaError("Division by zero.");
            Assert.AreEqual(expected, result);
        }

        /// <summary>
        /// Tests evaluating a formula to ensure accuracy. This case tests using a high number of parenthesis.
        /// </summary>
        [TestMethod]
        public void PublicTestEvaluationManyParenthesis()
        {
            Formula f = new Formula("((1 + 2) * (3 + 4) - (5 + 6)) / (2 + 3)", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == 2);
        }

        /// <summary>
        /// Tests evaluating a formula to ensure accuracy. This case tests proper order of operations usage.
        /// </summary>
        [TestMethod]
        public void PublicTestEvaluationOrderOfOperations()
        {
            Formula f = new Formula("4 + 5 * 4 - 8 / 2", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == 20);
        }

        /// <summary>
        /// Tests evaluating a formula to ensure accuracy. This case tests that doubles are handled properly.
        /// </summary>
        [TestMethod]
        public void PublicTestEvaluationDoubleSyntax()
        {
            Formula f = new Formula("(5e3 + 5) / 10.0 + 1.7", s => s, s => true);
            double result = Convert.ToDouble(f.Evaluate(null));
            Assert.IsTrue(result == 502.2);
        }

        /// <summary>
        /// Tests that formula is correctly evaluated when given a normalizer and validator. Heavy Variables.
        /// </summary>
        [TestMethod]
        public void PublicTestConstructorEvaluation1()
        {
            Formula f = new Formula("(2 + a) * b - (b * 3) / a", GoodNormalizer1, Validator2);
            double result = Convert.ToDouble(f.Evaluate(BasicLookup2));
            Assert.IsTrue(result == 64);
        }

        /// <summary>
        /// Tests that formula is correctly evaluated when given a normalizer and validator. Single variable and operator use.
        /// </summary>
        [TestMethod]
        public void PublicTestConstructorEvaluation2()
        {
            Formula f = new Formula("a * a * a * a * a", GoodNormalizer1, Validator2);
            double result = Convert.ToDouble(f.Evaluate(BasicLookup2));
            Assert.IsTrue(result == 3125);
        }

        /// <summary>
        /// Tests that formula is correctly evaluated when given a normalizer and validator. Stacked parenthesis.
        /// </summary>
        [TestMethod]
        public void PublicTestConstructorEvaluation3()
        {
            Formula f = new Formula("(((((1 + 1) * 2) - 3) * 2) / 2)", GoodNormalizer1, Validator2);
            double result = Convert.ToDouble(f.Evaluate(BasicLookup2));
            Assert.IsTrue(result == 1);
        }

        /// <summary>
        /// Tests that the class returns the correct normalized variables (skipping duplicates) with its GetVariables method. (GetFormulaVariables is used to obtain variables in list form)
        /// </summary>
        [TestMethod]
        public void PublicTestGetVariables()
        {
            Formula f = new Formula("a + b + c + b + a + d + e +f", GoodNormalizer1, Validator2);
            List<string> variables = f.GetFormulaVariables();
            Assert.IsTrue(variables[0] == "A");
            Assert.IsTrue(variables[1] == "B");
            Assert.IsTrue(variables[2] == "C");
            Assert.IsTrue(variables[3] == "D");
            Assert.IsTrue(variables[4] == "E");
            Assert.IsTrue(variables[5] == "F");
        }

        /// <summary>
        /// Tests that the toString method works correctly. (variables)
        /// </summary>
        [TestMethod]
        public void PublicTestToString1()
        {
            Formula f = new Formula("(a + b - c * d / e)", GoodNormalizer1, Validator2);
            Assert.IsTrue(f.ToString() == "(A+B-C*D/E)");
        }

        /// <summary>
        /// Tests that the toString method works correctly. (no variables)
        /// </summary>
        [TestMethod]
        public void PublicTestToString2()
        {
            Formula f = new Formula("(1 + 2)   - 5 * ( 6 + 9)", GoodNormalizer1, Validator2);
            Assert.IsTrue(f.ToString() == "(1+2)-5*(6+9)");
        }

        /// <summary>
        /// Tests that the equals method properly determines equality bewtween two similar formulas. (no normalizer/validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsSimpleSuccess()
        {
            Formula f = new Formula("( 1 + C ) - 3 * ( A + 5 )", s => s, s => true);
            Formula f2 = new Formula("(     1   +  C   ) -    3 *   ( A  +  5    )", s => s, s => true);
            Assert.IsTrue(f.Equals(f2));
        }

        /// <summary>
        /// Tests that the equals method properly determines equality bewtween two similar formulas. (no normalizer/validator)
        /// </summary>
        [TestMethod]
        public void AAAPublicTestEqualsSimpleSuccess1()
        {
            Formula f = new Formula("(1 + 1) * 42", s => s, s => true);
            Formula f2 = new Formula("(1 + 1) * 42", s => s, s => true);
            Assert.IsTrue(f.Equals(f2));
        }

        /// <summary>
        /// Tests that the equals method properly determines inequality bewtween two similar formulas. (no normalizer/validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsSimpleFailure()
        {
            Formula f = new Formula("( 1 + C ) - 3 * ( A + 5 )", s => s, s => true);
            Formula f2 = new Formula("(     2   +  D   ) -    3 *   ( A  +  6    )", s => s, s => true);
            Assert.IsFalse(f.Equals(f2));
        }

        /// <summary>
        /// Tests that the equals method properly determines equality bewtween two similar formulas. (using normalizer/ no validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsNormalizerSuccess()
        {
            Formula f = new Formula("a + b + c + b + a + d + e + f", GoodNormalizer1, s => true);
            Formula f2 = new Formula("A + B + C + B + A + D + E + F", s => s, s => true);
            Assert.IsTrue(f.Equals(f2));
        }

        /// <summary>
        /// Tests that the equals method properly determines inequality bewtween two similar formulas. (using normalizer/ no validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsNormalizerFailure()
        {
            Formula f = new Formula("a + b + c + b + a + d + e + f", GoodNormalizer1, s => true);
            Formula f2 = new Formula("a + b + c + b + a + d + e + f", s => s, s => true);
            Assert.IsFalse(f.Equals(f2));
        }

        /// <summary>
        /// Tests that the hashcodes of two equal formulas are equal.
        /// </summary>
        [TestMethod]
        public void PublicTestHashCodeEquality()
        {
            Formula f = new Formula("( 1 + C ) - 3 * ( A + 5 )");
            Formula f2 = new Formula("( 1 + C ) - 3 * ( A + 5 )");
            Assert.IsTrue(f.GetHashCode() == f2.GetHashCode());
        }

        /// <summary>
        /// Tests that the == override properly determines equality bewtween two similar formulas. (no normalizer/validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsSimpleSuccess2()
        {
            Formula f = new Formula("( 1 + C ) - 3 * ( A + 5 )", s => s, s => true);
            Formula f2 = new Formula("(     1   +  C   ) -    3 *   ( A  +  5    )", s => s, s => true);
            Assert.IsTrue(f == f2);
        }

        /// <summary>
        /// Tests that the != override properly determines inequality bewtween two similar formulas. (no normalizer/validator)
        /// </summary>
        [TestMethod]
        public void PublicTestEqualsSimpleSuccess3()
        {
            Formula f = new Formula("( 1 + C ) - 3 * ( A + 5 )", s => s, s => true);
            Formula f2 = new Formula("(     2   +  2   ) -    2 *   ( 2  +  2    )", s => s, s => true);
            Assert.IsTrue(f != f2);
        }
    }
    //*****ALL TESTS ARE PUBLIC*****
}
