namespace ViewsGenerator
{
    public partial class LanguagesEditor
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
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.dataGridViewLanguages = new System.Windows.Forms.DataGridView();
            this.LanguageId = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LanguageName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Country = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Language = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.labelLanguageConfiguration = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLanguages)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(209, 457);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 1;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.ButtonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(291, 457);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 2;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // dataGridViewLanguages
            // 
            this.dataGridViewLanguages.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewLanguages.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LanguageId,
            this.LanguageName,
            this.Country,
            this.Language});
            this.dataGridViewLanguages.Location = new System.Drawing.Point(12, 53);
            this.dataGridViewLanguages.Name = "dataGridViewLanguages";
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridViewLanguages.RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridViewLanguages.RowHeadersWidth = 61;
            this.dataGridViewLanguages.Size = new System.Drawing.Size(552, 392);
            this.dataGridViewLanguages.TabIndex = 0;
            // 
            // LanguageId
            // 
            this.LanguageId.HeaderText = "Language Id";
            this.LanguageId.MaxInputLength = 2;
            this.LanguageId.Name = "LanguageId";
            // 
            // LanguageName
            // 
            this.LanguageName.HeaderText = "Language Name";
            this.LanguageName.MaxInputLength = 50;
            this.LanguageName.Name = "LanguageName";
            this.LanguageName.Width = 227;
            // 
            // Country
            // 
            this.Country.HeaderText = "Country";
            this.Country.MaxInputLength = 2;
            this.Country.Name = "Country";
            this.Country.Width = 75;
            // 
            // Language
            // 
            this.Language.HeaderText = "Language";
            this.Language.MaxInputLength = 2;
            this.Language.Name = "Language";
            this.Language.Width = 70;
            // 
            // labelLanguageConfiguration
            // 
            this.labelLanguageConfiguration.AutoSize = true;
            this.labelLanguageConfiguration.Location = new System.Drawing.Point(13, 22);
            this.labelLanguageConfiguration.Name = "labelLanguageConfiguration";
            this.labelLanguageConfiguration.Size = new System.Drawing.Size(122, 13);
            this.labelLanguageConfiguration.TabIndex = 3;
            this.labelLanguageConfiguration.Text = "Language configuration:";
            // 
            // LanguagesEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(576, 495);
            this.Controls.Add(this.labelLanguageConfiguration);
            this.Controls.Add(this.dataGridViewLanguages);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LanguagesEditor";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Languages Editor";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewLanguages)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.DataGridView dataGridViewLanguages;
        private System.Windows.Forms.Label labelLanguageConfiguration;
        private System.Windows.Forms.DataGridViewTextBoxColumn LanguageId;
        private System.Windows.Forms.DataGridViewTextBoxColumn LanguageName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Country;
        private System.Windows.Forms.DataGridViewTextBoxColumn Language;
    }
}