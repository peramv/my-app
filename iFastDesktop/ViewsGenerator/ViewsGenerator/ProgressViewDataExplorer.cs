using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using ViewsGenerator.Templates.Progress;

namespace ViewsGenerator
{
    public partial class ProgressViewDataExplorer : BaseForm
    {
        public ProgressViewDataExplorer()
        {
            InitializeComponent();
        }

        public void LoadViewDataSetFiles()
        {
            ProgressModelObject.viewDataSetItemList.Clear();
            this.objectListViewProgressViews.ClearObjects();

            if (String.IsNullOrEmpty(ViewFolderPath))
            {
                MessageBox.Show("Path to \"view\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (Directory.Exists(ViewFolderPath))
            {
                var files = from file in Directory.EnumerateFiles(ViewFolderPath, "*.I", SearchOption.TopDirectoryOnly)
                            where (file.Contains("VEWR") || file.Contains("VEWP"))
                            from line in File.ReadLines(file, Encoding.Default)
                            where (line.Contains("* Definitions for transaction") ||
                                   (line.Contains("* Definitions for response") && !line.Contains("response type #1") && !line.Contains("response type #2")))
                            select new
                            {
                                File = file,
                                Line = line
                            };

                foreach (var file in files)
                {
                    ViewDataSetItem viewDataSetItem = new ViewDataSetItem();

                    viewDataSetItem.ViewDataFileName = Path.GetFileName(file.File);
                    viewDataSetItem.ViewId = Convert.ToInt32(Regex.Match(viewDataSetItem.ViewDataFileName, @"\d+").Value);
                    viewDataSetItem.ViewDescription = file.Line.Split('(', ')')[1];
                    viewDataSetItem.ViewFileType = GetFileType(viewDataSetItem.ViewDataFileName);

                    ViewMapItem viewMapItem = null;
                    string viewId = viewDataSetItem.ViewId.ToString();
                    ProgressModelObject.viewMapItemDictionary.TryGetValue(viewId, out viewMapItem);

                    if (viewMapItem != null)
                    {
                        viewMapItem.isValid = true;
                        ProgressModelObject.viewMapItemDictionary[viewId] = viewMapItem;

                        viewDataSetItem.ViewName = viewMapItem.ViewName;
                    }

                    ProgressModelObject.viewDataSetItemList.Add(viewDataSetItem);
                }

                ProgressModelObject.viewDataSetItemList = ProgressModelObject.viewDataSetItemList.OrderBy(x => x.ViewId).ToList();

                this.objectListViewProgressViews.SetObjects(ProgressModelObject.viewDataSetItemList);

                // Not used in the new Progress files format with descriptions
                //ProgressModelObject.RemoveInvalidViewsFromViewMap();
            }
        }

        private string GetFileType(string fileName)
        {
            string fileType = "";

            if (fileName.Contains("VEWR"))
            {
                fileType = "transaction";
            }
            else if (fileName.Contains("VEWP"))
            {
                fileType = "response";
            }

            return fileType;
        }

        private void objectListViewProgressViews_DoubleClick(object sender, EventArgs e)
        {
            ViewDataSetItem selectedObj = (ViewDataSetItem)objectListViewProgressViews.SelectedObject;

            if (selectedObj != null)
            {
                MainForm form = (MainForm)this.ParentForm;

                if (selectedObj.ViewFileType == "response")
                {
                    form.OpenViewResponseEditor(selectedObj.ViewDataFileName, selectedObj.ViewName, selectedObj.ViewDescription, selectedObj.ViewId);
                }
                else if (selectedObj.ViewFileType == "transaction")
                {
                    form.OpenViewTransactionsEditor(selectedObj.ViewDataFileName, selectedObj.ViewName, selectedObj.ViewDescription, selectedObj.ViewId);
                }
            }
        }

        public void CreateProgressFilesWithDescription()
        {
            CreateResponseProgressFilesWithDescription();
            CreateTransactionProgressFilesWithDescription();
        }

        private void CreateResponseProgressFilesWithDescription()
        {
            List<ViewDataSetItem> responseFiles = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewFileType.Equals("response")).ToList();

            foreach (ViewDataSetItem responseFile in responseFiles)
            {
                Tuple<List<ResponseItem>, List<ResponseItem>> responseItemsTuple = ProgressModelObject.GetResponseItemListsGroupedByResponseTypeForGivenViewId(responseFile.ViewId.ToString());

                List<ResponseItem> responseType1ItemList = responseItemsTuple.Item1;
                List<ResponseItem> responseType2ItemList = responseItemsTuple.Item2;

                // Generate response set file
                ResponseProgressFilesWithDescription_RuntimeTextTemplate page = new ResponseProgressFilesWithDescription_RuntimeTextTemplate();
                page.ViewItemName = responseFile.ViewName;
                page.ViewFileName = responseFile.ViewDataFileName;
                page.ViewDescription = responseFile.ViewDescription;
                page.ViewId = responseFile.ViewId.ToString();
                page.responseType1ItemList = responseType1ItemList ?? new List<ResponseItem>();
                page.responseType2ItemList = responseType2ItemList ?? new List<ResponseItem>();
                page.responseFieldTableItemsForView = ProgressModelObject.GetResponseFieldTableItemListForGivenView(responseFile.ViewId.ToString());
                String pageContent = page.TransformText().Replace("\r\n", "\n");
                string strResponseViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + /*"progress_conversion_description\\" +*/ responseFile.ViewDataFileName.ToUpper();
                System.IO.File.WriteAllText(strResponseViewFileName, pageContent);
            }
        }

        private void CreateTransactionProgressFilesWithDescription()
        {
            List<ViewDataSetItem> transactionFiles = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewFileType.Equals("transaction")).ToList();

            foreach (ViewDataSetItem transactionFile in transactionFiles)
            {
                List<TransactionItem> selectedTransactionsItemList = GetTransactionItemListsForGivenViewId(transactionFile.ViewId.ToString());

                // Generate transaction set file
                TransactionProgressFilesWithDescription_RuntimeTextTemplate page = new TransactionProgressFilesWithDescription_RuntimeTextTemplate();
                page.ViewItemName = transactionFile.ViewName;
                page.ViewFileName = transactionFile.ViewDataFileName;
                page.ViewDescription = transactionFile.ViewDescription;
                page.ViewId = transactionFile.ViewId.ToString();
                page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
                page.transactionFieldTableItemsForView = ProgressModelObject.GetTransactionFieldTableItemListForGivenView(transactionFile.ViewId.ToString());
                String pageContent = page.TransformText().Replace("\r\n", "\n");
                string strTransactionViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + /*"progress_conversion_description\\" +*/ transactionFile.ViewDataFileName.ToUpper();
                System.IO.File.WriteAllText(strTransactionViewFileName, pageContent);
            }
        }

        private List<TransactionItem> GetTransactionItemListsForGivenViewId(string viewId)
        {
            List<TransactionItem> transactionItemList = ProgressModelObject.transactionItemList.Where(x => x.ViewId.Equals(viewId)).ToList();

            return transactionItemList;
        }
    }
}
