using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace ViewsGenerator
{
    public partial class OutputWindow : DockContent
    {
        public OutputWindow()
        {
            InitializeComponent();
        }

        public void WriteLine(string line, Color? color = null)
        {
            this.richTextBoxOutputWindow.SelectionColor = color ?? Color.Black;
            this.richTextBoxOutputWindow.AppendText(line + Environment.NewLine);
            this.richTextBoxOutputWindow.ScrollToCaret();
        }

        public void WriteEmptyLine()
        {
            this.richTextBoxOutputWindow.AppendText(Environment.NewLine);
        }

        private void RichTextBoxOutputWindow_Click(object sender, EventArgs e)
        {
            int startIndex = richTextBoxOutputWindow.GetFirstCharIndexOfCurrentLine();
            int selectionLength = richTextBoxOutputWindow.Text.IndexOf('\n', startIndex) - startIndex;
            if (selectionLength > 0)
            {
                richTextBoxOutputWindow.Select(startIndex, selectionLength);
            }
        }

        private void RichTextBoxOutputWindow_DoubleClick(object sender, EventArgs e)
        {
            int startIndex = richTextBoxOutputWindow.GetFirstCharIndexOfCurrentLine();
            int selectionLength = richTextBoxOutputWindow.Text.IndexOf('\n', startIndex) - startIndex;
            if (selectionLength > 0)
            {
                richTextBoxOutputWindow.Select(startIndex, selectionLength);

                string filePath = richTextBoxOutputWindow.SelectedText;

                if (filePath.Contains("Generated file: "))
                {
                    filePath = filePath.Replace("Generated file: ", "").Trim();

                    if (File.Exists(filePath))
                    {
                        System.Diagnostics.Process.Start(filePath);
                    }
                }
            }
        }
    }
}
