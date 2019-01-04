namespace ViewsGenerator
{
    partial class SubstitutionSetsEditor
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.objectListViewSubstitutionSets = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnSubstitutionSetName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnSubstitutionSetLanguage = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnSubstitutiotnSetMarket = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnSubstitutiotnSetClient = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnSubstitutionSetId = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.dataGridViewSelectedSubstitutionSet = new System.Windows.Forms.DataGridView();
            this.ColumnKeys = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnValues = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.labelSubstitutionSets = new System.Windows.Forms.Label();
            this.labelSubstitutionSet = new System.Windows.Forms.Label();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonMoveUp = new System.Windows.Forms.Button();
            this.buttonMoveDown = new System.Windows.Forms.Button();
            this.buttonGenerateCode = new System.Windows.Forms.Button();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.contextMenuStripGridView = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewSubstitutionSets)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewSelectedSubstitutionSet)).BeginInit();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.contextMenuStripGridView.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.objectListViewSubstitutionSets, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.dataGridViewSelectedSubstitutionSet, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.labelSubstitutionSets, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelSubstitutionSet, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 2, 3);
            this.tableLayoutPanel1.Controls.Add(this.buttonGenerateCode, 2, 4);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 0, 3);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(889, 606);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // objectListViewSubstitutionSets
            // 
            this.objectListViewSubstitutionSets.AllColumns.Add(this.olvColumnSubstitutionSetName);
            this.objectListViewSubstitutionSets.AllColumns.Add(this.olvColumnSubstitutionSetLanguage);
            this.objectListViewSubstitutionSets.AllColumns.Add(this.olvColumnSubstitutiotnSetMarket);
            this.objectListViewSubstitutionSets.AllColumns.Add(this.olvColumnSubstitutiotnSetClient);
            this.objectListViewSubstitutionSets.AllColumns.Add(this.olvColumnSubstitutionSetId);
            this.objectListViewSubstitutionSets.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnSubstitutionSetName,
            this.olvColumnSubstitutionSetLanguage,
            this.olvColumnSubstitutiotnSetMarket,
            this.olvColumnSubstitutiotnSetClient,
            this.olvColumnSubstitutionSetId});
            this.objectListViewSubstitutionSets.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewSubstitutionSets.FullRowSelect = true;
            this.objectListViewSubstitutionSets.GridLines = true;
            this.objectListViewSubstitutionSets.Location = new System.Drawing.Point(3, 63);
            this.objectListViewSubstitutionSets.MultiSelect = false;
            this.objectListViewSubstitutionSets.Name = "objectListViewSubstitutionSets";
            this.objectListViewSubstitutionSets.Size = new System.Drawing.Size(423, 445);
            this.objectListViewSubstitutionSets.TabIndex = 0;
            this.objectListViewSubstitutionSets.TintSortColumn = true;
            this.objectListViewSubstitutionSets.UseCompatibleStateImageBehavior = false;
            this.objectListViewSubstitutionSets.View = System.Windows.Forms.View.Details;
            this.objectListViewSubstitutionSets.SelectedIndexChanged += new System.EventHandler(this.ObjectListViewSubstitutionSet_SelectionChanged);
            this.objectListViewSubstitutionSets.Enter += new System.EventHandler(this.ObjectListViewSubstitutionSet_Enter);
            this.objectListViewSubstitutionSets.Leave += new System.EventHandler(this.ObjectListViewSubstitutionSet_Leave);
            // 
            // olvColumnSubstitutionSetName
            // 
            this.olvColumnSubstitutionSetName.AspectName = "Name";
            this.olvColumnSubstitutionSetName.Text = "SubstitutionSetName";
            this.olvColumnSubstitutionSetName.Width = 250;
            // 
            // olvColumnSubstitutionSetLanguage
            // 
            this.olvColumnSubstitutionSetLanguage.AspectName = "Language";
            this.olvColumnSubstitutionSetLanguage.Sortable = false;
            this.olvColumnSubstitutionSetLanguage.Text = "Language";
            // 
            // olvColumnSubstitutiotnSetMarket
            // 
            this.olvColumnSubstitutiotnSetMarket.AspectName = "MarketName";
            this.olvColumnSubstitutiotnSetMarket.IsEditable = false;
            this.olvColumnSubstitutiotnSetMarket.Sortable = false;
            this.olvColumnSubstitutiotnSetMarket.Text = "Market";
            this.olvColumnSubstitutiotnSetMarket.Width = 80;
            // 
            // olvColumnSubstitutiotnSetClient
            // 
            this.olvColumnSubstitutiotnSetClient.AspectName = "ClientName";
            this.olvColumnSubstitutiotnSetClient.IsEditable = false;
            this.olvColumnSubstitutiotnSetClient.Sortable = false;
            this.olvColumnSubstitutiotnSetClient.Text = "Client";
            // 
            // olvColumnSubstitutionSetId
            // 
            this.olvColumnSubstitutionSetId.AspectName = "SubstitutionSetId";
            this.olvColumnSubstitutionSetId.FillsFreeSpace = true;
            this.olvColumnSubstitutionSetId.Text = "Substitution Set Id";
            this.olvColumnSubstitutionSetId.Width = 100;
            // 
            // dataGridViewSelectedSubstitutionSet
            // 
            this.dataGridViewSelectedSubstitutionSet.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewSelectedSubstitutionSet.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnKeys,
            this.ColumnValues});
            this.dataGridViewSelectedSubstitutionSet.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewSelectedSubstitutionSet.Location = new System.Drawing.Point(462, 63);
            this.dataGridViewSelectedSubstitutionSet.Name = "dataGridViewSelectedSubstitutionSet";
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewSelectedSubstitutionSet.RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridViewSelectedSubstitutionSet.RowHeadersWidth = 61;
            this.dataGridViewSelectedSubstitutionSet.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewSelectedSubstitutionSet.Size = new System.Drawing.Size(424, 445);
            this.dataGridViewSelectedSubstitutionSet.TabIndex = 1;
            this.dataGridViewSelectedSubstitutionSet.CellMouseDown += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridViewSelectedSubstitutionSet_CellMouseDown);
            this.dataGridViewSelectedSubstitutionSet.CellMouseUp += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridViewSelectedSubstitutionSet_CellMouseUp);
            this.dataGridViewSelectedSubstitutionSet.SelectionChanged += new System.EventHandler(this.DataGridViewSelectedSubstitutionSet_SelectionChanged);
            this.dataGridViewSelectedSubstitutionSet.KeyDown += new System.Windows.Forms.KeyEventHandler(this.dataGridViewSelectedSubstitutionSet_KeyDown);
            this.dataGridViewSelectedSubstitutionSet.Leave += new System.EventHandler(this.ObjectListViewSubstitutionSet_Leave);
            // 
            // ColumnKeys
            // 
            this.ColumnKeys.HeaderText = "Keys";
            this.ColumnKeys.Name = "ColumnKeys";
            this.ColumnKeys.Width = 250;
            // 
            // ColumnValues
            // 
            this.ColumnValues.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ColumnValues.HeaderText = "Values";
            this.ColumnValues.MinimumWidth = 100;
            this.ColumnValues.Name = "ColumnValues";
            this.ColumnValues.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // labelSubstitutionSets
            // 
            this.labelSubstitutionSets.AutoSize = true;
            this.labelSubstitutionSets.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSubstitutionSets.Location = new System.Drawing.Point(3, 36);
            this.labelSubstitutionSets.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.labelSubstitutionSets.Name = "labelSubstitutionSets";
            this.labelSubstitutionSets.Size = new System.Drawing.Size(113, 15);
            this.labelSubstitutionSets.TabIndex = 2;
            this.labelSubstitutionSets.Text = "Substitution sets";
            // 
            // labelSubstitutionSet
            // 
            this.labelSubstitutionSet.AutoSize = true;
            this.labelSubstitutionSet.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelSubstitutionSet.Location = new System.Drawing.Point(462, 36);
            this.labelSubstitutionSet.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.labelSubstitutionSet.Name = "labelSubstitutionSet";
            this.labelSubstitutionSet.Size = new System.Drawing.Size(114, 15);
            this.labelSubstitutionSet.TabIndex = 3;
            this.labelSubstitutionSet.Text = "Substitution set: ";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.buttonMoveUp, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.buttonMoveDown, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(462, 514);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 29F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(424, 29);
            this.tableLayoutPanel2.TabIndex = 4;
            // 
            // buttonMoveUp
            // 
            this.buttonMoveUp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonMoveUp.Location = new System.Drawing.Point(134, 3);
            this.buttonMoveUp.Name = "buttonMoveUp";
            this.buttonMoveUp.Size = new System.Drawing.Size(75, 23);
            this.buttonMoveUp.TabIndex = 0;
            this.buttonMoveUp.Text = "Move Up";
            this.buttonMoveUp.UseVisualStyleBackColor = true;
            this.buttonMoveUp.Click += new System.EventHandler(this.ButtonMoveUp_Click);
            // 
            // buttonMoveDown
            // 
            this.buttonMoveDown.Location = new System.Drawing.Point(215, 3);
            this.buttonMoveDown.Name = "buttonMoveDown";
            this.buttonMoveDown.Size = new System.Drawing.Size(75, 23);
            this.buttonMoveDown.TabIndex = 1;
            this.buttonMoveDown.Text = "Move Down";
            this.buttonMoveDown.UseVisualStyleBackColor = true;
            this.buttonMoveDown.Click += new System.EventHandler(this.ButtonMoveDown_Click);
            // 
            // buttonGenerateCode
            // 
            this.buttonGenerateCode.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonGenerateCode.Location = new System.Drawing.Point(597, 564);
            this.buttonGenerateCode.Name = "buttonGenerateCode";
            this.buttonGenerateCode.Size = new System.Drawing.Size(154, 23);
            this.buttonGenerateCode.TabIndex = 5;
            this.buttonGenerateCode.Text = "Generate Code ";
            this.buttonGenerateCode.UseVisualStyleBackColor = true;
            this.buttonGenerateCode.Click += new System.EventHandler(this.buttonGenerateCode_Click);
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.buttonAdd, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.buttonDelete, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 514);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 29F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(423, 29);
            this.tableLayoutPanel3.TabIndex = 6;
            // 
            // buttonAdd
            // 
            this.buttonAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAdd.Location = new System.Drawing.Point(133, 3);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 0;
            this.buttonAdd.Text = "Add";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(214, 3);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 1;
            this.buttonDelete.Text = "Delete";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // contextMenuStripGridView
            // 
            this.contextMenuStripGridView.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem3,
            this.toolStripMenuItem1,
            this.toolStripMenuItem2,
            this.toolStripSeparator1,
            this.toolStripMenuItem4});
            this.contextMenuStripGridView.Name = "contextMenuStripGridView";
            this.contextMenuStripGridView.Size = new System.Drawing.Size(145, 98);
            this.contextMenuStripGridView.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.ContextMenuStripGridView_ItemClicked);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.toolStripMenuItem3.Size = new System.Drawing.Size(144, 22);
            this.toolStripMenuItem3.Text = "Cut";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.toolStripMenuItem1.Size = new System.Drawing.Size(144, 22);
            this.toolStripMenuItem1.Text = "Copy";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.toolStripMenuItem2.Size = new System.Drawing.Size(144, 22);
            this.toolStripMenuItem2.Text = "Paste";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(141, 6);
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(144, 22);
            this.toolStripMenuItem4.Text = "Delete Row";
            // 
            // SubstitutionSetsEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(889, 606);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "SubstitutionSetsEditor";
            this.Text = "Substitution Sets Editor";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewSubstitutionSets)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewSelectedSubstitutionSet)).EndInit();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.contextMenuStripGridView.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private BrightIdeasSoftware.ObjectListView objectListViewSubstitutionSets;
        private BrightIdeasSoftware.OLVColumn olvColumnSubstitutionSetName;
        private BrightIdeasSoftware.OLVColumn olvColumnSubstitutionSetLanguage;
        private BrightIdeasSoftware.OLVColumn olvColumnSubstitutiotnSetMarket;
        private BrightIdeasSoftware.OLVColumn olvColumnSubstitutiotnSetClient;
        private System.Windows.Forms.DataGridView dataGridViewSelectedSubstitutionSet;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnKeys;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnValues;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripGridView;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.Label labelSubstitutionSets;
        private System.Windows.Forms.Label labelSubstitutionSet;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button buttonMoveUp;
        private System.Windows.Forms.Button buttonMoveDown;
        private BrightIdeasSoftware.OLVColumn olvColumnSubstitutionSetId;
        private System.Windows.Forms.Button buttonGenerateCode;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
    }
}