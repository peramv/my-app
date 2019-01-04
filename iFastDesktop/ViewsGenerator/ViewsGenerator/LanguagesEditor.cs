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
using System.Xml;
using System.Xml.Linq;

namespace ViewsGenerator
{
    public partial class LanguagesEditor : BaseForm
    {
        private List<LanguageItem> languageItemsList = new List<LanguageItem>();

        public LanguagesEditor()
        {
            this.InitializeComponent();

            for (int i = 0; i < 99; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(this.dataGridViewLanguages);

                row.Cells[0].Value = string.Empty;
                row.Cells[1].Value = string.Empty;
                row.Cells[2].Value = string.Empty;
                row.Cells[3].Value = string.Empty;

                dataGridViewLanguages.Rows.Add(row);
            }

            this.SetRowNumber(this.dataGridViewLanguages);
        }

        public string GetLanguagePathAndFileName()
        {
            return this.DataImplFolderPath + "\\languages.xml";
        }

        public void LoadLanguages()
        {
            string pathAndFileName = this.GetLanguagePathAndFileName();

            if (File.Exists(pathAndFileName))
            {
                try
                {
                    XDocument doc = XDocument.Load(pathAndFileName);

                    var languages = doc.Descendants("Language");

                    int row = 0;

                    foreach (var language in languages)
                    {
                        string languageId = language.Attribute("Language_Id").Value;
                        string languageName = language.Attribute("Language_Name").Value;
                        string country = language.Attribute("Country").Value;
                        string languageShort = language.Attribute("Language").Value;

                        if (dataGridViewLanguages.Rows.Count > row)
                        {
                            dataGridViewLanguages.Rows[row].Cells[0].Value = languageId;
                            dataGridViewLanguages.Rows[row].Cells[1].Value = languageName;
                            dataGridViewLanguages.Rows[row].Cells[2].Value = country;
                            dataGridViewLanguages.Rows[row].Cells[3].Value = languageShort;
                        }

                        row++;
                    }
                }
                catch (IOException ex)
                {
                    MessageBox.Show("An error occurred while loading languages xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Language xml file doesn't exist in the specified location.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void GetDataFromGrid()
        {
            int n = 0;

            foreach (DataGridViewRow row in dataGridViewLanguages.Rows)
            {
                if (row.Cells["LanguageId"].Value != null && int.TryParse(row.Cells["LanguageId"].Value.ToString(), out n) &&
                    row.Cells["LanguageName"].Value != null &&
                    row.Cells["Country"].Value != null &&
                    row.Cells["Language"].Value != null)
                {
                    LanguageItem languageItem = new LanguageItem();

                    languageItem.LanguageId = row.Cells["LanguageId"].Value.ToString();
                    languageItem.LanguageName = row.Cells["LanguageName"].Value.ToString();
                    languageItem.Country = row.Cells["Country"].Value.ToString();
                    languageItem.LanguageShort = row.Cells["Language"].Value.ToString();

                    if (languageItem.LanguageId != "" && languageItem.LanguageName != "" && languageItem.Country != "" && languageItem.LanguageShort != "")
                    {
                        this.languageItemsList.Add(languageItem);
                    }
                }
            }
        }

        private void SaveLanguages()
        {
            var sortedList = this.languageItemsList.OrderBy(x => Convert.ToInt32(x.LanguageId)).ToList();

            try
            {
                var element = new XElement("Root",
                                from lang in sortedList
                                select new XElement("Language",
                                         new XAttribute("Language_Id", lang.LanguageId),
                                         new XAttribute("Language_Name", lang.LanguageName),
                                         new XAttribute("Country", lang.Country),
                                         new XAttribute("Language", lang.LanguageShort)));

                string pathAndFileName = this.GetLanguagePathAndFileName();

                element.Save(pathAndFileName, SaveOptions.OmitDuplicateNamespaces);
            }
            catch (IOException ex)
            {
                MessageBox.Show("An error occurred while saving languages xml file. Error: " + ex, "Saving File Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonOK_Click(object sender, EventArgs e)
        {
            this.GetDataFromGrid();
            this.SaveLanguages();

            this.Close();
        }

        private void SetRowNumber(DataGridView dgv)
        {
            foreach (DataGridViewRow row in dgv.Rows)
            {
                row.HeaderCell.Value = (row.Index + 1).ToString();
            }
        }

        private struct LanguageItem
        {
            public string LanguageId { get; set; }
            public string LanguageName { get; set; }
            public string Country { get; set; }
            public string LanguageShort { get; set; }
        }
    }
}
