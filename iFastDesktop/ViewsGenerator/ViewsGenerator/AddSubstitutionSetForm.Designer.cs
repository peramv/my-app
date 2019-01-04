namespace ViewsGenerator
{
    partial class AddSubstitutionSetForm
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
            this.labelSubstitutionSetName = new System.Windows.Forms.Label();
            this.labelSubstitutionSetLanguage = new System.Windows.Forms.Label();
            this.labelMarket = new System.Windows.Forms.Label();
            this.labelClient = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBoxClient = new System.Windows.Forms.ComboBox();
            this.comboBoxMarket = new System.Windows.Forms.ComboBox();
            this.comboBoxLanguage = new System.Windows.Forms.ComboBox();
            this.textBoxNewSubstitutionSetName = new System.Windows.Forms.TextBox();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelSubstitutionSetName
            // 
            this.labelSubstitutionSetName.AutoSize = true;
            this.labelSubstitutionSetName.Location = new System.Drawing.Point(19, 68);
            this.labelSubstitutionSetName.Name = "labelSubstitutionSetName";
            this.labelSubstitutionSetName.Size = new System.Drawing.Size(111, 13);
            this.labelSubstitutionSetName.TabIndex = 0;
            this.labelSubstitutionSetName.Text = "Substitution set name:";
            // 
            // labelSubstitutionSetLanguage
            // 
            this.labelSubstitutionSetLanguage.AutoSize = true;
            this.labelSubstitutionSetLanguage.Location = new System.Drawing.Point(19, 105);
            this.labelSubstitutionSetLanguage.Name = "labelSubstitutionSetLanguage";
            this.labelSubstitutionSetLanguage.Size = new System.Drawing.Size(61, 13);
            this.labelSubstitutionSetLanguage.TabIndex = 1;
            this.labelSubstitutionSetLanguage.Text = "Language: ";
            // 
            // labelMarket
            // 
            this.labelMarket.AutoSize = true;
            this.labelMarket.Location = new System.Drawing.Point(19, 143);
            this.labelMarket.Name = "labelMarket";
            this.labelMarket.Size = new System.Drawing.Size(46, 13);
            this.labelMarket.TabIndex = 2;
            this.labelMarket.Text = "Market: ";
            // 
            // labelClient
            // 
            this.labelClient.AutoSize = true;
            this.labelClient.Location = new System.Drawing.Point(19, 181);
            this.labelClient.Name = "labelClient";
            this.labelClient.Size = new System.Drawing.Size(39, 13);
            this.labelClient.TabIndex = 3;
            this.labelClient.Text = "Client: ";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxClient);
            this.groupBox1.Controls.Add(this.comboBoxMarket);
            this.groupBox1.Controls.Add(this.comboBoxLanguage);
            this.groupBox1.Controls.Add(this.textBoxNewSubstitutionSetName);
            this.groupBox1.Location = new System.Drawing.Point(13, 32);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(455, 185);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Substitution Set Data";
            // 
            // comboBoxClient
            // 
            this.comboBoxClient.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxClient.FormattingEnabled = true;
            this.comboBoxClient.Location = new System.Drawing.Point(123, 140);
            this.comboBoxClient.Name = "comboBoxClient";
            this.comboBoxClient.Size = new System.Drawing.Size(316, 21);
            this.comboBoxClient.TabIndex = 3;
            // 
            // comboBoxMarket
            // 
            this.comboBoxMarket.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMarket.FormattingEnabled = true;
            this.comboBoxMarket.Location = new System.Drawing.Point(123, 102);
            this.comboBoxMarket.Name = "comboBoxMarket";
            this.comboBoxMarket.Size = new System.Drawing.Size(316, 21);
            this.comboBoxMarket.TabIndex = 2;
            this.comboBoxMarket.SelectedIndexChanged += new System.EventHandler(this.ComboBoxMarket_SelectedIndexChanged);
            // 
            // comboBoxLanguage
            // 
            this.comboBoxLanguage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxLanguage.FormattingEnabled = true;
            this.comboBoxLanguage.Location = new System.Drawing.Point(123, 64);
            this.comboBoxLanguage.Name = "comboBoxLanguage";
            this.comboBoxLanguage.Size = new System.Drawing.Size(316, 21);
            this.comboBoxLanguage.TabIndex = 1;
            this.comboBoxLanguage.SelectedIndexChanged += new System.EventHandler(this.ComboBoxLanguage_SelectedIndexChanged);
            // 
            // textBoxNewSubstitutionSetName
            // 
            this.textBoxNewSubstitutionSetName.Location = new System.Drawing.Point(123, 32);
            this.textBoxNewSubstitutionSetName.Name = "textBoxNewSubstitutionSetName";
            this.textBoxNewSubstitutionSetName.Size = new System.Drawing.Size(316, 20);
            this.textBoxNewSubstitutionSetName.TabIndex = 0;
            this.textBoxNewSubstitutionSetName.Leave += new System.EventHandler(this.TextBoxSubstitutionSetName_Leave);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(161, 234);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 5;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(243, 233);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 6;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // AddSubstitutionSetForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(480, 275);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.labelClient);
            this.Controls.Add(this.labelMarket);
            this.Controls.Add(this.labelSubstitutionSetLanguage);
            this.Controls.Add(this.labelSubstitutionSetName);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddSubstitutionSetForm";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Add Substitution Set Form";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelSubstitutionSetName;
        private System.Windows.Forms.Label labelSubstitutionSetLanguage;
        private System.Windows.Forms.Label labelMarket;
        private System.Windows.Forms.Label labelClient;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxClient;
        private System.Windows.Forms.ComboBox comboBoxMarket;
        private System.Windows.Forms.ComboBox comboBoxLanguage;
        private System.Windows.Forms.TextBox textBoxNewSubstitutionSetName;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
    }
}