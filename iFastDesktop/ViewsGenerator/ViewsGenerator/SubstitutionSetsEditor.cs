using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using ViewsGenerator.Templates.Desktop;

namespace ViewsGenerator
{
    public partial class SubstitutionSetsEditor : BaseForm
    {
        private readonly string substitutionSetHFile = "ifast_substitutions.h";
        private int rowIndex = 0;
        SubstitutionSetItem selectedSubstitutionSetItem = null;
        Dictionary<string, string> dictionarySelectedSubstitutionSet = new Dictionary<string, string>();

        public SubstitutionSetsEditor()
        {
            InitializeComponent();

            for (int i = 0; i < 199; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewSelectedSubstitutionSet);

                row.Cells[0].Value = string.Empty;
                row.Cells[1].Value = string.Empty;

                dataGridViewSelectedSubstitutionSet.Rows.Add(row);
            }

            SetRowNumber(dataGridViewSelectedSubstitutionSet);

            dataGridViewSelectedSubstitutionSet.ClearSelection();

            this.buttonMoveUp.Enabled = false;
            this.buttonMoveDown.Enabled = false;

            this.buttonDelete.Enabled = false;
        }

        public void LoadSubstitionSetsUI()
        {
            this.objectListViewSubstitutionSets.SetObjects(DesktopModelObject.substitutionsList);
        }

        private void AddMoreRows(int numberOfRowsToAdd)
        {
            for (int i = 0; i <= numberOfRowsToAdd; i++)
            {
                DataGridViewRow row = new DataGridViewRow();
                row.CreateCells(dataGridViewSelectedSubstitutionSet);

                row.Cells[0].Value = string.Empty;
                row.Cells[1].Value = string.Empty;

                dataGridViewSelectedSubstitutionSet.Rows.Add(row);
            }

            SetRowNumber(dataGridViewSelectedSubstitutionSet);
        }

        private void ObjectListViewSubstitutionSet_SelectionChanged(object sender, EventArgs e)
        {
            ClearGridView();

            selectedSubstitutionSetItem = (SubstitutionSetItem)this.objectListViewSubstitutionSets.SelectedObject;

            if (selectedSubstitutionSetItem == null)
            {
                return;
            }

            if (selectedSubstitutionSetItem.KeysArray.Count == selectedSubstitutionSetItem.ValuesArray.Count)
            {
                int count = selectedSubstitutionSetItem.KeysArray.Count;

                if (count > dataGridViewSelectedSubstitutionSet.RowCount)
                {
                    int numberOfRowsToAdd = count - dataGridViewSelectedSubstitutionSet.RowCount + 100;
                    AddMoreRows(numberOfRowsToAdd);
                }

                for (int i = 0; i < count; i++)
                {
                    SelectedSubstitutionItem selectedSubstitutionItem = new SelectedSubstitutionItem();
                    selectedSubstitutionItem.Key = selectedSubstitutionSetItem.KeysArray[i].ToString();
                    selectedSubstitutionItem.Value = selectedSubstitutionSetItem.ValuesArray[i].ToString();

                    dataGridViewSelectedSubstitutionSet.Rows[i].Cells[0].Value = selectedSubstitutionSetItem.KeysArray[i].ToString();
                    dataGridViewSelectedSubstitutionSet.Rows[i].Cells[1].Value = selectedSubstitutionSetItem.ValuesArray[i].ToString(); 
                }
            }

            string selectedSubstitutionSet = selectedSubstitutionSetItem.Name;

            if (selectedSubstitutionSetItem.Language != null && selectedSubstitutionSetItem.Language != "")
            {
                selectedSubstitutionSet += ", " + selectedSubstitutionSetItem.Language;
            }

            if (selectedSubstitutionSetItem.MarketName != null && selectedSubstitutionSetItem.MarketName != "")
            {
                selectedSubstitutionSet += ", " + selectedSubstitutionSetItem.MarketName;
            }

            if (selectedSubstitutionSetItem.ClientName != null && selectedSubstitutionSetItem.ClientName != "")
            {
                selectedSubstitutionSet += ", " + selectedSubstitutionSetItem.ClientName;
            }

            this.labelSubstitutionSet.Text = "Substitution set: " + selectedSubstitutionSet;

            this.buttonDelete.Enabled = true;
        }

        private void ClearGridView()
        {
            foreach (DataGridViewRow row in dataGridViewSelectedSubstitutionSet.Rows)
            {
                foreach (DataGridViewCell cell in row.Cells)
                {
                    cell.Value = "";
                }
            }
        }

        private void dataGridViewSelectedSubstitutionSet_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.C)
            {
                CopyDataToClipboard();
                e.Handled = true;
            }
            else if (e.Control && e.KeyCode == Keys.V)
            {
                PasteFromClipboard();
            }
            else if (e.Control && e.KeyCode == Keys.X)
            {
                CutDataToClipboard();
                e.Handled = true;
            }
        }

        private void CutDataToClipboard()
        {
            DataObject d = dataGridViewSelectedSubstitutionSet.GetClipboardContent();
            Clipboard.SetDataObject(d);

            foreach (DataGridViewCell cell in dataGridViewSelectedSubstitutionSet.SelectedCells)
            {
                cell.Value = string.Empty;
            }
        }

        private void CopyDataToClipboard()
        {
            dataGridViewSelectedSubstitutionSet.ClipboardCopyMode = DataGridViewClipboardCopyMode.EnableWithoutHeaderText;
            DataObject d = dataGridViewSelectedSubstitutionSet.GetClipboardContent();
            Clipboard.SetDataObject(d);
        }

        private void PasteFromClipboard()
        {
            string CopiedContent = Clipboard.GetText();
            string[] Lines = CopiedContent.Split('\n');
            int StartingRow = dataGridViewSelectedSubstitutionSet.CurrentCell.RowIndex;
            int StartingColumn = dataGridViewSelectedSubstitutionSet.CurrentCell.ColumnIndex;

            AddMoreRows(Lines.Count());

            foreach (var line in Lines)
            {
                if (StartingRow <= (dataGridViewSelectedSubstitutionSet.Rows.Count - 1))
                {
                    string[] cells = line.Split('\t');
                    int ColumnIndex = StartingColumn;

                    for (int i = 0; i < cells.Length && ColumnIndex <= (dataGridViewSelectedSubstitutionSet.Columns.Count - 1); i++)
                    {
                        dataGridViewSelectedSubstitutionSet[ColumnIndex++, StartingRow].Value = cells[i];
                    }

                    StartingRow++;
                }
            }
        }

        private void ContextMenuStripGridView_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            try
            {
                if (e.ClickedItem.Text == "Cut")
                {
                    CutDataToClipboard();
                }
                else if (e.ClickedItem.Text == "Copy")
                {
                    CopyDataToClipboard();
                }
                else if (e.ClickedItem.Text == "Paste")
                {
                    PasteFromClipboard();
                }
                else if (e.ClickedItem.Text == "Delete Row")
                {
                    foreach (DataGridViewCell cell in dataGridViewSelectedSubstitutionSet.SelectedCells)
                    {
                        if (cell != null && cell.RowIndex != -1)
                        {
                            dataGridViewSelectedSubstitutionSet.Rows.RemoveAt(cell.RowIndex);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Substitution Set Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void dataGridViewSelectedSubstitutionSet_CellMouseDown(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.ColumnIndex >= 0 && e.RowIndex >= 0)
            {
                if (e.Button == MouseButtons.Left)
                {
                    if (!IsCellSelected(e.RowIndex, e.ColumnIndex))
                    {
                        dataGridViewSelectedSubstitutionSet.ClearSelection();
                        dataGridViewSelectedSubstitutionSet.Rows[e.RowIndex].Cells[e.ColumnIndex].Selected = true;
                    }
                }
            }
        }

        private void dataGridViewSelectedSubstitutionSet_CellMouseUp(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (IsCellSelected(e.RowIndex, e.ColumnIndex))
                {
                    this.rowIndex = e.RowIndex;
                    this.contextMenuStripGridView.Show(this.dataGridViewSelectedSubstitutionSet, e.Location);
                    contextMenuStripGridView.Show(Cursor.Position);
                }
            }
        }

        private bool IsCellSelected(int cellRow, int cellColumn)
        {
            bool isCellSelected = false;

            foreach (DataGridViewCell cell in dataGridViewSelectedSubstitutionSet.SelectedCells)
            {
                if (cell != null && cell.RowIndex == cellRow && cell.ColumnIndex == cellColumn)
                {
                    isCellSelected = true;
                    break;
                }
            }

            return isCellSelected;
        }

        private void SetRowNumber(DataGridView dgv)
        {
            foreach (DataGridViewRow row in dgv.Rows)
            {
                row.HeaderCell.Value = (row.Index + 1).ToString();
            }
        }

        private void ObjectListViewSubstitutionSet_Leave(object sender, EventArgs e)
        {
            GetDataFromGrid();

            if (!this.buttonMoveUp.Focused && !this.buttonMoveDown.Focused)
            {
                dataGridViewSelectedSubstitutionSet.ClearSelection();
            }

            this.buttonDelete.Enabled = false;
        }

        private void ButtonMoveUp_Click(object sender, EventArgs e)
        {
            MoveUp(dataGridViewSelectedSubstitutionSet);
        }

        private void ButtonMoveDown_Click(object sender, EventArgs e)
        {
            MoveDown(dataGridViewSelectedSubstitutionSet);
        }

        private void MoveUp(DataGridView dgv)
        {
            if (dgv.RowCount <= 0)
            {
                return;
            }

            if (dgv.SelectedRows.Count <= 0)
            {
                return;
            }

            var index = dgv.SelectedCells[0].OwningRow.Index;

            if (index == 0)
            {
                return;
            }

            var rows = dgv.Rows;
            var prevRow = rows[index - 1];
            rows.Remove(prevRow);
            prevRow.Frozen = false;
            rows.Insert(index, prevRow);
            dgv.ClearSelection();
            dgv.Rows[index - 1].Selected = true;

            EnableMoveUpAndDownButtons();
        }

        private void MoveDown(DataGridView dgv)
        {
            if (dgv.RowCount <= 0)
            {
                return;
            }

            if (dgv.SelectedRows.Count <= 0)
            {
                return;
            }

            var rowCount = dgv.Rows.Count;
            var index = dgv.SelectedCells[0].OwningRow.Index;

            if (index == (rowCount - 2)) // include the header row
            {
                return;
            }

            var rows = dgv.Rows;
            var nextRow = rows[index + 1];
            rows.Remove(nextRow);
            nextRow.Frozen = false;
            rows.Insert(index, nextRow);
            dgv.ClearSelection();
            dgv.Rows[index + 1].Selected = true;

            EnableMoveUpAndDownButtons();
        }

        private void EnableMoveUpAndDownButtons()
        {
            int selectedItemsCount = dataGridViewSelectedSubstitutionSet.SelectedRows.Count;

            if (selectedItemsCount > 0)
            {
                if (selectedItemsCount > 1)
                {
                    this.buttonMoveUp.Enabled = false;
                    this.buttonMoveDown.Enabled = false;
                }
                else
                {
                    int selectedIndex = dataGridViewSelectedSubstitutionSet.SelectedCells[0].OwningRow.Index;

                    if (dataGridViewSelectedSubstitutionSet[0, selectedIndex].Value != null &&
                        dataGridViewSelectedSubstitutionSet[1, selectedIndex].Value != null)
                    {
                        string key = dataGridViewSelectedSubstitutionSet[0, selectedIndex].Value.ToString();
                        string value = dataGridViewSelectedSubstitutionSet[1, selectedIndex].Value.ToString();

                        if (key == "" && value == "")
                        {
                            this.buttonMoveUp.Enabled = false;
                            this.buttonMoveDown.Enabled = false;
                        }
                        else
                        {
                            if (selectedIndex == 0)
                            {
                                this.buttonMoveUp.Enabled = false;
                            }
                            else
                            {
                                this.buttonMoveUp.Enabled = true;
                            }

                            if (selectedIndex == dataGridViewSelectedSubstitutionSet.RowCount - 1)
                            {
                                this.buttonMoveDown.Enabled = false;
                            }
                            else
                            {
                                this.buttonMoveDown.Enabled = true;
                            }
                        }
                    }
                }
            }
            else
            {
                this.buttonMoveUp.Enabled = false;
                this.buttonMoveDown.Enabled = false;
            }
        }

        private void DataGridViewSelectedSubstitutionSet_SelectionChanged(object sender, EventArgs e)
        {
            EnableMoveUpAndDownButtons();
        }

        private void buttonGenerateCode_Click(object sender, EventArgs e)
        {
            GetDataFromGrid();

            if (selectedSubstitutionSetItem.isNewSubstitutionSet)
            {
                GenerateNewSubstitutionSet();
            }
            else
            {
                GenerateModifiedExistingSubstitutionSet();
            }
        }

        private void GetDataFromGrid()
        {
            dictionarySelectedSubstitutionSet.Clear();

            foreach (DataGridViewRow row in dataGridViewSelectedSubstitutionSet.Rows)
            {
                if (row.Cells["ColumnKeys"].Value != null &&
                    row.Cells["ColumnValues"].Value != null)
                {
                    string key = row.Cells["ColumnKeys"].Value.ToString().Replace("\r", "");
                    string value = row.Cells["ColumnValues"].Value.ToString().Replace("\r", "");

                    if (key != "" && value != "")
                    {
                        try
                        {
                            dictionarySelectedSubstitutionSet.Add(key, value);
                        }
                        catch (ArgumentException)
                        {
                            MessageBox.Show("An element with Key: " + key + " already exists.", "Substitution Set Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else
                    {
                        if (key != "" && value == "")
                        {
                            MessageBox.Show("Value is missing for key: " + key, "Substitution Set Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        else if (key == "" && value != "")
                        {
                            MessageBox.Show("Key is missing for value: " + value, "Substitution Set Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                }
            }

            //dictionarySelectedSubstitutionSet = dictionarySelectedSubstitutionSet.OrderBy(x => x.Key).ToDictionary(x => x.Key, x => x.Value);

            if (selectedSubstitutionSetItem != null)
            {
                selectedSubstitutionSetItem.KeysArray = new ArrayList(dictionarySelectedSubstitutionSet.Keys);
                selectedSubstitutionSetItem.ValuesArray = new ArrayList(dictionarySelectedSubstitutionSet.Values);
            }
        }

        private void GenerateNewSubstitutionSet()
        {
            OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - START");

            OutputWindow_WriteLine("Generate new substitution set with id: " + selectedSubstitutionSetItem.SubstitutionSetId);

            GenerateNewSubstitutionSetInSubstitutionsCppFile();
            GenerateNewSubstitutionSetInSubstitutionsHFile();
            GenerateNewSubstitutionSetInSubstitutionsChooserCppFile();

            OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private SubstitutionSetItem GetLastExistingSubstitutionSetItem()
        {
            SubstitutionSetItem lastSubstitutionSetsItem = DesktopModelObject.substitutionsList.
                                                           Where(x => x.isNewSubstitutionSet == false && x.SubstitutionSetCreationIndexInt < selectedSubstitutionSetItem.SubstitutionSetCreationIndexInt).
                                                           OrderBy(x => Convert.ToInt32(x.SubstitutionSetCreationIndex)).Last();

            return lastSubstitutionSetsItem;
        }

        private void GenerateNewSubstitutionSetInSubstitutionsCppFile()
        {
            SubstitutionSetItem lastSubstitutionSetsItem = GetLastExistingSubstitutionSetItem();

            var newItem = DesktopModelObject.substitutionsList.OrderBy(x => x.SubstitutionSetId)
                            .Select((Value, Index) => new { Value, Index }).First(x => x.Value.SubstitutionSetId == selectedSubstitutionSetItem.SubstitutionSetId);

            if (lastSubstitutionSetsItem != null)
            {
                var files = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                             where (file.Contains("ifast_substitutions_") && !file.Contains("chooser"))
                             from line in File.ReadLines(file, Encoding.Default)
                             where line.Contains("extern const BFSubstitutionSet SubSet_" + lastSubstitutionSetsItem.SubstitutionSetId + ";")
                             select new
                             {
                                 File = file,
                                 Line = line
                             }).Single();

                string fileName = Path.GetFileName(files.File);
                selectedSubstitutionSetItem.FileName = fileName;
                string fileFullPathName = DataImplFolderPath + "\\" + fileName;

                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where (line.Contains("namespace ifds") || (line.Contains(lastSubstitutionSetsItem.KeysName) && line.Contains(lastSubstitutionSetsItem.ValuesName)))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 2)
                {
                    // Generate substitutions cpp file
                    SubstitutionsCpp_RuntimeTextTemplate page = new SubstitutionsCpp_RuntimeTextTemplate();
                    page.substitutionSetItem = selectedSubstitutionSetItem;
                    page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfPreviousItemLastLine = significantLines.ToList().ElementAt(1).Index;
                    page.lines = lines.ToList();
                    String pageContent = page.TransformText();
                    string strSubstitutionsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                    System.IO.File.WriteAllText(strSubstitutionsCppFileName, pageContent, Encoding.UTF8);

                    OutputWindow_WriteIndentedLine("Generated file: " + strSubstitutionsCppFileName, Color.Green);
                }
            }
            // new substitution item is first in the list of all substitution items (is this realy needed?)
            else
            {
                string fileName = "ifast_substitutions_0.cpp";
                selectedSubstitutionSetItem.FileName = fileName;

                string fileFullPathName = GetFileFullPathName(fileName);

                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where line.Contains("namespace ifds")
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 1)
                {
                    // Generate substitutions cpp file
                    SubstitutionsCpp_RuntimeTextTemplate page = new SubstitutionsCpp_RuntimeTextTemplate();
                    page.substitutionSetItem = selectedSubstitutionSetItem;
                    page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfPreviousItemLastLine = page.indexOfIfdsNamespaceLine + 2;
                    page.lines = lines.ToList();
                    String pageContent = page.TransformText();
                    string strSubstitutionsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                    System.IO.File.WriteAllText(strSubstitutionsCppFileName, pageContent, Encoding.UTF8);

                    OutputWindow_WriteIndentedLine("Generated file: " + strSubstitutionsCppFileName, Color.Green);
                }
            }
        }

        private void GenerateNewSubstitutionSetInSubstitutionsHFile()
        {
            var fileName = "ifast_substitutions.h";

            string fileFullPathName = GetFileFullPathName(fileName);

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.Contains("extern const BFSubstitutionSet SubSet_Empty;") || line.Contains("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 3)
            {
                SubstitutionsH_RuntimeTextTemplate page = new SubstitutionsH_RuntimeTextTemplate();
                page.substitutionSetItem = selectedSubstitutionSetItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfSubSetEmptyLine = significantLines.ToList().ElementAt(1).Index;
                page.indexOfIfdsNamespaceCloseLine = significantLines.ToList().ElementAt(2).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strSubstitutionsHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strSubstitutionsHFileName, pageContent, Encoding.UTF8);

                OutputWindow_WriteIndentedLine("Generated file: " + strSubstitutionsHFileName, Color.Green);
            }
        }

        private void GenerateNewSubstitutionSetInSubstitutionsChooserCppFile()
        {
            var files = from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                         where file.Contains("ifast_substitutions_chooser_")
                         from line in File.ReadLines(file, Encoding.Default)
                         where line.Contains("extern const BFSubstitutionSet SubSet_" + selectedSubstitutionSetItem.SubstitutionSetShortId)
                         select new
                         {
                             File = file,
                             Line = line
                         };

            if (files.Count() == 0)
            {
                GenerateNewChooserFunction();
            }
            else
            {
                string fileName = Path.GetFileName(files.ElementAt(0).File);
                GenerateUpdatedExistingChooserFunction(fileName);
            }
        }

        private void GenerateNewChooserFunction()
        {
            SubstitutionSetItem lastSubstitutionSetsItem = GetLastExistingSubstitutionSetItem();

            if (lastSubstitutionSetsItem != null)
            {
                var files = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                             where file.Contains("ifast_substitutions_chooser")
                             from line in File.ReadLines(file, Encoding.Default)
                             where line.Contains("extern const BFSubstitutionSet SubSet_" + lastSubstitutionSetsItem.SubstitutionSetId + ";")
                             select new
                             {
                                 File = file,
                                 Line = line
                             }).Single();

                string fileName = Path.GetFileName(files.File);
                string fileFullPathName = DataImplFolderPath + "\\" + fileName;

                var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

                var significantLines = from line in lines
                                       where (line.Contains("namespace ifds") || (line.Contains(lastSubstitutionSetsItem.KeysName) && line.Contains(lastSubstitutionSetsItem.ValuesName)))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

                int count = significantLines.Count();

                if (count == 2)
                {
                    // Generate substitutions cpp file
                    AddNewChooserCpp_RuntimeTextTemplate page = new AddNewChooserCpp_RuntimeTextTemplate();
                    page.substitutionSetItem = selectedSubstitutionSetItem;
                    page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                    page.indexOfIfdsNamespaceCloseLine = significantLines.ToList().ElementAt(1).Index;
                    page.lines = lines.ToList();
                    String pageContent = page.TransformText();
                    string strAddChooserFunctionToCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                    System.IO.File.WriteAllText(strAddChooserFunctionToCppFileName, pageContent, Encoding.UTF8);

                    OutputWindow_WriteIndentedLine("Generated file: " + strAddChooserFunctionToCppFileName, Color.Green);
                }
            }
        }

        private void GenerateUpdatedExistingChooserFunction(string fileName)
        {
            string fileFullPathName = GetFileFullPathName(fileName);

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            // Not all substitution sets are actualy used, they are all defined in ifast_substitutions_*.cpp/h files, but in ifast_substitutions_chooser_*cpp files only some of them are used.
            // Instead of taking all substitution sets with the given id, make a search in the chooser file and take only used ids, so that the code is generated the same as in existing chooser files.
            List<SubstitutionSetItem> sameCreationIndexSubstitutionSetsAll = DesktopModelObject.substitutionsList.Where(x => x.SubstitutionSetCreationIndexInt == selectedSubstitutionSetItem.SubstitutionSetCreationIndexInt).OrderBy(x => x.SubstitutionSetId).ToList();

            var sameCreationIndexSubstitutionSetsFromChooserFile = (from line in lines
                                                                    where line.Contains("extern const BFSubstitutionSet SubSet_" + selectedSubstitutionSetItem.SubstitutionSetShortId)
                                                                        select new
                                                                        {
                                                                            Line = line,
                                                                            Index = lines.IndexOf(line)
                                                                        }).ToList();

            // This list should contain only substitutionSet items which are present in the chooser file plus the new substitutionSet.
            List<SubstitutionSetItem> sameCreationIndexSubstitutionSets = new List<SubstitutionSetItem>();

            foreach (var substitutionSet in sameCreationIndexSubstitutionSetsFromChooserFile)
            {
                string substitutionSetId = substitutionSet.Line.Replace("extern const BFSubstitutionSet SubSet_", "").Replace(";", "").Trim(); 
                SubstitutionSetItem substitutionSetItem = sameCreationIndexSubstitutionSetsAll.Find(x => x.SubstitutionSetId == substitutionSetId);

                if (substitutionSetItem != null)
                {
                    sameCreationIndexSubstitutionSets.Add(substitutionSetItem);
                }
            }

            sameCreationIndexSubstitutionSets.Add(selectedSubstitutionSetItem);
            sameCreationIndexSubstitutionSets = sameCreationIndexSubstitutionSets.OrderBy(x => x.SubstitutionSetId).ToList();

            var substitutionSetLines = from line in lines
                                       where (line.Contains("namespace ifds") || line.Contains("extern const BFSubstitutionSet SubSet_" + selectedSubstitutionSetItem.SubstitutionSetShortId) || 
                                                line.Contains("return SubSet_" + selectedSubstitutionSetItem.SubstitutionSetShortId))
                                       select new
                                       {
                                           Line = line,
                                           Index = lines.IndexOf(line)
                                       };

            int count = substitutionSetLines.Count();

            if (count >= 3)
            {
                int indexOfIfdsNamspaceLine = substitutionSetLines.ElementAt(0).Index;
                int firstSignificantLine = substitutionSetLines.ElementAt(1).Index;
                int lastSignificantLine = substitutionSetLines.ElementAt(count - 2).Index;

                // Generate substitutions cpp file
                ReplaceChooserCpp_RuntimeTextTemplate page = new ReplaceChooserCpp_RuntimeTextTemplate();
                page.substitutionSetItem = selectedSubstitutionSetItem;
                page.indexOfIfdsNamespaceLine = indexOfIfdsNamspaceLine;
                page.indexOfReplaceStartLine = firstSignificantLine;
                page.indexOfReplaceEndLine = lastSignificantLine;
                page.lines = lines.ToList();
                page.substitutionSetItemList = sameCreationIndexSubstitutionSets;
                page.SetUsedLanguagesInSetsChooser();
                String pageContent = page.TransformText();
                string strReplaceChooserFunctionInCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strReplaceChooserFunctionInCppFileName, pageContent, Encoding.UTF8);

                OutputWindow_WriteIndentedLine("Generated file: " + strReplaceChooserFunctionInCppFileName, Color.Green);
            }
        }

        private void GenerateModifiedExistingSubstitutionSet()
        {
            OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - START");

            string fileFullPathName = GetFileFullPathName(selectedSubstitutionSetItem.FileName);

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.Contains("static const I_CHAR* " + selectedSubstitutionSetItem.KeysName) ||
                                            line.Contains("static const I_CHAR* " + selectedSubstitutionSetItem.ValuesName) || 
                                            line.Contains("extern const BFSubstitutionSet SubSet_" + selectedSubstitutionSetItem.SubstitutionSetId))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 4)
            {
                // Generate substitutions file
                ReplaceSubstitutionsSetCpp_RuntimeTextTemplate page = new ReplaceSubstitutionsSetCpp_RuntimeTextTemplate();
                page.substitutionSetItem = selectedSubstitutionSetItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfArrayKeysLine = significantLines.ToList().ElementAt(1).Index;
                page.indexOfArrayValuesLine = significantLines.ToList().ElementAt(2).Index;
                page.indexOfSubstitutionSetLine = significantLines.ToList().ElementAt(3).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastSubstitutionsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + selectedSubstitutionSetItem.FileName;
                System.IO.File.WriteAllText(strIfastSubstitutionsCppFileName, pageContent, Encoding.UTF8);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastSubstitutionsCppFileName, Color.Green);

                OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - END");
                OutputWindow_WriteEmptyLine();
            }
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            AddSubstitutionSetForm addSubstitutionSetForm = new AddSubstitutionSetForm();
            addSubstitutionSetForm.model = DesktopModelObject;
            addSubstitutionSetForm.InitializeData();

            DialogResult result = addSubstitutionSetForm.ShowDialog(this);
            if (result == DialogResult.OK)
            {
                LoadSubstitionSetsUI();
                objectListViewSubstitutionSets.Focus();
                objectListViewSubstitutionSets.EnsureModelVisible(addSubstitutionSetForm.NewSubstitutionSetItem);
                objectListViewSubstitutionSets.SelectObject(addSubstitutionSetForm.NewSubstitutionSetItem);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            var files = from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                         where file.Contains("ifast_substitutions_chooser")
                         from line in File.ReadLines(file, Encoding.Default)
                         where line.Contains("extern const BFSubstitutionSet SubSet_" + selectedSubstitutionSetItem.SubstitutionSetId + ";")
                         select new
                         {
                             File = file,
                             Line = line
                         };

            if (files.Count() > 0)
            {
                MessageBox.Show("Selected Substitution Set is used in chooser functions\nand cannot be deleted.", "Substitution Sets Editor Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            GenerateSubstitutionSetDeleteFromFiles();

            // Update model
            DesktopModelObject.substitutionsList.Remove(selectedSubstitutionSetItem);
            DesktopModelObject.distinctSubstitutionsList.Remove(selectedSubstitutionSetItem);

            // Update GUI
            objectListViewSubstitutionSets.RemoveObject(selectedSubstitutionSetItem);
        }

        private void GenerateSubstitutionSetDeleteFromFiles()
        {
            OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - START");

            OutputWindow_WriteLine("Deleted substitution set with id: " + selectedSubstitutionSetItem.SubstitutionSetId);

            GenerateDeleteSubstitutionSetInSubstitutionsCppFile();
            GenerateDeleteSubstitutionSetInSubstitutionsHFile();

            OutputWindow_WriteLine(selectedSubstitutionSetItem.Name + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private void GenerateDeleteSubstitutionSetInSubstitutionsCppFile()
        {
            string fileFullPathName = GetFileFullPathName(selectedSubstitutionSetItem.FileName);

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") ||
                                          line.Contains("static const I_CHAR* " + selectedSubstitutionSetItem.KeysName) ||
                                          (line.Contains(selectedSubstitutionSetItem.KeysName) && line.Contains(selectedSubstitutionSetItem.ValuesName)))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 3)
            {
                // Generate substitutions file
                GenerateDeleteSubstitutionSetCpp_RuntimeTextTemplate page = new GenerateDeleteSubstitutionSetCpp_RuntimeTextTemplate();
                page.substitutionSetItem = selectedSubstitutionSetItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfAkeysLine = significantLines.ToList().ElementAt(1).Index;
                page.indexOfAkeysAvaluesLine = significantLines.ToList().ElementAt(2).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastSubstitutionsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + selectedSubstitutionSetItem.FileName;
                System.IO.File.WriteAllText(strIfastSubstitutionsCppFileName, pageContent, Encoding.UTF8);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastSubstitutionsCppFileName, Color.Green);
            }
        }

        private void GenerateDeleteSubstitutionSetInSubstitutionsHFile()
        {
            string fileFullPathName = GetFileFullPathName(substitutionSetHFile);

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") && !line.Contains("// end namespace ifds"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 1)
            {
                // Generate substitutions h file
                GenerateDeleteSubstitutionSetH_RuntimeTextTemplate page = new GenerateDeleteSubstitutionSetH_RuntimeTextTemplate();
                page.substitutionSetItem = selectedSubstitutionSetItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastSubstitutionsHFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + substitutionSetHFile;
                System.IO.File.WriteAllText(strIfastSubstitutionsHFileName, pageContent, Encoding.UTF8);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastSubstitutionsHFileName, Color.Green);
            }
        }

        private void ObjectListViewSubstitutionSet_Enter(object sender, EventArgs e)
        {
            selectedSubstitutionSetItem = (SubstitutionSetItem)this.objectListViewSubstitutionSets.SelectedObject;

            if (selectedSubstitutionSetItem != null)
            {
                this.buttonDelete.Enabled = true;
            }
        }

        private string GetFileFullPathName(string fileName)
        {
            string fileFullPathName = DataImplFolderPath + "\\" + fileName;
            string generatedFileFullPathName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;

            if (File.Exists(generatedFileFullPathName))
            {
                fileFullPathName = generatedFileFullPathName;
            }

            return fileFullPathName;
        }
    }

    public class SelectedSubstitutionItem
    {
        public string Key { get; set; }
        public string Value { get; set; }
    }
}
