using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using ViewsGenerator.Templates.Desktop;

namespace ViewsGenerator
{
    class GenerateMultipleDesktopViewsHandler
    {
        public ModelDesktop DesktopModelObject { get; set; }
        public IMainFormInterface MainFormInterface { get; set; }
        public string DataImplFolderPath { get; set; }

        public List<string> listOfFilesWithDataSetsWhereFieldIsUsed = null;
        public List<FieldItemLocationInfo> listOfWhereIsUsedFieldInfo = new List<FieldItemLocationInfo>();


        public GenerateMultipleDesktopViewsHandler()
        {
            this.MainFormInterface = null;
            this.DesktopModelObject = null;
        }

        public void GenerateFilesAffectedByFieldChange(string fieldName)
        {
            MainFormInterface.OutputWindow_WriteLine("---------- Generate Desktop files that contain modified field (" + fieldName + ") - START ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            listOfWhereIsUsedFieldInfo.Clear();

            foreach (string fileNameWithPath in listOfFilesWithDataSetsWhereFieldIsUsed)
            {
                string dataSetFileName = Path.GetFileName(fileNameWithPath);
                string dataSetItemName = GetDataSetItemNameBasedOnFileName(dataSetFileName);

                List<FieldItem> fieldItemList = GetFieldsFromFile(dataSetFileName);

                GenerateCodeForDataSet(dataSetItemName, dataSetFileName, fieldItemList);

                int viewNumber = FindDesktopViewNumber(dataSetFileName);

                FieldItemLocationInfo fieldLocationInfo = new FieldItemLocationInfo();
                fieldLocationInfo.ViewId = viewNumber;
                fieldLocationInfo.IndexOfFieldinView = fieldItemList.FindIndex(p => p.FieldName == fieldName);
                listOfWhereIsUsedFieldInfo.Add(fieldLocationInfo);
            }

            listOfFilesWithDataSetsWhereFieldIsUsed.Clear();

            MainFormInterface.OutputWindow_WriteLine("---------- Generate Desktop files that contain modified field (" + fieldName + ") - END ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            //GeneerateAllDesktopViews();
        }

        public void GeneerateAllDesktopViews()
        {
            MainFormInterface.OutputWindow_WriteLine("---------- Generate all Desktop view files - START ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            foreach (DataSetItem dataSetItemObject in DesktopModelObject.dataSetItemList)
            {
                string dataSetItemName = dataSetItemObject.DataSetItemName;
                string dataSetFileName = dataSetItemObject.DataSetItemFileName;

                List<FieldItem> fieldItemList = GetFieldsFromFile(dataSetFileName);

                GenerateCodeForDataSet(dataSetItemName, dataSetFileName, fieldItemList);
            }

            MainFormInterface.OutputWindow_WriteLine("---------- Generate all Desktop view files - END ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();
        }

        private void GenerateCodeForDataSet(string dataSetItemName, string dataSetFileName, List<FieldItem> fieldItemList)
        {
            MainFormInterface.OutputWindow_WriteLine(dataSetItemName + " - GENERATE CODE - START");

            // Generate data set files
            DseHpp_RuntimeTextTemplate page = new DseHpp_RuntimeTextTemplate();
            page.DataSetItemName = dataSetItemName;
            page.RepeatsFile = GetNameOfRepeatsFileIfApplicable(dataSetItemName, dataSetFileName);
            page.fieldItemList = fieldItemList;
            String pageContent = page.TransformText();
            string strDseHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dse_" + dataSetItemName.ToLower() + ".hpp";
            System.IO.File.WriteAllText(strDseHppFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strDseHppFileName, Color.Green);

            DsiCpp_RuntimeTextTemplate page1 = new DsiCpp_RuntimeTextTemplate();
            page1.DataSetItemName = dataSetItemName;
            page1.HeaderDataSetFileName = dataSetFileName.Replace("dse_dstc", "dsi_dstc").Replace(".hpp", ".h");
            page1.fieldItemList = fieldItemList;
            page1.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageContent1 = page1.TransformText();
            string strDsiCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + dataSetItemName.ToLower() + ".cpp";
            System.IO.File.WriteAllText(strDsiCppFileName, pageContent1);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strDsiCppFileName, Color.Green);

            DsiH_RuntimeTextTemplate page2 = new DsiH_RuntimeTextTemplate();
            page2.DataSetItemName = dataSetItemName;
            page2.fieldItemList = fieldItemList;
            String pageContent2 = page2.TransformText();
            string strDsiHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + dataSetItemName.ToLower() + ".h";
            System.IO.File.WriteAllText(strDsiHFileName, pageContent2);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strDsiHFileName, Color.Green);

            MainFormInterface.OutputWindow_WriteLine(dataSetItemName + " - GENERATE CODE - END");
            MainFormInterface.OutputWindow_WriteEmptyLine();
        }

        private string GetDataSetItemNameBasedOnFileName(string fileName)
        {
            string dataSetItemName = "";

            List<DataSetItem> matchesDataSetItemList = DesktopModelObject.dataSetItemList.Where(p => p.DataSetItemFileName == fileName).ToList();

            if (matchesDataSetItemList.Count() > 0)
            {
                dataSetItemName = matchesDataSetItemList[0].DataSetItemName;
            }

            return dataSetItemName;
        }

        private string GetDataSetType(string dataSetFileName)
        {
            string strDataSetType = "";

            if (dataSetFileName.Contains("vwrepeat_record."))
            {
                strDataSetType = "View Repeat Record";
            }
            else if (dataSetFileName.Contains("reqrepeat_record."))
            {
                strDataSetType = "Request Repeat Record";
            }
            else if (dataSetFileName.Contains("req."))
            {
                strDataSetType = "Request";
            }
            else if (dataSetFileName.Contains("vw."))
            {
                strDataSetType = "View";
            }

            return strDataSetType;
        }

        private string GetNameOfRepeatsFileIfApplicable(string dataSetItemName, string dataSetFileName)
        {
            string strRepeatsFile = "";

            string strDataSetType = GetDataSetType(dataSetFileName);

            if (strDataSetType != "" &&
                strDataSetType != "View Repeat Record" &&
                strDataSetType != "Request Repeat Record")
            {
                string strDataSetItemBase = "";
                string strRepeatsPath = "";

                if (dataSetItemName.Contains("_VW"))
                {
                    strDataSetItemBase = dataSetItemName.Replace("_VW", "");
                    strRepeatsPath = DataImplFolderPath + "\\" + "dse_" + strDataSetItemBase.ToLower() + "_vwrepeat_record" + ".hpp";
                }
                else if (dataSetItemName.Contains("_REQ"))
                {
                    strDataSetItemBase = dataSetItemName.Replace("_REQ", "");
                    strRepeatsPath = DataImplFolderPath + "\\" + "dse_" + strDataSetItemBase.ToLower() + "_reqrepeat_record" + ".hpp";
                }

                if (strRepeatsPath != "")
                {
                    if (File.Exists(strRepeatsPath))
                    {
                        strRepeatsFile = "dse_" + strDataSetItemBase.ToLower() + "_vwrepeat_record.hpp";
                    }
                }
            }

            return strRepeatsFile;
        }

        private List<FieldItem> GetFieldsFromFile(string dataSetFileName)
        {
            List<FieldItem> dataSetFieldItemList = new List<FieldItem>();

            string strFullFileNameWithPath = DataImplFolderPath + "\\" + dataSetFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = from file in Directory.EnumerateFiles(DataImplFolderPath, dataSetFileName, SearchOption.TopDirectoryOnly)
                            from line in File.ReadLines(file, Encoding.Default)
                            where (line.Contains("extern") && line.Contains("const") && !line.Contains("BFDataId"))
                            select new
                            {
                                File = file,
                                Line = line
                            };

                foreach (var line in lines)
                {
                    string fieldName = line.Line.Substring(line.Line.LastIndexOf(' ')).TrimStart().TrimEnd(';');

                    FieldItem fieldItemValue;
                    DesktopModelObject.fieldsDictionary.TryGetValue(fieldName, out fieldItemValue);

                    dataSetFieldItemList.Add(fieldItemValue);
                }
            }

            return dataSetFieldItemList;
        }

        private int FindDesktopViewNumber(string fileName)
        {
            string strDesktopViewNumber = new String(fileName.Where(Char.IsDigit).ToArray());

            int desktopViewNumber = -1;

            if (!String.IsNullOrEmpty(strDesktopViewNumber))
            {
                desktopViewNumber = Convert.ToInt32(strDesktopViewNumber);
            }

            return desktopViewNumber;
        }
    }
}
