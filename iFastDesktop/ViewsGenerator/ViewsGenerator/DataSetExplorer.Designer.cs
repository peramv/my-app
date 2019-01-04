namespace ViewsGenerator
{
    partial class DataSetExplorer
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
            this.objectListViewDataSets = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnDataSetName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnDataSetId = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnDataSetFile = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewDataSets)).BeginInit();
            this.SuspendLayout();
            // 
            // objectListViewDataSets
            // 
            this.objectListViewDataSets.AllColumns.Add(this.olvColumnDataSetName);
            this.objectListViewDataSets.AllColumns.Add(this.olvColumnDataSetId);
            this.objectListViewDataSets.AllColumns.Add(this.olvColumnDataSetFile);
            this.objectListViewDataSets.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnDataSetName,
            this.olvColumnDataSetId,
            this.olvColumnDataSetFile});
            this.objectListViewDataSets.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewDataSets.FullRowSelect = true;
            this.objectListViewDataSets.GridLines = true;
            this.objectListViewDataSets.HasCollapsibleGroups = false;
            this.objectListViewDataSets.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.objectListViewDataSets.Location = new System.Drawing.Point(0, 0);
            this.objectListViewDataSets.MultiSelect = false;
            this.objectListViewDataSets.Name = "objectListViewDataSets";
            this.objectListViewDataSets.Size = new System.Drawing.Size(284, 262);
            this.objectListViewDataSets.TabIndex = 0;
            this.objectListViewDataSets.TintSortColumn = true;
            this.objectListViewDataSets.UseCompatibleStateImageBehavior = false;
            this.objectListViewDataSets.View = System.Windows.Forms.View.Details;
            this.objectListViewDataSets.DoubleClick += new System.EventHandler(this.ObjectListViewDataSets_DoubleClick);
            // 
            // olvColumnDataSetName
            // 
            this.olvColumnDataSetName.AspectName = "DataSetItemName";
            this.olvColumnDataSetName.Groupable = false;
            this.olvColumnDataSetName.IsEditable = false;
            this.olvColumnDataSetName.Text = "Data Set Name";
            this.olvColumnDataSetName.Width = 170;
            // 
            // olvColumnDataSetId
            // 
            this.olvColumnDataSetId.AspectName = "DataSetId";
            this.olvColumnDataSetId.Text = "Data Set Id";
            this.olvColumnDataSetId.Width = 80;
            // 
            // olvColumnDataSetFile
            // 
            this.olvColumnDataSetFile.AspectName = "DataSetItemFileName";
            this.olvColumnDataSetFile.FillsFreeSpace = true;
            this.olvColumnDataSetFile.Groupable = false;
            this.olvColumnDataSetFile.IsEditable = false;
            this.olvColumnDataSetFile.Text = "File Name";
            // 
            // DataSetExplorer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.objectListViewDataSets);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.HideOnClose = true;
            this.Name = "DataSetExplorer";
            this.Text = "Data Set Explorer";
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewDataSets)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private BrightIdeasSoftware.ObjectListView objectListViewDataSets;
        private BrightIdeasSoftware.OLVColumn olvColumnDataSetName;
        private BrightIdeasSoftware.OLVColumn olvColumnDataSetFile;
        private BrightIdeasSoftware.OLVColumn olvColumnDataSetId;
    }
}