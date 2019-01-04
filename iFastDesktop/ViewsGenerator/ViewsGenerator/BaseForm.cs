using System.Drawing;
using WeifenLuo.WinFormsUI.Docking;

namespace ViewsGenerator
{
    public class BaseForm : DockContent
    {
        public ModelDesktop DesktopModelObject { get; set; }
        public ModelProgress ProgressModelObject { get; set; }
        public IMainFormInterface MainFormInterface { get; set; }
        public string DataImplFolderPath { get; set; }
        public string ViewFolderPath { get; set; }
        public string JavaFolderPath { get; set; }
        public string GeneratedFilesOutputFolder { get; set; }

        public BaseForm()
        {
            this.MainFormInterface = null;
            this.ProgressModelObject = null;
            this.DesktopModelObject = null;
        }

        protected void OutputWindow_WriteLine(string line, Color? color = null)
        {
            this.MainFormInterface.OutputWindow_WriteLine(line, color);
        }

        protected void OutputWindow_WriteIndentedLine(string line, Color? color = null)
        {
            this.MainFormInterface.OutputWindow_WriteIndentedLine(line, color);
        }

        protected void OutputWindow_WriteEmptyLine()
        {
            this.MainFormInterface.OutputWindow_WriteEmptyLine();
        }
    }
}
