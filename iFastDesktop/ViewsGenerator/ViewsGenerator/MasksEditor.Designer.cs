namespace ViewsGenerator
{
    partial class MasksEditor
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.dataGridViewMasks = new System.Windows.Forms.DataGridView();
            this.MaskId = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.MaskName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GroupId = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewMaskLanguages = new System.Windows.Forms.DataGridView();
            this.Language = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Mask = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.labelMasksList = new System.Windows.Forms.Label();
            this.labelMaskLanguageDefinitions = new System.Windows.Forms.Label();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMasks)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMaskLanguages)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.dataGridViewMasks, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.dataGridViewMaskLanguages, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelMasksList, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.labelMaskLanguageDefinitions, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.buttonOK, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.buttonCancel, 2, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1254, 594);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // dataGridViewMasks
            // 
            this.dataGridViewMasks.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewMasks.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.MaskId,
            this.MaskName,
            this.GroupId});
            this.dataGridViewMasks.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewMasks.Location = new System.Drawing.Point(3, 53);
            this.dataGridViewMasks.MultiSelect = false;
            this.dataGridViewMasks.Name = "dataGridViewMasks";
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewMasks.RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridViewMasks.RowHeadersWidth = 61;
            this.dataGridViewMasks.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewMasks.Size = new System.Drawing.Size(608, 488);
            this.dataGridViewMasks.TabIndex = 0;
            this.dataGridViewMasks.CellEndEdit += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewMasks_CellEndEdit);
            this.dataGridViewMasks.SelectionChanged += new System.EventHandler(this.DataGridViewMasks_SelectionChanged);
            // 
            // MaskId
            // 
            this.MaskId.HeaderText = "Mask Id";
            this.MaskId.Name = "MaskId";
            this.MaskId.Width = 70;
            // 
            // MaskName
            // 
            this.MaskName.HeaderText = "Mask Name";
            this.MaskName.Name = "MaskName";
            this.MaskName.Width = 377;
            // 
            // GroupId
            // 
            this.GroupId.HeaderText = "Group Id";
            this.GroupId.Name = "GroupId";
            this.GroupId.Width = 80;
            // 
            // dataGridViewMaskLanguages
            // 
            this.dataGridViewMaskLanguages.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewMaskLanguages.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Language,
            this.Mask});
            this.dataGridViewMaskLanguages.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridViewMaskLanguages.Location = new System.Drawing.Point(642, 53);
            this.dataGridViewMaskLanguages.Name = "dataGridViewMaskLanguages";
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewMaskLanguages.RowHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridViewMaskLanguages.RowHeadersWidth = 61;
            this.dataGridViewMaskLanguages.Size = new System.Drawing.Size(609, 488);
            this.dataGridViewMaskLanguages.TabIndex = 1;
            this.dataGridViewMaskLanguages.Leave += new System.EventHandler(this.DataGridViewMaskLanguages_Leave);
            // 
            // Language
            // 
            this.Language.HeaderText = "Language";
            this.Language.Name = "Language";
            this.Language.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.Language.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.Language.Width = 150;
            // 
            // Mask
            // 
            this.Mask.HeaderText = "Mask";
            this.Mask.Name = "Mask";
            this.Mask.Width = 378;
            // 
            // labelMasksList
            // 
            this.labelMasksList.AutoSize = true;
            this.labelMasksList.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelMasksList.Location = new System.Drawing.Point(3, 25);
            this.labelMasksList.Margin = new System.Windows.Forms.Padding(3, 25, 3, 0);
            this.labelMasksList.Name = "labelMasksList";
            this.labelMasksList.Size = new System.Drawing.Size(71, 15);
            this.labelMasksList.TabIndex = 2;
            this.labelMasksList.Text = "Masks list";
            // 
            // labelMaskLanguageDefinitions
            // 
            this.labelMaskLanguageDefinitions.AutoSize = true;
            this.labelMaskLanguageDefinitions.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelMaskLanguageDefinitions.Location = new System.Drawing.Point(644, 25);
            this.labelMaskLanguageDefinitions.Margin = new System.Windows.Forms.Padding(5, 25, 3, 0);
            this.labelMaskLanguageDefinitions.Name = "labelMaskLanguageDefinitions";
            this.labelMaskLanguageDefinitions.Size = new System.Drawing.Size(226, 15);
            this.labelMaskLanguageDefinitions.TabIndex = 3;
            this.labelMaskLanguageDefinitions.Text = "Mask per language definitions for:";
            // 
            // buttonOK
            // 
            this.buttonOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOK.Location = new System.Drawing.Point(539, 556);
            this.buttonOK.Margin = new System.Windows.Forms.Padding(3, 12, 0, 3);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 4;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.ButtonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(639, 556);
            this.buttonCancel.Margin = new System.Windows.Forms.Padding(0, 12, 3, 3);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 5;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // MasksEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1254, 594);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MasksEditor";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Masks Editor";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMasks)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewMaskLanguages)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataGridView dataGridViewMasks;
        private System.Windows.Forms.DataGridView dataGridViewMaskLanguages;
        private System.Windows.Forms.Label labelMasksList;
        private System.Windows.Forms.Label labelMaskLanguageDefinitions;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaskId;
        private System.Windows.Forms.DataGridViewTextBoxColumn MaskName;
        private System.Windows.Forms.DataGridViewTextBoxColumn GroupId;
        private System.Windows.Forms.DataGridViewComboBoxColumn Language;
        private System.Windows.Forms.DataGridViewTextBoxColumn Mask;
    }
}