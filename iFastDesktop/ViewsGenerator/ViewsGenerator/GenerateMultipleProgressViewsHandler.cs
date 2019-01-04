using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;
using ViewsGenerator.Templates.Progress;
using ViewsGenerator.Templates.Java;

namespace ViewsGenerator
{
    class GenerateMultipleProgressViewsHandler
    {
        public ModelProgress ProgressModelObject { get; set; }
        public IMainFormInterface MainFormInterface { get; set; }
        public string ViewFolderPath { get; set; }
        public string JavaFolderPath { get; set; }

        public List<FieldItemLocationInfo> listOfProgressViewIdsAndIndexesWhereFieldIsUsed = new List<FieldItemLocationInfo>();

        public GenerateMultipleProgressViewsHandler()
        {
            this.MainFormInterface = null;
            this.ProgressModelObject = null;
        }

        public void GenerateViewsAffectedByFieldChange(string fieldName)
        {
            MainFormInterface.OutputWindow_WriteLine("---------- Generate Progress and related files that contain modified field (" + fieldName + ") - START ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            foreach (FieldItemLocationInfo fieldItemLocationInfo in listOfProgressViewIdsAndIndexesWhereFieldIsUsed)
            {
                GenerateViewWithViewId(fieldItemLocationInfo.ViewId);
            }

            MainFormInterface.OutputWindow_WriteLine("---------- Generate Progress and related files that contain modified field (" + fieldName + ") - END ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            //GeneerateAllProgressViews();
            //GeneerateAllProgressViewsFromPackageXml();
        }

        public void GeneerateAllProgressViews()
        {
            MainFormInterface.OutputWindow_WriteLine("---------- Generate all Progress view files - START ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();

            listOfProgressViewIdsAndIndexesWhereFieldIsUsed.Clear();

            List<int> listOfViewIds = ProgressModelObject.viewMapItemDictionary.Keys.Select(s => Convert.ToInt32(s)).ToList();
            List<int> orderedListOfViewIds = listOfViewIds.OrderBy(c => c).ToList();

            foreach (int viewId in orderedListOfViewIds)
            {
                GenerateViewWithViewId(viewId);
            }

            MainFormInterface.OutputWindow_WriteLine("---------- Generate all Progress view files - END ----------");
            MainFormInterface.OutputWindow_WriteEmptyLine();
        }

        //public void GeneerateAllProgressViewsFromPackageXml()
        //{
        //    MainFormInterface.OutputWindow_WriteLine("---------- Generate all Progress view files specified in package.xml - START ----------");
        //    MainFormInterface.OutputWindow_WriteEmptyLine();

        //    listOfProgressViewIdsAndIndexesWhereFieldIsUsed.Clear();

        //    List<int> listOfViewIds = ProgressModelObject.viewIdsToBuildJavaClassesList.Select(s => Convert.ToInt32(s)).ToList();
        //    List<int> orderedListOfViewIds = listOfViewIds.OrderBy(c => c).ToList();

        //    foreach (int viewId in orderedListOfViewIds)
        //    {
        //        GenerateViewWithViewId(viewId);
        //    }

        //    MainFormInterface.OutputWindow_WriteLine("---------- Generate all Progress view files specified in package.xml - END ----------");
        //    MainFormInterface.OutputWindow_WriteEmptyLine();
        //}

        private void GenerateViewWithViewId(int viewId)
        {
            List<ViewDataSetItem> matchesResponseViewDataSetItem = ProgressModelObject.viewDataSetItemList.Where(p => p.ViewId == viewId && p.ViewFileType == "response").ToList();

            if (matchesResponseViewDataSetItem.Count > 0)
            {
                ViewDataSetItem viewDataSetItem = matchesResponseViewDataSetItem[0];

                MainFormInterface.OutputWindow_WriteLine(viewDataSetItem.ViewName + ", ViewId: " + viewDataSetItem.ViewId.ToString() + " - Response - GENERATE CODE - START");

                List<ResponseItem> responseItemList = GetItemsFromResponseView(viewDataSetItem.ViewDataFileName);

                GenerateResponseFileForResponseSet(viewDataSetItem, responseItemList);
                GenerateJavaFilesForResponseSet(viewDataSetItem, responseItemList);

                MainFormInterface.OutputWindow_WriteLine(viewDataSetItem.ViewName + ", ViewId: " + viewDataSetItem.ViewId.ToString() + " - Response - GENERATE CODE - END");
                MainFormInterface.OutputWindow_WriteEmptyLine();
            }

            List<ViewDataSetItem> matchesTransactionViewDataSetItem = ProgressModelObject.viewDataSetItemList.Where(p => p.ViewId == viewId && p.ViewFileType == "transaction").ToList();

            if (matchesTransactionViewDataSetItem.Count > 0)
            {
                ViewDataSetItem viewDataSetItem = matchesTransactionViewDataSetItem[0];

                MainFormInterface.OutputWindow_WriteLine(viewDataSetItem.ViewName + ", ViewId: " + viewDataSetItem.ViewId.ToString() + " - Transaction - GENERATE CODE - START");

                List<TransactionItem> transactionItemList = GetItemsFromTransactionView(viewDataSetItem.ViewDataFileName, viewId);

                GenerateTransactionFilesForTransactionSet(viewDataSetItem, transactionItemList);
                GenerateJavaFilesForTransactionSet(viewDataSetItem, transactionItemList);

                MainFormInterface.OutputWindow_WriteLine(viewDataSetItem.ViewName + ", ViewId: " + viewDataSetItem.ViewId.ToString() + " - Transaction - GENERATE CODE - END");
                MainFormInterface.OutputWindow_WriteEmptyLine();
            }
        }

        private void GenerateResponseFileForResponseSet(ViewDataSetItem viewDataSetItem, List<ResponseItem> responseItemList)
        {
            List<ResponseItem> responseType1ItemList = responseItemList.Where(x => x.ResponseType == "response type #1").ToList();
            List<ResponseItem> responseType2ItemList = responseItemList.Where(x => x.ResponseType == "response type #2").ToList();

            // Generate response set file
            ResponseProgressFilesWithDescription_RuntimeTextTemplate page = new ResponseProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = viewDataSetItem.ViewName;
            page.ViewFileName = viewDataSetItem.ViewDataFileName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDataSetItem.ViewDescription;
            page.responseType1ItemList = responseType1ItemList ?? new List<ResponseItem>();
            page.responseType2ItemList = responseType2ItemList ?? new List<ResponseItem>();
            page.responseFieldTableItemsForView = ProgressModelObject.GetResponseFieldTableItemListForGivenView(viewDataSetItem.ViewId.ToString());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strResponseViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewDataSetItem.ViewDataFileName.ToUpper();
            System.IO.File.WriteAllText(strResponseViewFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strResponseViewFileName, Color.Green);

            // Add response type 2 items to response 1 items list and add to dictionary
            page.responseType1ItemList.AddRange(page.responseType2ItemList);
            ProgressModelObject.responseItemListsOfGeneratedResponseViewsDictionary[page.ViewId] = page.responseType1ItemList;
        }

        private void GenerateJavaFilesForResponseSet(ViewDataSetItem viewDataSetItem, List<ResponseItem> responseItemList)
        {
            List<ResponseFieldTableItem> responseFieldItemListForCurrentView = ProgressModelObject.GetListOfResponseFieldItemsForViewId(viewDataSetItem.ViewId.ToString());

            GenerateJavaViewClassForResponseView(viewDataSetItem, responseItemList, responseFieldItemListForCurrentView);
            GenerateJavaClassResponseHtmlForResponseView(viewDataSetItem, responseItemList, responseFieldItemListForCurrentView);
        }

        private void GenerateJavaViewClassForResponseView(ViewDataSetItem viewDataSetItem, List<ResponseItem> responseItemList, List<ResponseFieldTableItem> responseFieldItemListForCurrentView)
        {
            string viewJavaClassName = viewDataSetItem.ViewName + "View";
            string viewJavaClassFileName = viewJavaClassName + ".java";

            // Generate Java view class file
            GenerateJavaViewClass_RuntimeTextTemplate page = new GenerateJavaViewClass_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.JavaClassName = viewJavaClassName;
            page.JavaFileName = viewJavaClassFileName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.responseItemList = responseItemList ?? new List<ResponseItem>();
            page.responseFieldItemList = responseFieldItemListForCurrentView ?? new List<ResponseFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strJavaViewClassFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewJavaClassFileName;
            System.IO.File.WriteAllText(strJavaViewClassFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strJavaViewClassFileName, Color.Green);
        }

        private void GenerateJavaClassResponseHtmlForResponseView(ViewDataSetItem viewDataSetItem, List<ResponseItem> responseItemList, List<ResponseFieldTableItem> responseFieldItemListForCurrentView)
        {
            string responseViewHtmlFileName = viewDataSetItem.ViewName + "Response.html";

            string viewDescription = viewDataSetItem.ViewDescription;

            // Generate Java response class html documentation file
            JavaClassResponseHtml_RuntimeTextTemplate page = new JavaClassResponseHtml_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDescription;
            page.responseItemList = responseItemList ?? new List<ResponseItem>();
            page.responseFieldItemList = responseFieldItemListForCurrentView ?? new List<ResponseFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strResponseHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strResponseHtmlFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strResponseHtmlFileName, Color.Green);
        }

        public List<ResponseItem> GetItemsFromResponseView(string viewDataSetFileName)
        {
            List<ResponseItem> responseItemList = new List<ResponseItem>();

            string strFullFileNameWithPath = ViewFolderPath + "\\" + viewDataSetFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, viewDataSetFileName, SearchOption.TopDirectoryOnly)
                             from line in File.ReadLines(file, Encoding.Default)
                             where (line.TrimStart().StartsWith("define") || line.TrimStart().StartsWith("format") || line.Contains("response type #1") || line.Contains("response type #2"))
                             select new
                             {
                                 File = file,
                                 Line = line
                             }).ToList();

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

                        if (lines[i].Line.Contains("define"))
                        {
                            string[] result = lines[i].Line.Split(stringSeparators, StringSplitOptions.RemoveEmptyEntries);

                            if (result.Count() == 3)
                            {
                                responseItem.Scope = result[0].Trim();
                                responseItem.ResponseVariableName = result[1].Trim();
                                responseItem.ResponseVariableTypeDeclaration = result[2].Trim().TrimEnd('.');
                                responseItem.ResponseType = strResponseType;
                            }
                        }

                        if (lines.Count > i + 1)
                        {
                            if (lines[i + 1].Line.Contains("format"))
                            {
                                string[] result = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                                if (result.Count() == 2)
                                {
                                    responseItem.Format = result[1].Trim().TrimEnd('.');
                                }

                                i++;
                            }
                        }

                        responseItemList.Add(responseItem);
                    }
                }
            }

            return responseItemList;
        }

        private void GenerateTransactionFilesForTransactionSet(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList)
        {
            GenerateAffectedTransactionFile(viewDataSetItem, transactionItemList);

            // Smart view
            GenerateAffectedSmartViewServicingRoutine(viewDataSetItem, transactionItemList);
        }

        private void GenerateAffectedTransactionFile(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList)
        {
            // Generate transaction set file
            TransactionProgressFilesWithDescription_RuntimeTextTemplate page = new TransactionProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = viewDataSetItem.ViewName;
            page.ViewFileName = viewDataSetItem.ViewDataFileName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDataSetItem.ViewDescription;
            page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
            page.transactionFieldTableItemsForView = ProgressModelObject.GetTransactionFieldTableItemListForGivenView(viewDataSetItem.ViewId.ToString());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTransactionViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewDataSetItem.ViewDataFileName.ToUpper();
            System.IO.File.WriteAllText(strTransactionViewFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strTransactionViewFileName, Color.Green);
        }

        private void GenerateAffectedSmartViewServicingRoutine(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList)
        {
            string viewFileName = "VEWZ" + viewDataSetItem.ViewId.ToString() + ".P";

            string fileFullPathName = ViewFolderPath + "\\" + viewFileName;

            if (File.Exists(fileFullPathName))
            {
                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where (line.Contains(" * History:") || (line.Contains("define input")))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 2)
                {
                    // Generate smart view servicing routine file
                    SmartViewServicingRoutine_RuntimeTextTemplate page = new SmartViewServicingRoutine_RuntimeTextTemplate();
                    page.ViewItemName = viewDataSetItem.ViewName;
                    page.ViewFileName = viewDataSetItem.ViewDataFileName;
                    page.ViewId = viewDataSetItem.ViewId.ToString();
                    page.smartViewFileName = viewFileName;
                    page.lines = lines.ToList();
                    page.indexOfHistoryCommentLastLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfFirstDefineInputLine = significantLines.ToList().ElementAt(1).Index;
                    page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
                    page.responseItemList = ProgressModelObject.GetResponseItemListForSelectedView(page.ViewId) ?? new List<ResponseItem>();
                    String pageContent = page.TransformText().Replace("\r\n", "\n");
                    string strSmartViewServicingRoutineFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewFileName.ToUpper();
                    System.IO.File.WriteAllText(strSmartViewServicingRoutineFileName, pageContent);

                    MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strSmartViewServicingRoutineFileName, Color.Green);
                }
            }
        }

        public List<TransactionItem> GetItemsFromTransactionView(string viewDataSetFileName, int viewId)
        {
            List<TransactionItem> transactionItemList = new List<TransactionItem>();

            string strFullFileNameWithPath = ViewFolderPath + "\\" + viewDataSetFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, viewDataSetFileName, SearchOption.TopDirectoryOnly)
                             from line in File.ReadLines(file, Encoding.Default)
                             where (line.TrimStart().StartsWith("define") || line.TrimStart().StartsWith("format"))
                             select new
                             {
                                 File = file,
                                 Line = line
                             }).ToList();

                string[] stringSeparators = new string[] { "define {*}", " variable ", " as " };

                for (int i = 0; i < lines.Count(); i++)
                {
                    TransactionItem transactionItem = new TransactionItem();

                    if (lines[i].Line.Contains("define"))
                    {
                        string[] result = lines[i].Line.Split(stringSeparators, StringSplitOptions.RemoveEmptyEntries);

                        if (result.Count() == 3)
                        {
                            transactionItem.Scope = result[0].Trim();
                            transactionItem.TransactionVariableName = result[1].Trim();
                            transactionItem.TransactionVariableTypeDeclaration = result[2].Trim().TrimEnd('.');
                        }
                    }

                    if (lines.Count > i + 1)
                    {
                        if (lines[i + 1].Line.Contains("format"))
                        {
                            string[] result = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                            if (result.Count() == 2)
                            {
                                transactionItem.Format = result[1].Trim().TrimEnd('.');
                            }

                            i++;
                        }
                    }

                    // Update loaded values from file with the latest values from the Progress model
                    transactionItem = ProgressModelObject.distinctTransactionItemList.Find(p => p.TransactionVariableName == transactionItem.TransactionVariableName);

                    transactionItemList.Add(transactionItem);
                }

                // Update format of the changed field
                if (listOfProgressViewIdsAndIndexesWhereFieldIsUsed.Count > 0)
                {
                    FieldItemLocationInfo fieldItemInfo = listOfProgressViewIdsAndIndexesWhereFieldIsUsed.Find(p => p.ViewId == viewId);

                    if (fieldItemInfo.IndexOfFieldinView <= transactionItemList.Count)
                    {
                        TransactionItem transactionItem = transactionItemList[fieldItemInfo.IndexOfFieldinView];
                        transactionItem.Format = fieldItemInfo.ProgressFieldFormat;
                    }
                }
            }

            return transactionItemList;
        }

        private void GenerateJavaFilesForTransactionSet(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList)
        {
            List<TransactionFieldTableItem> transactionFieldItemListForSelectedView = ProgressModelObject.GetListOfTransactionFieldItemsForViewId(viewDataSetItem.ViewId.ToString());

            GenerateJavaRequestClassForTransactionView(viewDataSetItem, transactionItemList);

            GenerateJavaClassRequestHtmlForTransactionView(viewDataSetItem, transactionItemList, transactionFieldItemListForSelectedView);
            GenerateJavaTestHtmlFileForTransactionView(viewDataSetItem, transactionItemList, transactionFieldItemListForSelectedView);
            GenerateJavaTestJspFileForTransactionView(viewDataSetItem, transactionItemList, transactionFieldItemListForSelectedView);
        }

        private void GenerateJavaRequestClassForTransactionView(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList)
        {
            string requestJavaClassName = viewDataSetItem.ViewName + "Request";
            string requestJavaClassFileName = requestJavaClassName + ".java";

            // Generate Java request class file
            GenerateJavaRequestClass_RuntimeTextTemplate page = new GenerateJavaRequestClass_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.JavaClassName = requestJavaClassName;
            page.JavaFileName = requestJavaClassFileName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strJavaRequestClassFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + requestJavaClassFileName;
            System.IO.File.WriteAllText(strJavaRequestClassFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strJavaRequestClassFileName, Color.Green);
        }

        private void GenerateJavaClassRequestHtmlForTransactionView(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = viewDataSetItem.ViewName + "Request.html";

            string viewDescription = viewDataSetItem.ViewDescription;

            // Generate Java request class html documentation file
            JavaClassRequestHtml_RuntimeTextTemplate page = new JavaClassRequestHtml_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDescription;
            page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strRequestHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strRequestHtmlFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strRequestHtmlFileName, Color.Green);
        }

        private void GenerateJavaTestHtmlFileForTransactionView(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = viewDataSetItem.ViewName + "View.html";

            string viewDescription = viewDataSetItem.ViewDescription;

            // Generate Java request class html test file
            GenerateJavaHtmlTest_RuntimeTextTemplate page = new GenerateJavaHtmlTest_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDescription;
            page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTestHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strTestHtmlFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strTestHtmlFileName, Color.Green);
        }

        private void GenerateJavaTestJspFileForTransactionView(ViewDataSetItem viewDataSetItem, List<TransactionItem> transactionItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = viewDataSetItem.ViewName + ".jsp";

            List<ResponseItem> selectedResponseItemList = ProgressModelObject.GetResponseItemListForSelectedView(viewDataSetItem.ViewId.ToString());
            List<ResponseFieldTableItem> responseFieldItemListForSelectedView = ProgressModelObject.GetListOfResponseFieldItemsForViewId(viewDataSetItem.ViewId.ToString());

            List<ResponseItem> characterAndLogicalNoUndoResponseItemList = ProgressModelObject.GetListOfCharacterAndLogicalNoUndoResponseItems();

            string viewDescription = viewDataSetItem.ViewDescription;

            // Generate Java request class jsp test file
            GenerateJavaJspTest_RuntimeTextTemplate page = new GenerateJavaJspTest_RuntimeTextTemplate();
            page.ViewName = viewDataSetItem.ViewName;
            page.ViewId = viewDataSetItem.ViewId.ToString();
            page.ViewDescription = viewDescription;
            page.transactionItemList = transactionItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            page.responseFieldItemList = responseFieldItemListForSelectedView ?? new List<ResponseFieldTableItem>();
            page.characterAndLogicalResponseItemList = characterAndLogicalNoUndoResponseItemList ?? new List<ResponseItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTestJspFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strTestJspFileName, pageContent);

            MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strTestJspFileName, Color.Green);
        }

        public void SetProgressFieldFormat(string fieldFormat)
        {
            foreach (FieldItemLocationInfo fieldItemLocationInfo in listOfProgressViewIdsAndIndexesWhereFieldIsUsed)
            {
                fieldItemLocationInfo.ProgressFieldFormat = fieldFormat;
            }
        }
    }
}
