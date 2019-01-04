namespace ViewsGenerator
{
    partial class ProgressViewDataExplorer
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
            this.objectListViewProgressViews = new BrightIdeasSoftware.ObjectListView();
            this.olvColumnViewName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewId = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewFileName = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            this.olvColumnViewFileType = ((BrightIdeasSoftware.OLVColumn)(new BrightIdeasSoftware.OLVColumn()));
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewProgressViews)).BeginInit();
            this.SuspendLayout();
            // 
            // objectListViewProgressViews
            // 
            this.objectListViewProgressViews.AllColumns.Add(this.olvColumnViewName);
            this.objectListViewProgressViews.AllColumns.Add(this.olvColumnViewId);
            this.objectListViewProgressViews.AllColumns.Add(this.olvColumnViewFileName);
            this.objectListViewProgressViews.AllColumns.Add(this.olvColumnViewFileType);
            this.objectListViewProgressViews.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.olvColumnViewName,
            this.olvColumnViewId,
            this.olvColumnViewFileName,
            this.olvColumnViewFileType});
            this.objectListViewProgressViews.Dock = System.Windows.Forms.DockStyle.Fill;
            this.objectListViewProgressViews.FullRowSelect = true;
            this.objectListViewProgressViews.GridLines = true;
            this.objectListViewProgressViews.Location = new System.Drawing.Point(0, 0);
            this.objectListViewProgressViews.Name = "objectListViewProgressViews";
            this.objectListViewProgressViews.ShowGroups = false;
            this.objectListViewProgressViews.Size = new System.Drawing.Size(284, 262);
            this.objectListViewProgressViews.TabIndex = 0;
            this.objectListViewProgressViews.UseAlternatingBackColors = true;
            this.objectListViewProgressViews.UseCompatibleStateImageBehavior = false;
            this.objectListViewProgressViews.View = System.Windows.Forms.View.Details;
            this.objectListViewProgressViews.DoubleClick += new System.EventHandler(this.objectListViewProgressViews_DoubleClick);
            // 
            // olvColumnViewName
            // 
            this.olvColumnViewName.AspectName = "ViewName";
            this.olvColumnViewName.Text = "View Name";
            this.olvColumnViewName.Width = 220;
            // 
            // olvColumnViewId
            // 
            this.olvColumnViewId.AspectName = "ViewId";
            this.olvColumnViewId.Text = "View Id";
            // 
            // olvColumnViewFileName
            // 
            this.olvColumnViewFileName.AspectName = "ViewDataFileName";
            this.olvColumnViewFileName.Text = "File Name";
            this.olvColumnViewFileName.Width = 90;
            // 
            // olvColumnViewFileType
            // 
            this.olvColumnViewFileType.AspectName = "ViewFileType";
            this.olvColumnViewFileType.Text = "Type";
            this.olvColumnViewFileType.Width = 80;
            // 
            // ProgressViewDataExplorer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.objectListViewProgressViews);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "ProgressViewDataExplorer";
            this.Text = "Progress View Data Explorer";
            ((System.ComponentModel.ISupportInitialize)(this.objectListViewProgressViews)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private BrightIdeasSoftware.ObjectListView objectListViewProgressViews;
        private BrightIdeasSoftware.OLVColumn olvColumnViewId;
        private BrightIdeasSoftware.OLVColumn olvColumnViewFileName;
        private BrightIdeasSoftware.OLVColumn olvColumnViewName;
        private BrightIdeasSoftware.OLVColumn olvColumnViewFileType;
    }
}