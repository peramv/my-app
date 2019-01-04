using BrightIdeasSoftware;
using System;
using System.Collections;
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
using ViewsGenerator.Templates.Desktop;
using WeifenLuo.WinFormsUI.Docking;

namespace ViewsGenerator
{
    public partial class DataSetEditor : BaseForm
    {
        private readonly string DataSetEditorErrorBoxCaption = "DataSet Editor Error";
        private List<FieldItem> dataSetFieldItemList = new List<FieldItem>();
        public string DataSetFileName { get; set; }
        public string DataSetItemName { get; set; }
        public bool isNewDataSet { get; set; }

        public DataSetEditor()
        {
            InitializeComponent();

            this.btnMoveRight.Enabled = false;
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;

            this.objectListViewFields.TintSortColumn = true;
            this.objectListViewFields.UseFiltering = true;
        }

        public void LoadFieldsUI()
        {
            this.objectListViewFields.SetObjects(DesktopModelObject.fieldItemList);
        }

        public void LoadSelectedFileFields()
        {
            if (String.IsNullOrEmpty(DataImplFolderPath) && String.IsNullOrEmpty(DataSetFileName))
            {
                MessageBox.Show("File path is not valid!", DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = DataImplFolderPath + "\\" + DataSetFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = from file in Directory.EnumerateFiles(DataImplFolderPath, DataSetFileName, SearchOption.TopDirectoryOnly)
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

                this.objectListViewSelectedDataSetFields.SetObjects(dataSetFieldItemList);
                labelDataSetElements.Text += DataSetItemName;

                SetNumberOfFielsForSelectedDataSet();
                SetTotalFieldsLengthForSelectedDataSet();
            }
            else
            {
                MessageBox.Show(strFullFileNameWithPath + "does not exists!", DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        public void SetDataSetName()
        {
            this.textBoxDataSetName.Text = DataSetItemName;

            if (DataSetItemName.Trim() != "")
            {
                this.textBoxDataSetName.ReadOnly = true;
            }
        }

        public void SetDataSetTypeComboBox()
        {
            this.textBoxDataSetName.Text = DataSetItemName;

            if (DataSetItemName.Trim() != "")
            {
                int selectedIndex = 0;

                if (DataSetFileName.Contains("vwrepeat_record."))
                {
                    selectedIndex = this.comboBoxDataSetType.Items.IndexOf("View Repeat Record");
                }
                else if (DataSetFileName.Contains("reqrepeat_record."))
                {
                    selectedIndex = this.comboBoxDataSetType.Items.IndexOf("Request Repeat Record");
                }
                else if (DataSetFileName.Contains("req."))
                {
                    selectedIndex = this.comboBoxDataSetType.Items.IndexOf("Request");
                }
                else if (DataSetFileName.Contains("vw."))
                {
                    selectedIndex = this.comboBoxDataSetType.Items.IndexOf("View");
                }

                this.comboBoxDataSetType.SelectedIndex = selectedIndex;
            }

            if (!isNewDataSet)
            {
                this.comboBoxDataSetType.Enabled = false;
            }
        }

        private string IsAnyOfTheSelectedItemsAlreadyPresent()
        {
            if (objectListViewFields.SelectedObjects.Count > 0)
            {
                List<FieldItem> fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();

                IList itemList = objectListViewFields.SelectedObjects;

                foreach (FieldItem item in itemList)
                {
                    string variableName = item.FieldName;

                    FieldItem foundItem = fieldItemList.Find(x => x.FieldName.Equals(variableName));

                    if (foundItem != null)
                    {
                        return foundItem.FieldName;
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
                MessageBox.Show("The following field item is already present: " + duplicateItem, DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            objectListViewSelectedDataSetFields.AddObjects(objectListViewFields.SelectedObjects);

            SetNumberOfFielsForSelectedDataSet();
            SetTotalFieldsLengthForSelectedDataSet();

            objectListViewFields.DeselectAll();
        }

        private void btnMoveLeft_Click(object sender, EventArgs e)
        {
            objectListViewSelectedDataSetFields.RemoveObjects(objectListViewSelectedDataSetFields.SelectedObjects);

            foreach (FieldItem fieldItem in objectListViewSelectedDataSetFields.SelectedObjects)
            {
                objectListViewSelectedDataSetFields.RemoveObject(fieldItem);
            }

            SetNumberOfFielsForSelectedDataSet();
            SetTotalFieldsLengthForSelectedDataSet();

            objectListViewSelectedDataSetFields.DeselectAll();
        }

        private void objectListViewFields_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewFields.SelectedObjects.Count > 0)
            {
                this.btnMoveRight.Enabled = true;
            }
            else
            {
                this.btnMoveRight.Enabled = false;
            }
        }

        private void objectListViewSeletedDataSetFields_SelectionChanged(object sender, EventArgs e)
        {
            if (objectListViewSelectedDataSetFields.SelectedObjects.Count > 0)
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
            int selectedItemsCount = objectListViewSelectedDataSetFields.SelectedObjects.Count;

            if (selectedItemsCount > 0)
            {
                if (selectedItemsCount > 1)
                {
                    this.btnMoveUp.Enabled = false;
                    this.btnMoveDown.Enabled = false;
                }
                else
                {
                    int selectedIndex = objectListViewSelectedDataSetFields.GetDisplayOrderOfItemIndex(objectListViewSelectedDataSetFields.SelectedItem.Index);

                    if (selectedIndex == 0)
                    {
                        this.btnMoveUp.Enabled = false;
                    }
                    else
                    {
                        this.btnMoveUp.Enabled = true;
                    }

                    if (selectedIndex == objectListViewSelectedDataSetFields.Items.Count - 1)
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
            int index = objectListViewSelectedDataSetFields.GetDisplayOrderOfItemIndex(objectListViewSelectedDataSetFields.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedDataSetFields.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedDataSetFields.GetNthItemInDisplayOrder(index - 1);

            objectListViewSelectedDataSetFields.Items.Remove(next);
            objectListViewSelectedDataSetFields.Items.Insert(index, next);

            objectListViewSelectedDataSetFields.Focus();
            objectListViewSelectedDataSetFields.EnsureModelVisible(selectedObj);
            objectListViewSelectedDataSetFields.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void btnMoveDown_Click(object sender, EventArgs e)
        {
            int index = objectListViewSelectedDataSetFields.GetDisplayOrderOfItemIndex(objectListViewSelectedDataSetFields.SelectedItem.Index);
            OLVListItem selectedObj = objectListViewSelectedDataSetFields.GetNthItemInDisplayOrder(index);
            OLVListItem next = objectListViewSelectedDataSetFields.GetNthItemInDisplayOrder(index + 1);

            objectListViewSelectedDataSetFields.Items.Remove(next);
            objectListViewSelectedDataSetFields.Items.Insert(index, next);

            objectListViewSelectedDataSetFields.Focus();
            objectListViewSelectedDataSetFields.EnsureModelVisible(selectedObj);
            objectListViewSelectedDataSetFields.SelectObject(selectedObj);

            EnableMoveUpAndDownButtons();
        }

        private void DataSetEditor_Leave(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;
        }

        private void objectListViewSelectedDataSetFields_Enter(object sender, EventArgs e)
        {
            this.btnMoveRight.Enabled = false;
        }

        private void objectListViewFields_Enter(object sender, EventArgs e)
        {
            this.btnMoveLeft.Enabled = false;

            this.btnMoveUp.Enabled = false;
            this.btnMoveDown.Enabled = false;
        }

        private void objectListViewFields_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            OLVColumn col = objectListViewFields.GetColumn(e.Column);
            objectListViewFields.Sort(col, SortOrder.Ascending);
        }

        private void btnGenerateCode_Click(object sender, EventArgs e)
        {
            if (isNewDataSet)
            {
                if (this.textBoxDataSetName.Text.Trim() == "")
                {
                    MessageBox.Show("Data Set name is missing!", DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (this.comboBoxDataSetType.Text.Trim() == "")
                {
                    MessageBox.Show("Data Set type is missing!", DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (objectListViewSelectedDataSetFields.Items.Count == 0)
                {
                    MessageBox.Show("Data Set fields are missing!", DataSetEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                GenerateCodeForNewDataSet();
            }
            else
            {
                GenerateCodeForExistingDataSet();
            }
        }

        private List<FieldItem> GetSelectedDataSetFieldsSortedBasedOnItemIndex()
        {
            List<FieldItem> fieldItemList = new List<FieldItem>();

            for (int i = 0; i < objectListViewSelectedDataSetFields.Items.Count; i++)
            {
                FieldItem item = (FieldItem)objectListViewSelectedDataSetFields.GetNthItemInDisplayOrder(i).RowObject;

                fieldItemList.Add(item);
            }

            return fieldItemList;
        }

        private void GenerateCodeForExistingDataSet()
        {
            OutputWindow_WriteLine(DataSetItemName + " - GENERATE CODE - START");

            // Generate data set files
            DseHpp_RuntimeTextTemplate page = new DseHpp_RuntimeTextTemplate();
            page.DataSetItemName = DataSetItemName;
            page.RepeatsFile = GetRepeatsFileIfApplicable();
            page.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            String pageContent = page.TransformText();
            string strDseHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dse_" + DataSetItemName.ToLower() + ".hpp";
            System.IO.File.WriteAllText(strDseHppFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDseHppFileName, Color.Green);

            DsiCpp_RuntimeTextTemplate page1 = new DsiCpp_RuntimeTextTemplate();
            page1.DataSetItemName = DataSetItemName;
            page1.HeaderDataSetFileName = DataSetFileName.Replace("dse_dstc", "dsi_dstc").Replace(".hpp", ".h");
            page1.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            page1.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageContent1 = page1.TransformText();
            string strDsiCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + DataSetItemName.ToLower() + ".cpp";
            System.IO.File.WriteAllText(strDsiCppFileName, pageContent1);

            OutputWindow_WriteIndentedLine("Generated file: " + strDsiCppFileName, Color.Green);

            DsiH_RuntimeTextTemplate page2 = new DsiH_RuntimeTextTemplate();
            page2.DataSetItemName = DataSetItemName;
            page2.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            String pageContent2 = page2.TransformText();
            string strDsiHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + DataSetItemName.ToLower() + ".h";
            System.IO.File.WriteAllText(strDsiHFileName, pageContent2);

            OutputWindow_WriteIndentedLine("Generated file: " + strDsiHFileName, Color.Green);

            OutputWindow_WriteLine(DataSetItemName + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private void GenerateCodeForNewDataSet()
        {
            DataSetItemName = textBoxDataSetName.Text.Trim();
            string dataSetType = comboBoxDataSetType.Text.Trim();
            DataSetItemName = DesktopModelObject.GetFullNameOfNewDataSet(DataSetItemName, dataSetType);
            DesktopModelObject.AddNewDataSetToDictionary(DataSetItemName);
            DataSetItemName = DataSetItemName.Replace(".", "_").Replace("RepeatRecord", "Repeat_Record");
            textBoxDataSetName.Text = DataSetItemName;

            OutputWindow_WriteLine(DataSetItemName + " - GENERATE CODE - START");

            // Generate data set files
            DseHpp_RuntimeTextTemplate page = new DseHpp_RuntimeTextTemplate();
            page.DataSetItemName = DataSetItemName;
            page.RepeatsFile = GetRepeatsFileIfApplicable();
            page.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            String pageContent = page.TransformText();
            string strDseHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dse_" + DataSetItemName.ToLower() + ".hpp";
            System.IO.File.WriteAllText(strDseHppFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDseHppFileName, Color.Green);

            DsiCpp_RuntimeTextTemplate page1 = new DsiCpp_RuntimeTextTemplate();
            page1.DataSetItemName = DataSetItemName;
            page1.HeaderDataSetFileName = "dsi_" + DataSetItemName.ToLower() + ".h";
            page1.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            page1.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageContent1 = page1.TransformText();
            string strDsiCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + DataSetItemName.ToLower() + ".cpp";
            System.IO.File.WriteAllText(strDsiCppFileName, pageContent1);

            OutputWindow_WriteIndentedLine("Generated file: " + strDsiCppFileName, Color.Green);

            DsiH_RuntimeTextTemplate page2 = new DsiH_RuntimeTextTemplate();
            page2.DataSetItemName = DataSetItemName;
            page2.fieldItemList = GetSelectedDataSetFieldsSortedBasedOnItemIndex();
            String pageContent2 = page2.TransformText();
            string strDsiHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "dsi_" + DataSetItemName.ToLower() + ".h";
            System.IO.File.WriteAllText(strDsiHFileName, pageContent2);

            OutputWindow_WriteIndentedLine("Generated file: " + strDsiHFileName, Color.Green);

            // Generate data implementation exists file
            DataImplExistsCpp_RuntimeTextTemplate pageDataImplExistsCpp = new DataImplExistsCpp_RuntimeTextTemplate();
            pageDataImplExistsCpp.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageDataImplExistsCppContent = pageDataImplExistsCpp.TransformText();
            string strDataImplExistsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_dataimpl_exists.cpp";
            System.IO.File.WriteAllText(strDataImplExistsCppFileName, pageDataImplExistsCppContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDataImplExistsCppFileName, Color.Green);

            // Generate data implementation file
            DataImplFactoryCpp_RuntimeTextTemplate pageDataImplFactoryCpp = new DataImplFactoryCpp_RuntimeTextTemplate();
            pageDataImplFactoryCpp.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageDataImplFactoryCppContent = pageDataImplFactoryCpp.TransformText();
            string strDataImplFactoryCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_dataimplfactory.cpp";
            System.IO.File.WriteAllText(strDataImplFactoryCppFileName, pageDataImplFactoryCppContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDataImplFactoryCppFileName, Color.Green);

            // Generate data ids files
            DataIdsCpp_RuntimeTextTemplate pageDataIdsCpp = new DataIdsCpp_RuntimeTextTemplate();
            pageDataIdsCpp.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageDataIdsCppContent = pageDataIdsCpp.TransformText();
            string strDataIdsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_dataids.cpp";
            System.IO.File.WriteAllText(strDataIdsCppFileName, pageDataIdsCppContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDataIdsCppFileName, Color.Green);

            DataIdsHpp_RuntimeTextTemplate pageDataIdsHpp = new DataIdsHpp_RuntimeTextTemplate();
            pageDataIdsHpp.dataSetNameAndIDsDictionary = DesktopModelObject.dataSetNameAndIDsDictionary;
            String pageDataIdsHppContent = pageDataIdsHpp.TransformText();
            string strDataIdsHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_dataids.hpp";
            System.IO.File.WriteAllText(strDataIdsHppFileName, pageDataIdsHppContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strDataIdsHppFileName, Color.Green);

            OutputWindow_WriteLine(DataSetItemName + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        public string GetRepeatsFileIfApplicable()
        {
            string strRepeatsFile = "";

            if (this.comboBoxDataSetType.Text != "" &&
                this.comboBoxDataSetType.Text != "View Repeat Record" &&
                this.comboBoxDataSetType.Text != "Request Repeat Record")
            {
                string strDataSetItemBase = "";
                string strRepeatsPath = "";

                if (DataSetItemName.Contains("_VW"))
                {
                    strDataSetItemBase = DataSetItemName.Replace("_VW", "");
                    strRepeatsPath = DataImplFolderPath + "\\" + "dse_" + strDataSetItemBase.ToLower() + "_vwrepeat_record" + ".hpp";
                }
                else if (DataSetItemName.Contains("_REQ"))
                {
                    strDataSetItemBase = DataSetItemName.Replace("_REQ", "");
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

        private void ComboBoxDataSetType_SelectionChangeCommitted(object sender, EventArgs e)
        {
            string dataSetBaseName = this.textBoxDataSetName.Text.ToUpper().Trim();
            dataSetBaseName = dataSetBaseName.Replace("_REQ", "").Replace("_VW", "").ReplaceCaseInsensitive("Repeat_Record", "");

            if (dataSetBaseName != "")
            {
                if (this.comboBoxDataSetType.Text == "View Repeat Record")
                {
                    this.textBoxDataSetName.Text = dataSetBaseName + "_VWRepeat_Record";
                }
                else if (this.comboBoxDataSetType.Text == "Request Repeat Record")
                {
                    this.textBoxDataSetName.Text = dataSetBaseName + "_REQRepeat_Record";
                }
                else if (this.comboBoxDataSetType.Text == "View")
                {
                    this.textBoxDataSetName.Text = dataSetBaseName + "_VW";
                }
                else if (this.comboBoxDataSetType.Text == "Request")
                {
                    this.textBoxDataSetName.Text = dataSetBaseName + "_REQ";
                }

                this.Text = "Data Set Editor - " + this.textBoxDataSetName.Text;
                this.labelDataSetElements.Text = "Data Set Elements for: " + this.textBoxDataSetName.Text;
            }
        }

        private void tbQuickFieldSearchTextUpDate(object sender, EventArgs e)
        {
            var senderText = sender.GetType().ToString();
            if (senderText == "System.Windows.Forms.TextBox")
            {
                var searchFieldTextBox = (TextBox)sender;
                var searchString = searchFieldTextBox.Text;
                if (searchString != null)
                {
                    this.objectListViewFields.ModelFilter = TextMatchFilter.Contains(this.objectListViewFields, searchString);
                    this.objectListViewFields.RedrawItems(0, this.objectListViewFields.GetItemCount() - 1, false);
                }
            }
        }

        private void SetNumberOfFielsForSelectedDataSet()
        {
            List<FieldItem> fielsItemsInSelectedDataSet = GetSelectedDataSetFieldsSortedBasedOnItemIndex();

            this.textBoxNumberOfFields.Text = fielsItemsInSelectedDataSet.Count.ToString();
        }

        private void SetTotalFieldsLengthForSelectedDataSet()
        {
            List<FieldItem> fieldItemsInSelectedDataSet = GetSelectedDataSetFieldsSortedBasedOnItemIndex();

            int totalLength = 0;
            if (fieldItemsInSelectedDataSet.Count > 0)
            {
                totalLength = fieldItemsInSelectedDataSet.Select(o => o.FieldLength).Aggregate((x, y) => x + y);
            }

            this.textBoxTotalFieldsLength.Text = totalLength.ToString();
        }
    }
}
