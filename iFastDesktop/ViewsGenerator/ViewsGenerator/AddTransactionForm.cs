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
    public partial class AddTransactionForm : Form
    {
        private readonly string AddTransactionErrorBoxCaption = "Add Transaction Error";
        public ModelProgress ModelProgressObject { get; set; }
        public TransactionItem transactionItem = new TransactionItem();

        
        public AddTransactionForm()
        {
            InitializeComponent();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (IsInputValid())
            {
                CreateNewTransactionDefinition();
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private bool IsInputValid()
        {
            if (this.textBoxVariableName.Text == string.Empty)
            {
                MessageBox.Show("Variable name is missing!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableName.Focus();
                return false;
            }
            else if (this.textBoxDescription.Text == string.Empty)
            {
                MessageBox.Show("Variable description is missing!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxDescription.Focus();
                return false;
            }
            else if (this.textBoxVariableType.Text == string.Empty)
            {
                MessageBox.Show("Variable type is missing!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableType.Focus();
                return false;
            }
            else if (this.textBoxFormat.Text == string.Empty)
            {
                MessageBox.Show("Format is not defined!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxFormat.Focus();
                return false;
            }
            else if (this.textBoxScope.Text == string.Empty)
            {
                MessageBox.Show("Scope is not defined!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxScope.Focus();
                return false;
            }

            var duplicates = ModelProgressObject.distinctTransactionItemList.Where(x => x.TransactionVariableName == this.textBoxVariableName.Text);
            if (duplicates.Count() > 0)
            {
                MessageBox.Show("Variable name already exists!", AddTransactionErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.textBoxVariableName.Focus();
                return false;
            }

            return true;
        }

        private void CreateNewTransactionDefinition()
        {
            transactionItem.TransactionVariableName = textBoxVariableName.Text.Trim();
            transactionItem.VariableDescription = textBoxDescription.Text.Trim();
            transactionItem.TransactionVariableTypeDeclaration = textBoxVariableType.Text.Trim();
            transactionItem.Format = textBoxFormat.Text.Trim();
            transactionItem.Scope = textBoxScope.Text.Trim();

            transactionItem.isNewField = true;

            ModelProgressObject.distinctTransactionItemList.Add(transactionItem);
        }
    }
}
