using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using WeifenLuo.WinFormsUI.Docking;

namespace ViewsGenerator
{
    public partial class DataSetExplorer : BaseForm
    {
        public DataSetExplorer()
        {
            this.InitializeComponent();
        }

        public void LoadDataSetFiles()
        {
            this.DesktopModelObject.dataSetItemList.Clear();
            this.objectListViewDataSets.ClearObjects();

            if (string.IsNullOrEmpty(this.DataImplFolderPath))
            {
                MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (Directory.Exists(this.DataImplFolderPath))
            {
                var files = from file in Directory.EnumerateFiles(this.DataImplFolderPath, "*.hpp", SearchOption.TopDirectoryOnly)
                            where file.Contains("dse_")
                            from line in File.ReadLines(file, Encoding.Default)
                            where line.Contains("extern __declspec(dllimport) const BFDataId")
                            select new
                            {
                                File = file,
                                Line = line
                            };

                foreach (var file in files)
                {
                    DataSetItem dataSetItem = new DataSetItem();

                    dataSetItem.DataSetItemFileName = Path.GetFileName(file.File);
                    string strDataSetItemName = file.Line.Replace("extern __declspec(dllimport) const BFDataId", "").Replace(";", "").Trim();
                    dataSetItem.DataSetItemName = strDataSetItemName;

                    string dataSetId = string.Empty;
                    string strDataSetItemNameFormatedForDictionarySearch = strDataSetItemName.ReplaceFirst("_", ".").Replace("Repeat_Record", "RepeatRecord");
                    if (DesktopModelObject.dataSetNameAndIDsDictionary.TryGetValue(strDataSetItemNameFormatedForDictionarySearch, out dataSetId))
                    {
                        dataSetItem.DataSetId = dataSetId;
                    }

                    DesktopModelObject.dataSetItemList.Add(dataSetItem);
                }

                int count = DesktopModelObject.dataSetItemList.Count();

                this.objectListViewDataSets.SetObjects(DesktopModelObject.dataSetItemList);
            }
        }

        private void ObjectListViewDataSets_DoubleClick(object sender, EventArgs e)
        {
            DataSetItem selectedObj = (DataSetItem)objectListViewDataSets.SelectedObject;

            if (selectedObj != null)
            {
                MainForm form = (MainForm)this.ParentForm;
                form.OpenDataSetEditor(selectedObj.DataSetItemFileName, selectedObj.DataSetItemName);
            }
        }
    }

    public class DataSetItem
    {
        public string DataSetId { get; set; }
        public string DataSetItemName { get; set; }
        public string DataSetItemFileName { get; set; }
    }
}
