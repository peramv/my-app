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
using System.Xml.Linq;
using ViewsGenerator.Templates.Desktop;

namespace ViewsGenerator
{
    public partial class MasksEditor : BaseForm
    {
        private readonly string fileNameMasksH = "ifast_masks.h";
        private readonly string fileNameMasksCpp = "ifast_masks.cpp";
        private List<MaskItem> maskItemList = new List<MaskItem>();
        private List<MaskItem> maskItemListToSave = new List<MaskItem>();

        public MasksEditor()
        {
            InitializeComponent();
        }

        public void InitializeDataGridViews()
        {
            for (int i = 0; i < 199; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewMasks);

                row.Cells[0].Value = string.Empty;
                row.Cells[1].Value = string.Empty;
                row.Cells[2].Value = string.Empty;

                dataGridViewMasks.Rows.Add(row);
            }

            SetRowNumber(dataGridViewMasks);

            var languages = DesktopModelObject.uniqueIdToCountryLanguageDictionary.Values.ToList();

            for (int i = 0; i < 29; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewMaskLanguages);

                DataGridViewComboBoxCell comboBoxCell = new DataGridViewComboBoxCell();

                comboBoxCell.Items.Add(string.Empty);

                foreach (var lang in languages)
                {
                    comboBoxCell.Items.Add(lang);
                }

                row.Cells[0] = comboBoxCell;
                row.Cells[1].Value = string.Empty;

                dataGridViewMaskLanguages.Rows.Add(row);
            }

            SetRowNumber(dataGridViewMaskLanguages);
        }

        public string GetLanguagePathAndFileName()
        {
            return DataImplFolderPath + "\\masks.xml";
        }

        private void SetRowNumber(DataGridView dgv)
        {
            foreach (DataGridViewRow row in dgv.Rows)
            {
                row.HeaderCell.Value = (row.Index + 1).ToString();
            }
        }

        public void LoadMasks()
        {
            LoadMasksXmlFile();
            PopulateDataGridViewMasks();
        }

        private void LoadMasksXmlFile()
        {
            string pathAndFileName = GetLanguagePathAndFileName();

            if (File.Exists(pathAndFileName))
            {
                try
                {
                    XDocument doc = XDocument.Load(pathAndFileName);

                    var masks = doc.Descendants("Mask");

                    foreach (var mask in masks)
                    {
                        MaskItem maskItem = new MaskItem();
                        maskItem.GroupId = mask.Attribute("Group_Id").Value;
                        maskItem.MaskId = mask.Attribute("Mask_Id").Value;
                        maskItem.MaskName = mask.Attribute("Mask_Name").Value;

                        var languageMasks = mask.Descendants("Language_Mask");

                        foreach (var languageMask in languageMasks)
                        {
                            LanguageMaskItem languageMaskItem = new LanguageMaskItem();
                            languageMaskItem.LanguageId = languageMask.Attribute("Language_Id").Value;
                            languageMaskItem.Mask = languageMask.Value;

                            maskItem.languageMaskItemList.Add(languageMaskItem);
                        }

                        maskItemList.Add(maskItem);
                    }
                }
                catch (IOException ex)
                {
                    MessageBox.Show("An error occurred while loading masks xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Masks xml file doesn't exist in the specified location.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void PopulateDataGridViewMasks()
        {
            int row = 0;

            foreach (var maskItem in maskItemList)
            {
                if (dataGridViewMasks.Rows.Count > row)
                {
                    dataGridViewMasks.Rows[row].Cells[0].Value = maskItem.MaskId;
                    dataGridViewMasks.Rows[row].Cells[1].Value = maskItem.MaskName;
                    dataGridViewMasks.Rows[row].Cells[2].Value = maskItem.GroupId;

                    row++;
                }
            }

            dataGridViewMasks.Rows[0].Selected = true;
            SelectionChangedHandler();
        }

        private void ClearGridViewMaskLanguages()
        {
            foreach (DataGridViewRow row in dataGridViewMaskLanguages.Rows)
            {
                DataGridViewComboBoxCell comboCell = (DataGridViewComboBoxCell)row.Cells[0];
                comboCell.Value = string.Empty;
                row.Cells[1].Value = string.Empty;
            }
        }

        private void DataGridViewMasks_SelectionChanged(object sender, EventArgs e)
        {
            SelectionChangedHandler();
        }

        private void SelectionChangedHandler()
        {
            int selectedItemsCount = dataGridViewMasks.SelectedRows.Count;

            if (selectedItemsCount > 0)
            {
                ClearGridViewMaskLanguages();

                PopulateGridViewMaskLanguages();

                string maskName = dataGridViewMasks.SelectedRows[0].Cells[1].Value.ToString().Trim();
                labelMaskLanguageDefinitions.Text = "Mask per language definitions for: " + maskName;
            }
        }

        private void PopulateGridViewMaskLanguages()
        {
            string maskId = dataGridViewMasks.SelectedRows[0].Cells[0].Value.ToString().Trim();
            string groupId = dataGridViewMasks.SelectedRows[0].Cells[2].Value.ToString().Trim();

            if (maskId != string.Empty && groupId != string.Empty)
            {
                MaskItem maskItem = maskItemList.Find(x => x.MaskId == maskId && x.GroupId == groupId);

                if (maskItem != null)
                {
                    int row = 0;

                    foreach (var maskItemLanguage in maskItem.languageMaskItemList)
                    {
                        if (dataGridViewMaskLanguages.Rows.Count > row)
                        {
                            string languageCountry = string.Empty;
                            DesktopModelObject.uniqueIdToCountryLanguageDictionary.TryGetValue(maskItemLanguage.LanguageId, out languageCountry);

                            dataGridViewMaskLanguages.Rows[row].Cells[0].Value = languageCountry;
                            dataGridViewMaskLanguages.Rows[row].Cells[1].Value = maskItemLanguage.Mask;

                            row++;
                        }
                    }
                }
            }
        }

        private void GetDataFromMaskLanguagesGrid()
        {
            MaskItem selectedMaskItem = GetSelectedMaskItem();

            if (selectedMaskItem != null)
            {
                selectedMaskItem.languageMaskItemList.Clear();

                foreach (DataGridViewRow row in dataGridViewMaskLanguages.Rows)
                {
                    if (row.Cells["Language"].Value != null && String.IsNullOrEmpty(row.Cells["Language"].Value.ToString()) == false &&
                        row.Cells["Mask"].Value != null && String.IsNullOrEmpty(row.Cells["Mask"].Value.ToString()) == false)
                    {
                        LanguageMaskItem languageMaskItem = new LanguageMaskItem();

                        string languageCountry = row.Cells["Language"].Value.ToString();
                        string languageId = string.Empty;
                        DesktopModelObject.uniqueCountryLanguageToIdDictionary.TryGetValue(languageCountry, out languageId);

                        languageMaskItem.LanguageId = languageId;
                        languageMaskItem.Mask = row.Cells["Mask"].Value.ToString();

                        if (languageMaskItem.LanguageId != string.Empty && languageMaskItem.Mask != string.Empty)
                        {
                            selectedMaskItem.languageMaskItemList.Add(languageMaskItem);
                        }
                    }
                }

                MaskItem maskItem = maskItemList.Find(x => x.MaskName == selectedMaskItem.MaskName);

                if (maskItem != null)
                {
                    maskItem = selectedMaskItem;
                }
            }
        }

        private MaskItem GetSelectedMaskItem()
        {
            MaskItem selectedMaskItem = null;

            int selectedItemsCount = dataGridViewMasks.SelectedRows.Count;

            if (selectedItemsCount > 0)
            {
                string maskName = dataGridViewMasks.SelectedRows[0].Cells[1].Value.ToString().Trim();
                selectedMaskItem = maskItemList.Where(x => x.MaskName == maskName).FirstOrDefault();
            }

            return selectedMaskItem;
        }

        private void GetDataFromMasksGrid()
        {
            maskItemListToSave.Clear();

            foreach (DataGridViewRow row in dataGridViewMasks.Rows)
            {
                if (row.Cells["MaskId"].Value != null && String.IsNullOrEmpty(row.Cells["MaskId"].Value.ToString()) == false &&
                    row.Cells["MaskName"].Value != null && String.IsNullOrEmpty(row.Cells["MaskName"].Value.ToString()) == false &&
                    row.Cells["GroupId"].Value != null && String.IsNullOrEmpty(row.Cells["GroupId"].Value.ToString()) == false)
                {
                    string maskName = row.Cells["MaskName"].Value.ToString();

                    MaskItem maskItem = maskItemList.Find(x => x.MaskName == maskName);

                    if (maskItem != null)
                    {
                        maskItem.MaskName = maskName;
                        maskItem.MaskId = row.Cells["MaskId"].Value.ToString();
                        maskItem.GroupId = row.Cells["GroupId"].Value.ToString();

                        maskItemListToSave.Add(maskItem);
                    }
                }
            }
        }

        private void DataGridViewMaskLanguages_Leave(object sender, EventArgs e)
        {
            GetDataFromMaskLanguagesGrid();
        }

        private void GetDataFromDataViewGrids()
        {
            GetDataFromMaskLanguagesGrid();
            GetDataFromMasksGrid();
        }

        private void ButtonOK_Click(object sender, EventArgs e)
        {
            GetDataFromDataViewGrids();
            SaveDataToXmlFile();

            GenerateMasksFiles();

            Close();
        }

        private void DataGridViewMasks_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            int row = e.RowIndex;
            int column = e.ColumnIndex;

            if (dataGridViewMasks.Rows[row].Cells["MaskId"].Value != null && String.IsNullOrEmpty(dataGridViewMasks.Rows[row].Cells["MaskId"].Value.ToString()) == false &&
                dataGridViewMasks.Rows[row].Cells["MaskName"].Value != null && String.IsNullOrEmpty(dataGridViewMasks.Rows[row].Cells["MaskName"].Value.ToString()) == false &&
                dataGridViewMasks.Rows[row].Cells["GroupId"].Value != null && String.IsNullOrEmpty(dataGridViewMasks.Rows[row].Cells["GroupId"].Value.ToString()) == false)
            {
                string maskName = dataGridViewMasks.Rows[row].Cells["MaskName"].Value.ToString().Trim();
                string maskId = dataGridViewMasks.Rows[row].Cells["MaskId"].Value.ToString().Trim();
                string groupId = dataGridViewMasks.Rows[row].Cells["GroupId"].Value.ToString().Trim();

                MaskItem maskItem = maskItemList.Find(x => x.MaskId == maskId && x.GroupId == groupId && x.MaskName == maskName);
                if (maskItem == null)
                {
                    maskItem = new MaskItem();
                    maskItem.MaskName = maskName;
                    maskItem.MaskId = maskId;
                    maskItem.GroupId = groupId;
                    maskItem.languageMaskItemList = new List<LanguageMaskItem>();

                    maskItemList.Add(maskItem);
                }
            }
        }

        private void SaveDataToXmlFile()
        {
            var sortedList = maskItemListToSave.OrderBy(x => Convert.ToInt32(x.GroupId)).ThenBy(x => Convert.ToInt32(x.MaskId));

            var element = new XElement("Root",
                            from mask in sortedList
                            select new XElement("Mask",
                                     new XAttribute("Group_Id", mask.GroupId),
                                     new XAttribute("Mask_Id", mask.MaskId),
                                     new XAttribute("Mask_Name", mask.MaskName),
                                         from lMask in mask.languageMaskItemList
                                         select new XElement("Language_Mask", 
                                            new XAttribute("Language_Id", lMask.LanguageId),
                                            lMask.Mask)));

            string pathAndFileName = GetLanguagePathAndFileName();

            element.Save(pathAndFileName, SaveOptions.OmitDuplicateNamespaces);
        }

        private void GenerateMasksFiles()
        {
            string maskFiles = "Generate mask files";
            OutputWindow_WriteLine(maskFiles + " - GENERATE CODE - START");

            GenerateMasksCppFile();
            GenerateMasksHFile();

            OutputWindow_WriteLine(maskFiles + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private void GenerateMasksHFile()
        {
            // Generate mask h file
            GenerateIfastMasksH_RuntimeTextTemplate page = new GenerateIfastMasksH_RuntimeTextTemplate();
            page.maskItemList = maskItemListToSave;
            string pageContent = page.TransformText();
            string strIfastMasksHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileNameMasksH;
            System.IO.File.WriteAllText(strIfastMasksHFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strIfastMasksHFileName, Color.Green);
        }

        private void GenerateMasksCppFile()
        {
            // Generate mask cpp file
            GenerateIfastMasksCpp_RuntimeTextTemplate page = new GenerateIfastMasksCpp_RuntimeTextTemplate();
            page.maskItemList = maskItemListToSave;
            page.uniqueIdToCountryLanguageDictionary = DesktopModelObject.uniqueIdToCountryLanguageDictionary;
            string pageContent = page.TransformText();
            string strIfastMasksCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileNameMasksCpp;
            System.IO.File.WriteAllText(strIfastMasksCppFileName, pageContent);

            OutputWindow_WriteIndentedLine("Generated file: " + strIfastMasksCppFileName, Color.Green);
        }
    }
}
