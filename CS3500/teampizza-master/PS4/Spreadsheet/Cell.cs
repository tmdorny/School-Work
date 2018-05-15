using SpreadsheetUtilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SS
{
    class Cell
    {//
        /// <summary>
        /// Name of cell.
        /// </summary>
        private string CellName;

        /// <summary>
        /// Content of cell
        /// </summary>
        private object CellContent;

        /// <summary>
        /// Value of cell
        /// </summary>
        private object CellValue;

        /// <summary>
        /// True if cell contains double.
        /// </summary>
        public bool IsDouble { get; protected set; }

        /// <summary>
        /// True if cell contains string.
        /// </summary>
        public bool IsString { get; protected set; }

        /// <summary>
        /// True if cell contains Formula.
        /// </summary>
        public bool IsFormula { get; protected set; }
        //private object CellValue;
        /// <summary>
        /// Creates a new cell object with the specified name containing an empty string.
        /// </summary>
        /// <param name="cellName"></param>
        public Cell(string cellName)
        {
            CellName = cellName;
            CellContent = "";
        }
        public Cell(string name, object content)
        {
            CellName = name;
            CellContent = content;
        }
        /// <summary>
        /// Returns the name of a cell in string form.
        /// </summary>
        /// <returns></returns>
        public string Name()
        {
            return CellName;
        }
        /// <summary>
        /// Returns the contents of a cell.
        /// </summary>
        /// <returns></returns>
        public object Content()
        {
            return CellContent;
        }
        /// <summary>
        /// Returns value of cell.
        /// </summary>
        /// <returns></returns>
        public object Value()
        {
            return CellValue;
        }

        /// <summary>
        /// Changes bool to indicate cell contains a string, updates cell value accordingly.
        /// </summary>
        public void SetContentTypeString()
        {
            IsString = true;

            CellValue = CellContent.ToString();
        }

        /// <summary>
        /// Changes bool to indicate cell contains a string, updates cell value accordingly.
        /// </summary>
        public void SetContentTypeDouble()
        {
            IsDouble = true;

            CellValue = Double.Parse(CellContent.ToString());
        }

        /// <summary>
        /// Changes bool to indicate cell contains a string, updates cell value accordingly. Uses provided lookup function for variable values.
        /// </summary>
        public void SetContentTypeFormula(Func<string, double> lookup)
        {
            IsFormula = true;

            Formula CellFormula = CellContent as Formula;
            CellValue = CellFormula.Evaluate(lookup);
        }
    }
}