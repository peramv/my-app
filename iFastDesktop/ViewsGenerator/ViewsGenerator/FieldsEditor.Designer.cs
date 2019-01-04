namespace ViewsGenerator
{
    partial class FieldsEditor
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
            this.objectListViewAllFields = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnFieldName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnFieldId = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnFieldType = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnFieldLength = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnFieldPropertiesName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.propertyGridFields = new System.Windows.Forms.PropertyGrid();
            this.labelFieldList = new System.Windows.Forms.Label();
            this.labelFieldProperties = new System.Windows.Forms.Label();
            this.buttonGenerateCode = new System.Windows.Forms.Button();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.buttonAddField = new System.Windows.Forms.Button();
            this.buttonDeleteField = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewAllFields)).BeginInit();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.objectListViewAllFields, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.propertyGridFields, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.labelFieldList, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelFieldProperties, 2, 1);
            this.tableLayoutPanel1.Controls.Add(this.buttonGenerateCode, 2, 4);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 3);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 60F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(816, 604);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // objectListViewAllFields
            // 
            this.objectListViewAllFields.AllColumns.Add(this.olvColumnFieldName);
            this.objectListViewAllFields.AllColumns.Add(this.olvColumnFieldId);
            this.objectListViewAllFields.AllColumns.Add(this.olvColumnFieldType);
            this.objectListViewAllFields.AllColumns.Add(this.olvColumnFieldLength);
            this.objectListViewAllFields.AllColumns.Add(this.olvColumnFieldPropertiesName);
            this.objectListViewAllFields.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnFieldName,
            this.olvColumnFieldId,
            this.olvColumnFieldType,
            this.olvColumnFieldLength,
            this.olvColumnFieldPropertiesName});
            this.objectListViewAllFields.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewAllFields.FullRowSelect = true;
            this.objectListViewAllFields.GridLines = true;
            this.objectListViewAllFields.HasCollapsibleGroups = false;
            this.objectListViewAllFields.Location = new System.Drawing.Point(3, 63);
            this.objectListViewAllFields.MultiSelect = false;
            this.objectListViewAllFields.Name = "objectListViewAllFields";
            this.objectListViewAllFields.SelectAllOnControlA = false;
            this.objectListViewAllFields.ShowGroups = false;
            this.objectListViewAllFields.Size = new System.Drawing.Size(387, 443);
            this.objectListViewAllFields.TabIndex = 0;
            this.objectListViewAllFields.UseCompatibleStateImageBehavior = false;
            this.objectListViewAllFields.View = System.Windows.Forms.View.Details;
            this.objectListViewAllFields.SelectionChanged += new System.EventHandler(this.ObjectListViewAllFields_SelectionChanged);
            this.objectListViewAllFields.Enter += new System.EventHandler(this.ObjectListViewAllFields_Enter);
            this.objectListViewAllFields.Leave += new System.EventHandler(this.ObjectListViewAllFields_Leave);
            // 
            // olvColumnFieldName
            // 
            this.olvColumnFieldName.AspectName = "FieldName";
            this.olvColumnFieldName.IsEditable = false;
            this.olvColumnFieldName.Text = "Field Name";
            this.olvColumnFieldName.Width = 180;
            // 
            // olvColumnFieldId
            // 
            this.olvColumnFieldId.AspectName = "FieldId";
            this.olvColumnFieldId.IsEditable = false;
            this.olvColumnFieldId.Text = "Field Id";
            this.olvColumnFieldId.Width = 80;
            // 
            // olvColumnFieldType
            // 
            this.olvColumnFieldType.AspectName = "FieldDerivedType";
            this.olvColumnFieldType.IsEditable = false;
            this.olvColumnFieldType.Text = "Field Type";
            this.olvColumnFieldType.Width = 100;
            // 
            // olvColumnFieldLength
            // 
            this.olvColumnFieldLength.AspectName = "FieldLength";
            this.olvColumnFieldLength.IsEditable = false;
            this.olvColumnFieldLength.Text = "Field Length";
            this.olvColumnFieldLength.Width = 70;
            // 
            // olvColumnFieldPropertiesName
            // 
            this.olvColumnFieldPropertiesName.AspectName = "FieldPropertiesName";
            this.olvColumnFieldPropertiesName.FillsFreeSpace = true;
            this.olvColumnFieldPropertiesName.IsEditable = false;
            this.olvColumnFieldPropertiesName.Text = "Field Properties Name";
            this.olvColumnFieldPropertiesName.Width = 150;
            // 
            // propertyGridFields
            // 
            this.propertyGridFields.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGridFields.Location = new System.Drawing.Point(426, 63);
            this.propertyGridFields.Name = "propertyGridFields";
            this.propertyGridFields.PropertySort = System.Windows.Forms.PropertySort.Categorized;
            this.tableLayoutPanel1.SetRowSpan(this.propertyGridFields, 2);
            this.propertyGridFields.Size = new System.Drawing.Size(387, 478);
            this.propertyGridFields.TabIndex = 1;
            this.propertyGridFields.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.PropertyGridFields_PropertyValueChanged);
            this.propertyGridFields.Leave += new System.EventHandler(this.PropertyGridFields_Leave);
            // 
            // labelFieldList
            // 
            this.labelFieldList.AutoSize = true;
            this.labelFieldList.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelFieldList.Location = new System.Drawing.Point(3, 36);
            this.labelFieldList.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.labelFieldList.Name = "labelFieldList";
            this.labelFieldList.Size = new System.Drawing.Size(62, 15);
            this.labelFieldList.TabIndex = 2;
            this.labelFieldList.Text = "Field list";
            // 
            // labelFieldProperties
            // 
            this.labelFieldProperties.AutoSize = true;
            this.labelFieldProperties.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelFieldProperties.Location = new System.Drawing.Point(426, 36);
            this.labelFieldProperties.Margin = new System.Windows.Forms.Padding(3, 6, 3, 0);
            this.labelFieldProperties.Name = "labelFieldProperties";
            this.labelFieldProperties.Size = new System.Drawing.Size(132, 15);
            this.labelFieldProperties.TabIndex = 3;
            this.labelFieldProperties.Text = "Field properties of: ";
            // 
            // buttonGenerateCode
            // 
            this.buttonGenerateCode.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.buttonGenerateCode.Location = new System.Drawing.Point(541, 562);
            this.buttonGenerateCode.Name = "buttonGenerateCode";
            this.buttonGenerateCode.Size = new System.Drawing.Size(156, 23);
            this.buttonGenerateCode.TabIndex = 4;
            this.buttonGenerateCode.Text = "Generate Code";
            this.buttonGenerateCode.UseVisualStyleBackColor = true;
            this.buttonGenerateCode.Click += new System.EventHandler(this.ButtonGenerateCode_Click);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.buttonAddField, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.buttonDeleteField, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 512);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(387, 29);
            this.tableLayoutPanel2.TabIndex = 5;
            // 
            // buttonAddField
            // 
            this.buttonAddField.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonAddField.Location = new System.Drawing.Point(115, 3);
            this.buttonAddField.Name = "buttonAddField";
            this.buttonAddField.Size = new System.Drawing.Size(75, 23);
            this.buttonAddField.TabIndex = 0;
            this.buttonAddField.Text = "Add";
            this.buttonAddField.UseVisualStyleBackColor = true;
            this.buttonAddField.Click += new System.EventHandler(this.buttonAddField_Click);
            // 
            // buttonDeleteField
            // 
            this.buttonDeleteField.Location = new System.Drawing.Point(196, 3);
            this.buttonDeleteField.Name = "buttonDeleteField";
            this.buttonDeleteField.Size = new System.Drawing.Size(75, 23);
            this.buttonDeleteField.TabIndex = 1;
            this.buttonDeleteField.Text = "Delete";
            this.buttonDeleteField.UseVisualStyleBackColor = true;
            this.buttonDeleteField.Click += new System.EventHandler(this.buttonDeleteField_Click);
            // 
            // FieldsEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(816, 604);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "FieldsEditor";
            this.Text = "Fields Editor";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewAllFields)).EndInit();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private BrightIdeasSoftware.ObjectListView objectListViewAllFields;
        private System.Windows.Forms.PropertyGrid propertyGridFields;
        private BrightIdeasSoftware.OLVColumn olvColumnFieldName;
        private BrightIdeasSoftware.OLVColumn olvColumnFieldId;
        private BrightIdeasSoftware.OLVColumn olvColumnFieldType;
        private BrightIdeasSoftware.OLVColumn olvColumnFieldLength;
        private BrightIdeasSoftware.OLVColumn olvColumnFieldPropertiesName;
        private System.Windows.Forms.Label labelFieldList;
        private System.Windows.Forms.Label labelFieldProperties;
        private System.Windows.Forms.Button buttonGenerateCode;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button buttonAddField;
        private System.Windows.Forms.Button buttonDeleteField;
    }
}