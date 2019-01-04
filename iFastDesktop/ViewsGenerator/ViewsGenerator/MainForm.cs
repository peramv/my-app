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
using WeifenLuo.WinFormsUI.Docking;

namespace ViewsGenerator
{
    public partial class MainForm : Form, IMainFormInterface
    {
        private readonly string generatedFilesOutputFolder = "\\generated_files\\";
        private readonly string helpFilesFolder = "\\Help\\";
        private readonly string viewsGeneratorConfigFileName = "viewsgenerator_config.xml";
        private ModelDesktop model = new ModelDesktop();
        private ModelProgress modelProgress = new ModelProgress();
        private DataSetExplorer dataSetExplorer = new DataSetExplorer();
        private ProgressViewDataExplorer progressViewDataExplorer = new ProgressViewDataExplorer();
        private OutputWindow outputWindow = new OutputWindow();


        public string GetGeneratedFilesOutputFolder { get { return generatedFilesOutputFolder; } }

        public MainForm()
        {
            InitializeComponent();

            this.WindowState = FormWindowState.Maximized;
            this.toolbarNewDataSet.Enabled = false;
            this.newDataSetMenuItem.Enabled = false;

            this.toolbarButtonOpenFieldsEditor.Enabled = false;
            this.openFieldsEditorToolStripMenuItem.Enabled = false;

            this.toolbarButtonOpenSubstitutionSetsEditor.Enabled = false;
            this.openSubstitutionSetEditorToolStripMenuItem.Enabled = false;

            this.toolStripButton_NewViewResponseSet.Enabled = false;
            this.newViewResponseSetToolStripMenuItem.Enabled = false;

            this.toolStripButton_NewViewTransactionSet.Enabled = false;
            this.newViewTransactionSetToolStripMenuItem.Enabled = false;

            // Read folder paths from the config file if available
            GetFolderPathsFromConfig();

            dataSetExplorer.DataImplFolderPath = dataImplFolderPath.Text;
            dataSetExplorer.Show(dockPanel1, DockState.DockLeft);

            progressViewDataExplorer.ViewFolderPath = textBoxViewFolderPath.Text;
            progressViewDataExplorer.Show(dockPanel1, DockState.DockLeft);
            progressViewDataExplorer.MainFormInterface = this;

            outputWindow.Show(dockPanel1, DockState.DockBottom);
        }

        public void GetFolderPathsFromConfig()
        {
            string dir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string configPathAndFileName = dir + "\\" + viewsGeneratorConfigFileName;

            if (File.Exists(configPathAndFileName))
            {
                try
                {
                    XDocument doc = XDocument.Load(configPathAndFileName);

                    var folders = doc.Descendants("Folder");

                    foreach (var folder in folders)
                    {
                        string name = folder.Attribute("Name").Value.Trim();

                        if (Directory.Exists(folder.Value))
                        {
                            if (name == "dataimpl")
                            {
                                dataImplFolderPath.Text = folder.Value.Trim();

                                if (!Directory.Exists(dataImplFolderPath.Text + generatedFilesOutputFolder))
                                {
                                    Directory.CreateDirectory(dataImplFolderPath.Text + generatedFilesOutputFolder);
                                }
                            }
                            else if (name == "view")
                            {
                                textBoxViewFolderPath.Text = folder.Value.Trim();

                                if (!Directory.Exists(textBoxViewFolderPath.Text + generatedFilesOutputFolder))
                                {
                                    Directory.CreateDirectory(textBoxViewFolderPath.Text + generatedFilesOutputFolder);
                                }
                            }
                            else if (name == "java")
                            {
                                textBoxJavaFolderPath.Text = folder.Value.Trim();

                                if (!Directory.Exists(textBoxJavaFolderPath.Text + generatedFilesOutputFolder))
                                {
                                    Directory.CreateDirectory(textBoxJavaFolderPath.Text + generatedFilesOutputFolder);
                                }
                            }
                        }
                    }
                }
                catch (IOException ex)
                {
                    MessageBox.Show("An error occurred while loading config xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        public void OpenDataSetEditor(string fileName, string dataSetItemName)
        {
            DataSetEditor dataSetEditor = new DataSetEditor();
            dataSetEditor.DesktopModelObject = model;
            dataSetEditor.MainFormInterface = this;
            dataSetEditor.Show(dockPanel1, DockState.Document);

            dataSetEditor.isNewDataSet = false;

            string strTitle = dataSetEditor.Text;
            strTitle += " - " + dataSetItemName;
            dataSetEditor.Text = strTitle;

            dataSetEditor.DataImplFolderPath = dataImplFolderPath.Text;
            dataSetEditor.DataSetFileName = fileName;

            dataSetEditor.DataSetItemName = dataSetItemName;

            dataSetEditor.LoadFieldsUI();
            dataSetEditor.LoadSelectedFileFields();
            dataSetEditor.SetDataSetName();
            dataSetEditor.SetDataSetTypeComboBox();
        }

        private void BrowseForFolderBtn_OnClick(object sender, EventArgs e)
        {
            using (FolderBrowserDialog dlg = new FolderBrowserDialog())
            {
                dlg.RootFolder = Environment.SpecialFolder.MyComputer;
                dlg.Description = "Select a folder";

                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    dataImplFolderPath.Text = dlg.SelectedPath.Trim();
                    dataSetExplorer.DataImplFolderPath = dlg.SelectedPath.Trim();

                    string path = dataSetExplorer.DataImplFolderPath + generatedFilesOutputFolder;

                    Directory.CreateDirectory(path);
                }
            }
        }

        private void LoadDataBtn_OnCLick(object sender, EventArgs e)
        {
            this.btnLoadData.Enabled = false;

            if (dataImplFolderPath.Text.Trim() != string.Empty)
            {
                if (Directory.Exists(dataImplFolderPath.Text))
                {
                    try
                    {
                        model.MainFormInterface = this;
                        model.DataImplFolderPath = dataImplFolderPath.Text;
                        model.LoadData();

                        dataSetExplorer.DesktopModelObject = model;
                        dataSetExplorer.LoadDataSetFiles();
                        dataSetExplorer.Activate();

                        this.toolbarNewDataSet.Enabled = true;
                        this.newDataSetMenuItem.Enabled = true;

                        this.toolbarButtonOpenFieldsEditor.Enabled = true;
                        this.openFieldsEditorToolStripMenuItem.Enabled = true;

                        this.toolbarButtonOpenSubstitutionSetsEditor.Enabled = true;
                        this.openSubstitutionSetEditorToolStripMenuItem.Enabled = true;
                    }
                    catch (Exception loadingException)
                    {
                        MessageBox.Show("An error occurred during data loading: " + loadingException, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Path to ifastdataimpl folder is not defined.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void EnableLoadDesktopDataButton()
        {
            this.btnLoadData.Enabled = true;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void dataSetExplorerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dataSetExplorer.Show(dockPanel1, DockState.DockLeft);
        }

        private void outputWindowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            outputWindow.Show(dockPanel1, DockState.DockBottom);
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewDataSetEditor();
        }

        private void toolbarNewDataSet_Click(object sender, EventArgs e)
        {
            NewDataSetEditor();
        }

        private void NewDataSetEditor()
        {
            DataSetEditor dataSetEditor = new DataSetEditor();
            dataSetEditor.DesktopModelObject = model;
            dataSetEditor.MainFormInterface = this;
            dataSetEditor.Show(dockPanel1, DockState.Document);

            dataSetEditor.DataImplFolderPath = dataImplFolderPath.Text;

            dataSetEditor.LoadFieldsUI();
            dataSetEditor.isNewDataSet = true;
        }

        private void OpenFieldsEditor()
        {
            FieldsEditor fieldsEditor = new FieldsEditor();
            fieldsEditor.DesktopModelObject = model;
            fieldsEditor.MainFormInterface = this;
            fieldsEditor.ProgressModelObject = modelProgress;
            fieldsEditor.Show(dockPanel1, DockState.Document);

            fieldsEditor.DataImplFolderPath = dataImplFolderPath.Text;

            fieldsEditor.LoadFieldsUI();
        }

        private void OpenSubstitutionSetsEditor()
        {
            SubstitutionSetsEditor substitutionSetsEditor = new SubstitutionSetsEditor();
            substitutionSetsEditor.DesktopModelObject = model;
            substitutionSetsEditor.MainFormInterface = this;
            substitutionSetsEditor.Show(dockPanel1, DockState.Document);

            substitutionSetsEditor.DataImplFolderPath = dataImplFolderPath.Text;

            substitutionSetsEditor.LoadSubstitionSetsUI();
        }

        private void openFieldsEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFieldsEditor();
        }

        private void openSubstitutionSetEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenSubstitutionSetsEditor();
        }

        private void toolbarButtonOpenFieldsEditor_Click(object sender, EventArgs e)
        {
            OpenFieldsEditor();
        }

        private void toolbarButtonOpenSubstitutionSetsEditor_Click(object sender, EventArgs e)
        {
            OpenSubstitutionSetsEditor();
        }

        private void openLanguagesEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenLanguagesEditor();
        }

        private void toolStripButtonLanguages_Click(object sender, EventArgs e)
        {
            OpenLanguagesEditor();
        }

        private void OpenLanguagesEditor()
        {
            LanguagesEditor languagesEditor = new LanguagesEditor();
            languagesEditor.DesktopModelObject = model;
            languagesEditor.MainFormInterface = this;

            if (dataImplFolderPath.Text.Trim() != string.Empty)
            {
                if (Directory.Exists(dataImplFolderPath.Text))
                {
                    languagesEditor.DataImplFolderPath = dataImplFolderPath.Text.Trim();

                    languagesEditor.LoadLanguages();

                    languagesEditor.ShowDialog(this);
                }
                else
                {
                    MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Path to ifastdataimpl folder is not defined.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void openClientsEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenClientsEditor();
        }

        private void toolStripButtonOpenClientsEditor_Click(object sender, EventArgs e)
        {
            OpenClientsEditor();
        }

        private void OpenClientsEditor()
        {
            ClientsEditor clientsEditor = new ClientsEditor();
            clientsEditor.model = model;
            clientsEditor.mainForm = this;

            if (dataImplFolderPath.Text.Trim() != string.Empty)
            {
                if (Directory.Exists(dataImplFolderPath.Text))
                {
                    clientsEditor.DataImplFolderPath = dataImplFolderPath.Text.Trim();

                    clientsEditor.LoadClientsToDataGridView();

                    clientsEditor.ShowDialog(this);
                }
                else
                {
                    MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Path to ifastdataimpl folder is not defined.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void openMasksEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenMasksEditor();
        }

        private void toolStripButtonOpenMasksEditor_Click(object sender, EventArgs e)
        {
            OpenMasksEditor();
        }

        private void OpenMasksEditor()
        {
            if (dataImplFolderPath.Text.Trim() != string.Empty)
            {
                if (Directory.Exists(dataImplFolderPath.Text))
                {
                    model.DataImplFolderPath = dataImplFolderPath.Text;
                    model.LoadLanguageCountryData();

                    MasksEditor masksEditor = new MasksEditor();
                    masksEditor.DesktopModelObject = model;
                    masksEditor.MainFormInterface = this;
                    masksEditor.InitializeDataGridViews();

                    masksEditor.DataImplFolderPath = dataImplFolderPath.Text.Trim();

                    masksEditor.LoadMasks();

                    masksEditor.ShowDialog(this);
                }
                else
                {
                    MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Path to ifastdataimpl folder is not defined.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void OutputWindow_WriteLine(string line, Color? color = null)
        {
            outputWindow.WriteLine(line, color);
        }

        public void OutputWindow_WriteIndentedLine(string line, Color? color = null)
        {
            string indent = "   ";
            outputWindow.WriteLine(indent + line, color);
        }

        public void OutputWindow_WriteEmptyLine()
        {
            outputWindow.WriteEmptyLine();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBoxViewsGenerator aboutDialogBox = new AboutBoxViewsGenerator();
            aboutDialogBox.Show();
        }

        private string GetApplicationPath()
        {
            string path = Path.GetDirectoryName(System.Windows.Forms.Application.ExecutablePath);

            return path;
        }

        private void introductionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Introduction.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void languagesToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Languages.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void marketsAndClientsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Markets and Clients.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void masksToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Masks.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void dataSetsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Data Sets.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void fieldsToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Fields.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void substitutionSetsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Substitution Sets.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void progressTransactionViewsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Transaction Views Progress.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void progressResponseViewsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = GetApplicationPath() + helpFilesFolder + "Response Views Progress.docx";

            if (File.Exists(filePath))
            {
                System.Diagnostics.Process.Start(filePath);
            }
        }

        private void buttonBrowseForViewFolder_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog dlg = new FolderBrowserDialog())
            {
                dlg.RootFolder = Environment.SpecialFolder.MyComputer;
                dlg.Description = "Select a folder";

                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    textBoxViewFolderPath.Text = dlg.SelectedPath.Trim();
                    progressViewDataExplorer.ViewFolderPath = dlg.SelectedPath.Trim();

                    string path = progressViewDataExplorer.ViewFolderPath + generatedFilesOutputFolder;

                    Directory.CreateDirectory(path);
                }
            }
        }

        private void buttonLoadViewData_Click(object sender, EventArgs e)
        {
            this.buttonLoadViewData.Enabled = false;

            if (textBoxViewFolderPath.Text.Trim() != string.Empty)
            {
                if (Directory.Exists(textBoxViewFolderPath.Text))
                {
                    try
                    {
                        modelProgress.MainFormInterface = this;
                        modelProgress.ViewFolderPath = textBoxViewFolderPath.Text;
                        modelProgress.JavaFolderPath = textBoxJavaFolderPath.Text;

                        modelProgress.LoadData();

                        progressViewDataExplorer.ProgressModelObject = modelProgress;
                        progressViewDataExplorer.LoadViewDataSetFiles();
                        progressViewDataExplorer.Activate();

                        this.toolStripButton_NewViewResponseSet.Enabled = true;
                        this.newViewResponseSetToolStripMenuItem.Enabled = true;

                        this.toolStripButton_NewViewTransactionSet.Enabled = true;
                        this.newViewTransactionSetToolStripMenuItem.Enabled = true;
                    }
                    catch (Exception loadingException)
                    {
                        MessageBox.Show("An error occurred during data loading: " + loadingException, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Path to \"view\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Path to view folder is not defined.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void EnableLoadViewDataButton()
        {
            this.buttonLoadViewData.Enabled = true;

            // Needed only for CONVERSION 
            // At this point all progress data should have been already loaded
            // This code triggers a one time conversion of Progress files in which descriptions are added to the existing source files.
            //progressViewDataExplorer.CreateProgressFilesWithDescription();
        }

        public void OpenViewResponseEditor(string fileName, string viewItemName, string viewItemDescription, int viewId)
        {
            ViewResponseEditor viewResponseEditor = new ViewResponseEditor();
            viewResponseEditor.ProgressModelObject = modelProgress;
            viewResponseEditor.MainFormInterface = this;
            viewResponseEditor.Show(dockPanel1, DockState.Document);

            viewResponseEditor.isNewView = false;

            string strTitle = viewResponseEditor.Text;
            strTitle += " - " + "(" + viewId + ") " + viewItemName;
            viewResponseEditor.Text = strTitle;

            viewResponseEditor.ViewFolderPath = textBoxViewFolderPath.Text;
            viewResponseEditor.JavaFolderPath = textBoxJavaFolderPath.Text;
            viewResponseEditor.ViewFileName = fileName;
            viewResponseEditor.ViewItemDescription = viewItemDescription;

            viewResponseEditor.ViewItemName = viewItemName;
            viewResponseEditor.ViewId = viewId;

            viewResponseEditor.LoadResponseDefinitionsUI();
            viewResponseEditor.LoadSelectedResponseView();
            viewResponseEditor.SetViewNameAndId();
        }

        public void OpenViewTransactionsEditor(string fileName, string viewItemName, string viewItemDescription, int viewId)
        {
            ViewTransactionsEditor viewTransactionsEditor = new ViewTransactionsEditor();
            viewTransactionsEditor.ProgressModelObject = modelProgress;
            viewTransactionsEditor.MainFormInterface = this;
            viewTransactionsEditor.Show(dockPanel1, DockState.Document);

            viewTransactionsEditor.isNewView = false;

            string strTitle = viewTransactionsEditor.Text;
            strTitle += " - " + "(" + viewId + ") " + viewItemName;
            viewTransactionsEditor.Text = strTitle;

            viewTransactionsEditor.ViewFolderPath = textBoxViewFolderPath.Text;
            viewTransactionsEditor.JavaFolderPath = textBoxJavaFolderPath.Text;
            viewTransactionsEditor.ViewFileName = fileName;
            viewTransactionsEditor.ViewItemDescription = viewItemDescription;

            viewTransactionsEditor.ViewItemName = viewItemName;
            viewTransactionsEditor.ViewId = viewId;

            viewTransactionsEditor.LoadTransactionDefinitionsUI();
            viewTransactionsEditor.LoadSelectedTransactionView();
            viewTransactionsEditor.SetViewNameAndId();
        }

        private void AddNewViewResponseSet()
        {
            ViewResponseEditor viewResponseEditor = new ViewResponseEditor();
            viewResponseEditor.ProgressModelObject = modelProgress;
            viewResponseEditor.MainFormInterface = this;
            viewResponseEditor.Show(dockPanel1, DockState.Document);

            viewResponseEditor.isNewView = true;

            viewResponseEditor.ViewFolderPath = textBoxViewFolderPath.Text;
            viewResponseEditor.JavaFolderPath = textBoxJavaFolderPath.Text;

            viewResponseEditor.LoadResponseDefinitionsUI();
            viewResponseEditor.AddDefaultFieldsFoNewResponseView();
        }

        private void AddnewViewTransactionSet()
        {
            ViewTransactionsEditor viewTransactionsEditor = new ViewTransactionsEditor();
            viewTransactionsEditor.ProgressModelObject = modelProgress;
            viewTransactionsEditor.MainFormInterface = this;
            viewTransactionsEditor.Show(dockPanel1, DockState.Document);

            viewTransactionsEditor.isNewView = true;

            viewTransactionsEditor.ViewFolderPath = textBoxViewFolderPath.Text;
            viewTransactionsEditor.JavaFolderPath = textBoxJavaFolderPath.Text;

            viewTransactionsEditor.LoadTransactionDefinitionsUI();
        }

        private void newViewResponseSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddNewViewResponseSet();
        }

        private void newViewTransactionSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddnewViewTransactionSet();
        }

        private void toolStripButton_NewViewResponseSet_Click(object sender, EventArgs e)
        {
            AddNewViewResponseSet();
        }

        private void toolStripButton_NewViewTransactionSet_Click(object sender, EventArgs e)
        {
            AddnewViewTransactionSet();
        }

        private void buttonBrowseForJavaFolder_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog dlg = new FolderBrowserDialog())
            {
                dlg.RootFolder = Environment.SpecialFolder.MyComputer;
                dlg.Description = "Select a folder";

                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    textBoxJavaFolderPath.Text = dlg.SelectedPath.Trim();
                    progressViewDataExplorer.JavaFolderPath = dlg.SelectedPath.Trim();

                    string path = progressViewDataExplorer.JavaFolderPath + generatedFilesOutputFolder;

                    Directory.CreateDirectory(path);
                }
            }
        }

        private void buttonSaveFoldeerPaths_Click(object sender, EventArgs e)
        {
            SaveFolderPathsToConfig();
        }

        private void SaveFolderPathsToConfig()
        {
            string dir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string configPathAndFileName = dir + "\\" + viewsGeneratorConfigFileName;

            if (Directory.Exists(dir))
            {
                try
                {
                    string strDataImplFolderPath = dataImplFolderPath.Text.Trim();
                    string strViewFolderPath = textBoxViewFolderPath.Text.Trim();
                    string strJavaFolderPath = textBoxJavaFolderPath.Text.Trim();

                    XDocument doc = new XDocument(
                        new XDeclaration("1.0", "utf-8", "yes"),
                        new XElement("Root",
                            new XElement("Folders", new XAttribute("Description", "Data folders with source code"),
                                new XElement("Folder", new XAttribute("Name", "dataimpl"), new XAttribute("Description", "Folder with C++ source code"), new XText(strDataImplFolderPath)),
                                new XElement("Folder", new XAttribute("Name", "view"), new XAttribute("Description", "Folder with Progress source code"), new XText(strViewFolderPath)),
                                new XElement("Folder", new XAttribute("Name", "java"), new XAttribute("Description", "Folder with Java source code"), new XText(strJavaFolderPath)))));

                    doc.Save(configPathAndFileName);
                }
                catch (IOException ex)
                {
                    MessageBox.Show("An error occurred while saving config xml file. Error: " + ex, "Saving Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        public void SetProgressModelDataForFieldsEditor(FieldsEditor fieldsEditor)
        {
            fieldsEditor.ViewFolderPath = textBoxViewFolderPath.Text.Trim();
            fieldsEditor.JavaFolderPath = textBoxJavaFolderPath.Text.Trim();
            fieldsEditor.ProgressModelObject = modelProgress;
        }
    }
}

