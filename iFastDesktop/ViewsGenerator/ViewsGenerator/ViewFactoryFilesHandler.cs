using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ViewsGenerator.Templates.Progress;

namespace ViewsGenerator
{
    class ViewFactoryFilesHandler
    {
        public string ViewFolderPath { get; set; }
        public string ViewItemName { get; set; }
        public string ViewId { get; set; }
        public IMainFormInterface MainFormInterface { get; set; }
        public ModelProgress ProgressModelObject { get; set; }


        private ViewFactoryFilesHandler()
        {
            MainFormInterface = null;
            ProgressModelObject = null;
        }
        
        public ViewFactoryFilesHandler(string viewFolderPath, string viewItemName, string viewId)
        {
            ViewFolderPath = viewFolderPath;
            ViewItemName = viewItemName;
            ViewId = viewId;
            MainFormInterface = null;
            ProgressModelObject = null;
        }

        public void GenerateViewFactoryFiles()
        {
            if (MainFormInterface != null)
            {
                GenerateViewAPIHandlerFile();
                GenerateViewNASUHandlerFile();
            }
            else
            {
                Debug.Assert(MainFormInterface != null, "MainFormInterface is not initialized.");
            }
        }

        private void GenerateViewAPIHandlerFile()
        {
            string viewFileName = "VEWAPIHDL1.P";

            string fileFullPathName = ViewFolderPath + "\\" + viewFileName;

            if (File.Exists(fileFullPathName))
            {
                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where (line.Contains("*              Created.") || (line.Contains("end case.")))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 2)
                {
                    string smartViewFileName = "VEWZ" + ViewId + ".P";

                    // Generate business logic for transaction file
                    ViewAPIHandler_RuntimeTextTemplate page = new ViewAPIHandler_RuntimeTextTemplate();
                    page.ViewFileName = viewFileName;
                    page.ViewId = ViewId.ToString();
                    page.smartViewFileName = smartViewFileName;
                    page.lines = lines.ToList();
                    page.indexOfHistoryCommentLastLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfEndCaseLine = significantLines.ToList().ElementAt(1).Index;
                    String pageContent = page.TransformText().Replace("\r\n", "\n");
                    string strViewAPIHandlerFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewFileName.ToUpper();
                    System.IO.File.WriteAllText(strViewAPIHandlerFileName, pageContent);

                    MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strViewAPIHandlerFileName, Color.Green);
                }
            }
        }

        private void GenerateViewNASUHandlerFile()
        {
            string viewFileName = "VEWNASUHDL1.P";

            string fileFullPathName = ViewFolderPath + "\\" + viewFileName;

            if (File.Exists(fileFullPathName))
            {
                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where (line.Contains("*              Created.") || (line.Contains("end case.")))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 2)
                {
                    string smartViewFileName = "VEWZ" + ViewId + ".P";

                    // Generate business logic for transaction file
                    ViewNASUHandler_RuntimeTextTemplate page = new ViewNASUHandler_RuntimeTextTemplate();
                    page.ViewFileName = viewFileName;
                    page.ViewId = ViewId.ToString();
                    page.smartViewFileName = smartViewFileName;
                    page.lines = lines.ToList();
                    page.indexOfHistoryCommentLastLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfEndCaseLine = significantLines.ToList().ElementAt(1).Index;
                    String pageContent = page.TransformText().Replace("\r\n", "\n");
                    string strViewNASUHandlerFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewFileName.ToUpper();
                    System.IO.File.WriteAllText(strViewNASUHandlerFileName, pageContent);

                    MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strViewNASUHandlerFileName, Color.Green);
                }
            }
        }
    }
}
