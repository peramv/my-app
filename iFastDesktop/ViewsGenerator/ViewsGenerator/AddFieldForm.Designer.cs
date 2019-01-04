namespace ViewsGenerator
{
    partial class AddFieldForm
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
            this.labelNewFieldName = new System.Windows.Forms.Label();
            this.textBoxNewFieldName = new System.Windows.Forms.TextBox();
            this.buttonNewFieldOK = new System.Windows.Forms.Button();
            this.buttonNewFieldCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelNewFieldName
            // 
            this.labelNewFieldName.AutoSize = true;
            this.labelNewFieldName.Location = new System.Drawing.Point(13, 19);
            this.labelNewFieldName.Name = "labelNewFieldName";
            this.labelNewFieldName.Size = new System.Drawing.Size(63, 13);
            this.labelNewFieldName.TabIndex = 0;
            this.labelNewFieldName.Text = "Field Name:";
            // 
            // textBoxNewFieldName
            // 
            this.textBoxNewFieldName.Location = new System.Drawing.Point(13, 40);
            this.textBoxNewFieldName.Name = "textBoxNewFieldName";
            this.textBoxNewFieldName.Size = new System.Drawing.Size(301, 20);
            this.textBoxNewFieldName.TabIndex = 1;
            // 
            // buttonNewFieldOK
            // 
            this.buttonNewFieldOK.Location = new System.Drawing.Point(87, 82);
            this.buttonNewFieldOK.Name = "buttonNewFieldOK";
            this.buttonNewFieldOK.Size = new System.Drawing.Size(75, 23);
            this.buttonNewFieldOK.TabIndex = 2;
            this.buttonNewFieldOK.Text = "OK";
            this.buttonNewFieldOK.UseVisualStyleBackColor = true;
            this.buttonNewFieldOK.Click += new System.EventHandler(this.buttonNewFieldOK_Click);
            // 
            // buttonNewFieldCancel
            // 
            this.buttonNewFieldCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonNewFieldCancel.Location = new System.Drawing.Point(169, 82);
            this.buttonNewFieldCancel.Name = "buttonNewFieldCancel";
            this.buttonNewFieldCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonNewFieldCancel.TabIndex = 3;
            this.buttonNewFieldCancel.Text = "Cancel";
            this.buttonNewFieldCancel.UseVisualStyleBackColor = true;
            // 
            // AddFieldForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.buttonNewFieldCancel;
            this.ClientSize = new System.Drawing.Size(327, 120);
            this.Controls.Add(this.buttonNewFieldCancel);
            this.Controls.Add(this.buttonNewFieldOK);
            this.Controls.Add(this.textBoxNewFieldName);
            this.Controls.Add(this.labelNewFieldName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddFieldForm";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Add New Field";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelNewFieldName;
        private System.Windows.Forms.TextBox textBoxNewFieldName;
        private System.Windows.Forms.Button buttonNewFieldOK;
        private System.Windows.Forms.Button buttonNewFieldCancel;
    }
}