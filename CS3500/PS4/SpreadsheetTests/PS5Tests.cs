using Microsoft.VisualStudio.TestTools.UnitTesting;
using SpreadsheetUtilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SS
{
    [TestClass]
    public class PS5Tests
    {

        [TestMethod]
        public void TestXMLFilez()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "=(1+1)*2");
            sheety.SetContentsOfCell("B1", "69");
            sheety.SetContentsOfCell("C1", "HI MOM");
            sheety.Save(@"C:\Users\Tim\Documents\Visual Studio 2015\XMLTESTS\test42.xml");

            AbstractSpreadsheet sheety2 = new Spreadsheet(@"C:\Users\Tim\Documents\Visual Studio 2015\XMLTESTS\test42.xml", s => true, s => s, "default");

            Assert.AreEqual(sheety.GetCellContents("A1"), sheety2.GetCellContents("A1"));
            Assert.AreEqual(sheety.GetCellContents("B1"), sheety2.GetCellContents("B1"));
            Assert.AreEqual(sheety.GetCellContents("C1"), sheety2.GetCellContents("C1"));
        }

        [TestMethod]
        public void TestFormlaValues()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "4");
            sheety.SetContentsOfCell("B1", "=A1 * 2");
            sheety.SetContentsOfCell("C1", "=A1 + B1");

            Assert.AreEqual(4.0, sheety.GetCellValue("A1"));
            Assert.AreEqual(8.0, sheety.GetCellValue("B1"));
            Assert.AreEqual(12.0, sheety.GetCellValue("C1"));
        }

        [TestMethod]
        public void TestDoubleValues()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "4");
            sheety.SetContentsOfCell("B1", "8");
            sheety.SetContentsOfCell("C1", "12");

            Assert.AreEqual(4.0, sheety.GetCellValue("A1"));
            Assert.AreEqual(8.0, sheety.GetCellValue("B1"));
            Assert.AreEqual(12.0, sheety.GetCellValue("C1"));
        }

        [TestMethod]
        public void TestStringValues()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "hello");
            sheety.SetContentsOfCell("B1", "world");
            sheety.SetContentsOfCell("C1", "!!!");

            Assert.AreEqual("hello", sheety.GetCellValue("A1"));
            Assert.AreEqual("world", sheety.GetCellValue("B1"));
            Assert.AreEqual("!!!", sheety.GetCellValue("C1"));
        }

        [TestMethod]
        public void TestFormlaContent()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "=4 * 4");
            sheety.SetContentsOfCell("B1", "=(2 + 3) * 2");
            sheety.SetContentsOfCell("C1", "=1 + 1 + 1 + 1");

            Assert.AreEqual(new Formula("4 * 4"), sheety.GetCellContents("A1"));
            Assert.AreEqual(new Formula("(2 + 3) * 2"), sheety.GetCellContents("B1"));
            Assert.AreEqual(new Formula("1 + 1 + 1 + 1"), sheety.GetCellContents("C1"));
        }

        [TestMethod]
        public void TestDoubleContent()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "4");
            sheety.SetContentsOfCell("B1", "8");
            sheety.SetContentsOfCell("C1", "12");

            Assert.AreEqual(4.0, sheety.GetCellContents("A1"));
            Assert.AreEqual(8.0, sheety.GetCellContents("B1"));
            Assert.AreEqual(12.0, sheety.GetCellContents("C1"));
        }

        [TestMethod]
        public void TestStringContent()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "hello");
            sheety.SetContentsOfCell("B1", "world");
            sheety.SetContentsOfCell("C1", "!!!");

            Assert.AreEqual("hello", sheety.GetCellContents("A1"));
            Assert.AreEqual("world", sheety.GetCellContents("B1"));
            Assert.AreEqual("!!!", sheety.GetCellContents("C1"));
        }

        [TestMethod]
        public void TestNonemptyCells()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("A1", "hello");
            sheety.SetContentsOfCell("B1", "world");
            sheety.SetContentsOfCell("C1", "!!!");

            IEnumerable<string> NonemptyCells = sheety.GetNamesOfAllNonemptyCells();
            Assert.AreEqual(true, NonemptyCells.Contains("A1"));
            Assert.AreEqual(true, NonemptyCells.Contains("B1"));
            Assert.AreEqual(true, NonemptyCells.Contains("C1"));
            Assert.AreEqual(false, NonemptyCells.Contains("D1"));
        }

        [TestMethod]
        public void TestConstructor1()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            sheety.SetContentsOfCell("a1", "4");

            Assert.AreEqual(4.0, sheety.GetCellContents("a1"));
            Assert.AreEqual("default", sheety.Version);
            
        }

        private string NormalizerUpper (string s)
        {
            return s.ToUpper();
        }

        [TestMethod]
        public void TestConstructor2()
        {
            AbstractSpreadsheet sheety = new Spreadsheet(s=>true, NormalizerUpper, "1.10101010");
            sheety.SetContentsOfCell("a1", "4");

            Assert.AreEqual(4.0, sheety.GetCellContents("A1"));
            Assert.AreEqual("1.10101010", sheety.Version);

        }

        [TestMethod]
        public void TestConstructor3()
        {
            AbstractSpreadsheet sheety = new Spreadsheet(@"C:\Users\Tim\Documents\Visual Studio 2015\XMLTESTS\test42.xml", s => true, NormalizerUpper, "1.10101010");
            sheety.SetContentsOfCell("a1", "4");

            Assert.AreEqual(4.0, sheety.GetCellContents("A1"));
            Assert.AreEqual("1.10101010", sheety.Version);

        }

        [TestMethod]
        public void TestChanged()
        {
            AbstractSpreadsheet sheety = new Spreadsheet();
            Assert.AreEqual(false, sheety.Changed);
            sheety.SetContentsOfCell("A1", "4");
            Assert.AreEqual(true, sheety.Changed);

            sheety.Save(@"C:\Users\Tim\Documents\Visual Studio 2015\XMLTESTS\test42.xml");
            Assert.AreEqual(false, sheety.Changed);

        }

        private bool ValidatorBasic (string s)
        {
            if (s.Length > 2)
            {
                return false;
            }
            else
            {
                return true;
            }

        }

        [TestMethod]
        [ExpectedException(typeof(InvalidNameException))]
        public void TestValidationFail()
        {
            AbstractSpreadsheet sheety = new Spreadsheet(ValidatorBasic, NormalizerUpper, "2.0");
            
            sheety.SetContentsOfCell("AA1", "4");          
        }

        [TestMethod]
        [ExpectedException(typeof(InvalidNameException))]
        public void TestInvalidVariable()
        {
            AbstractSpreadsheet sheety = new Spreadsheet(ValidatorBasic, NormalizerUpper, "2.0");

            sheety.SetContentsOfCell("A1", "4");
            sheety.GetCellContents("AA1");
        }


    }
}
