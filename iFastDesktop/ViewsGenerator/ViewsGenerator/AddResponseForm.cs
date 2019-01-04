using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ViewsGenerator
{
    public partial class AddResponseForm : Form
    {
        private readonly string AddResponseErrorBoxCaption = "Add Response Error";
        public ModelProgress ModelProgressObject { get; set; }
        public ResponseItem responseItem = new ResponseItem();


        public AddResponseForm()
        {
            InitializeComponent();

            ModelProgressObject = null;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (IsInputValid())
            {
                CreateNewResponseDefinition();
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private bool IsInputValid()
        {
            if (this.textBoxVariableName.Text == string.Empty)
            {
                MessageBox.Show("Variable name is missing!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableName.Focus();
                return false;
            }
            else if (this.textBoxDescription.Text == string.Empty)
            {
                MessageBox.Show("Variable description is missing!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxDescription.Focus();
                return false;
            }
            else if (this.textBoxVariableType.Text == string.Empty)
            {
                MessageBox.Show("Variable type is missing!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableType.Focus();
                return false;
            }
            else if (this.textBoxFormat.Text == string.Empty)
            {
                MessageBox.Show("Format is not defined!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxFormat.Focus();
                return false;
            }
            else if (this.textBoxScope.Text == string.Empty)
            {
                MessageBox.Show("Scope is not defined!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxScope.Focus();
                return false;
            }
            else if (this.comboBoxResponseType.Text == string.Empty)
            {
                MessageBox.Show("Response type is not defined!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.comboBoxResponseType.Focus();
                return false;
            }

            var duplicates = ModelProgressObject.distinctResponseItemList.Where(x => x.ResponseVariableName == this.textBoxVariableName.Text);
            if (duplicates.Count() > 0)
            {
                MessageBox.Show("Variable name already exists!", AddResponseErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableName.Focus();
                return false;
            }

            return true;
        }

        private void CreateNewResponseDefinition()
        {
            responseItem.ResponseVariableName = textBoxVariableName.Text.Trim();
            responseItem.VariableDescription = textBoxDescription.Text.Trim();
            responseItem.ResponseVariableTypeDeclaration = textBoxVariableType.Text.Trim();
            responseItem.Format = textBoxFormat.Text.Trim();
            responseItem.Scope = textBoxScope.Text.Trim();

            string responseType = comboBoxResponseType.Text.Replace(" (Error Occurred)", "").Replace(" (Data)", "");
            responseItem.ResponseType = responseType;
            responseItem.isNewField = true;

            ModelProgressObject.distinctResponseItemList.Add(responseItem);
        }
    }
}
