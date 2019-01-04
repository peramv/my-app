using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;

namespace ViewsGenerator
{
    public class ModelProgress
    {
        public IMainFormInterface MainFormInterface { get; set; }
        public string ViewFolderPath { get; set; }
        public string JavaFolderPath { get; set; }
        public readonly string viewMapFileName = "ViewMap.txt";
        public readonly string packageXmlFileName = "package.xml";
        public readonly string responseTableCsvFile = "RespFieldTable.csv";
        public readonly string transactionTableCsvFile = "TransFieldTable.csv";
        public List<ViewDataSetItem> viewDataSetItemList = new List<ViewDataSetItem>();
        public List<TransactionItem> transactionItemList = new List<TransactionItem>();
        public List<TransactionItem> distinctTransactionItemList = new List<TransactionItem>();
        public List<ResponseItem> responseItemList = new List<ResponseItem>();
        public List<ResponseItem> distinctResponseItemList = new List<ResponseItem>();
        public Dictionary<string, List<ResponseItem>> responseItemListsOfGeneratedResponseViewsDictionary = new Dictionary<string, List<ResponseItem>>();
        public Dictionary<string, ViewMapItem> viewMapItemDictionary = new Dictionary<string, ViewMapItem>();
        //public List<string> viewIdsToBuildJavaClassesList = new List<string>();         // Not used for now for code generation, it should be used only in Java APIs build
        public List<ResponseFieldTableItem> responseFieldTableItemsList = new List<ResponseFieldTableItem>();
        public List<TransactionFieldTableItem> transactionFieldTableItemsList = new List<TransactionFieldTableItem>();


        public ModelProgress()
        {
            this.MainFormInterface = null;
            this.ViewFolderPath = string.Empty;
            this.JavaFolderPath = string.Empty;
        }

        public async void LoadData()
        {
            if (String.IsNullOrEmpty(ViewFolderPath))
            {
                MessageBox.Show("Path to \"view\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // Must be synchronous, it creates the view map dictionary
            //LoadViewMap();    // Needed only for CONVERSION 
            LoadTransactionProperties();

            //await Task.Run(() => LoadPackageXml());                   // Not used for now for code generation
            //await Task.Run(() => LoadTransactionProperties());
            await Task.Run(() => LoadResponseProperties());
            //await Task.Run(() => LoadResponseFieldTable());          // Needed only for CONVERSION
            //await Task.Run(() => LoadTransactionsFieldTable());    // Needed only for CONVERSION

            MainFormInterface.EnableLoadViewDataButton();
        }

        private async void LoadTransactionProperties()
        {
            this.transactionItemList.Clear();

            if (Directory.Exists(ViewFolderPath))
            {
                List<FileAndLineHelper> lines = (from file in Directory.EnumerateFiles(ViewFolderPath, "*.I", SearchOption.TopDirectoryOnly)
                                        where (file.Contains("VEWR") && !file.Contains("REPLV") && !file.Contains("WRTSHD"))
                                        from line in File.ReadLines(file, Encoding.Default)
                                        where (line.TrimStart().StartsWith("define") || line.TrimStart().StartsWith("format") ||
                                               // In the new implementation of transaction files all descriptions data are embedded in a transaction file, so read it from file.
                                               line.TrimStart().StartsWith("* View Id:") || line.TrimStart().StartsWith("* View name:") || line.TrimStart().StartsWith("* View description:") || line.TrimStart().StartsWith("/* Section ID:"))
                                        select new FileAndLineHelper
                                        {
                                            File = file,
                                            Line = line
                                        }).ToList();

                CreateViewMapFromLoadedLines(lines);          // Disable this line when converting files to create descriptions the first time
                await Task.Run(() => CreateTransactionFieldTableItemsList(lines));
                await Task.Run(() => CreateTransactionItemListFromLoadedLines(lines));
            }
        }

        private void CreateViewMapFromLoadedLines(List<FileAndLineHelper> lines)
        {
            viewMapItemDictionary.Clear();

            for (int i = 0; i < lines.Count(); i++)
            {
                if (lines[i].Line.Contains("* View Id:"))
                {
                    ViewMapItem viewMapItem = new ViewMapItem();
                    viewMapItem.isValid = true;
                    viewMapItem.isNewView = false;

                    string[] resultViewId = lines[i].Line.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

                    if (resultViewId.Count() == 2)
                    {
                        viewMapItem.ViewId = resultViewId[1].Trim();
                    }
                    else
                    {
                        MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    i++;

                    if (lines[i].Line.Contains("* View name:"))
                    {
                        string[] resultViewName = lines[i].Line.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

                        if (resultViewName.Count() == 2)
                        {
                            viewMapItem.ViewName = resultViewName[1].Trim();
                        }
                        else
                        {
                            MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }

                        i++;
                    }

                    if (lines[i].Line.Contains("* View description:"))
                    {
                        string[] resultViewDescription = lines[i].Line.Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);

                        if (resultViewDescription.Count() == 2)
                        {
                            viewMapItem.ViewDescription = resultViewDescription[1].Trim();
                        }
                        else
                        {
                            MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }
                    }

                    viewMapItemDictionary[viewMapItem.ViewId] = viewMapItem;
                }
            }
        }

        private void CreateTransactionFieldTableItemsList(List<FileAndLineHelper> lines)
        {
            transactionFieldTableItemsList.Clear();

            for (int i = 0; i < lines.Count(); i++)
            {
                if (lines[i].Line.Contains("/* Section ID:"))
                {
                    string line = lines[i].Line.Replace("/*", "").Replace("*/", "");

                    string[] result = line.Split(new string[] { ":", "," }, StringSplitOptions.RemoveEmptyEntries);

                    if (result.Count() == 10)
                    {
                        TransactionFieldTableItem transactionFieldTableItem = new TransactionFieldTableItem();

                        transactionFieldTableItem.SectionId = result[1].Trim();
                        transactionFieldTableItem.FieldId = result[3].Trim();
                        transactionFieldTableItem.FieldName = result[5].Trim();
                        transactionFieldTableItem.FieldDescription = result[7].Trim();
                        transactionFieldTableItem.ViewId = result[9].Trim();

                        transactionFieldTableItemsList.Add(transactionFieldTableItem);
                    }
                }
            }
        }

        private void CreateTransactionItemListFromLoadedLines(List<FileAndLineHelper> lines)
        {
            string[] stringSeparators = new string[] { "define {*}", " variable ", " as " };

            for (int i = 0; i < lines.Count(); i++)
            {
                TransactionItem transactionItem = new TransactionItem();

                transactionItem.ViewId = Path.GetFileName(lines[i].File).Replace("VEWR", "").Replace(".I", "");

                if (lines[i].Line.TrimStart().StartsWith("define"))
                {
                    string[] resultDefine = lines[i].Line.Split(stringSeparators, StringSplitOptions.RemoveEmptyEntries);

                    if (resultDefine.Count() == 3)
                    {
                        transactionItem.Scope = resultDefine[0].Trim();
                        transactionItem.TransactionVariableName = resultDefine[1].Trim();
                        transactionItem.TransactionVariableTypeDeclaration = resultDefine[2].Trim().TrimEnd('.');
                    }
                    else
                    {
                        MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }

                    if (lines[i + 1].Line.Contains("format"))
                    {
                        string[] resultFormat = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                        if (resultFormat.Count() == 2)
                        {
                            transactionItem.Format = resultFormat[1].Trim().TrimEnd('.');
                        }
                        else
                        {
                            MessageBox.Show("File: " + lines[i + 1].File + ", Line invalid format: \n" + lines[i + 1].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }

                        i++;
                    }

                    transactionItemList.Add(transactionItem);
                }
            }

            distinctTransactionItemList = transactionItemList.GroupBy(x => x.TransactionVariableName).Select(o => o.First()).OrderBy(x => x.TransactionVariableName).ToList();
        }

        private void LoadResponseProperties()
        {
            responseItemList.Clear();

            if (Directory.Exists(ViewFolderPath))
            {
                List<FileAndLineHelper> lines = (from file in Directory.EnumerateFiles(ViewFolderPath, "*.I", SearchOption.TopDirectoryOnly)
                                        where file.Contains("VEWP")
                                        from line in File.ReadLines(file, Encoding.Default)
                                        where (line.TrimStart().StartsWith("define") || line.TrimStart().StartsWith("format") || line.Contains("response type #1") || line.Contains("response type #2") ||
                                        // In the new implementation of transaction files all descriptions data are embedded in a transaction file, so read it from file.
                                        line.TrimStart().StartsWith("* View Id:") || line.TrimStart().StartsWith("* View name:") || line.TrimStart().StartsWith("* View description:") || line.TrimStart().StartsWith("/* Section ID:"))
                                        select new FileAndLineHelper
                                        {
                                            File = file,
                                            Line = line,
                                        }).ToList();

                CreateResponseFieldTableItemsList(lines);
                CreateResponseItemListFromLoadedLines(lines);
            }
        }

        private void CreateResponseFieldTableItemsList(List<FileAndLineHelper> lines)
        {
            responseFieldTableItemsList.Clear();

            for (int i = 0; i < lines.Count(); i++)
            {
                if (lines[i].Line.Contains("/* Section ID:"))
                {
                    string line = lines[i].Line.Replace("/*", "").Replace("*/", "");

                    string[] result = line.Split(new string[] { ":", "," }, StringSplitOptions.RemoveEmptyEntries);

                    if (result.Count() == 12)
                    {
                        ResponseFieldTableItem responseFieldTableItem = new ResponseFieldTableItem();

                        responseFieldTableItem.SectionId = result[1].Trim();
                        responseFieldTableItem.FieldId = result[3].Trim();
                        responseFieldTableItem.FieldName = result[5].Trim();
                        responseFieldTableItem.FieldDescription = result[7].Trim();
                        responseFieldTableItem.ViewId = result[9].Trim();
                        responseFieldTableItem.ResponseType = result[11].Trim();

                        responseFieldTableItemsList.Add(responseFieldTableItem);
                    }
                }
            }
        }

        private void CreateResponseItemListFromLoadedLines(List<FileAndLineHelper> lines)
        {
            string[] stringSeparators = new string[] { "define {*}", " variable ", " as " };

            string strResponseType = "";

            for (int i = 0; i < lines.Count(); i++)
            {
                if (lines[i].Line.Contains("response type #1"))
                {
                    strResponseType = "response type #1";
                }
                else if (lines[i].Line.Contains("response type #2"))
                {
                    strResponseType = "response type #2";
                }
                else
                {
                    ResponseItem responseItem = new ResponseItem();

                    responseItem.ViewId = Path.GetFileName(lines[i].File).Replace("VEWP", "").Replace(".I", "");

                    if (lines[i].Line.TrimStart().StartsWith("define"))
                    {
                        string[] resultDefine = lines[i].Line.Split(stringSeparators, StringSplitOptions.RemoveEmptyEntries);

                        if (resultDefine.Count() == 3)
                        {
                            responseItem.Scope = resultDefine[0].Trim();
                            responseItem.ResponseVariableName = resultDefine[1].Trim();
                            responseItem.ResponseVariableTypeDeclaration = resultDefine[2].Trim().TrimEnd('.');
                            responseItem.ResponseType = strResponseType;
                        }
                        else
                        {
                            MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }

                        if (lines[i + 1].Line.Contains("format"))
                        {
                            string[] resultFormat = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                            if (resultFormat.Count() == 2)
                            {
                                responseItem.Format = resultFormat[1].Trim().TrimEnd('.');
                            }
                            else
                            {
                                MessageBox.Show("File: " + lines[i + 1].File + ", Line invalid format: \n" + lines[i + 1].Line, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }

                            i++;
                        }

                        responseItemList.Add(responseItem);
                    }
                }
            }

            distinctResponseItemList = responseItemList.GroupBy(x => x.ResponseVariableName).Select(o => o.First()).OrderBy(x => x.ResponseVariableName).ToList();
        }

        private void LoadViewMap()
        {
            viewMapItemDictionary.Clear();

            if (String.IsNullOrEmpty(JavaFolderPath))
            {
                MessageBox.Show("Path to \"java\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string viewMapFullFilePath = GetViewMapPathAndFileName();

            if (File.Exists(viewMapFullFilePath))
            {
                string[] lines = File.ReadAllLines(viewMapFullFilePath, Encoding.Default);

                foreach (string line in lines)
                {
                    string[] lineArray = line.Split(':');

                    if (lineArray.Count() == 3)
                    {
                        ViewMapItem viewMapItem = new ViewMapItem();

                        viewMapItem.ViewId = lineArray[0].Trim();
                        viewMapItem.ViewName = lineArray[1].Trim();
                        viewMapItem.ViewDescription = lineArray[2].Trim();
                        viewMapItem.isNewView = false;
                        viewMapItem.isValid = false;

                        viewMapItemDictionary[viewMapItem.ViewId] = viewMapItem;
                    }
                }
            }
        }

        //private void LoadPackageXml()
        //{
        //    viewIdsToBuildJavaClassesList.Clear();

        //    string pathAndFileName = GetPackageXmlPathAndFileName();

        //    if (File.Exists(pathAndFileName))
        //    {
        //        try
        //        {
        //            XDocument xDoc = XDocument.Load(pathAndFileName);

        //            var views = xDoc.Descendants("TargetPackage").Where(x => x.Attribute("name").Value == "SSII_JavaAPI").Descendants("View");

        //            foreach (var view in views)
        //            {
        //                string viewId = view.Value;

        //                viewIdsToBuildJavaClassesList.Add(viewId);
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            MessageBox.Show("An error occurred while loading package xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        //        }
        //    }
        //    else
        //    {
        //        MessageBox.Show("Package XML file doesn't exist in the specified location.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        //    }
        //}

        private void LoadResponseFieldTable()
        {
            responseFieldTableItemsList.Clear();

            string responseDataTablePathAndFileName = JavaFolderPath + "\\" + responseTableCsvFile;

            if (File.Exists(responseDataTablePathAndFileName))
            {
                var lines = File.ReadAllLines(responseDataTablePathAndFileName, Encoding.Default).Skip(1);

                foreach (var line in lines)
                {
                    string[] responseColumns = line.Split('|');

                    if (responseColumns.Count() == 6)
                    { 
                        ResponseFieldTableItem responseFieldTableItem = new ResponseFieldTableItem();

                        responseFieldTableItem.ViewId = responseColumns[0];
                        responseFieldTableItem.ResponseType = responseColumns[1];
                        responseFieldTableItem.SectionId = responseColumns[2];
                        responseFieldTableItem.FieldId = responseColumns[3];
                        responseFieldTableItem.FieldDescription = responseColumns[4];
                        responseFieldTableItem.FieldName = responseColumns[5];

                        responseFieldTableItemsList.Add(responseFieldTableItem);
                    }
                }
            }
            else
            {
                MessageBox.Show("Package \"RespFieldTable.csv\" file doesn't exist in java folder path.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void LoadTransactionsFieldTable()
        {
            transactionFieldTableItemsList.Clear();

            string transactionsDataTablePathAndFileName = JavaFolderPath + "\\" + transactionTableCsvFile;

            if (File.Exists(transactionsDataTablePathAndFileName))
            {
                var lines = File.ReadAllLines(transactionsDataTablePathAndFileName, Encoding.Default).Skip(1);

                foreach (var line in lines)
                {
                    string[] transactionColumns = line.Split('|');

                    if (transactionColumns.Count() == 5)
                    {
                        TransactionFieldTableItem transactionFieldTableItem = new TransactionFieldTableItem();

                        transactionFieldTableItem.ViewId = transactionColumns[0];
                        transactionFieldTableItem.SectionId = transactionColumns[1];
                        transactionFieldTableItem.FieldId = transactionColumns[2];
                        transactionFieldTableItem.FieldDescription = transactionColumns[3];
                        transactionFieldTableItem.FieldName = transactionColumns[4];

                        transactionFieldTableItemsList.Add(transactionFieldTableItem);
                    }
                }
            }
            else
            {
                MessageBox.Show("Package \"TransFieldTable.csv\" file doesn't exist in Java folder path.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public string GetPackageXmlPathAndFileName()
        {
            return JavaFolderPath + "\\" + packageXmlFileName;
        }

        public string GetViewMapPathAndFileName()
        {
            return JavaFolderPath + "\\" + viewMapFileName;
        }

        public List<TransactionFieldTableItem> GetTransactionFieldTableItemListForGivenView(string viewId)
        {
            List<TransactionFieldTableItem> transactionFieldTableItemsForView = transactionFieldTableItemsList.Where(x => x.ViewId.Equals(viewId)).ToList();

            return transactionFieldTableItemsForView;
        }

        public Tuple<List<ResponseItem>, List<ResponseItem>> GetResponseItemListsGroupedByResponseTypeForGivenViewId(string viewId)
        {
            List<ResponseItem> responseType1ItemList = responseItemList.Where(x => x.ViewId.Equals(viewId) && x.ResponseType == "response type #1").ToList();
            List<ResponseItem> responseType2ItemList = responseItemList.Where(x => x.ViewId.Equals(viewId) && x.ResponseType == "response type #2").ToList();

            return new Tuple<List<ResponseItem>, List<ResponseItem>>(responseType1ItemList, responseType2ItemList);
        }

        public List<ResponseFieldTableItem> GetListOfResponseFieldItemsForViewId(string viewId)
        {
            List<ResponseFieldTableItem> responseFieldsList = new List<ResponseFieldTableItem>();

            responseFieldsList = responseFieldTableItemsList.Where(x => x.ViewId.Equals(viewId)).ToList();

            return responseFieldsList;
        }

        public int GetMaxExistingSectionId()
        {
            int sectionId = responseFieldTableItemsList.Where(x => x.SectionId != "").Max(x => Convert.ToInt32(x.SectionId));

            return sectionId;
        }

        public int GetMaxExistingFieldId()
        {
            int fieldId = responseFieldTableItemsList.Where(x => x.FieldId != "").Max(x => Convert.ToInt32(x.FieldId));

            return fieldId;
        }                                                                

        public ResponseFieldTableItem GetResponseFieldItemWithName(string fieldName)
        {
            ResponseFieldTableItem responseFieldItem = null;

            bool exists = responseFieldTableItemsList.Any(x => x.FieldName.Equals(fieldName));

            if (exists)
            {
                responseFieldItem = responseFieldTableItemsList.First(x => x.FieldName.Equals(fieldName));
            }

            return responseFieldItem;
        }

        public TransactionFieldTableItem GetTransactionFieldItemWithName(string fieldName)
        {
            TransactionFieldTableItem transactionFieldItem = null;

            bool exists = transactionFieldTableItemsList.Any(x => x.FieldName.Equals(fieldName));

            if (exists)
            {
                transactionFieldItem = transactionFieldTableItemsList.First(x => x.FieldName.Equals(fieldName));
            }

            return transactionFieldItem;
        }

        public ResponseFieldTableItem GetResponseFieldItemWithNameAndViewId(string viewId, string fieldName)
        {
            ResponseFieldTableItem responseFieldItem = null;

            bool exists = responseFieldTableItemsList.Any(x => x.ViewId.Equals(viewId) && x.FieldName.Equals(fieldName));

            if (exists)
            {
                responseFieldItem = responseFieldTableItemsList.First(x => x.ViewId.Equals(viewId) && x.FieldName.Equals(fieldName));
            }

            return responseFieldItem;
        }

        public List<ResponseFieldTableItem> GetResponseFieldTableItemListForGivenView(string viewId)
        {
            List<ResponseFieldTableItem> responseFieldTableItemsForView = responseFieldTableItemsList.Where(x => x.ViewId.Equals(viewId)).ToList();

            return responseFieldTableItemsForView;
        }

        public List<ResponseItem> GetListOfCharacterAndLogicalNoUndoResponseItems()
        {
            List<ResponseItem> logicalNoUndoYesNoResponseItemList = new List<ResponseItem>();

            string variableTypeLogical = "logical no-undo";
            string formatLogical = "'Yes/No'.";
            string variableTypeCharacter = "character no-undo";
            string formatCharacter = "'x(60)'.";

            logicalNoUndoYesNoResponseItemList = responseItemList.Where(x => (x.ResponseVariableTypeDeclaration.Equals(variableTypeLogical) && x.Format.Equals(formatLogical)) ||
                                                                             (x.ResponseVariableTypeDeclaration.Equals(variableTypeCharacter) && x.Format.Equals(formatCharacter))).ToList();

            return logicalNoUndoYesNoResponseItemList;
        }

        public List<TransactionFieldTableItem> GetListOfTransactionFieldItemsForViewId(string viewId)
        {
            List<TransactionFieldTableItem> transactionFieldsList = new List<TransactionFieldTableItem>();

            transactionFieldsList = transactionFieldTableItemsList.Where(x => x.ViewId.Equals(viewId)).ToList();

            return transactionFieldsList;
        }

        public List<ResponseItem> GetResponseItemListForSelectedView(string viewId)
        {
            List<ResponseItem> responseItemList = new List<ResponseItem>();

            // This dictionary is generated only after Generate button is pressed in Response Editor.
            responseItemListsOfGeneratedResponseViewsDictionary.TryGetValue(viewId, out responseItemList);

            return responseItemList;
        }

        public ResultCodeEnum IsVariableUsedInTransactionFiles(string variableName)
        {
            if (String.IsNullOrEmpty(ViewFolderPath))
            {
                return ResultCodeEnum.FolderPathIsNotDefined;
            }

            if (Directory.Exists(ViewFolderPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, "*.I", SearchOption.TopDirectoryOnly)
                             where (file.Contains("VEWR") && !file.Contains("REPLV") && !file.Contains("WRTSHD"))
                             from line in File.ReadLines(file, Encoding.Default)
                             where (line.TrimStart().StartsWith("define") && line.Contains("variable " + variableName))
                             select new
                             {
                                 File = file,
                                 Line = line,
                             }).ToList();

                if (lines.Count() > 0)
                {
                    return ResultCodeEnum.ItemIsUsedInFiles;
                }
            }
            else
            {
                return ResultCodeEnum.FolderDoesntExist;
            }

            return ResultCodeEnum.ResultIsOK;
        }

        public ResultCodeEnum IsVariableUsedInResponseFiles(string variableName)
        {
            if (String.IsNullOrEmpty(ViewFolderPath))
            {
                return ResultCodeEnum.FolderPathIsNotDefined;
            }

            if (Directory.Exists(ViewFolderPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, "*.I", SearchOption.TopDirectoryOnly)
                             where file.Contains("VEWP")
                             from line in File.ReadLines(file, Encoding.Default)
                             where (line.TrimStart().StartsWith("define") && line.Contains("variable " + variableName))
                             select new
                             {
                                 File = file,
                                 Line = line,
                             }).ToList();

                if (lines.Count() > 0)
                {
                    return ResultCodeEnum.ItemIsUsedInFiles;
                }
            }
            else
            {
                return ResultCodeEnum.FolderDoesntExist;
            }

            return ResultCodeEnum.ResultIsOK;
        }

        public string GetProgressFieldTypeFormat(FieldItem fieldItem)
        {
            string progressFieldTypeFormat = "";

            if (fieldItem.FieldType.Contains("Text"))
            {
                progressFieldTypeFormat = "'x(" + fieldItem.FieldLength + ")'";
            }
            else if (fieldItem.FieldType == "BFNumericField" ||
                     fieldItem.FieldType == "BFDecimalField")
            {
                progressFieldTypeFormat = "'->,>>>,>>>,>>>,>>9.9999999999'";
            }
            else if (fieldItem.FieldType == "BFIntegerField")
            {
                progressFieldTypeFormat = "'->,>>>,>>>,>>9'";
            }
            else if (fieldItem.FieldType == "BFTimeField")
            {
                progressFieldTypeFormat = "'99/99/9999'";
            }

            return progressFieldTypeFormat;
        }

        // Not used in the new Progress files format with descriptions
        //public void AddNewViewToViewMap(string viewId, string viewName, string viewDescription)
        //{
        //    if (!viewMapItemDictionary.ContainsKey(viewId))
        //    {
        //        ViewMapItem viewMapItem = new ViewMapItem();
        //        viewMapItem.ViewId = viewId;
        //        viewMapItem.ViewName = viewName;
        //        viewMapItem.ViewDescription = viewDescription;
        //        viewMapItem.isNewView = true;

        //        viewMapItemDictionary[viewId] = viewMapItem;

        //        string viewMapFullFilePath = GetViewMapPathAndFileName();
        //        string newLine = viewId + ":" + viewName + ":" + viewDescription;

        //        File.AppendAllLines(viewMapFullFilePath, new string[] { newLine });
        //    }
        //}

        //// Views which only exist in ViewMap.txt, but there are not actual files (Progress, Java, html, jsp) are not valid.
        //// This should happen only during testing or if something goes wrong during new view creation.
        //public void RemoveInvalidViewsFromViewMap()
        //{
        //    // Filter out invalid view items only where viewId > 466
        //    List<ViewMapItem> sortedValidViewItems = viewMapItemDictionary.Where(x => Convert.ToInt32(x.Key) <= 466 || x.Value.isValid == true).OrderBy(x => Convert.ToInt32(x.Key)).Select(x => x.Value).ToList();

        //    List<string> lines = new List<string>();

        //    foreach (ViewMapItem sortedValidViewItem in sortedValidViewItems)
        //    {
        //        string line = sortedValidViewItem.ViewId + ":" + sortedValidViewItem.ViewName + ":" + sortedValidViewItem.ViewDescription;

        //        lines.Add(line);
        //    }

        //    string viewMapFullFilePath = GetViewMapPathAndFileName();

        //    File.WriteAllLines(viewMapFullFilePath, lines);
        //}
    }
}
