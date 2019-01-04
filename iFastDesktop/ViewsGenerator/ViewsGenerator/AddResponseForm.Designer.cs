namespace ViewsGenerator
{
    partial class AddResponseForm
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
            this.groupBoxAddNewResponse = new System.Windows.Forms.GroupBox();
            this.textBoxDescription = new System.Windows.Forms.TextBox();
            this.labelDescription = new System.Windows.Forms.Label();
            this.comboBoxResponseType = new System.Windows.Forms.ComboBox();
            this.textBoxScope = new System.Windows.Forms.TextBox();
            this.textBoxFormat = new System.Windows.Forms.TextBox();
            this.textBoxVariableType = new System.Windows.Forms.TextBox();
            this.textBoxVariableName = new System.Windows.Forms.TextBox();
            this.labelResponseType = new System.Windows.Forms.Label();
            this.labelScope = new System.Windows.Forms.Label();
            this.labelFormat = new System.Windows.Forms.Label();
            this.labelVariableType = new System.Windows.Forms.Label();
            this.labelVariableName = new System.Windows.Forms.Label();
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.groupBoxAddNewResponse.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxAddNewResponse
            // 
            this.groupBoxAddNewResponse.Controls.Add(this.textBoxDescription);
            this.groupBoxAddNewResponse.Controls.Add(this.labelDescription);
            this.groupBoxAddNewResponse.Controls.Add(this.comboBoxResponseType);
            this.groupBoxAddNewResponse.Controls.Add(this.textBoxScope);
            this.groupBoxAddNewResponse.Controls.Add(this.textBoxFormat);
            this.groupBoxAddNewResponse.Controls.Add(this.textBoxVariableType);
            this.groupBoxAddNewResponse.Controls.Add(this.textBoxVariableName);
            this.groupBoxAddNewResponse.Controls.Add(this.labelResponseType);
            this.groupBoxAddNewResponse.Controls.Add(this.labelScope);
            this.groupBoxAddNewResponse.Controls.Add(this.labelFormat);
            this.groupBoxAddNewResponse.Controls.Add(this.labelVariableType);
            this.groupBoxAddNewResponse.Controls.Add(this.labelVariableName);
            this.groupBoxAddNewResponse.Location = new System.Drawing.Point(13, 24);
            this.groupBoxAddNewResponse.Name = "groupBoxAddNewResponse";
            this.groupBoxAddNewResponse.Size = new System.Drawing.Size(521, 237);
            this.groupBoxAddNewResponse.TabIndex = 0;
            this.groupBoxAddNewResponse.TabStop = false;
            this.groupBoxAddNewResponse.Text = "Response Definition";
            // 
            // textBoxDescription
            // 
            this.textBoxDescription.Location = new System.Drawing.Point(128, 64);
            this.textBoxDescription.Name = "textBoxDescription";
            this.textBoxDescription.Size = new System.Drawing.Size(387, 20);
            this.textBoxDescription.TabIndex = 3;
            // 
            // labelDescription
            // 
            this.labelDescription.AutoSize = true;
            this.labelDescription.Location = new System.Drawing.Point(6, 69);
            this.labelDescription.Name = "labelDescription";
            this.labelDescription.Size = new System.Drawing.Size(102, 13);
            this.labelDescription.TabIndex = 2;
            this.labelDescription.Text = "Variable description:";
            // 
            // comboBoxResponseType
            // 
            this.comboBoxResponseType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxResponseType.FormattingEnabled = true;
            this.comboBoxResponseType.Items.AddRange(new object[] {
            "response type #1 (Error Occurred)",
            "response type #2 (Data)"});
            this.comboBoxResponseType.Location = new System.Drawing.Point(128, 192);
            this.comboBoxResponseType.Name = "comboBoxResponseType";
            this.comboBoxResponseType.Size = new System.Drawing.Size(387, 21);
            this.comboBoxResponseType.TabIndex = 11;
            // 
            // textBoxScope
            // 
            this.textBoxScope.Location = new System.Drawing.Point(128, 160);
            this.textBoxScope.Name = "textBoxScope";
            this.textBoxScope.Size = new System.Drawing.Size(387, 20);
            this.textBoxScope.TabIndex = 9;
            // 
            // textBoxFormat
            // 
            this.textBoxFormat.Location = new System.Drawing.Point(128, 128);
            this.textBoxFormat.Name = "textBoxFormat";
            this.textBoxFormat.Size = new System.Drawing.Size(387, 20);
            this.textBoxFormat.TabIndex = 7;
            // 
            // textBoxVariableType
            // 
            this.textBoxVariableType.Location = new System.Drawing.Point(128, 96);
            this.textBoxVariableType.Name = "textBoxVariableType";
            this.textBoxVariableType.Size = new System.Drawing.Size(387, 20);
            this.textBoxVariableType.TabIndex = 5;
            // 
            // textBoxVariableName
            // 
            this.textBoxVariableName.Location = new System.Drawing.Point(128, 32);
            this.textBoxVariableName.Name = "textBoxVariableName";
            this.textBoxVariableName.Size = new System.Drawing.Size(387, 20);
            this.textBoxVariableName.TabIndex = 1;
            // 
            // labelResponseType
            // 
            this.labelResponseType.AutoSize = true;
            this.labelResponseType.Location = new System.Drawing.Point(6, 197);
            this.labelResponseType.Name = "labelResponseType";
            this.labelResponseType.Size = new System.Drawing.Size(81, 13);
            this.labelResponseType.TabIndex = 10;
            this.labelResponseType.Text = "Response type:";
            // 
            // labelScope
            // 
            this.labelScope.AutoSize = true;
            this.labelScope.Location = new System.Drawing.Point(6, 165);
            this.labelScope.Name = "labelScope";
            this.labelScope.Size = new System.Drawing.Size(41, 13);
            this.labelScope.TabIndex = 8;
            this.labelScope.Text = "Scope:";
            // 
            // labelFormat
            // 
            this.labelFormat.AutoSize = true;
            this.labelFormat.Location = new System.Drawing.Point(6, 133);
            this.labelFormat.Name = "labelFormat";
            this.labelFormat.Size = new System.Drawing.Size(42, 13);
            this.labelFormat.TabIndex = 6;
            this.labelFormat.Text = "Format:";
            // 
            // labelVariableType
            // 
            this.labelVariableType.AutoSize = true;
            this.labelVariableType.Location = new System.Drawing.Point(6, 101);
            this.labelVariableType.Name = "labelVariableType";
            this.labelVariableType.Size = new System.Drawing.Size(71, 13);
            this.labelVariableType.TabIndex = 4;
            this.labelVariableType.Text = "Variable type:";
            // 
            // labelVariableName
            // 
            this.labelVariableName.AutoSize = true;
            this.labelVariableName.Location = new System.Drawing.Point(6, 37);
            this.labelVariableName.Name = "labelVariableName";
            this.labelVariableName.Size = new System.Drawing.Size(77, 13);
            this.labelVariableName.TabIndex = 0;
            this.labelVariableName.Text = "Variable name:";
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(197, 271);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 1;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(279, 271);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 2;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // AddResponseForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(546, 307);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.groupBoxAddNewResponse);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddResponseForm";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Add New Response";
            this.groupBoxAddNewResponse.ResumeLayout(false);
            this.groupBoxAddNewResponse.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxAddNewResponse;
        private System.Windows.Forms.Label labelVariableType;
        private System.Windows.Forms.Label labelVariableName;
        private System.Windows.Forms.ComboBox comboBoxResponseType;
        private System.Windows.Forms.TextBox textBoxScope;
        private System.Windows.Forms.TextBox textBoxFormat;
        private System.Windows.Forms.TextBox textBoxVariableType;
        private System.Windows.Forms.TextBox textBoxVariableName;
        private System.Windows.Forms.Label labelResponseType;
        private System.Windows.Forms.Label labelScope;
        private System.Windows.Forms.Label labelFormat;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Label labelDescription;
        private System.Windows.Forms.TextBox textBoxDescription;
    }
}