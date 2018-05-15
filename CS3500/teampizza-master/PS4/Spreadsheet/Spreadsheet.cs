using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SpreadsheetUtilities;
using System.Xml;
using System.IO;

namespace SS
{
    /// <summary>
    /// Class representing a spreadsheet object. Extends the AbstractSpreadsheet class:
    /// 
    /// An AbstractSpreadsheet object represents the state of a simple spreadsheet.  A 
    /// spreadsheet consists of an infinite number of named cells.
    /// 
    /// A string is a valid cell name if and only if:
    ///   (1) its first character is an underscore or a letter
    ///   (2) its remaining characters (if any) are underscores and/or letters and/or digits
    /// Note that this is the same as the definition of valid variable from the PS3 Formula class.
    /// 
    /// For example, "x", "_", "x2", "y_15", and "___" are all valid cell  names, but
    /// "25", "2x", and "&" are not.  Cell names are case sensitive, so "x" and "X" are
    /// different cell names.
    /// 
    /// A spreadsheet contains a cell corresponding to every possible cell name.  (This
    /// means that a spreadsheet contains an infinite number of cells.)  In addition to 
    /// a name, each cell has a contents and a value.  The distinction is important.
    /// 
    /// The contents of a cell can be (1) a string, (2) a double, or (3) a Formula.  If the
    /// contents is an empty string, we say that the cell is empty.  (By analogy, the contents
    /// of a cell in Excel is what is displayed on the editing line when the cell is selected.)
    /// 
    /// In a new spreadsheet, the contents of every cell is the empty string.
    ///  
    /// The value of a cell can be (1) a string, (2) a double, or (3) a FormulaError.  
    /// (By analogy, the value of an Excel cell is what is displayed in that cell's position
    /// in the grid.)
    /// 
    /// If a cell's contents is a string, its value is that string.
    /// 
    /// If a cell's contents is a double, its value is that double.
    /// 
    /// If a cell's contents is a Formula, its value is either a double or a FormulaError,
    /// as reported by the Evaluate method of the Formula class.  The value of a Formula,
    /// of course, can depend on the values of variables.  The value of a variable is the 
    /// value of the spreadsheet cell it names (if that cell's value is a double) or 
    /// is undefined (otherwise).
    /// 
    /// Spreadsheets are never allowed to contain a combination of Formulas that establish
    /// a circular dependency.  A circular dependency exists when a cell depends on itself.
    /// For example, suppose that A1 contains B1*2, B1 contains C1*2, and C1 contains A1*2.
    /// A1 depends on B1, which depends on C1, which depends on A1.  That's a circular
    /// dependency.
    /// </summary>
    public class Spreadsheet : AbstractSpreadsheet //****** PS5 WRITTEN BY TIM DORNY U0829896 ******
    {
        /// <summary>
        /// Graph used to track dependencies between cells.
        /// </summary>
        private DependencyGraph Graph;

        /// <summary>
        /// Dictionary containing cell objects using their names as keys.
        /// </summary>
        private Dictionary<string, Cell> Cells;

        /// <summary>
        /// Delegate reserved for a function that determines the validity of variables.
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        private Func<string, bool> Validator;

        /// <summary>
        /// Delegate reserved for a function that 'normalizes' variable names.
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        private Func<string, string> Normalizer;

        /// <summary>
        /// String referencing a path to a file location
        /// </summary>
        private string Filepath;

        /// <summary>
        /// String containing the version number of a spreadsheet
        /// </summary>
        private string SpreadsheetVersion;

        /// <summary>
        /// True if this spreadsheet has been modified since it was created or saved                  
        /// (whichever happened most recently); false otherwise.
        /// </summary>
        public override bool Changed { get; protected set; }

        /// <summary>
        /// Constructs an empty spreadsheet.
        /// </summary>
        public Spreadsheet() :
            this(s => true, s => s, "default")
        {

        }

        /// <summary>
        /// Creates an empty spreadsheet with the given version and validator/normalizer functions.
        /// </summary>
        /// <param name="validator"></param>
        /// <param name="normalizer"></param>
        /// <param name="version"></param>
        public Spreadsheet (Func<string, bool> validator, Func<string, string> normalizer, string version) :
            base(validator, normalizer, version)
        {
            // Initiallize member variables to an empty spreadsheet and the passed in arguments.
            Cells = new Dictionary<string, Cell>();
            Graph = new DependencyGraph();
            Validator = validator;
            Normalizer = normalizer;
            SpreadsheetVersion = version;
            Changed = false;
        }

        /// <summary>
        /// Creates a spreadsheet from the given filepath using the provided validator/normalizer functions.
        /// </summary>
        /// <param name="filepath"></param>
        /// <param name="validator"></param>
        /// <param name="normalizer"></param>
        /// <param name="version"></param>
        public Spreadsheet(string filepath, Func<string, bool> validator, Func<string, string> normalizer, string version) :
            base(validator, normalizer, version)
        {
            // Initiallize member variables to an empty spreadsheet and the passed in arguments.
            Cells = new Dictionary<string, Cell>();
            Graph = new DependencyGraph();
            Validator = validator;
            Normalizer = normalizer;
            SpreadsheetVersion = version;
            Filepath = filepath;
            Changed = false;
            if (!(GetSavedVersion(Filepath) == SpreadsheetVersion))
            {
                throw new SpreadsheetReadWriteException("Versions do not match up.");
            }
            // Create spreadsheet from file
            ReadSpreadsheetFile();

        }

        private void ReadSpreadsheetFile()
        {

            try
            {
                using (XmlReader Reader = XmlReader.Create(Filepath))
                {
                    while (Reader.ReadToFollowing("cell"))
                    {
                        // Read to name and store it.
                        Reader.ReadToFollowing("name");
                        string CurrentName = Reader.ReadElementContentAsString();
                        // Reader is now on contents, store that value as well
                        string CurrentContents = Reader.ReadElementContentAsString();

                        // Put cell into spreadsheet
                        SetContentsOfCell(CurrentName, CurrentContents);
                    }

                    // Once all cells have been added, close reader and return.
                    Reader.Close();
                    Changed = false;
                    return;
                }
            }
            catch (Exception)
            {
                throw new SpreadsheetReadWriteException("Error reading file.");
            }
        }

        /// /// <summary>
        /// If name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, returns the contents (as opposed to the value) of the named cell.  The return
        /// value should be either a string, a double, or a Formula.
        public override object GetCellContents(string name)
        {
            // Normalize name
            name = Normalizer(name);

            if (name == null || !(name.IsValidVariableName()))
            {
                throw new InvalidNameException();
            }
            else if (!(Validator(name)))
            {
                throw new InvalidNameException();
            }
            else if (!(Cells.ContainsKey(name)))
            {
                // If the given name does not have an existing cell, return empty string(empty cell)
                return "";
            }

            return Cells[name].Content();

        }
        /// <summary>
        /// Enumerates the names of all the non-empty cells in the spreadsheet.
        /// </summary>
        public override IEnumerable<string> GetNamesOfAllNonemptyCells()
        {
            return Cells.Keys;
        }

        /// <summary>
        /// If the formula parameter is null, throws an ArgumentNullException.
        /// 
        /// Otherwise, if name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, if changing the contents of the named cell to be the formula would cause a 
        /// circular dependency, throws a CircularException.  (No change is made to the spreadsheet.)
        /// 
        /// Otherwise, the contents of the named cell becomes formula.  The method returns a
        /// Set consisting of name plus the names of all other cells whose value depends,
        /// directly or indirectly, on the named cell.
        /// 
        /// For example, if name is A1, B1 contains A1*2, and C1 contains B1+A1, the
        /// set {A1, B1, C1} is returned.
        /// </summary>
        protected override ISet<string> SetCellContents(string name, Formula formula)
        {
            if (formula == null)
            {
                throw new ArgumentNullException();
            }

            // Update dependencies from formula
            IEnumerable<string> Variables = formula.GetVariables();

            // If Variables is not null, add dependencies for variables.
            if (!(Variables == null))
            {
                foreach (string Variable in Variables)
                {
                    // Normalize Variable
                    string NormVariable = Normalizer(Variable);
                    // Check if variable is valid
                    if (NormVariable == null || !(NormVariable.IsValidVariableName()))
                    {
                        throw new FormulaFormatException("Invalid variable.");
                    }
                    else if (!(Validator(NormVariable)))
                    {
                        throw new FormulaFormatException("Invalid variable.");
                    }

                    // Add each variable/cell number to the dependency graph (Given cell depends on cells listed in the formula (variables)).
                    Graph.AddDependency(name, NormVariable);
                }
            }

            // Next, check for any circular dependencies that might be caused by adding the formula.
            CheckCircularDependencies(name, name, new HashSet<string>());

            // If no circular dependencies are found, update the content of the cell.
            Cells[name] = new Cell(name, formula);

            // Update type of cell's content
            Cells[name].SetContentTypeFormula(LookupFunction);

            // Create set to hold names of all direct/indirect dependees of 'name'.
            HashSet<string> DependeesSet = new HashSet<string>();

            // Add all indirect and direct dependees of 'name' to DependeeSet
            GetAllDependees(name, DependeesSet);

            // Get list of cells to Recalculate.
            IEnumerable<string> CellsToRecalculate = GetCellsToRecalculate(DependeesSet);

            // Recalculate cells.
            RecalculateCells(CellsToRecalculate);

            // Return finished set
            return DependeesSet;
        }

        /// <summary>
        /// If text is null, throws an ArgumentNullException.
        /// 
        /// Otherwise, if name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, the contents of the named cell becomes text.  The method returns a
        /// set consisting of name plus the names of all other cells whose value depends, 
        /// directly or indirectly, on the named cell.
        /// 
        /// For example, if name is A1, B1 contains A1*2, and C1 contains B1+A1, the
        /// set {A1, B1, C1} is returned.
        /// </summary>
        protected override ISet<string> SetCellContents(string name, string text)
        {
            // If text is null 
            if (text == null)
            {
                throw new ArgumentNullException();
            }
            // If text is empty string, do nothing and return an empty hashset.
            if (text == "")
            {
                return new HashSet<string>();
            }

            // Update the content of the cell.
            Cells[name] = new Cell(name, text);

            // Update type of cell's content
            Cells[name].SetContentTypeString();

            // Since cell contains a string, we remove any cells that it may have depended on.
            Graph.ReplaceDependents(name, new HashSet<string>());

            // Create set to hold names of all direct/indirect dependees of 'name'.
            HashSet<string> DependeesSet = new HashSet<string>();

            // Add all indirect and direct dependees of 'name' to DependeeSet
            GetAllDependees(name, DependeesSet);

            // Get list of cells to Recalculate.
            IEnumerable<string> CellsToRecalculate = GetCellsToRecalculate(DependeesSet);

            // Recalculate cells.
            RecalculateCells(CellsToRecalculate);

            // Return finished set
            return DependeesSet;
        }

        /// <summary>
        /// If name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, the contents of the named cell becomes number.  The method returns a
        /// set consisting of name plus the names of all other cells whose value depends, 
        /// directly or indirectly, on the named cell.
        /// 
        /// For example, if name is A1, B1 contains A1*2, and C1 contains B1+A1, the
        /// set {A1, B1, C1} is returned.
        /// </summary>
        protected override ISet<string> SetCellContents(string name, double number)
        {
            // Update the content of the cell.
            Cells[name] = new Cell(name, number);

            // Update type of cell's content
            Cells[name].SetContentTypeDouble();

            // Since cell contains a double, we remove any cells that it may have depended on.
            Graph.ReplaceDependents(name, new HashSet<string>());

            // Create set to hold names of all direct/indirect dependees of 'name'.
            HashSet<string> DependeesSet = new HashSet<string>();

            // Add all indirect and direct dependees of 'name' to DependeeSet
            GetAllDependees(name, DependeesSet);

            // Get list of cells to Recalculate.
            IEnumerable<string> CellsToRecalculate = GetCellsToRecalculate(name);
            // Remove current cell from CellsToRecalc
            

            // Recalculate cells.
            RecalculateCells(CellsToRecalculate);

            // Return finished set
            return DependeesSet;

        }

        private void RecalculateCells (IEnumerable<string> cells)
        {
            foreach (string name in cells)
            {
                if (Cells[name].IsFormula)
                {
                    // Recalculate each formula's value.
                    Cells[name].SetContentTypeFormula(LookupFunction);
                }
                
            }
        }
        /// <summary>
        /// Adds all direct and indirect dependees of cell named 'name' to the provided HashSet 'finalSet'.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="finalSet"></param>
        private void GetAllDependees(string name, HashSet<string> finalSet)
        {
            // Add cell name to final set.
            finalSet.Add(name);
            // Initialize HashSet to store dependees of cell 'name'.
            HashSet<string> currentDependees = GetDirectDependents(name) as HashSet<string>;

            // If cell 'name' has no dependees, return.
            if (currentDependees == null)
            {
                return;
            }

            foreach (string CellName in currentDependees)
            {
                // Check and add all dependencies of the cell named 'CellName'.
                GetAllDependees(CellName, finalSet);
            }
        }
        /// <summary>
        /// Checks for circular dependencies when adding a formula object to a cell.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="dependencies"></param>
        private void CheckCircularDependencies(string name, string start, HashSet<string> visited)
        {
            // If cell has already been visited, return
            if (visited.Contains(name))
            {
                return;
            }
            // Add current cell to visited set.
            visited.Add(name);
            // Add dependents of current cell to set
            HashSet<string> currentDependees = GetDirectDependents(name) as HashSet<string>;

            // Check each dependent of 'name' for circular dependencies
            foreach (string CellName in currentDependees)
            {
                // If 'start' is found as a direct dependant of 'CellName', a circular exception is found and an exception is thrown.
                if (CellName == start)
                {
                    throw new CircularException();
                }
                // Otherwise, iterate through all indirect dependencies recursively and check for circular dependencies.
                CheckCircularDependencies(CellName, start, visited);
            }
            return;
        }
        /// <summary>
        /// If name is null, throws an ArgumentNullException.
        /// 
        /// Otherwise, if name isn't a valid cell name, throws an InvalidNameException.
        /// 
        /// Otherwise, returns an enumeration, without duplicates, of the names of all cells whose
        /// values depend directly on the value of the named cell.  In other words, returns
        /// an enumeration, without duplicates, of the names of all cells that contain
        /// formulas containing name.
        /// 
        /// For example, suppose that
        /// A1 contains 3
        /// B1 contains the formula A1 * A1
        /// C1 contains the formula B1 + A1
        /// D1 contains the formula B1 - C1
        /// The direct dependents of A1 are B1 and C1
        /// </summary>
        protected override IEnumerable<string> GetDirectDependents(string name)
        {
            // Normalize name
            name = Normalizer(name);

            if (name == null || !(name.IsValidVariableName()))
            {
                throw new InvalidNameException();
            }
            else if (!(Validator(name)))
            {
                throw new InvalidNameException();
            }

            return Graph.GetDependees(name);
        }

        /// <summary>
        /// Returns the version information of the spreadsheet saved in the named file.
        /// If there are any problems opening, reading, or closing the file, the method
        /// should throw a SpreadsheetReadWriteException with an explanatory message.
        /// </summary>
        public override string GetSavedVersion(string filename)
        {
            try
            {
                using (XmlReader Reader = XmlReader.Create(filename))
                {
                    Reader.ReadToFollowing("spreadsheet");
                    Reader.MoveToFirstAttribute();
                    return Reader.Value;
                }
            }
            catch (Exception)
            {
                throw new SpreadsheetReadWriteException("Error obtaining version information.");
            }


        }

        /// <summary>
        /// Writes the contents of this spreadsheet to the named file using an XML format.
        /// The XML elements should be structured as follows:
        /// 
        /// <spreadsheet version="version information goes here">
        /// 
        /// <cell>
        /// <name>
        /// cell name goes here
        /// </name>
        /// <contents>
        /// cell contents goes here
        /// </contents>    
        /// </cell>
        /// 
        /// </spreadsheet>
        /// 
        /// There should be one cell element for each non-empty cell in the spreadsheet.  
        /// If the cell contains a string, it should be written as the contents.  
        /// If the cell contains a double d, d.ToString() should be written as the contents.  
        /// If the cell contains a Formula f, f.ToString() with "=" prepended should be written as the contents.
        /// 
        /// If there are any problems opening, writing, or closing the file, the method should throw a
        /// SpreadsheetReadWriteException with an explanatory message.
        /// </summary>
        public override void Save(string filename)
        {
            try
            {
                // Create writer
                using (XmlWriter Writer = XmlWriter.Create(filename))
                {
                    // Write spreadsheet version
                    Writer.WriteStartElement("spreadsheet");
                    Writer.WriteAttributeString("version", Version);
                    // Write XML data for each cell
                    foreach (string key in Cells.Keys)
                    {
                        // Cell header
                        Writer.WriteStartElement("cell");
                        // Name of cell
                        Writer.WriteElementString("name", key);
                        // Contents
                        // Set string 'Contents' to a string representing the contents of the current cell.
                        string Contents = "";
                        if (Cells[key].IsDouble)
                        {
                            Contents = Cells[key].Content().ToString();
                        }
                        else if (Cells[key].IsString)
                        {
                            Contents = Cells[key].Content() as string;
                        }
                        else if (Cells[key].IsFormula)
                        {
                            Contents = "=" + Cells[key].Content().ToString();
                        }
                        // Write content of cell
                        Writer.WriteElementString("contents", Contents);

                        // Write end of 'cell' element
                        Writer.WriteEndElement();
                    }
                    // After each cell is written, end 'spreadsheet' element and close writer
                    Writer.WriteEndElement();
                    Writer.Close();
                    Changed = false;
                }
            }
            catch (Exception)
            {
                throw new SpreadsheetReadWriteException("Error saving file.");
            }
            
       }

        /// <summary>
        /// If name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, returns the value (as opposed to the contents) of the named cell.  The return
        /// value should be either a string, a double, or a SpreadsheetUtilities.FormulaError.
        /// </summary>
        public override object GetCellValue(string name)
        {
            // Normalize name
            name = Normalizer(name);

            if (!GetNamesOfAllNonemptyCells().Contains(name))
            {
                return "";
            }


          //  try
          //  {
                return Cells[name].Value();
         //   }
         //   catch (KeyNotFoundException)
          //  {
          //      return "";
           // }
        }

        /// <summary>
        /// If content is null, throws an ArgumentNullException.
        /// 
        /// Otherwise, if name is null or invalid, throws an InvalidNameException.
        /// 
        /// Otherwise, if content parses as a double, the contents of the named
        /// cell becomes that double.
        /// 
        /// Otherwise, if content begins with the character '=', an attempt is made
        /// to parse the remainder of content into a Formula f using the Formula
        /// constructor.  There are then three possibilities:
        /// 
        ///   (1) If the remainder of content cannot be parsed into a Formula, a 
        ///       SpreadsheetUtilities.FormulaFormatException is thrown.
        ///       
        ///   (2) Otherwise, if changing the contents of the named cell to be f
        ///       would cause a circular dependency, a CircularException is thrown.
        ///       
        ///   (3) Otherwise, the contents of the named cell becomes f.
        /// 
        /// Otherwise, the contents of the named cell becomes content.
        /// 
        /// If an exception is not thrown, the method returns a set consisting of
        /// name plus the names of all other cells whose value depends, directly
        /// or indirectly, on the named cell.
        /// 
        /// For example, if name is A1, B1 contains A1*2, and C1 contains B1+A1, the
        /// set {A1, B1, C1} is returned.
        /// </summary>
        public override ISet<string> SetContentsOfCell(string name, string content)
        {
            // Normalize name.
            name = Normalizer(name);

            // If name is null/invalid throw exception.
            if (content == null)
            {
                throw new ArgumentNullException("Content is null.");
            }
            // If empty string, remove cell from dictionary.
            if (content == "")
            {
                // Create set to hold names of all direct/indirect dependees of 'name'.
                HashSet<string> DependeesSet = new HashSet<string>();

                // Add all indirect and direct dependees of 'name' to DependeeSet
                GetAllDependees(name, DependeesSet);             

                // Remove cell from dictionary (causing its contents to become "").
                Cells.Remove(name);
                DependeesSet.Remove(name);

                // Get list of cells to Recalculate.
                IEnumerable<string> CellsToRecalculate = GetCellsToRecalculate(DependeesSet);
                // Recalculate cells.
                RecalculateCells(CellsToRecalculate);

                
            }
            if (name == null || !name.IsValidVariableName())
            {
                throw new ArgumentException();
            }
            else if (!(Validator(name)))
            {
                throw new InvalidNameException();
            }

            double Parse;
            if (Double.TryParse(content, out Parse))
            {
                // Spreadsheet has been changed.
                Changed = true;

                return SetCellContents(name, Parse);
            }
            // If empty string, cell is not cleared.
            char FirstCharacter;
            try
            {
                FirstCharacter = content.First();
            }
            catch (InvalidOperationException)
            {
                Cells[name] = new Cell(name);

                return new HashSet<string>();
            }            
            

            if (content.First() == '=')
            {
                // Spreadsheet has been changed.
                Changed = true;

                string FormulaString = content.Substring(1);
                Formula CellFormula = new Formula(FormulaString);
                return SetCellContents(name, CellFormula);
            }
            else
            {
                // Spreadsheet has been changed.
                Changed = true;

                return SetCellContents(name, content);
            }


        }
        /// <summary>
        /// Removes a cell from dictionary. (sets to empty)
        /// </summary>
        /// <param name="name"></param>
        public void RemoveCell (string name)
        {
            Cells.Remove(name);
        }

        private double LookupFunction (string name)
        {
            // Normalize name
            name = Normalizer(name);

            // If name is not valid variable, throw exception.
            if (name == null || !name.IsValidVariableName())
            {
                throw new ArgumentException();
            }
            else if (!(Validator(name)))
            {
                throw new ArgumentException();
            }
            double Result;
            try
            {
                Result = Double.Parse(GetCellValue(name).ToString());
            }
            catch (NullReferenceException)
            {
                throw new ArgumentException();
            }
            catch (KeyNotFoundException)
            {
                throw new ArgumentException();
            }
            catch (FormatException)
            {
                throw new ArgumentException();
            }
            return Result;
            

        }
    }

    public static class NameChecker
    {
        public static bool IsValidVariableName(this String name)
        {
            // Signifies that the end of letters in the cell name has ended and the digits have begun
            bool LettersEnd = false;
            if (!(Char.IsLetter(name[0])))
            {
                return false;
            }
            for (int i = 0; i < name.Length; i++)
            {
                // If a non-letter character is found before the first digit, name/variable is not valid
                if (!(Char.IsLetter(name[0])) && LettersEnd == false)
                {
                    return false;
                }
                // Sets bool value to true once the first digit is found. Now the remaining characters must all be digits.
                if (Char.IsDigit(name[i]) && LettersEnd == false)
                {
                    LettersEnd = true;
                }
                // If another letter is found after the first digit, name/variable is not valid.
                if (LettersEnd == true && Char.IsLetter(name[i]))
                {
                    return false;
                }
            }
            // If end of string is reached, the name/variable is valid.
            return true;

        }
    }

}