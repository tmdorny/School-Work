using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SS;
using System.Text.RegularExpressions;
using SpreadsheetUtilities;

namespace SpreadsheetGUI
{
    /// <summary>
    /// Class containing code for spreadsheet gui.
    /// </summary>
    public partial class Form1 : Form
    {
        /// <summary>
        /// The actual spreadsheet object that holds all cell data.
        /// </summary>
        private AbstractSpreadsheet Spreadsheet;
        /// <summary>
        /// Name of the currently selected cell.
        /// </summary>
        private string CurrentCellName;
        /// <summary>
        /// Row number of the selected cell.
        /// </summary>
        private int CurrentRow;
        /// <summary>
        /// Column number of the selected cell.
        /// </summary>
        private int CurrentColumn;
        /// <summary>
        /// Variable used to store cell contents when copy/pasting.
        /// </summary>
        private object CopyContents = "";
        /// <summary>
        /// Variable used to store cell value when copy/pasting.
        /// </summary>
        private object CopyValue = "";

        private BackgroundWorker BGWorker;

        /// <summary>
        /// GUI constructor
        /// </summary>
        public Form1()
        {
            InitializeComponent();

            BGWorker = new BackgroundWorker();
            BGWorker.DoWork += new DoWorkEventHandler(BGDoWork);
            
            // When spreadsheetPanel's selection is changed, run the getselectionvalues method.
            SpreadSheetPanel.SelectionChanged += GetSelectionValues;

            // Cell A1 is selected initially
            CurrentCellName = "A1";
            CellNameDisplayLabel.Text = CurrentCellName;

            // Create underlying spreadsheet.
            Spreadsheet = new Spreadsheet(Validator, Normalizer, "ps6");
            
            
        }
        /// <summary>
        /// Update spreadsheet values.
        /// </summary>
        public void Update()
        {
            BGWorker.RunWorkerAsync();
        }
        /// <summary>
        /// Background worker doin stuff
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BGDoWork(object sender, DoWorkEventArgs e)
        {
            UpdateCells();
        }
        /// <summary>
        /// Normalizer for spreadsheet, ensures that all letters are capitalized.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private string Normalizer(string name)
        {
            return name.ToUpper();
        }
        /// <summary>
        /// Validator for spreadsheet, ensures that all cell names consist of a single capital letter followed by 1-2 digits.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private bool Validator(string name)
        {
            char FirstLetter = name.First();
            if (!(FirstLetter > 'A' || FirstLetter < 'Z'))
            {
                return false;
            }
            string Number = name.Substring(1);
            double RowNumber;
            if (!(Double.TryParse(Number, out RowNumber)))
            {
                return false;
            }
            else if (!(RowNumber > 0 || RowNumber < 99))
            {
                return false;
            }

            return true;
            
        }
        /// <summary>
        /// Creates a string containing the corresponding cell name from a row and column number.
        /// </summary>
        /// <param name="column"></param>
        /// <param name="row"></param>
        /// <returns></returns>
        private string GetCellName (int column, int row)
        {
            char Letter = Convert.ToChar(column + 65);
            return "" + Letter + (row + 1);
        }
        /// <summary>
        /// Gets the coordinates of a cell from its name.
        /// </summary>
        /// <param name="name"></param>
        private void GetCoordsFromName (string name)
        {
            char Letter = name.First();
            string Number = name.Substring(1);

            CurrentColumn = Letter - 65;
            CurrentRow = Int32.Parse(Number) - 1;
            
        }
        /// <summary>
        /// Gets cell contents and value from the selected cell and displays them on their corresponding GUI elements.
        /// </summary>
        /// <param name="panel"></param>
        private void GetSelectionValues (SpreadsheetPanel panel)
        {
            // Get row and column values from the GUI and convert them to correspond with the spreadsheet.
            panel.GetSelection(out CurrentColumn, out CurrentRow);
            CurrentCellName = GetCellName(CurrentColumn, CurrentRow);
            // Update cell name on GUI
            CellNameDisplayLabel.Text = CurrentCellName;
            // Update cell content on GUI
            CellContentsField.AcceptsReturn = true;
            // Get contents of selected cell.
            object CellContents = Spreadsheet.GetCellContents(CurrentCellName);

            // If cell is empty, display empty cell.
            if (CellContents.ToString() == "")
            {
                CellValueDisplayLabel.Text = "";
                CellContentsField.Text = "";
            }
            // If formula, add an = to beginning of content string.
            else if (CellContents is Formula)
            {
                CellContentsField.Text = "=" + Spreadsheet.GetCellContents(CurrentCellName).ToString();
                // Update cell value on GUI
                CellValueDisplayLabel.Text = Spreadsheet.GetCellValue(CurrentCellName).ToString();
            }
            else
            {
                CellContentsField.Text = Spreadsheet.GetCellContents(CurrentCellName).ToString();
                // Update cell value on GUI
                CellValueDisplayLabel.Text = Spreadsheet.GetCellValue(CurrentCellName).ToString();

                
            }
        }
        /// <summary>
        /// ???
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// ???
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void spreadsheetPanel1_Load(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// Updates cell content/value when text is entered into the textbox and the enter key is pressed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                // Get rid of ANNOYING DING
                e.SuppressKeyPress = true;
                // Store the previous contents of cell if later needed.
                string OldContents = Spreadsheet.GetCellContents(CurrentCellName).ToString();

                // Try to set the contents of cell to the entered text.
                try
                {
                    Spreadsheet.SetContentsOfCell(CurrentCellName, CellContentsField.Text);
                }
                // Supposed to catch argument exception (which is supposed to cause formula error in formula class), something is wrong here sadly :((((((
                catch (ArgumentException)
                {
                    MessageBox.Show(null, "Error, error in formula calculation.", "Error");
                    Spreadsheet.SetContentsOfCell(CurrentCellName, OldContents);
                    CellContentsField.Text = OldContents;
                    return;
                }
                // If an invalid formula is entered, an error message pops up and the cell returns to its original contents.
                catch (FormulaFormatException)
                {
                    MessageBox.Show(null, "Error, formula format is invalid.", "Error");
                    Spreadsheet.SetContentsOfCell(CurrentCellName, OldContents);
                    CellContentsField.Text = OldContents;
                    return;

                }
                
                // If a circular exception is encountered, an error message is show and the cell returns to its original contents.
                catch(CircularException)
                {
                    MessageBox.Show(null, "Error, circular dependcy exists, check your formulas.", "Error");
                    Spreadsheet.SetContentsOfCell(CurrentCellName, OldContents);
                    CellContentsField.Text = OldContents;
                    return;
                }
                // Get the value of the current cell in the spreadsheet.
                object CellType = Spreadsheet.GetCellValue(CurrentCellName);                

                // If a formula error was returned, an error message is shown and the cell returns to its original contents.
                if (CellType is FormulaError)
                {
                    MessageBox.Show(null, "Error, formlua returns FormulaError.", "Error");
                    Spreadsheet.SetContentsOfCell(CurrentCellName, OldContents);
                    CellContentsField.Text = OldContents;
                    return;
                }
                string CellValue = "";

                // If no errors are encountered, store the cell value as a string.
                try
                {
                    CellValue = CellType.ToString();
                }
                catch (NullReferenceException)
                {
                    
                }

                // Update the spreadsheetpanel with the new value.
                SpreadSheetPanel.SetValue(CurrentColumn, CurrentRow, CellValue);
                // Update corresponding label.
                this.CellValueDisplayLabel.Text = CellValue;

                Update();
                GetSelectionValues(SpreadSheetPanel);


            }
        }
        /// <summary>
        /// Updates the values of all nonempty cells in the spreadsheet. Used to recalculate formulas when cells are changed.
        /// </summary>
        private void UpdateCells()
        {
            // Store coordinates of selection to restore at end of updating process.
            int StartRow = CurrentRow;
            int StartColumn = CurrentColumn;

            foreach (string name in Spreadsheet.GetNamesOfAllNonemptyCells())
            {
                // Get value of current cell
                object CellValue = Spreadsheet.GetCellValue(name);
                // If a formula has broken, a message is displayed and the formula is removed.
                if (CellValue is FormulaError)
                {
                    MessageBox.Show(null, "Deletion has caused a formula to break.", "Error");
                }
                
                // Get spreadsheetpanel coordinates for current cell.
                GetCoordsFromName(name);
                // Update each cell with its new value.
                try
                {
                    SpreadSheetPanel.SetValue(CurrentColumn, CurrentRow, CellValue.ToString());
                }
                // If current cell is empty when method is called a NRE will be thrown, in this case, move to the next cell.
                catch (NullReferenceException)
                {
                    continue;
                }
            }

            // Restore initial coordinates.
            CurrentRow = StartRow;
            CurrentColumn = StartColumn;
        }  

        /// <summary>
        /// Opens spreadsheet from file, current spreadsheet will be closed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Create file dialog window and add filter.
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "sprd files (*.sprd)|*sprd| All files (*.*)|*.*";

            // Store result of dialog choice.
            DialogResult Result = openFileDialog.ShowDialog();
            // If OK was pressed, attempt to save file to the specified location. If an exception occurs, display an error message and exit.
            if (Result == DialogResult.OK)
            {
                try
                {
                    SpreadSheetPanel.Clear();
                    Spreadsheet = new Spreadsheet(openFileDialog.FileName, Validator, Normalizer, "ps6");
                    GetSelectionValues(SpreadSheetPanel);

                    Update();
                }
                catch (Exception)
                {
                    MessageBox.Show(null, "Error reading file.", "Error");
                }
            }
            // If cancel is pressed, simply return to spreadsheet.
            else if (Result == DialogResult.Cancel)
            {
                return;
            }
        }
        /// <summary>
        /// Saves the current spreadsheet to a file.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Create save dialog window and add filter.
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "sprd files (*.sprd)|*sprd| All files (*.*)|*.*";
            // Display the window to user.
            saveFileDialog.ShowDialog();

            // If .sprd is not added to end of filename, add the extension.
            if (!saveFileDialog.FileName.EndsWith(".sprd"))
            {
                saveFileDialog.FileName += ".sprd";
            }
            // Attempt to save spreadsheet.
            try
            {
                Spreadsheet.Save(saveFileDialog.FileName);
            }
            // If exception is thrown, display error message and exit window.
            catch (Exception)
            {
                MessageBox.Show(null, "Error saving file.", "Error");
            }
        }
        /// <summary>
        /// Displays helpful information about the spreadsheet program.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void helpToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            // Show a messsagebox containing helpful information about the spreadsheet.
            MessageBox.Show(null, "Welcome to the Help menu.\n\nTo select a cell, simply click on it.\n\nTo change the contents of a cell, select the cell, enter the desired content into the textbox, and hit enter.\n\nAdditional Feature:\n\nCopy and paste has been added. Right click a selected cell to open the copy/paste option.", "Help Window");
        }
        /// <summary>
        /// Terminate spreadsheet program.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // If spreadsheet has changed since it was last saved/created/opened, open a diaglog box warning the user that information could be lost.
            if (Spreadsheet.Changed)
            {
                DialogResult SaveResult = MessageBox.Show("There is unsaved data. Are you sure that you want to exit?", "Careful", MessageBoxButtons.YesNo);

                // If user decides not to exit, return to the spreadsheet.
                if (SaveResult.Equals(DialogResult.No))
                {
                    return;
                }
                // If the user decides to terminate anyways, close the program.
                else
                {
                    Application.Exit();
                }
            }

            Application.Exit();
        }
        /// <summary>
        /// Button that creates a new blank spreadsheet. Does not close current one.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Create a new form in the appcontext
            SpreadsheetApplicationContext.getAppContext().RunForm(new Form1());
        }

        /// <summary>
        /// Event when the mouse is clicked on the spreadsheetpanel.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SpreadSheetPanel_MouseClick(object sender, MouseEventArgs e)
        {
            // Only execute if the right mouse button was clicked
            if (e.Button == MouseButtons.Right)
            {
                // Display contextmenu containing Copy/paste/delete
                ContextMenuStrip context = CopyPasteMenu;
                // Display menu at location of mouseclick
                context.Show(this, new Point(e.X, e.Y));
            }
        }
        /// <summary>
        /// Event when the copy option is clicked on the right-click menu.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Get current selection's coordinates and name.
            SpreadSheetPanel.GetSelection(out CurrentColumn, out CurrentRow);
            CurrentCellName = GetCellName(CurrentColumn, CurrentRow);
            // Get contents of cell and store them.
            CopyContents = Spreadsheet.GetCellContents(CurrentCellName);
            // If cell is empty, the copy operation cannot be performed. Display error messgae.
            if (CopyContents.ToString() == "")
            {
                MessageBox.Show(null, "Error: Cannot copy empty cell.", "Error");
            }
            // Store the cell's value as well.
            CopyValue = Spreadsheet.GetCellValue(CurrentCellName);
        }
        /// <summary>
        /// Event when the paste option is clicked on the right-click menu.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pasteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // If nothing has been copied, do nothing.
            if (CopyContents.ToString() == "")
            {
                return;
            }
            // Otherwise, get coordinates and name of selected cell.
            SpreadSheetPanel.GetSelection(out CurrentColumn, out CurrentRow);
            CurrentCellName = GetCellName(CurrentColumn, CurrentRow);

            // If copied cell was a formula, append an = to the beginning of the content string.
            if (CopyContents is Formula)
            {
                Spreadsheet.SetContentsOfCell(CurrentCellName, "=" + CopyContents.ToString());
            }
            // Otherwise simply add the copied contents to the cell.
            else
            {
                Spreadsheet.SetContentsOfCell(CurrentCellName, CopyContents.ToString());
            }
            // Update cells and selection values.
            Update();
            GetSelectionValues(SpreadSheetPanel);

        }
        /// <summary>
        /// Event when delete option is clicked on the right-clikc menu.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Get selected cell's coordinates and name.
            SpreadSheetPanel.GetSelection(out CurrentColumn, out CurrentRow);

            

            Spreadsheet.SetContentsOfCell(CurrentCellName, "");
            // Set the displayed value and contents to ""
            SpreadSheetPanel.SetValue(CurrentColumn, CurrentRow, "");
            CellContentsField.Text = "";
            // Update cells and selection values.
            Update();
            GetSelectionValues(SpreadSheetPanel);

        }
    }
}
