using BrightIdeasSoftware;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using ViewsGenerator.Templates.Progress;
using ViewsGenerator.Templates.Java;
using WeifenLuo.WinFormsUI.Docking;
using System.Collections;

namespace ViewsGenerator
{
    public partial class ViewTransactionsEditor : BaseForm
    {
        private readonly string ViewTransactionsEditorErrorBoxCaption = "Transaction Editor Error";
        private List<TransactionItem> transactionItemList = new List<TransactionItem>();
        public string ViewFileName { get; set; }
        public string ViewItemName { get; set; }
        public string ViewItemDescription { get; set; }
        public int ViewId { get; set; }
        public bool isNewView { get; set; }

        public ViewTransactionsEditor()
        {
            InitializeComponent();

            ViewFileName = string.Empty;
            ViewItemName = string.Empty;
            ViewItemDescription = string.Empty;
            ViewId = 0;
            isNewView = false;

            this.btnMoveRight.Enabled = false;
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;

            this.buttonDeleteTransaction.Enabled = false;

            this.objectListViewAllTransactionDefinitions.TintSortColumn = true;
            this.objectListViewAllTransactionDefinitions.UseFiltering = true;
        }

        public void LoadTransactionDefinitionsUI()
        {
            this.objectListViewAllTransactionDefinitions.SetObjects(ProgressModelObject.distinctTransactionItemList);
        }

        public void LoadSelectedTransactionView()
        {
            if (String.IsNullOrEmpty(ViewFolderPath) && String.IsNullOrEmpty(ViewFileName))
            {
                MessageBox.Show("File path is not valid!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = ViewFolderPath + "\\" + ViewFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, ViewFileName, SearchOption.TopDirectoryOnly)
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
                        else
                        {
                            MessageBox.Show("File: " + lines[i].File + ", Line invalid format: " + lines[i], ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }
                    }

                    if (lines[i + 1].Line.Contains("format"))
                    {
                        string[] result = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                        if (result.Count() == 2)
                        {
                            transactionItem.Format = result[1].Trim().TrimEnd('.');
                        }
                        else
                        {
                            MessageBox.Show("File: " + lines[i + 1].File + ", Line invalid format: " + lines[i + 1], ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                            return;
                        }

                        i++;
                    }

                    transactionItemList.Add(transactionItem);
                }

                this.objectListViewSelectedTransactionView.SetObjects(transactionItemList);
            }
            else
            {
                MessageBox.Show(strFullFileNameWithPath + "does not exists!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        public void SetViewNameAndId()
        {
            this.textBoxViewItemName.Text = ViewItemName;
            this.textBoxViewItemDescription.Text = ViewItemDescription;
            this.textBoxViewId.Text = ViewId.ToString();

            if (!isNewView)
            {
                if (ViewItemName.Trim() != string.Empty)
                {
                    this.textBoxViewItemName.ReadOnly = true;
                    this.labelViewTransactionElements.Text += ViewItemName;
                }

                if (ViewItemDescription.Trim() != string.Empty)
                {
                    this.textBoxViewItemDescription.ReadOnly = true;
                }

                if (this.textBoxViewId.Text.Trim() != string.Empty)
                {
                    this.textBoxViewId.ReadOnly = true;
                }
            }
        }

        private string IsAnyOfTheSelectedItemsAlreadyPresent()
        {
            if (objectListViewAllTransactionDefinitions.SelectedObjects.Count > 0)
            {
                List<TransactionItem> transactionItemList = GetTransactionObjectsListSortedBasedOnItemIndex();

                IList itemList = objectListViewAllTransactionDefinitions.SelectedObjects;

                foreach (TransactionItem item in itemList)
                {
                    string variableName = item.TransactionVariableName;

                    TransactionItem foundItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(variableName));

                    if (foundItem != null)
                    {
                        return foundItem.TransactionVariableName;
                    }
                }
            }

            return String.Empty;
        }

        private void btnMoveRight_Click(object sender, EventArgs e)
        {
            string duplicateItem = IsAnyOfTheSelectedItemsAlreadyPresent();

            if (duplicateItem != String.Empty)
            {
                MessageBox.Show("The following transaction field is already present: " + duplicateItem, ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            objectListViewSelectedTransactionView.AddObjects(objectListViewAllTransactionDefinitions.SelectedObjects);

            objectListViewAllTransactionDefinitions.DeselectAll();
        }

        private void btnMoveLeft_Click(object sender, EventArgs e)
        {
            objectListViewSelectedTransactionView.RemoveObjects(objectListViewSelectedTransactionView.SelectedObjects);

            foreach (FieldItem fieldItem in objectListViewSelectedTransactionView.SelectedObjects)
            {
                objectListViewSelectedTransactionView.RemoveObject(fieldItem);
            }

            objectListViewSelectedTransactionView.DeselectAll();
        }

        private void objectListViewAllResponseDefinitions_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewAllTransactionDefinitions.SelectedObjects.Count > 0)
            {
                this.btnMoveRight.Enabled = true;

                if (objectListViewAllTransactionDefinitions.SelectedObjects.Count == 1)
                {
                    this.buttonDeleteTransaction.Enabled = true;
                }
                else
                {
                    this.buttonDeleteTransaction.Enabled = false;
                }
            }
            else
            {
                this.btnMoveRight.Enabled = false;
                this.buttonDeleteTransaction.Enabled = false;
            }
        }

        private void objectListViewSelectedResponseView_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewSelectedTransactionView.SelectedObjects.Count > 0)
            {
                this.btnMoveLeft.Enabled = true;
                this.btnMoveRight.Enabled = false;
            }
            else
            {
                this.btnMoveLeft.Enabled = false;
            }

            EnableMoveUpAndDownButtons();
        }

        private void EnableMoveUpAndDownButtons()
        {
            int selectedItemsCount = objectListViewSelectedTransactionView.SelectedObjects.Count;

            if (selectedItemsCount > 0)
            {
                if (selectedItemsCount > 1)
                {
                    this.btnMoveUp.Enabled = false;
                    this.btnMoveDown.Enabled = false;
                }
                else
                {
                    int selectedIndex = objectListViewSelectedTransactionView.GetDisplayOrderOfItemIndex(objectListViewSelectedTransactionView.SelectedItem.Index);

                    if (selectedIndex == 0)
                    {
                        this.btnMoveUp.Enabled = false;
                    }
                    else
                    {
                        this.btnMoveUp.Enabled = true;
                    }

                    if (selectedIndex == objectListViewSelectedTransactionView.Items.Count - 1)
                    {
                        this.btnMoveDown.Enabled = false;
                    }
                    else
                    {
                        this.btnMoveDown.Enabled = true;
                    }
                }
            }
            else
            {
                this.btnMoveUp.Enabled = false;
                this.btnMoveDown.Enabled = false;
            }
        }

        private void btnMoveUp_Click(object sender, EventArgs e)
        {
            int index = objectListViewSelectedTransactionView.GetDisplayOrderOfItemIndex(objectListViewSelectedTransactionView.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedTransactionView.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedTransactionView.GetNthItemInDisplayOrder(index - 1);

            objectListViewSelectedTransactionView.Items.Remove(next);
            objectListViewSelectedTransactionView.Items.Insert(index, next);

            objectListViewSelectedTransactionView.Focus();
            objectListViewSelectedTransactionView.EnsureModelVisible(selectedObj);
            objectListViewSelectedTransactionView.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            int index = objectListViewSelectedTransactionView.GetDisplayOrderOfItemIndex(objectListViewSelectedTransactionView.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedTransactionView.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedTransactionView.GetNthItemInDisplayOrder(index + 1);

            objectListViewSelectedTransactionView.Items.Remove(next);
            objectListViewSelectedTransactionView.Items.Insert(index, next);

            objectListViewSelectedTransactionView.Focus();
            objectListViewSelectedTransactionView.EnsureModelVisible(selectedObj);
            objectListViewSelectedTransactionView.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void ViewTransactionEditor_Leave(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;

            this.buttonDeleteTransaction.Enabled = false;
        }

        private void objectListViewSelectedResponseView_Enter(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;

            this.buttonDeleteTransaction.Enabled = false;
        }

        private void objectListViewAllResponseDefinitions_Enter(object sender, EventArgs e)
        {
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;
        }

        private void objectListViewAllResponseDefinitions_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            OLVColumn col = objectListViewAllTransactionDefinitions.GetColumn(e.Column);
            objectListViewAllTransactionDefinitions.Sort(col, SortOrder.Ascending);
        }

        private string GetViewId()
        {
            return this.textBoxViewId.Text.Trim();
        }

        private string GetViewItemName()
        {
            return this.textBoxViewItemName.Text.Trim();
        }

        private string IsAnyOfTransactionFieldsUsedInResponseView()
        {
            if (objectListViewSelectedTransactionView.Items.Count > 0)
            {
                List<TransactionItem> transactionItemList = GetSelectedTransactionItemList();

                List<string> responseItemList = ProgressModelObject.GetResponseItemListForSelectedView(GetViewId()).Select(item => item.ResponseVariableName).ToList() ?? new List<string>();

                List<TransactionItem> duplicateTransactionItemList = transactionItemList.Where(x => responseItemList.Contains(x.TransactionVariableName)).ToList();

                if (duplicateTransactionItemList.Count > 0)
                {
                    string duplicateField = duplicateTransactionItemList[0].TransactionVariableName;

                    return duplicateField;
                }
            }

            return String.Empty;
        }

        private void btnGenerateCode_Click(object sender, EventArgs e)
        {
            if (Directory.Exists(ViewFolderPath))
            {
                DialogResult dialogResult = MessageBox.Show("Response files must be generated first for the current view.\nDid you generate response files already?", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (dialogResult == DialogResult.No)
                {
                    return;
                }

                string duplicateItem = IsAnyOfTransactionFieldsUsedInResponseView();

                if (duplicateItem != String.Empty)
                {
                    MessageBox.Show("The following transaction field is already present in response view: " + duplicateItem, ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                OutputWindow_WriteLine(GetViewItemName() + " - Transactions - GENERATE CODE - START");

                if (isNewView)
                {
                    if (IsInputForNewTransactionFileValid())
                    {
                        //AddNewViewToViewMap();
                        AddFieldIdAndSectionIdForFieldsInNewView();
                        GenerateNewTransactionFiles();
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    AddFieldIdAndSectionIdForNewFieldsInExistingView();
                    GenerateModifiedTransactionFiles();
                }

                GenerateJavaFiles();

                OutputWindow_WriteLine(GetViewItemName() + " - Transactions - GENERATE CODE - END");
                OutputWindow_WriteEmptyLine();
            }
            else
            {
                MessageBox.Show("View (Progress) source code folder path is not defined!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool IsInputForNewTransactionFileValid()
        {
            if (this.textBoxViewItemName.Text == string.Empty)
            {
                MessageBox.Show("View name is missing!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewItemName.Focus();
                return false;
            }
            else if (this.textBoxViewId.Text == string.Empty)
            {
                MessageBox.Show("View Id is missing!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewId.Focus();
                return false;
            }

            var duplicatesViewName = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewName == this.textBoxViewItemName.Text);
            if (duplicatesViewName.Count() > 0)
            {
                MessageBox.Show("View name already exists!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewItemName.Focus();
                return false;
            }

            var duplicatesViewId = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewId.ToString() == this.textBoxViewId.Text);
            if (duplicatesViewId.Count() > 0)
            {
                MessageBox.Show("View Id already exists!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewId.Focus();
                return false;
            }

            return true;
        }

        // Not used in the new Progress files format with descriptions
        //private void AddNewViewToViewMap()
        //{
        //    string viewId = this.textBoxViewId.Text;
        //    string viewName = this.textBoxViewItemName.Text;
        //    string viewDescription = this.textBoxViewItemDescription.Text;

        //    ProgressModelObject.AddNewViewToViewMap(viewId, viewName, viewDescription);
        //}

        private List<TransactionItem> GetTransactionObjectsListSortedBasedOnItemIndex()
        {
            List<TransactionItem> transactionItemList = new List<TransactionItem>();

            for (int i = 0; i < objectListViewSelectedTransactionView.Items.Count; i++)
            {
                TransactionItem item = (TransactionItem)objectListViewSelectedTransactionView.GetNthItemInDisplayOrder(i).RowObject;

                transactionItemList.Add(item);
            }

            return transactionItemList;
        }

        private void AddFieldIdAndSectionIdForFieldsInNewView()
        {
            if (objectListViewSelectedTransactionView.Objects != null)
            {
                List<TransactionItem> transactionItemList = GetTransactionObjectsListSortedBasedOnItemIndex();

                // Each view has new section IDs
                int lastSectionId = ProgressModelObject.GetMaxExistingSectionId();

                // Transaction type section ID
                int type1SectionId = lastSectionId;

                int lastFieldId = ProgressModelObject.GetMaxExistingFieldId();

                foreach (TransactionItem transactionItem in transactionItemList)
                {
                    TransactionFieldTableItem transactionFieldTableItem = new TransactionFieldTableItem();

                    transactionFieldTableItem.ViewId = this.textBoxViewId.Text;
                    transactionFieldTableItem.FieldName = transactionItem.TransactionVariableName;
                    // Each view has new field Ids
                    transactionFieldTableItem.FieldId = lastFieldId++.ToString();
                    transactionFieldTableItem.SectionId = type1SectionId.ToString();

                    TransactionFieldTableItem transactionFieldItem = ProgressModelObject.GetTransactionFieldItemWithName(transactionItem.TransactionVariableName);

                    if (transactionFieldItem == null)
                    {
                        transactionFieldTableItem.FieldDescription = transactionItem.VariableDescription;
                    }
                    else
                    {
                        transactionFieldTableItem.FieldDescription = transactionFieldItem.FieldDescription;
                    }

                    bool exists = ProgressModelObject.responseFieldTableItemsList.Any(x => x.ViewId.Equals(this.textBoxViewId.Text) && x.FieldName.Equals(transactionItem.TransactionVariableName));

                    if (!exists)
                    {
                        ProgressModelObject.transactionFieldTableItemsList.Add(transactionFieldTableItem);
                    }
                }
            }
        }

        private void AddFieldIdAndSectionIdForNewFieldsInExistingView()
        {
            if (objectListViewSelectedTransactionView.Objects != null)
            {
                List<TransactionItem> transactionItemList = objectListViewSelectedTransactionView.Objects.Cast<TransactionItem>().Where(x => x.isNewField).ToList();

                if (transactionItemList.Count() > 0)
                {
                    string sectionId1 = GetSectionIdsOfTransactionFieldsInSelectedView();

                    foreach (TransactionItem transactionItem in transactionItemList)
                    {
                        int index = objectListViewSelectedTransactionView.FindItemWithText(transactionItem.TransactionVariableName).Index;

                        TransactionFieldTableItem transactionFieldTableItem = new TransactionFieldTableItem();

                        transactionFieldTableItem.ViewId = GetViewId();
                        transactionFieldTableItem.FieldName = transactionItem.TransactionVariableName;
                        transactionFieldTableItem.FieldDescription = transactionItem.VariableDescription;
                        // Each view has new field Ids
                        int lastFieldId = ProgressModelObject.GetMaxExistingFieldId() + 1;
                        transactionFieldTableItem.FieldId = lastFieldId.ToString();
                        transactionFieldTableItem.SectionId = sectionId1;

                        ProgressModelObject.transactionFieldTableItemsList.Add(transactionFieldTableItem);
                    }
                }
            }
        }

        private string GetSectionIdsOfTransactionFieldsInSelectedView()
        {
            string sectionId1 = "";

            List<TransactionFieldTableItem> transactionFieldItemList = ProgressModelObject.GetTransactionFieldTableItemListForGivenView(GetViewId());

            if (transactionFieldItemList.Count > 0)
            {
                sectionId1 = transactionFieldItemList[0].SectionId;
            }
            else
            {
                throw new System.InvalidOperationException("Transaction field sectionIds are not valid for the current view!");
            }

            return sectionId1;
        }

        private void GenerateNewTransactionFiles()
        {
            GenerateNewTransactionFile();
            GenerateNewBusinessLogicForTransactionFile();

            // Factory common files 
            string viewId = textBoxViewId.Text.Trim();
            ViewFactoryFilesHandler viewFactoryFilesHandler = new ViewFactoryFilesHandler(ViewFolderPath, ViewItemName, viewId);
            viewFactoryFilesHandler.MainFormInterface = MainFormInterface;
            viewFactoryFilesHandler.ProgressModelObject = ProgressModelObject;
            viewFactoryFilesHandler.GenerateViewFactoryFiles();
            
            // Smart view
            List<TransactionItem> selectedTransactionsItemList = GetTransactionObjectsListSortedBasedOnItemIndex();
            GenerateNewSmartViewServicingRoutine(selectedTransactionsItemList);
        }

        private void GenerateNewTransactionFile()
        {
            List<TransactionItem> selectedTransactionsItemList = GetTransactionObjectsListSortedBasedOnItemIndex();

            ViewItemName = textBoxViewItemName.Text.Trim();

            ViewId = Convert.ToInt32(textBoxViewId.Text.Trim());
            ViewFileName = "VEWR" + ViewId.ToString() + ".I";

            // Generate transaction set file
            TransactionProgressFilesWithDescription_RuntimeTextTemplate page = new TransactionProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = ViewItemName;
            page.ViewFileName = ViewFileName;
            page.ViewId = ViewId.ToString();
            page.ViewDescription = this.textBoxViewItemDescription.Text;
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            page.transactionFieldTableItemsForView = ProgressModelObject.GetTransactionFieldTableItemListForGivenView(textBoxViewId.Text.Trim());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTransactionViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + ViewFileName.ToUpper();
            System.IO.File.WriteAllText(strTransactionViewFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strTransactionViewFileName, Color.Green);
        }

        private void GenerateNewBusinessLogicForTransactionFile()
        {
            ViewItemName = textBoxViewItemName.Text.Trim();

            ViewId = Convert.ToInt32(textBoxViewId.Text.Trim());
            ViewFileName = "VEWB" + ViewId.ToString() + ".P";

            // Generate business logic for transaction file
            BusinessLogicForTransaction_RuntimeTextTemplate page = new BusinessLogicForTransaction_RuntimeTextTemplate();
            page.ViewItemName = ViewItemName;
            page.ViewFileName = ViewFileName;
            page.ViewId = ViewId.ToString();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strBusinessLogicForTransactionFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + ViewFileName.ToUpper();
            System.IO.File.WriteAllText(strBusinessLogicForTransactionFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strBusinessLogicForTransactionFileName, Color.Green);
        }

        private void GenerateNewSmartViewServicingRoutine(List<TransactionItem> selectedTransactionsItemList)
        {
            string viewFileName = "VEWZ" + ViewId + ".P";

            string fileFullPathName = ViewFolderPath + "\\" + viewFileName;

            if (Directory.Exists(ViewFolderPath))
            {
                // Generate smart view servicing routine file
                SmartViewServicingRoutine_RuntimeTextTemplate page = new SmartViewServicingRoutine_RuntimeTextTemplate();
                page.ViewItemName = ViewItemName;
                page.ViewFileName = viewFileName;
                page.ViewId = ViewId.ToString();
                page.smartViewFileName = viewFileName;
                page.lines = new List<string>();
                page.indexOfHistoryCommentLastLine = -1;
                page.indexOfFirstDefineInputLine = -1;
                page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
                page.responseItemList = ProgressModelObject.GetResponseItemListForSelectedView(page.ViewId) ?? new List<ResponseItem>();
                String pageContent = page.TransformText().Replace("\r\n", "\n");
                string strSmartViewServicingRoutineFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewFileName.ToUpper();
                System.IO.File.WriteAllText(strSmartViewServicingRoutineFileName, pageContent);

                MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strSmartViewServicingRoutineFileName, Color.Green);
            }
        }

        private void GenerateModifiedTransactionFiles()
        {
            GenerateModifiedTransactionFile();

            //string viewId = textBoxViewId.Text.Trim();
            //ViewFactoryFilesHandler viewFactoryFilesHandler = new ViewFactoryFilesHandler(ViewFolderPath, ViewItemName, viewId);
            //viewFactoryFilesHandler.MainFormInterface = MainFormInterface;
            //viewFactoryFilesHandler.ProgressModelObject = ProgressModelObject;

            // Smart view
            List<TransactionItem> selectedTransactionsItemList = GetTransactionObjectsListSortedBasedOnItemIndex();
            GenerateModifiedSmartViewServicingRoutine(selectedTransactionsItemList);
        }

        private void GenerateModifiedTransactionFile()
        {
            List<TransactionItem> selectedTransactionsItemList = GetTransactionObjectsListSortedBasedOnItemIndex();

            // Generate transaction set file
            TransactionProgressFilesWithDescription_RuntimeTextTemplate page = new TransactionProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = ViewItemName;
            page.ViewFileName = ViewFileName;
            page.ViewId = textBoxViewId.Text.Trim();
            page.ViewDescription = this.textBoxViewItemDescription.Text;
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            page.transactionFieldTableItemsForView = ProgressModelObject.GetTransactionFieldTableItemListForGivenView(textBoxViewId.Text.Trim());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTransactionViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + ViewFileName.ToUpper();
            System.IO.File.WriteAllText(strTransactionViewFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strTransactionViewFileName, Color.Green);
        }

        private void GenerateModifiedSmartViewServicingRoutine(List<TransactionItem> selectedTransactionsItemList)
        {
            string viewFileName = "VEWZ" + ViewId + ".P";

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
                    page.ViewItemName = ViewItemName;
                    page.ViewFileName = viewFileName;
                    page.ViewId = ViewId.ToString();
                    page.smartViewFileName = viewFileName;
                    page.lines = lines.ToList();
                    page.indexOfHistoryCommentLastLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfFirstDefineInputLine = significantLines.ToList().ElementAt(1).Index;
                    page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
                    page.responseItemList = ProgressModelObject.GetResponseItemListForSelectedView(page.ViewId) ?? new List<ResponseItem>();
                    String pageContent = page.TransformText().Replace("\r\n", "\n");
                    string strSmartViewServicingRoutineFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewFileName.ToUpper();
                    System.IO.File.WriteAllText(strSmartViewServicingRoutineFileName, pageContent);

                    MainFormInterface.OutputWindow_WriteIndentedLine("Generated file: " + strSmartViewServicingRoutineFileName, Color.Green);
                }
            }
        }

        private void GenerateJavaFiles()
        {
            string viewId = textBoxViewId.Text.Trim();
            List<TransactionItem> selectedTransactionsItemList = GetTransactionObjectsListSortedBasedOnItemIndex();
            //List<TransactionFieldTableItem> transactionFieldItemListForSelectedView = ProgressModelObject.GetListOfTransactionFieldItemsForViewId(viewId);
            List<TransactionFieldTableItem> transactionFieldItemListForSelectedView = GetTransactionFieldItemsForSelectedItemsInView(viewId, selectedTransactionsItemList); ;

            GenerateJavaRequestClass(viewId, selectedTransactionsItemList);

            //if (selectedTransactionsItemList.Count() == transactionFieldItemListForSelectedView.Count())
            //{
                GenerateJavaClassRequestHtml(viewId, selectedTransactionsItemList, transactionFieldItemListForSelectedView);
                GenerateJavaTestHtmlFile(viewId, selectedTransactionsItemList, transactionFieldItemListForSelectedView);
                GenerateJavaTestJspFile(viewId, selectedTransactionsItemList, transactionFieldItemListForSelectedView);
            //}
            //else
            //{
            //    OutputWindow_WriteLine(ViewItemName + " - GENERATE HTML AND JSP CODE FAILED");
            //    OutputWindow_WriteIndentedLine("Number of transaction field items mismatch!", Color.Red);
            //}
        }

        private List<TransactionFieldTableItem> GetTransactionFieldItemsForSelectedItemsInView(string viewId, List<TransactionItem> selectedTransactionItemList)
        {
            List<TransactionFieldTableItem> allTransactionFieldItemListForSelectedView = ProgressModelObject.GetListOfTransactionFieldItemsForViewId(viewId);
            List<TransactionFieldTableItem> transactionFieldItemListForSelectedView = new List<TransactionFieldTableItem>();

            foreach (TransactionItem transactionItem in selectedTransactionItemList)
            {
                bool exists = allTransactionFieldItemListForSelectedView.Any(x => x.FieldName.Equals(transactionItem.TransactionVariableName));

                if (exists)
                {
                    TransactionFieldTableItem transactionFieldTableItem = allTransactionFieldItemListForSelectedView.Find(x => x.FieldName.Equals(transactionItem.TransactionVariableName));
                    transactionFieldItemListForSelectedView.Add(transactionFieldTableItem);
                }
            }

            return transactionFieldItemListForSelectedView;
        }

        private void GenerateJavaTestHtmlFile(string viewId, List<TransactionItem> selectedTransactionsItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = ViewItemName + "View.html";

            string viewDescription = this.textBoxViewItemDescription.Text.Trim();

            // Generate Java request class html test file
            GenerateJavaHtmlTest_RuntimeTextTemplate page = new GenerateJavaHtmlTest_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.ViewId = viewId;
            page.ViewDescription = viewDescription;
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTestHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strTestHtmlFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strTestHtmlFileName, Color.Green);
        }

        private void GenerateJavaTestJspFile(string viewId, List<TransactionItem> selectedTransactionsItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = ViewItemName + ".jsp";

            List<ResponseItem> selectedResponseItemList = ProgressModelObject.GetResponseItemListForSelectedView(viewId);
            List<ResponseFieldTableItem> responseFieldItemListForSelectedView = ProgressModelObject.GetListOfResponseFieldItemsForViewId(viewId);

            List<ResponseItem> characterAndLogicalNoUndoResponseItemList = ProgressModelObject.GetListOfCharacterAndLogicalNoUndoResponseItems();

            string viewDescription = this.textBoxViewItemDescription.Text.Trim();

            // Generate Java request class jsp test file
            GenerateJavaJspTest_RuntimeTextTemplate page = new GenerateJavaJspTest_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.ViewId = viewId;
            page.ViewDescription = viewDescription;
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            page.responseFieldItemList = responseFieldItemListForSelectedView ?? new List<ResponseFieldTableItem>();
            page.characterAndLogicalResponseItemList = characterAndLogicalNoUndoResponseItemList ?? new List<ResponseItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strTestJspFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strTestJspFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strTestJspFileName, Color.Green);
        }

        private void GenerateJavaRequestClass(string viewId, List<TransactionItem> selectedTransactionsItemList)
        {
            string requestJavaClassName = ViewItemName + "Request";
            string requestJavaClassFileName = requestJavaClassName + ".java";

            // Generate Java request class file
            GenerateJavaRequestClass_RuntimeTextTemplate page = new GenerateJavaRequestClass_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.JavaClassName = requestJavaClassName;
            page.JavaFileName = requestJavaClassFileName;
            page.ViewId = textBoxViewId.Text.Trim();
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strJavaRequestClassFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + requestJavaClassFileName;
            System.IO.File.WriteAllText(strJavaRequestClassFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strJavaRequestClassFileName, Color.Green);
        }

        private void GenerateJavaClassRequestHtml(string viewId, List<TransactionItem> selectedTransactionsItemList, List<TransactionFieldTableItem> transactionFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = ViewItemName + "Request.html";

            string viewDescription = this.textBoxViewItemDescription.Text.Trim();

            // Generate Java request class html documentation file
            JavaClassRequestHtml_RuntimeTextTemplate page = new JavaClassRequestHtml_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.ViewId = viewId;
            page.ViewDescription = viewDescription;
            page.transactionItemList = selectedTransactionsItemList ?? new List<TransactionItem>();
            page.transactionFieldItemList = transactionFieldItemListForSelectedView ?? new List<TransactionFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strRequestHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strRequestHtmlFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strRequestHtmlFileName, Color.Green);
        }

        private List<TransactionItem> GetSelectedTransactionItemList()
        {
            List<TransactionItem> selectedTransactionsItemList = null;

            if (objectListViewSelectedTransactionView.Objects != null)
            {
                selectedTransactionsItemList = objectListViewSelectedTransactionView.Objects.Cast<TransactionItem>().ToList();
            }

            return selectedTransactionsItemList;
        }

        private void buttonAddTransaction_Click(object sender, EventArgs e)
        {
            AddTransactionForm addTransactionForm = new AddTransactionForm();
            addTransactionForm.ModelProgressObject = ProgressModelObject;
            DialogResult result = addTransactionForm.ShowDialog(this);

            if (result == DialogResult.OK)
            {
                LoadTransactionDefinitionsUI();
                objectListViewAllTransactionDefinitions.Focus();
                objectListViewAllTransactionDefinitions.EnsureModelVisible(addTransactionForm.transactionItem);
                objectListViewAllTransactionDefinitions.SelectObject(addTransactionForm.transactionItem);
            }
        }

        private void buttonDeleteTransaction_Click(object sender, EventArgs e)
        {
            if (objectListViewAllTransactionDefinitions.SelectedObjects.Count == 1)
            {
                TransactionItem transactionItem = (TransactionItem)objectListViewAllTransactionDefinitions.SelectedObjects[0];
                ResultCodeEnum result = this.ProgressModelObject.IsVariableUsedInTransactionFiles(transactionItem.TransactionVariableName);

                if (result == ResultCodeEnum.ResultIsOK)
                {
                    int indexToSelect = 0;
                    int indexOfSelectedItem = objectListViewAllTransactionDefinitions.IndexOf(transactionItem);
                    if (indexOfSelectedItem > 0)
                    {
                        indexToSelect = indexOfSelectedItem - 1;
                    }
                    else
                    {
                        indexToSelect = indexOfSelectedItem + 1;
                    }

                    TransactionItem itemToSelect = (TransactionItem)objectListViewAllTransactionDefinitions.GetModelObject(indexToSelect);

                    ProgressModelObject.distinctTransactionItemList.Remove(transactionItem);

                    LoadTransactionDefinitionsUI();
                    objectListViewAllTransactionDefinitions.Focus();

                    if (itemToSelect != null)
                    {
                        objectListViewAllTransactionDefinitions.EnsureModelVisible(itemToSelect);
                        objectListViewAllTransactionDefinitions.SelectObject(itemToSelect);
                    }
                }
                else if (result == ResultCodeEnum.FolderPathIsNotDefined)
                {
                    MessageBox.Show("View (Progress) source code folder path is not defined!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else if (result == ResultCodeEnum.FolderDoesntExist)
                {
                    MessageBox.Show("Specified views (Progress) source code folder path does not exists!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else if (result == ResultCodeEnum.ItemIsUsedInFiles)
                {
                    MessageBox.Show("Item is used in files and cannot be deleted!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else if (objectListViewAllTransactionDefinitions.SelectedObjects.Count > 1)
            {
                MessageBox.Show("Only one item can be deleted at the time!", ViewTransactionsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            this.buttonDeleteTransaction.Enabled = false;
        }

        private void textBoxViewItemName_Leave(object sender, EventArgs e)
        {
            this.Text = "View Transaction Editor - " + "(" + this.textBoxViewId.Text + ") " + this.textBoxViewItemName.Text.Trim();
            this.labelViewTransactionElements.Text = "Transaction definitions for: " + this.textBoxViewItemName.Text.Trim();
        }

        private void textBoxViewId_Leave(object sender, EventArgs e)
        {
            this.Text = "View Transaction Editor - " + "(" + this.textBoxViewId.Text + ") " + this.textBoxViewItemName.Text.Trim();
        }

        private void tbQuickFieldSearch_TextChanged(object sender, EventArgs e)
        {
            var senderText = sender.GetType().ToString();
            if (senderText == "System.Windows.Forms.TextBox")
            {
                var searchFieldTextBox = (TextBox)sender;
                var searchString = searchFieldTextBox.Text;
                if (searchString != null)
                {
                    this.objectListViewAllTransactionDefinitions.ModelFilter = TextMatchFilter.Contains(this.objectListViewAllTransactionDefinitions, searchString);
                    this.objectListViewAllTransactionDefinitions.RedrawItems(0, this.objectListViewAllTransactionDefinitions.GetItemCount() - 1, false);
                }
            }
        }
    }
}
