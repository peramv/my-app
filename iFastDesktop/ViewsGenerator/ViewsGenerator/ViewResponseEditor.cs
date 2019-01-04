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
    public partial class ViewResponseEditor : BaseForm
    {
        private readonly string ViewResponseEditorErrorBoxCaption = "Response Editor Error";
        private List<ResponseItem> responseItemList = new List<ResponseItem>();
        public string ViewFileName { get; set; }
        public string ViewItemName { get; set; }
        public string ViewItemDescription { get; set; }
        public int ViewId { get; set; }
        public bool isNewView { get; set; }


        public ViewResponseEditor()
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

            this.buttonDeleteResponse.Enabled = false;

            this.objectListViewAllResponseDefinitions.TintSortColumn = true;
            this.objectListViewAllResponseDefinitions.UseFiltering = true;
        }

        public void LoadResponseDefinitionsUI()
        {
            this.objectListViewAllResponseDefinitions.SetObjects(ProgressModelObject.distinctResponseItemList);
        }

        public void AddDefaultFieldsFoNewResponseView()
        {
            List<ResponseItem> responseType1ItemList = ProgressModelObject.distinctResponseItemList.Where(x => x.ResponseType == "response type #1" && (x.ResponseVariableName == "ErrorCode" || x.ResponseVariableName == "ErrorDesc")).ToList();

            this.objectListViewSelectedResponseView.SetObjects(responseType1ItemList);
        }

        public void LoadSelectedResponseView()
        {
            if (String.IsNullOrEmpty(ViewFolderPath) && String.IsNullOrEmpty(ViewFileName))
            {
                MessageBox.Show("File path is not valid!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = ViewFolderPath + "\\" + ViewFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = (from file in Directory.EnumerateFiles(ViewFolderPath, ViewFileName, SearchOption.TopDirectoryOnly)
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
                            else
                            {
                                MessageBox.Show("File: " + lines[i].File + ", Line invalid format: \n" + lines[i].Line, ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }
                        }

                        if (lines[i + 1].Line.Contains("format"))
                        {
                            string[] result = lines[i + 1].Line.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                            if (result.Count() == 2)
                            {
                                responseItem.Format = result[1].Trim().TrimEnd('.');
                            }
                            else
                            {
                                MessageBox.Show("File: " + lines[i + 1].File + ", Line invalid format: \n" + lines[i + 1].Line, ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                            }

                            i++;
                        }

                        responseItemList.Add(responseItem);
                    }
                }

                this.objectListViewSelectedResponseView.SetObjects(responseItemList);
            }
            else
            {
                MessageBox.Show(strFullFileNameWithPath + "does not exists!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                    this.labelViewResponseElements.Text += ViewItemName;
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
            if (objectListViewAllResponseDefinitions.SelectedObjects.Count > 0)
            {
                List<ResponseItem> responseItemList = GetResponseObjectsListSortedBasedOnItemIndex();

                IList itemList = objectListViewAllResponseDefinitions.SelectedObjects;

                foreach (ResponseItem item in itemList)
                {
                    string variableName = item.ResponseVariableName;

                    ResponseItem foundItem = responseItemList.Find(x => x.ResponseVariableName.Equals(variableName));

                    if (foundItem != null)
                    {
                        return foundItem.ResponseVariableName;
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
                MessageBox.Show("The following response field is already present: " + duplicateItem, ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            objectListViewSelectedResponseView.AddObjects(objectListViewAllResponseDefinitions.SelectedObjects);

            objectListViewAllResponseDefinitions.DeselectAll();
        }

        private void btnMoveLeft_Click(object sender, EventArgs e)
        {
            objectListViewSelectedResponseView.RemoveObjects(objectListViewSelectedResponseView.SelectedObjects);

            foreach (FieldItem fieldItem in objectListViewSelectedResponseView.SelectedObjects)
            {
                objectListViewSelectedResponseView.RemoveObject(fieldItem);
            }

            objectListViewSelectedResponseView.DeselectAll();
        }

        private void objectListViewAllResponseDefinitions_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewAllResponseDefinitions.SelectedObjects.Count > 0)
            {
                this.btnMoveRight.Enabled = true;

                if (objectListViewAllResponseDefinitions.SelectedObjects.Count == 1)
                {
                    this.buttonDeleteResponse.Enabled = true;
                }
                else
                {
                    this.buttonDeleteResponse.Enabled = false;
                }
            }
            else
            {
                this.btnMoveRight.Enabled = false;
                this.buttonDeleteResponse.Enabled = false;
            }
        }

        private void objectListViewSelectedResponseView_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewSelectedResponseView.SelectedObjects.Count > 0)
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
            int selectedItemsCount = objectListViewSelectedResponseView.SelectedObjects.Count;

            if (selectedItemsCount > 0)
            {
                if (selectedItemsCount > 1)
                {
                    this.btnMoveUp.Enabled = false;
                    this.btnMoveDown.Enabled = false;
                }
                else
                {
                    int selectedIndex = objectListViewSelectedResponseView.GetDisplayOrderOfItemIndex(objectListViewSelectedResponseView.SelectedItem.Index);

                    if (selectedIndex == 0)
                    {
                        this.btnMoveUp.Enabled = false;
                    }
                    else
                    {
                        this.btnMoveUp.Enabled = true;
                    }

                    if (selectedIndex == objectListViewSelectedResponseView.Items.Count - 1)
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
            int index = objectListViewSelectedResponseView.GetDisplayOrderOfItemIndex(objectListViewSelectedResponseView.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedResponseView.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedResponseView.GetNthItemInDisplayOrder(index - 1);

            objectListViewSelectedResponseView.Items.Remove(next);
            objectListViewSelectedResponseView.Items.Insert(index, next);

            objectListViewSelectedResponseView.Focus();
            objectListViewSelectedResponseView.EnsureModelVisible(selectedObj);
            objectListViewSelectedResponseView.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            int index = objectListViewSelectedResponseView.GetDisplayOrderOfItemIndex(objectListViewSelectedResponseView.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedResponseView.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedResponseView.GetNthItemInDisplayOrder(index + 1);

            objectListViewSelectedResponseView.Items.Remove(next);
            objectListViewSelectedResponseView.Items.Insert(index, next);

            objectListViewSelectedResponseView.Focus();
            objectListViewSelectedResponseView.EnsureModelVisible(selectedObj);
            objectListViewSelectedResponseView.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void ViewResponseEditor_Leave(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;

            this.buttonDeleteResponse.Enabled = false;
        }

        private void objectListViewSelectedResponseView_Enter(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;

            this.buttonDeleteResponse.Enabled = false;
        }

        private void objectListViewAllResponseDefinitions_Enter(object sender, EventArgs e)
        {
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;
        }

        private void objectListViewAllResponseDefinitions_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            OLVColumn col = objectListViewAllResponseDefinitions.GetColumn(e.Column);
            objectListViewAllResponseDefinitions.Sort(col, SortOrder.Ascending);
        }

        private string GetViewId()
        {
            return this.textBoxViewId.Text.Trim();
        }

        private string GetViewItemName()
        {
            return this.textBoxViewItemName.Text.Trim();
        }

        private void btnGenerateCode_Click(object sender, EventArgs e)
        {
            if (Directory.Exists(ViewFolderPath))
            {
                OutputWindow_WriteLine(GetViewItemName() + " - Response - GENERATE CODE - START");

                if (isNewView)
                {
                    if (IsInputForNewResponseFileValid())
                    {
                        //AddNewViewToViewMap();
                        AddFieldIdAndSectionIdForFieldsInNewView();
                        GenerateNewResponseFile();
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    AddFieldIdAndSectionIdForNewFieldsInExistingView();
                    GenerateModifiedResponseFile();
                }

                GenerateJavaFiles();

                OutputWindow_WriteLine(GetViewItemName() + " - Response - GENERATE CODE - END");
                OutputWindow_WriteEmptyLine();
            }
            else
            {
                MessageBox.Show("View (Progress) source code folder path is not defined!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool IsInputForNewResponseFileValid()
        {
            if (this.textBoxViewItemName.Text == string.Empty)
            {
                MessageBox.Show("View name is missing!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewItemName.Focus();
                return false;
            }
            else if (this.textBoxViewId.Text == string.Empty)
            {
                MessageBox.Show("View Id is missing!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewId.Focus();
                return false;
            }

            var duplicatesViewName = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewName == this.textBoxViewItemName.Text);
            if (duplicatesViewName.Count() > 0)
            {
                MessageBox.Show("View name already exists!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewItemName.Focus();
                return false;
            }

            var duplicatesViewId = ProgressModelObject.viewDataSetItemList.Where(x => x.ViewId.ToString() == this.textBoxViewId.Text);
            if (duplicatesViewId.Count() > 0)
            {
                MessageBox.Show("View Id already exists!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxViewId.Focus();
                return false;
            }

            return true;
        }

        // Not used in the new Progress files format with descriptions
        //private void AddNewViewToViewMap()
        //{
        //    string viewId = GetViewId();
        //    string viewName = this.textBoxViewItemName.Text;
        //    string viewDescription = this.textBoxViewItemDescription.Text;

        //    ProgressModelObject.AddNewViewToViewMap(viewId, viewName, viewDescription);
        //}

        private List<ResponseItem> GetResponseObjectsListSortedBasedOnItemIndex()
        {
            List<ResponseItem> responseItemList = new List<ResponseItem>();

            for (int i = 0; i < objectListViewSelectedResponseView.Items.Count; i++)
            {
                ResponseItem item = (ResponseItem)objectListViewSelectedResponseView.GetNthItemInDisplayOrder(i).RowObject;

                responseItemList.Add(item);
            }

            return responseItemList;
        }

        private void AddFieldIdAndSectionIdForFieldsInNewView()
        {
            if (objectListViewSelectedResponseView.Objects != null)
            {
                List<ResponseItem> responseItemList = GetResponseObjectsListSortedBasedOnItemIndex();

                // Each view has new section IDs
                int lastSectionId = ProgressModelObject.GetMaxExistingSectionId();

                // Response type groups have different section IDs
                int type1SectionId = -1;
                bool existsResponseType1 = responseItemList.Any(x => x.ResponseType.Equals("response type #1"));
                if (existsResponseType1)
                {
                    lastSectionId++;
                    type1SectionId = lastSectionId;
                }

                int type2SectionId = -1;
                bool existsResponseType2 = responseItemList.Any(x => x.ResponseType.Equals("response type #2"));
                if (existsResponseType2)
                {
                    lastSectionId++;
                    type2SectionId = lastSectionId;
                }

                int lastFieldId = ProgressModelObject.GetMaxExistingFieldId();

                foreach (ResponseItem responseItem in responseItemList)
                {
                    ResponseFieldTableItem responseFieldTableItem = new ResponseFieldTableItem();

                    responseFieldTableItem.ViewId = this.textBoxViewId.Text;
                    responseFieldTableItem.FieldName = responseItem.ResponseVariableName;
                    responseFieldTableItem.ResponseType = Regex.Match(responseItem.ResponseType, @"\d+").Value;
                    // Each view has new field Ids
                    responseFieldTableItem.FieldId = lastFieldId++.ToString();

                    if (responseFieldTableItem.ResponseType == "1")
                    {
                        responseFieldTableItem.SectionId = type1SectionId.ToString();
                    }
                    else
                    {
                        responseFieldTableItem.SectionId = type2SectionId.ToString();
                    }

                    ResponseFieldTableItem responseFieldItem = ProgressModelObject.GetResponseFieldItemWithName(responseItem.ResponseVariableName);

                    if (responseFieldItem == null)
                    {
                        responseFieldTableItem.FieldDescription = responseItem.VariableDescription;
                    }
                    else
                    {
                        responseFieldTableItem.FieldDescription = responseFieldItem.FieldDescription;
                    }

                    bool exists = ProgressModelObject.responseFieldTableItemsList.Any(x => x.ViewId.Equals(this.textBoxViewId.Text) && x.FieldName.Equals(responseItem.ResponseVariableName));

                    if (!exists)
                    {
                        ProgressModelObject.responseFieldTableItemsList.Add(responseFieldTableItem);
                    }
                }
            }
        }

        private void AddFieldIdAndSectionIdForNewFieldsInExistingView()
        {
            if (objectListViewSelectedResponseView.Objects != null)
            {
                List<ResponseItem> responseItemList = objectListViewSelectedResponseView.Objects.Cast<ResponseItem>().Where(x => x.isNewField).ToList();

                if (responseItemList.Count() > 0)
                { 
                    Tuple<string, string, string, int, int, int> sectionIdTuple = GetSectionIdsOfResponseFieldsInSelectedView();
                    string sectionId1 = sectionIdTuple.Item1;
                    string sectionId2 = sectionIdTuple.Item2;
                    string sectionId3 = sectionIdTuple.Item3;
                    int index1 = sectionIdTuple.Item4;
                    int index2 = sectionIdTuple.Item5;
                    int index3 = sectionIdTuple.Item6;

                    foreach (ResponseItem responseItem in responseItemList)
                    {
                        int index = objectListViewSelectedResponseView.FindItemWithText(responseItem.ResponseVariableName).Index;

                        ResponseFieldTableItem responseFieldTableItem = new ResponseFieldTableItem();

                        responseFieldTableItem.ViewId = GetViewId();
                        responseFieldTableItem.FieldName = responseItem.ResponseVariableName;
                        responseFieldTableItem.ResponseType = Regex.Match(responseItem.ResponseType, @"\d+").Value;
                        responseFieldTableItem.FieldDescription = responseItem.VariableDescription;
                        // Each view has new field Ids
                        int lastFieldId = ProgressModelObject.GetMaxExistingFieldId() + 1;
                        responseFieldTableItem.FieldId = lastFieldId.ToString();

                        if (responseItem.ResponseType.Equals("response type #1"))
                        {
                            responseFieldTableItem.SectionId = sectionId1;
                        }
                        else
                        {
                            if (index3 != -1 && index > index3)
                            {
                                responseFieldTableItem.SectionId = sectionId3;
                            }
                            else if (index2 != -1 && index > index2)
                            {
                                responseFieldTableItem.SectionId = sectionId2;
                            }
                            else if (index1 != -1 && index > index1)
                            {
                                responseFieldTableItem.SectionId = sectionId1;
                            }
                        }

                        ProgressModelObject.responseFieldTableItemsList.Add(responseFieldTableItem);
                    }
                }
            }
        }

        private Tuple<string, string, string, int, int, int> GetSectionIdsOfResponseFieldsInSelectedView()
        {
            string sectionId1 = "";
            string sectionId2 = "";
            string sectionId3 = "";
            int index1 = -1;
            int index2 = -1;
            int index3 = -1;

            List<ResponseFieldTableItem> responseFieldItemList = ProgressModelObject.GetResponseFieldTableItemListForGivenView(GetViewId());

            var sectionIdsAndIndexes = responseFieldItemList.Select((n, i) => new { Value = n.SectionId, Index = i }).GroupBy(n => n.Value).Select(n => n.First()).ToList();

            int count = sectionIdsAndIndexes.Count();

            if (count > 0)
            {
                sectionId1 = sectionIdsAndIndexes[0].Value;
                index1 = sectionIdsAndIndexes[0].Index;

                if (count > 1)
                {
                    sectionId2 = sectionIdsAndIndexes[1].Value;
                    index2 = sectionIdsAndIndexes[1].Index;

                    if (count > 2)
                    {
                        sectionId3 = sectionIdsAndIndexes[2].Value;
                        index3 = sectionIdsAndIndexes[2].Index;
                    }
                }
            }
            else
            {
                throw new System.InvalidOperationException("Response field sectionIds are not valid for the current view!");
            }

            return new Tuple<string, string, string, int, int, int>(sectionId1, sectionId2, sectionId3, index1, index2, index3);
        }

        private Tuple<List<ResponseItem>, List<ResponseItem>> GetResponseItemListsGroupedByResponseType()
        {
            List<ResponseItem> responseType1ItemList = null;
            List<ResponseItem> responseType2ItemList = null;

            List<ResponseItem> responseItemList = GetResponseObjectsListSortedBasedOnItemIndex();

            if (responseItemList != null)
            {
                responseType1ItemList = responseItemList.Where(x => x.ResponseType == "response type #1").ToList();
                responseType2ItemList = responseItemList.Where(x => x.ResponseType == "response type #2").ToList();
            }

            return new Tuple<List<ResponseItem>, List<ResponseItem>>(responseType1ItemList, responseType2ItemList);
        }

        private void GenerateNewResponseFile()
        {
            Tuple<List<ResponseItem>, List<ResponseItem>> responseItemsTuple = GetResponseItemListsGroupedByResponseType();

            List<ResponseItem> responseType1ItemList = responseItemsTuple.Item1;
            List<ResponseItem> responseType2ItemList = responseItemsTuple.Item2; 

            ViewItemName = textBoxViewItemName.Text.Trim();

            ViewId = Convert.ToInt32(textBoxViewId.Text.Trim());
            ViewFileName = "VEWP" + ViewId.ToString() + ".I";

            // Generate data set files
            ResponseProgressFilesWithDescription_RuntimeTextTemplate page = new ResponseProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = ViewItemName;
            page.ViewFileName = ViewFileName;
            page.ViewId = ViewId.ToString();
            page.ViewDescription = this.textBoxViewItemDescription.Text;
            page.responseType1ItemList = responseType1ItemList ?? new List<ResponseItem>();
            page.responseType2ItemList = responseType2ItemList ?? new List<ResponseItem>();
            page.responseFieldTableItemsForView = ProgressModelObject.GetResponseFieldTableItemListForGivenView(textBoxViewId.Text.Trim());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strResponseViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + ViewFileName.ToUpper();
            System.IO.File.WriteAllText(strResponseViewFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strResponseViewFileName, Color.Green);

            // Add response type 2 items to response 1 items list and add to dictionary
            page.responseType1ItemList.AddRange(page.responseType2ItemList);
            ProgressModelObject.responseItemListsOfGeneratedResponseViewsDictionary[page.ViewId] = page.responseType1ItemList;
        }

        private void GenerateModifiedResponseFile()
        {
            Tuple<List<ResponseItem>, List<ResponseItem>> responseItemsTuple = GetResponseItemListsGroupedByResponseType();

            List<ResponseItem> responseType1ItemList = responseItemsTuple.Item1;
            List<ResponseItem> responseType2ItemList = responseItemsTuple.Item2; 

            // Generate response set file
            ResponseProgressFilesWithDescription_RuntimeTextTemplate page = new ResponseProgressFilesWithDescription_RuntimeTextTemplate();
            page.ViewItemName = ViewItemName;
            page.ViewFileName = ViewFileName;
            page.ViewId = textBoxViewId.Text.Trim();
            page.ViewDescription = this.textBoxViewItemDescription.Text;
            page.responseType1ItemList = responseType1ItemList ?? new List<ResponseItem>();
            page.responseType2ItemList = responseType2ItemList ?? new List<ResponseItem>();
            page.responseFieldTableItemsForView = ProgressModelObject.GetResponseFieldTableItemListForGivenView(textBoxViewId.Text.Trim());
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strResponseViewFileName = ViewFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + ViewFileName.ToUpper();
            System.IO.File.WriteAllText(strResponseViewFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strResponseViewFileName, Color.Green);

            // Add response type 2 items to response 1 items list and add to dictionary
            page.responseType1ItemList.AddRange(page.responseType2ItemList);
            ProgressModelObject.responseItemListsOfGeneratedResponseViewsDictionary[page.ViewId] = page.responseType1ItemList;
        }

        private void GenerateJavaFiles()
        {
            string viewId = textBoxViewId.Text.Trim();
            List<ResponseItem> selectedResponseItemList = ProgressModelObject.GetResponseItemListForSelectedView(viewId);
            //List<ResponseFieldTableItem> responseFieldItemListForSelectedView = ProgressModelObject.GetListOfResponseFieldItemsForViewId(viewId);
            List<ResponseFieldTableItem> responseFieldItemListForSelectedView = GetResponseFieldItemsForSelectedItemsInView(viewId, selectedResponseItemList);

            //if (selectedResponseItemList.Count() == responseFieldItemListForSelectedView.Count())
            //{
                GenerateJavaViewClass(viewId, selectedResponseItemList, responseFieldItemListForSelectedView);
                GenerateJavaClassResponseHtml(viewId, selectedResponseItemList, responseFieldItemListForSelectedView);
            //}
            //else
            //{
            //    OutputWindow_WriteLine(ViewItemName + " - GENERATE JAVA CODE FAILED");
            //    OutputWindow_WriteIndentedLine("Number of response field items mismatch!", Color.Red);
            //}
        }

        private List<ResponseFieldTableItem> GetResponseFieldItemsForSelectedItemsInView(string viewId, List<ResponseItem> selectedResponseItemList)
        {
            List<ResponseFieldTableItem> allResponseFieldItemListForSelectedView = ProgressModelObject.GetListOfResponseFieldItemsForViewId(viewId);
            List<ResponseFieldTableItem> responseFieldItemListForSelectedView = new List<ResponseFieldTableItem>();

            foreach (ResponseItem responseItem in selectedResponseItemList)
            {
                bool exists = allResponseFieldItemListForSelectedView.Any(x => x.FieldName.Equals(responseItem.ResponseVariableName));

                if (exists)
                {
                    ResponseFieldTableItem responseFieldTableItem = allResponseFieldItemListForSelectedView.Find(x => x.FieldName.Equals(responseItem.ResponseVariableName));
                    responseFieldItemListForSelectedView.Add(responseFieldTableItem);
                }
            }

            return responseFieldItemListForSelectedView;
        }

        private void GenerateJavaViewClass(string viewId, List<ResponseItem> selectedResponseItemList, List<ResponseFieldTableItem> responseFieldItemListForSelectedView)
        {
            string viewJavaClassName = ViewItemName + "View";
            string viewJavaClassFileName = viewJavaClassName + ".java";

            // Generate Java view class file
            GenerateJavaViewClass_RuntimeTextTemplate page = new GenerateJavaViewClass_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.JavaClassName = viewJavaClassName;
            page.JavaFileName = viewJavaClassFileName;
            page.ViewId = viewId;
            page.responseItemList = selectedResponseItemList ?? new List<ResponseItem>();
            page.responseFieldItemList = responseFieldItemListForSelectedView ?? new List<ResponseFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strJavaViewClassFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + viewJavaClassFileName;
            System.IO.File.WriteAllText(strJavaViewClassFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strJavaViewClassFileName, Color.Green);
        }

        private void GenerateJavaClassResponseHtml(string viewId, List<ResponseItem> selectedResponseItemList, List<ResponseFieldTableItem> responseFieldItemListForSelectedView)
        {
            string responseViewHtmlFileName = ViewItemName + "Response.html";

            string viewDescription = this.textBoxViewItemDescription.Text.Trim();

            // Generate Java response class html documentation file
            JavaClassResponseHtml_RuntimeTextTemplate page = new JavaClassResponseHtml_RuntimeTextTemplate();
            page.ViewName = ViewItemName;
            page.ViewId = viewId;
            page.ViewDescription = viewDescription;
            page.responseItemList = selectedResponseItemList ?? new List<ResponseItem>();
            page.responseFieldItemList = responseFieldItemListForSelectedView ?? new List<ResponseFieldTableItem>();
            String pageContent = page.TransformText().Replace("\r\n", "\n");
            string strResponseHtmlFileName = JavaFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + responseViewHtmlFileName;
            System.IO.File.WriteAllText(strResponseHtmlFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strResponseHtmlFileName, Color.Green);
        }

        private void buttonAddResponse_Click(object sender, EventArgs e)
        {
            AddResponseForm addResponseForm = new AddResponseForm();
            addResponseForm.ModelProgressObject = ProgressModelObject;
            DialogResult result = addResponseForm.ShowDialog(this);

            if (result == DialogResult.OK)
            {
                LoadResponseDefinitionsUI();
                objectListViewAllResponseDefinitions.Focus();
                objectListViewAllResponseDefinitions.EnsureModelVisible(addResponseForm.responseItem);
                objectListViewAllResponseDefinitions.SelectObject(addResponseForm.responseItem);
            }
        }

        private void buttonDeleteResponse_Click(object sender, EventArgs e)
        {
            if (objectListViewAllResponseDefinitions.SelectedObjects.Count == 1)
            {
                ResponseItem responseItem = (ResponseItem)objectListViewAllResponseDefinitions.SelectedObjects[0];
                ResultCodeEnum result = this.ProgressModelObject.IsVariableUsedInResponseFiles(responseItem.ResponseVariableName);

                if (result == ResultCodeEnum.ResultIsOK)
                {
                    int indexToSelect = 0;
                    int indexOfSelectedItem = objectListViewAllResponseDefinitions.IndexOf(responseItem);
                    if (indexOfSelectedItem > 0)
                    {
                        indexToSelect = indexOfSelectedItem - 1;
                    }
                    else
                    {
                        indexToSelect = indexOfSelectedItem + 1;
                    }

                    ResponseItem itemToSelect = (ResponseItem)objectListViewAllResponseDefinitions.GetModelObject(indexToSelect);

                    ProgressModelObject.distinctResponseItemList.Remove(responseItem);

                    LoadResponseDefinitionsUI();
                    objectListViewAllResponseDefinitions.Focus();

                    if (itemToSelect != null)
                    {
                        objectListViewAllResponseDefinitions.EnsureModelVisible(itemToSelect);
                        objectListViewAllResponseDefinitions.SelectObject(itemToSelect);
                    }
                }
                else if (result == ResultCodeEnum.FolderPathIsNotDefined)
                {
                    MessageBox.Show("View (Progress) source code folder path is not defined!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else if (result == ResultCodeEnum.FolderDoesntExist)
                {
                    MessageBox.Show("Specified views (Progress) source code folder path does not exists!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else if (result == ResultCodeEnum.ItemIsUsedInFiles)
                {
                    MessageBox.Show("Item is used in files and cannot be deleted!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else if (objectListViewAllResponseDefinitions.SelectedObjects.Count > 1)
            {
                MessageBox.Show("Only one item can be deleted at the time!", ViewResponseEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            this.buttonDeleteResponse.Enabled = false;
        }

        private void textBoxViewItemName_Leave(object sender, EventArgs e)
        {
            this.Text = "View Response Editor - " + "(" + this.textBoxViewId.Text + ") " + this.textBoxViewItemName.Text.Trim();
            this.labelViewResponseElements.Text = "Response definitions for: " + this.textBoxViewItemName.Text.Trim();
        }

        private void textBoxViewId_Leave(object sender, EventArgs e)
        {
            this.Text = "View Response Editor - " + "(" + this.textBoxViewId.Text + ") " + this.textBoxViewItemName.Text.Trim();
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
                    this.objectListViewAllResponseDefinitions.ModelFilter = TextMatchFilter.Contains(this.objectListViewAllResponseDefinitions, searchString);
                    this.objectListViewAllResponseDefinitions.RedrawItems(0, this.objectListViewAllResponseDefinitions.GetItemCount() - 1, false);
                }
            }
        }
    }
}
