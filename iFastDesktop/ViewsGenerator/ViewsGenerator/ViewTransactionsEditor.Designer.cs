namespace ViewsGenerator
{
    partial class ViewTransactionsEditor	
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.objectListViewSelectedTransactionView = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnViewSelectedResponseVariableName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewSelectedResponseVariableType = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewSelectedResponseVariableFormat = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewSelectedResponseVariableScope = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.labelViewTransactionElements = new System.Windows.Forms.Label();
            this.labelTransactionDefinitionsList = new System.Windows.Forms.Label();
            this.objectListViewAllTransactionDefinitions = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnViewResponseVariableName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewResponseVariableType = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewResponseVariableFormat = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewResponseVariableScope = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.btnMoveUp = new System.Windows.Forms.Button();
            this.btnMoveDown = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tbQuickFieldSearch = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxViewItemDescription = new System.Windows.Forms.TextBox();
            this.labelViewDescription = new System.Windows.Forms.Label();
            this.textBoxViewId = new ViewsGenerator.NumericTextBox();
            this.labelViewId = new System.Windows.Forms.Label();
            this.textBoxViewItemName = new System.Windows.Forms.TextBox();
            this.lblViewName = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.btnGenerateCode = new System.Windows.Forms.Button();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btnMoveRight = new System.Windows.Forms.Button();
            this.btnMoveLeft = new System.Windows.Forms.Button();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonAddTransaction = new System.Windows.Forms.Button();
            this.buttonDeleteTransaction = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewSelectedTransactionView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewAllTransactionDefinitions)).BeginInit();
            this.tableLayoutPanel3.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.objectListViewSelectedTransactionView, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.labelViewTransactionElements, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelTransactionDefinitionsList, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.objectListViewAllTransactionDefinitions, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 2, 3);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel2, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.panel3, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel5, 0, 3);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1029, 546);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // objectListViewSelectedTransactionView
            // 
            this.objectListViewSelectedTransactionView.AllColumns.Add(this.olvColumnViewSelectedResponseVariableName);
            this.objectListViewSelectedTransactionView.AllColumns.Add(this.olvColumnViewSelectedResponseVariableType);
            this.objectListViewSelectedTransactionView.AllColumns.Add(this.olvColumnViewSelectedResponseVariableFormat);
            this.objectListViewSelectedTransactionView.AllColumns.Add(this.olvColumnViewSelectedResponseVariableScope);
            this.objectListViewSelectedTransactionView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnViewSelectedResponseVariableName,
            this.olvColumnViewSelectedResponseVariableType,
            this.olvColumnViewSelectedResponseVariableFormat,
            this.olvColumnViewSelectedResponseVariableScope});
            this.objectListViewSelectedTransactionView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewSelectedTransactionView.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.objectListViewSelectedTransactionView.FullRowSelect = true;
            this.objectListViewSelectedTransactionView.GridLines = true;
            this.objectListViewSelectedTransactionView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.objectListViewSelectedTransactionView.Location = new System.Drawing.Point(537, 113);
            this.objectListViewSelectedTransactionView.Name = "objectListViewSelectedTransactionView";
            this.objectListViewSelectedTransactionView.Size = new System.Drawing.Size(489, 335);
            this.objectListViewSelectedTransactionView.TabIndex = 1;
            this.objectListViewSelectedTransactionView.TintSortColumn = true;
            this.objectListViewSelectedTransactionView.UseCompatibleStateImageBehavior = false;
            this.objectListViewSelectedTransactionView.View = System.Windows.Forms.View.Details;
            this.objectListViewSelectedTransactionView.SelectionChanged += new System.EventHandler(this.objectListViewSelectedResponseView_SelectionChanged);
            this.objectListViewSelectedTransactionView.Enter += new System.EventHandler(this.objectListViewSelectedResponseView_Enter);
            // 
            // olvColumnViewSelectedResponseVariableName
            // 
            this.olvColumnViewSelectedResponseVariableName.AspectName = "TransactionVariableName";
            this.olvColumnViewSelectedResponseVariableName.Groupable = false;
            this.olvColumnViewSelectedResponseVariableName.IsEditable = false;
            this.olvColumnViewSelectedResponseVariableName.Text = "Variable Name";
            this.olvColumnViewSelectedResponseVariableName.Width = 170;
            // 
            // olvColumnViewSelectedResponseVariableType
            // 
            this.olvColumnViewSelectedResponseVariableType.AspectName = "TransactionVariableTypeDeclaration";
            this.olvColumnViewSelectedResponseVariableType.Groupable = false;
            this.olvColumnViewSelectedResponseVariableType.IsEditable = false;
            this.olvColumnViewSelectedResponseVariableType.Text = "Variable Type";
            this.olvColumnViewSelectedResponseVariableType.Width = 210;
            // 
            // olvColumnViewSelectedResponseVariableFormat
            // 
            this.olvColumnViewSelectedResponseVariableFormat.AspectName = "Format";
            this.olvColumnViewSelectedResponseVariableFormat.Groupable = false;
            this.olvColumnViewSelectedResponseVariableFormat.IsEditable = false;
            this.olvColumnViewSelectedResponseVariableFormat.Text = "Format";
            this.olvColumnViewSelectedResponseVariableFormat.Width = 210;
            // 
            // olvColumnViewSelectedResponseVariableScope
            // 
            this.olvColumnViewSelectedResponseVariableScope.AspectName = "Scope";
            this.olvColumnViewSelectedResponseVariableScope.FillsFreeSpace = true;
            this.olvColumnViewSelectedResponseVariableScope.Groupable = false;
            this.olvColumnViewSelectedResponseVariableScope.IsEditable = false;
            this.olvColumnViewSelectedResponseVariableScope.Text = "Scope";
            this.olvColumnViewSelectedResponseVariableScope.Width = 80;
            // 
            // labelViewTransactionElements
            // 
            this.labelViewTransactionElements.AutoSize = true;
            this.labelViewTransactionElements.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelViewTransactionElements.Location = new System.Drawing.Point(537, 86);
            this.labelViewTransactionElements.Margin = new System.Windows.Forms.Padding(3, 6, 3, 3);
            this.labelViewTransactionElements.Name = "labelViewTransactionElements";
            this.labelViewTransactionElements.Size = new System.Drawing.Size(182, 15);
            this.labelViewTransactionElements.TabIndex = 5;
            this.labelViewTransactionElements.Text = "Transaction definitions for: ";
            // 
            // labelTransactionDefinitionsList
            // 
            this.labelTransactionDefinitionsList.AutoSize = true;
            this.labelTransactionDefinitionsList.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTransactionDefinitionsList.Location = new System.Drawing.Point(3, 86);
            this.labelTransactionDefinitionsList.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.labelTransactionDefinitionsList.Name = "labelTransactionDefinitionsList";
            this.labelTransactionDefinitionsList.Size = new System.Drawing.Size(176, 15);
            this.labelTransactionDefinitionsList.TabIndex = 6;
            this.labelTransactionDefinitionsList.Text = "Transaction definitions list";
            // 
            // objectListViewAllTransactionDefinitions
            // 
            this.objectListViewAllTransactionDefinitions.AllColumns.Add(this.olvColumnViewResponseVariableName);
            this.objectListViewAllTransactionDefinitions.AllColumns.Add(this.olvColumnViewResponseVariableType);
            this.objectListViewAllTransactionDefinitions.AllColumns.Add(this.olvColumnViewResponseVariableFormat);
            this.objectListViewAllTransactionDefinitions.AllColumns.Add(this.olvColumnViewResponseVariableScope);
            this.objectListViewAllTransactionDefinitions.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnViewResponseVariableName,
            this.olvColumnViewResponseVariableType,
            this.olvColumnViewResponseVariableFormat,
            this.olvColumnViewResponseVariableScope});
            this.objectListViewAllTransactionDefinitions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewAllTransactionDefinitions.FullRowSelect = true;
            this.objectListViewAllTransactionDefinitions.GridLines = true;
            this.objectListViewAllTransactionDefinitions.HasCollapsibleGroups = false;
            this.objectListViewAllTransactionDefinitions.Location = new System.Drawing.Point(3, 113);
            this.objectListViewAllTransactionDefinitions.Name = "objectListViewAllTransactionDefinitions";
            this.objectListViewAllTransactionDefinitions.ShowGroups = false;
            this.objectListViewAllTransactionDefinitions.Size = new System.Drawing.Size(488, 335);
            this.objectListViewAllTransactionDefinitions.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.objectListViewAllTransactionDefinitions.TabIndex = 0;
            this.objectListViewAllTransactionDefinitions.UseCompatibleStateImageBehavior = false;
            this.objectListViewAllTransactionDefinitions.View = System.Windows.Forms.View.Details;
            this.objectListViewAllTransactionDefinitions.SelectionChanged += new System.EventHandler(this.objectListViewAllResponseDefinitions_SelectionChanged);
            this.objectListViewAllTransactionDefinitions.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.objectListViewAllResponseDefinitions_ColumnClick);
            this.objectListViewAllTransactionDefinitions.Enter += new System.EventHandler(this.objectListViewAllResponseDefinitions_Enter);
            // 
            // olvColumnViewResponseVariableName
            // 
            this.olvColumnViewResponseVariableName.AspectName = "TransactionVariableName";
            this.olvColumnViewResponseVariableName.Groupable = false;
            this.olvColumnViewResponseVariableName.IsEditable = false;
            this.olvColumnViewResponseVariableName.Text = "Variable Name";
            this.olvColumnViewResponseVariableName.Width = 170;
            // 
            // olvColumnViewResponseVariableType
            // 
            this.olvColumnViewResponseVariableType.AspectName = "TransactionVariableTypeDeclaration";
            this.olvColumnViewResponseVariableType.Groupable = false;
            this.olvColumnViewResponseVariableType.IsEditable = false;
            this.olvColumnViewResponseVariableType.Text = "Variable Type";
            this.olvColumnViewResponseVariableType.Width = 210;
            // 
            // olvColumnViewResponseVariableFormat
            // 
            this.olvColumnViewResponseVariableFormat.AspectName = "Format";
            this.olvColumnViewResponseVariableFormat.Groupable = false;
            this.olvColumnViewResponseVariableFormat.IsEditable = false;
            this.olvColumnViewResponseVariableFormat.Text = "Format";
            this.olvColumnViewResponseVariableFormat.Width = 210;
            // 
            // olvColumnViewResponseVariableScope
            // 
            this.olvColumnViewResponseVariableScope.AspectName = "Scope";
            this.olvColumnViewResponseVariableScope.FillsFreeSpace = true;
            this.olvColumnViewResponseVariableScope.Groupable = false;
            this.olvColumnViewResponseVariableScope.IsEditable = false;
            this.olvColumnViewResponseVariableScope.Text = "Scope";
            this.olvColumnViewResponseVariableScope.Width = 80;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.btnMoveUp, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.btnMoveDown, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(537, 454);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 29F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(489, 29);
            this.tableLayoutPanel3.TabIndex = 7;
            // 
            // btnMoveUp
            // 
            this.btnMoveUp.Dock = System.Windows.Forms.DockStyle.Right;
            this.btnMoveUp.Location = new System.Drawing.Point(166, 3);
            this.btnMoveUp.Name = "btnMoveUp";
            this.btnMoveUp.Size = new System.Drawing.Size(75, 23);
            this.btnMoveUp.TabIndex = 0;
            this.btnMoveUp.Text = "Move Up";
            this.btnMoveUp.UseVisualStyleBackColor = true;
            this.btnMoveUp.Click += new System.EventHandler(this.btnMoveUp_Click);
            // 
            // btnMoveDown
            // 
            this.btnMoveDown.Dock = System.Windows.Forms.DockStyle.Left;
            this.btnMoveDown.Location = new System.Drawing.Point(247, 3);
            this.btnMoveDown.Name = "btnMoveDown";
            this.btnMoveDown.Size = new System.Drawing.Size(75, 23);
            this.btnMoveDown.TabIndex = 1;
            this.btnMoveDown.Text = "Move Down";
            this.btnMoveDown.UseVisualStyleBackColor = true;
            this.btnMoveDown.Click += new System.EventHandler(this.btnMoveDown_Click);
            // 
            // panel1
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.panel1, 3);
            this.panel1.Controls.Add(this.tbQuickFieldSearch);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.textBoxViewItemDescription);
            this.panel1.Controls.Add(this.labelViewDescription);
            this.panel1.Controls.Add(this.textBoxViewId);
            this.panel1.Controls.Add(this.labelViewId);
            this.panel1.Controls.Add(this.textBoxViewItemName);
            this.panel1.Controls.Add(this.lblViewName);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1029, 80);
            this.panel1.TabIndex = 0;
            // 
            // tbQuickFieldSearch
            // 
            this.tbQuickFieldSearch.Location = new System.Drawing.Point(118, 46);
            this.tbQuickFieldSearch.Name = "tbQuickFieldSearch";
            this.tbQuickFieldSearch.Size = new System.Drawing.Size(229, 20);
            this.tbQuickFieldSearch.TabIndex = 7;
            this.tbQuickFieldSearch.TextChanged += new System.EventHandler(this.tbQuickFieldSearch_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Quick Field Search:";
            // 
            // textBoxViewItemDescription
            // 
            this.textBoxViewItemDescription.Location = new System.Drawing.Point(477, 19);
            this.textBoxViewItemDescription.Name = "textBoxViewItemDescription";
            this.textBoxViewItemDescription.Size = new System.Drawing.Size(302, 20);
            this.textBoxViewItemDescription.TabIndex = 3;
            // 
            // labelViewDescription
            // 
            this.labelViewDescription.AutoSize = true;
            this.labelViewDescription.Location = new System.Drawing.Point(386, 22);
            this.labelViewDescription.Name = "labelViewDescription";
            this.labelViewDescription.Size = new System.Drawing.Size(87, 13);
            this.labelViewDescription.TabIndex = 2;
            this.labelViewDescription.Text = "View description:";
            // 
            // textBoxViewId
            // 
            this.textBoxViewId.Location = new System.Drawing.Point(914, 19);
            this.textBoxViewId.Name = "textBoxViewId";
            this.textBoxViewId.Size = new System.Drawing.Size(100, 20);
            this.textBoxViewId.TabIndex = 5;
            this.textBoxViewId.Leave += new System.EventHandler(this.textBoxViewId_Leave);
            // 
            // labelViewId
            // 
            this.labelViewId.AutoSize = true;
            this.labelViewId.Location = new System.Drawing.Point(858, 22);
            this.labelViewId.Name = "labelViewId";
            this.labelViewId.Size = new System.Drawing.Size(45, 13);
            this.labelViewId.TabIndex = 4;
            this.labelViewId.Text = "View Id:";
            // 
            // textBoxViewItemName
            // 
            this.textBoxViewItemName.Location = new System.Drawing.Point(118, 19);
            this.textBoxViewItemName.Name = "textBoxViewItemName";
            this.textBoxViewItemName.Size = new System.Drawing.Size(229, 20);
            this.textBoxViewItemName.TabIndex = 1;
            this.textBoxViewItemName.Leave += new System.EventHandler(this.textBoxViewItemName_Leave);
            // 
            // lblViewName
            // 
            this.lblViewName.AutoSize = true;
            this.lblViewName.Location = new System.Drawing.Point(11, 22);
            this.lblViewName.Name = "lblViewName";
            this.lblViewName.Size = new System.Drawing.Size(62, 13);
            this.lblViewName.TabIndex = 0;
            this.lblViewName.Text = "View name:";
            // 
            // panel2
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.panel2, 3);
            this.panel2.Controls.Add(this.tableLayoutPanel4);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 486);
            this.panel2.Margin = new System.Windows.Forms.Padding(0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1029, 60);
            this.panel2.TabIndex = 11;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.ColumnCount = 3;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.btnGenerateCode, 2, 0);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(1029, 60);
            this.tableLayoutPanel4.TabIndex = 0;
            // 
            // btnGenerateCode
            // 
            this.btnGenerateCode.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.btnGenerateCode.Location = new System.Drawing.Point(703, 16);
            this.btnGenerateCode.Margin = new System.Windows.Forms.Padding(3, 16, 3, 3);
            this.btnGenerateCode.Name = "btnGenerateCode";
            this.btnGenerateCode.Size = new System.Drawing.Size(156, 23);
            this.btnGenerateCode.TabIndex = 0;
            this.btnGenerateCode.Text = "Generate Code";
            this.btnGenerateCode.UseVisualStyleBackColor = true;
            this.btnGenerateCode.Click += new System.EventHandler(this.btnGenerateCode_Click);
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.tableLayoutPanel2);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(494, 80);
            this.panel3.Margin = new System.Windows.Forms.Padding(0);
            this.panel3.Name = "panel3";
            this.tableLayoutPanel1.SetRowSpan(this.panel3, 3);
            this.panel3.Size = new System.Drawing.Size(40, 406);
            this.panel3.TabIndex = 12;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Controls.Add(this.btnMoveRight, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.btnMoveLeft, 0, 1);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(40, 406);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // btnMoveRight
            // 
            this.btnMoveRight.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btnMoveRight.Location = new System.Drawing.Point(3, 177);
            this.btnMoveRight.Name = "btnMoveRight";
            this.btnMoveRight.Size = new System.Drawing.Size(34, 23);
            this.btnMoveRight.TabIndex = 0;
            this.btnMoveRight.Text = ">>";
            this.btnMoveRight.UseVisualStyleBackColor = true;
            this.btnMoveRight.Click += new System.EventHandler(this.btnMoveRight_Click);
            // 
            // btnMoveLeft
            // 
            this.btnMoveLeft.Dock = System.Windows.Forms.DockStyle.Top;
            this.btnMoveLeft.Location = new System.Drawing.Point(3, 206);
            this.btnMoveLeft.Name = "btnMoveLeft";
            this.btnMoveLeft.Size = new System.Drawing.Size(34, 23);
            this.btnMoveLeft.TabIndex = 1;
            this.btnMoveLeft.Text = "<<";
            this.btnMoveLeft.UseVisualStyleBackColor = true;
            this.btnMoveLeft.Click += new System.EventHandler(this.btnMoveLeft_Click);
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.ColumnCount = 2;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel5.Controls.Add(this.buttonAddTransaction, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.buttonDeleteTransaction, 1, 0);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(3, 454);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 1;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(488, 29);
            this.tableLayoutPanel5.TabIndex = 13;
            // 
            // buttonAddTransaction
            // 
            this.buttonAddTransaction.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddTransaction.Location = new System.Drawing.Point(166, 3);
            this.buttonAddTransaction.Name = "buttonAddTransaction";
            this.buttonAddTransaction.Size = new System.Drawing.Size(75, 23);
            this.buttonAddTransaction.TabIndex = 0;
            this.buttonAddTransaction.Text = "Add";
            this.buttonAddTransaction.UseVisualStyleBackColor = true;
            this.buttonAddTransaction.Click += new System.EventHandler(this.buttonAddTransaction_Click);
            // 
            // buttonDeleteTransaction
            // 
            this.buttonDeleteTransaction.Location = new System.Drawing.Point(247, 3);
            this.buttonDeleteTransaction.Name = "buttonDeleteTransaction";
            this.buttonDeleteTransaction.Size = new System.Drawing.Size(75, 23);
            this.buttonDeleteTransaction.TabIndex = 1;
            this.buttonDeleteTransaction.Text = "Delete";
            this.buttonDeleteTransaction.UseVisualStyleBackColor = true;
            this.buttonDeleteTransaction.Click += new System.EventHandler(this.buttonDeleteTransaction_Click);
            // 
            // ViewTransactionsEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1029, 546);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "ViewTransactionsEditor";
            this.ShowIcon = false;
            this.Text = "View Transactions Editor";
            this.Leave += new System.EventHandler(this.ViewTransactionEditor_Leave);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewSelectedTransactionView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewAllTransactionDefinitions)).EndInit();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel5.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private BrightIdeasSoftware.ObjectListView objectListViewAllTransactionDefinitions;
        private BrightIdeasSoftware.ObjectListView objectListViewSelectedTransactionView;
        private BrightIdeasSoftware.OLVColumn olvColumnViewResponseVariableName;
        private BrightIdeasSoftware.OLVColumn olvColumnViewResponseVariableType;
        private BrightIdeasSoftware.OLVColumn olvColumnViewResponseVariableFormat;
        private BrightIdeasSoftware.OLVColumn olvColumnViewResponseVariableScope;
        private BrightIdeasSoftware.OLVColumn olvColumnViewSelectedResponseVariableName;
        private BrightIdeasSoftware.OLVColumn olvColumnViewSelectedResponseVariableType;
        private BrightIdeasSoftware.OLVColumn olvColumnViewSelectedResponseVariableFormat;
        private BrightIdeasSoftware.OLVColumn olvColumnViewSelectedResponseVariableScope;
        private System.Windows.Forms.Label labelViewTransactionElements;
        private System.Windows.Forms.Label labelTransactionDefinitionsList;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Button btnMoveUp;
        private System.Windows.Forms.Button btnMoveDown;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnMoveRight;
        private System.Windows.Forms.Button btnMoveLeft;
        private System.Windows.Forms.Button btnGenerateCode;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.TextBox textBoxViewItemName;
        private System.Windows.Forms.Label lblViewName;
        private NumericTextBox textBoxViewId;
        private System.Windows.Forms.Label labelViewId;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.Button buttonAddTransaction;
        private System.Windows.Forms.Button buttonDeleteTransaction;
        private System.Windows.Forms.TextBox textBoxViewItemDescription;
        private System.Windows.Forms.Label labelViewDescription;
        private System.Windows.Forms.TextBox tbQuickFieldSearch;
        private System.Windows.Forms.Label label1;

    }
}