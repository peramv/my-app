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
    public partial class AddFieldForm : Form
    {
        public ModelDesktop model = null;
        public FieldItem newFieldItem = new FieldItem();

        public AddFieldForm()
        {
            InitializeComponent();
        }

        private void buttonNewFieldOK_Click(object sender, EventArgs e)
        {
            if (this.textBoxNewFieldName.Text.Trim() != "")
            {
                string newFieldName = this.textBoxNewFieldName.Text;

                if (IsNewFieldNameAlreadyInUse(newFieldName))
                {
                    MessageBox.Show("Field name is already in use, please enter a different field name.", "New Field Name Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    CreateNewField(newFieldName);
                    this.DialogResult = DialogResult.OK;
                    this.Close();
                }
            }
        }

        private bool IsNewFieldNameAlreadyInUse(string fieldName)
        {
            bool isInUse = false;

            var fieldItem = model.fieldItemList.FirstOrDefault(n => n.FieldName == fieldName);

            if (fieldItem != null)
            {
                isInUse = true;
            }

            return isInUse;
        }

        private void CreateNewField(string newFieldName)
        {
            newFieldItem.isNewField = true;
            newFieldItem.FieldName = newFieldName;

            int maxDataSetId = Convert.ToInt32(model.dataSetNameAndIDsDictionary.Max(x => x.Value));
            int maxFieldId = Convert.ToInt32(model.fieldItemList.Max(x => x.FieldId));

            int newFieldItemId = Math.Max(maxDataSetId, maxFieldId) + 1;

            newFieldItem.FieldId = newFieldItemId.ToString();
            newFieldItem.FieldShortId = newFieldItem.FieldId.Remove(0, 1).TrimStart('0');
            newFieldItem.FieldPropertiesName = "s_FldProp_" + newFieldName;

            model.fieldItemList.Add(newFieldItem);

            FieldPropertiesItem fieldPropertiesItem = new FieldPropertiesItem();
            fieldPropertiesItem.FieldName = newFieldItem.FieldName;
            fieldPropertiesItem.DefaultValueStringFunctionName = newFieldItem.FieldPropertiesName + "_s_DVF";
            fieldPropertiesItem.DefaultValueIntegerFunctionName = "NULL";
            fieldPropertiesItem.DefaultValueDoubleFunctionName = "NULL";
            fieldPropertiesItem.LabelFunctionName = newFieldItem.FieldPropertiesName + "_FLF";
            fieldPropertiesItem.FieldNameIsDeprecated = "NULL";
            fieldPropertiesItem.Justification = "None";
            fieldPropertiesItem.SubstitutionSetSuperChooser = "NULL";
            fieldPropertiesItem.Label_enUS = newFieldName;
            model.fieldPropertiesDictionary.Add(newFieldItem.FieldPropertiesName, fieldPropertiesItem);
        }
    }
}
