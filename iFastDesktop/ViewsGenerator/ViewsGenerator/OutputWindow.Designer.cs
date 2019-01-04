namespace ViewsGenerator
{
    partial class OutputWindow
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
            this.richTextBoxOutputWindow = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // richTextBoxOutputWindow
            // 
            this.richTextBoxOutputWindow.BackColor = System.Drawing.Color.White;
            this.richTextBoxOutputWindow.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxOutputWindow.Location = new System.Drawing.Point(0, 0);
            this.richTextBoxOutputWindow.Name = "richTextBoxOutputWindow";
            this.richTextBoxOutputWindow.ReadOnly = true;
            this.richTextBoxOutputWindow.Size = new System.Drawing.Size(284, 262);
            this.richTextBoxOutputWindow.TabIndex = 0;
            this.richTextBoxOutputWindow.Text = "";
            this.richTextBoxOutputWindow.Click += new System.EventHandler(this.RichTextBoxOutputWindow_Click);
            this.richTextBoxOutputWindow.DoubleClick += new System.EventHandler(this.RichTextBoxOutputWindow_DoubleClick);
            // 
            // OutputWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.richTextBoxOutputWindow);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.HideOnClose = true;
            this.Name = "OutputWindow";
            this.Text = "Output Window";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBoxOutputWindow;
    }
}