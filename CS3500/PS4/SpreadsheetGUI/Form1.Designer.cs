namespace SpreadsheetGUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.CellContentsField = new System.Windows.Forms.TextBox();
            this.CellNameHeader = new System.Windows.Forms.Label();
            this.CellNameDisplayLabel = new System.Windows.Forms.Label();
            this.CellContentHeader = new System.Windows.Forms.Label();
            this.CellValueHeader = new System.Windows.Forms.Label();
            this.CellValueDisplayLabel = new System.Windows.Forms.Label();
            this.SpreadSheetPanel = new SS.SpreadsheetPanel();
            this.FileStrip = new System.Windows.Forms.MenuStrip();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.NewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.CopyPasteMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.FileStrip.SuspendLayout();
            this.CopyPasteMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // CellContentsField
            // 
            this.CellContentsField.Location = new System.Drawing.Point(216, 30);
            this.CellContentsField.Name = "CellContentsField";
            this.CellContentsField.Size = new System.Drawing.Size(126, 20);
            this.CellContentsField.TabIndex = 1;
            this.CellContentsField.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox1_KeyDown);
            // 
            // CellNameHeader
            // 
            this.CellNameHeader.AutoSize = true;
            this.CellNameHeader.Location = new System.Drawing.Point(12, 33);
            this.CellNameHeader.Name = "CellNameHeader";
            this.CellNameHeader.Size = new System.Drawing.Size(58, 13);
            this.CellNameHeader.TabIndex = 2;
            this.CellNameHeader.Text = "Cell Name:";
            // 
            // CellNameDisplayLabel
            // 
            this.CellNameDisplayLabel.AutoSize = true;
            this.CellNameDisplayLabel.Location = new System.Drawing.Point(76, 33);
            this.CellNameDisplayLabel.Name = "CellNameDisplayLabel";
            this.CellNameDisplayLabel.Size = new System.Drawing.Size(35, 13);
            this.CellNameDisplayLabel.TabIndex = 3;
            this.CellNameDisplayLabel.Text = "Name";
            // 
            // CellContentHeader
            // 
            this.CellContentHeader.AutoSize = true;
            this.CellContentHeader.Location = new System.Drawing.Point(134, 33);
            this.CellContentHeader.Name = "CellContentHeader";
            this.CellContentHeader.Size = new System.Drawing.Size(67, 13);
            this.CellContentHeader.TabIndex = 4;
            this.CellContentHeader.Text = "Cell Content:";
            // 
            // CellValueHeader
            // 
            this.CellValueHeader.AutoSize = true;
            this.CellValueHeader.Location = new System.Drawing.Point(348, 30);
            this.CellValueHeader.Name = "CellValueHeader";
            this.CellValueHeader.Size = new System.Drawing.Size(57, 13);
            this.CellValueHeader.TabIndex = 5;
            this.CellValueHeader.Text = "Cell Value:";
            // 
            // CellValueDisplayLabel
            // 
            this.CellValueDisplayLabel.AutoSize = true;
            this.CellValueDisplayLabel.Location = new System.Drawing.Point(411, 30);
            this.CellValueDisplayLabel.Name = "CellValueDisplayLabel";
            this.CellValueDisplayLabel.Size = new System.Drawing.Size(0, 13);
            this.CellValueDisplayLabel.TabIndex = 6;
            // 
            // SpreadSheetPanel
            // 
            this.SpreadSheetPanel.ContextMenuStrip = this.CopyPasteMenu;
            this.SpreadSheetPanel.Location = new System.Drawing.Point(1, 59);
            this.SpreadSheetPanel.Name = "SpreadSheetPanel";
            this.SpreadSheetPanel.Size = new System.Drawing.Size(811, 587);
            this.SpreadSheetPanel.TabIndex = 7;
            this.SpreadSheetPanel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.SpreadSheetPanel_MouseClick);
            // 
            // FileStrip
            // 
            this.FileStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.helpToolStripMenuItem});
            this.FileStrip.Location = new System.Drawing.Point(0, 0);
            this.FileStrip.Name = "FileStrip";
            this.FileStrip.Size = new System.Drawing.Size(812, 24);
            this.FileStrip.TabIndex = 14;
            this.FileStrip.Text = "FileStrip";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NewToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.helpToolStripMenuItem1,
            this.closeToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.helpToolStripMenuItem.Text = "File";
            // 
            // NewToolStripMenuItem
            // 
            this.NewToolStripMenuItem.Name = "NewToolStripMenuItem";
            this.NewToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.NewToolStripMenuItem.Text = "New";
            this.NewToolStripMenuItem.Click += new System.EventHandler(this.NewToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem1
            // 
            this.helpToolStripMenuItem1.Name = "helpToolStripMenuItem1";
            this.helpToolStripMenuItem1.Size = new System.Drawing.Size(152, 22);
            this.helpToolStripMenuItem1.Text = "Help";
            this.helpToolStripMenuItem1.Click += new System.EventHandler(this.helpToolStripMenuItem1_Click);
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // CopyPasteMenu
            // 
            this.CopyPasteMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.pasteToolStripMenuItem,
            this.deleteToolStripMenuItem});
            this.CopyPasteMenu.Name = "CopyPasteMenu";
            this.CopyPasteMenu.Size = new System.Drawing.Size(153, 92);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.copyToolStripMenuItem.Text = "Copy";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // pasteToolStripMenuItem
            // 
            this.pasteToolStripMenuItem.Name = "pasteToolStripMenuItem";
            this.pasteToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.pasteToolStripMenuItem.Text = "Paste";
            this.pasteToolStripMenuItem.Click += new System.EventHandler(this.pasteToolStripMenuItem_Click);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.ClientSize = new System.Drawing.Size(812, 641);
            this.Controls.Add(this.FileStrip);
            this.Controls.Add(this.SpreadSheetPanel);
            this.Controls.Add(this.CellValueDisplayLabel);
            this.Controls.Add(this.CellValueHeader);
            this.Controls.Add(this.CellContentHeader);
            this.Controls.Add(this.CellNameDisplayLabel);
            this.Controls.Add(this.CellNameHeader);
            this.Controls.Add(this.CellContentsField);
            this.MainMenuStrip = this.FileStrip;
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.FileStrip.ResumeLayout(false);
            this.FileStrip.PerformLayout();
            this.CopyPasteMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox CellContentsField;
        private System.Windows.Forms.Label CellNameHeader;
        private System.Windows.Forms.Label CellNameDisplayLabel;
        private System.Windows.Forms.Label CellContentHeader;
        private System.Windows.Forms.Label CellValueHeader;
        private System.Windows.Forms.Label CellValueDisplayLabel;
        private SS.SpreadsheetPanel SpreadSheetPanel;
        private System.Windows.Forms.MenuStrip FileStrip;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem NewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip CopyPasteMenu;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pasteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
    }
}

