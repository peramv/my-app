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
using WeifenLuo.WinFormsUI.Docking;
using ViewsGenerator.Templates.Desktop;
using BrightIdeasSoftware;

namespace ViewsGenerator
{
    public partial class FieldsEditor : BaseForm
    {
        private readonly string FieldsEditorErrorBoxCaption = "Fields Editor Error";
        private FieldPropertiesUI fieldProperties = new FieldPropertiesUI();
        private FieldItem fieldItem = null;
        private FieldPropertiesItem fieldPropertiesItem = null;

        public FieldsEditor()
        {
            InitializeComponent();

            this.objectListViewAllFields.TintSortColumn = true;

            this.buttonGenerateCode.Enabled = false;

            this.buttonDeleteField.Enabled = false;
        }

        public void LoadFieldsUI()
        {
            this.objectListViewAllFields.SetObjects(DesktopModelObject.fieldItemList);
        }

        public void PopulatePropertyGrid()
        {
            this.propertyGridFields.SelectedObject = fieldProperties;

            this.buttonGenerateCode.Enabled = true;
        }

        private string FindMaskNameBasedOnChooserFunction(string chooser)
        {
            string mask = "No Mask";

            if (chooser != "NULL")
            {
                var maskList = DesktopModelObject.masksDictionary.Where(x => x.Value.MaskChooser == chooser).Select(y => y.Value.MaskName).ToList();
                if (maskList.Count >= 1)
                {
                    mask = maskList[0];
                }
            }

            return mask;                                                                       
        }

        private string FindSubstituitionSetBasedOnChooserFunction(string chooser)
        {
            string substituitionSet = "";
            string chooserGroupAndId = chooser.Replace("chooser_ss_", "");

            if (chooser != "NULL")
            {
                var substitutionSetList = DesktopModelObject.distinctSubstitutionsList.Where(x => x.KeysName.Contains(chooserGroupAndId)).Select(y => y.Name).ToList();
                if (substitutionSetList.Count >= 1)
                {
                    substituitionSet = substitutionSetList[0];
                }
            }

            return substituitionSet;
        }

        private void ObjectListViewAllFields_SelectionChanged(object sender, EventArgs e)
        {
            fieldItem = (FieldItem)this.objectListViewAllFields.SelectedObject;

            fieldProperties.FieldName = fieldItem.FieldName;
            fieldProperties.FieldId = fieldItem.FieldId;

            fieldProperties.AvailableExactFieldTypeValues = DesktopModelObject.distinctExactFieldItemTypes.ToArray();
            fieldProperties.FieldType = fieldItem.FieldDerivedType;

            fieldPropertiesItem = null;
            DesktopModelObject.fieldPropertiesDictionary.TryGetValue(fieldItem.FieldPropertiesName, out fieldPropertiesItem);

            if (fieldPropertiesItem != null)
            {
                fieldProperties.FieldPropertyName = fieldItem.FieldPropertiesName;

                fieldProperties.AvailableBaseFieldTypeValues = DesktopModelObject.distinctBaseFieldItemTypes.ToArray();
                fieldProperties.FieldPropertyType = fieldPropertiesItem.FieldType;
                
                fieldProperties.FieldLength = Convert.ToInt32(fieldPropertiesItem.FieldLength);
                fieldProperties.FieldMinimumLength = Convert.ToInt32(fieldPropertiesItem.FieldMinimumLength);
                fieldProperties.FieldDecimals = Convert.ToDecimal(fieldPropertiesItem.FieldDecimals);

                fieldProperties.AvailableMaskFieldTypeValues = DesktopModelObject.maskNamesList.ToArray();
                fieldProperties.MaskName = FindMaskNameBasedOnChooserFunction(fieldPropertiesItem.MaskChooserFunction);

                //fieldProperties.MaskChooserFunction = fieldPropertiesItem.MaskChooserFunction;

                fieldProperties.DefaultValueString = fieldPropertiesItem.DefaultValueStringFunctionName;

                fieldProperties.AvailableDefaultValueIntegerValues = new string[2] { "NULL", fieldItem.FieldPropertiesName + "_i_DVF" };
                fieldProperties.DefaultValueInteger = fieldPropertiesItem.DefaultValueIntegerFunctionName;

                fieldProperties.AvailableDefaultValueDoubleValues = new string[2] { "NULL", fieldItem.FieldPropertiesName + "_d_DVF" };
                fieldProperties.DefaultValueDouble = fieldPropertiesItem.DefaultValueDoubleFunctionName;

                fieldProperties.FieldLabel = fieldPropertiesItem.LabelFunctionName;
                fieldProperties.FieldNameIsDeprecated = fieldPropertiesItem.FieldNameIsDeprecated;
                fieldProperties.AllowNulls = Convert.ToBoolean(fieldPropertiesItem.AllowNulls);
                fieldProperties.Justification = fieldPropertiesItem.Justification;

                fieldProperties.AvailableSubstituitionSetTypeValues = DesktopModelObject.distinctSubstitutionsList.Select(x => x.Name).ToArray();

                if (fieldPropertiesItem.Chooser_ss_function != null)
                {
                    fieldProperties.SubstitutionSet = FindSubstituitionSetBasedOnChooserFunction(fieldPropertiesItem.Chooser_ss_function);
                }
                else
                {
                    fieldProperties.SubstitutionSet = "NULL";
                }

                //fieldProperties.SubstitutionSet = fieldPropertiesItem.SubstitutionSetSuperChooser;

                fieldProperties.DoubleDefaultValue_enUS = fieldPropertiesItem.DefaultValueDouble_enUS;
                fieldProperties.DoubleDefaultValue_enCA = fieldPropertiesItem.DefaultValueDouble_enCA;
                fieldProperties.DoubleDefaultValue_frFR = fieldPropertiesItem.DefaultValueDouble_frFR;
                fieldProperties.DoubleDefaultValue_frCA = fieldPropertiesItem.DefaultValueDouble_frCA;
                fieldProperties.DoubleDefaultValue_enIE = fieldPropertiesItem.DefaultValueDouble_enIE;
                fieldProperties.DoubleDefaultValue_deDE = fieldPropertiesItem.DefaultValueDouble_deDE;
                fieldProperties.DoubleDefaultValue_esEs = fieldPropertiesItem.DefaultValueDouble_esEs;

                fieldProperties.IntegerDefaultValue_enUS = fieldPropertiesItem.DefaultValueInteger_enUS;
                fieldProperties.IntegerDefaultValue_enCA = fieldPropertiesItem.DefaultValueInteger_enCA;
                fieldProperties.IntegerDefaultValue_frFR = fieldPropertiesItem.DefaultValueInteger_frFR;
                fieldProperties.IntegerDefaultValue_frCA = fieldPropertiesItem.DefaultValueInteger_frCA;
                fieldProperties.IntegerDefaultValue_enIE = fieldPropertiesItem.DefaultValueInteger_enIE;
                fieldProperties.IntegerDefaultValue_deDE = fieldPropertiesItem.DefaultValueInteger_deDE;
                fieldProperties.IntegerDefaultValue_esEs = fieldPropertiesItem.DefaultValueInteger_esEs;

                fieldProperties.StringDefaultValue_enUS = "\"" + fieldPropertiesItem.DefaultValueString_enUS + "\"";
                fieldProperties.StringDefaultValue_enCA = "\"" + fieldPropertiesItem.DefaultValueString_enCA + "\"";
                fieldProperties.StringDefaultValue_frFR = "\"" + fieldPropertiesItem.DefaultValueString_frFR + "\"";
                fieldProperties.StringDefaultValue_frCA = "\"" + fieldPropertiesItem.DefaultValueString_frCA + "\"";
                fieldProperties.StringDefaultValue_enIE = "\"" + fieldPropertiesItem.DefaultValueString_enIE + "\"";
                fieldProperties.StringDefaultValue_deDE = "\"" + fieldPropertiesItem.DefaultValueString_deDE + "\"";
                fieldProperties.StringDefaultValue_esEs = "\"" + fieldPropertiesItem.DefaultValueString_esEs + "\"";

                fieldProperties.LabelValue_enUS = "\"" + fieldPropertiesItem.Label_enUS + "\"";
                fieldProperties.LabelValue_enCA = "\"" + fieldPropertiesItem.Label_enCA + "\"";
                fieldProperties.LabelValue_frFR = "\"" + fieldPropertiesItem.Label_frFR + "\"";
                fieldProperties.LabelValue_frCA = "\"" + fieldPropertiesItem.Label_frCA + "\"";
                fieldProperties.LabelValue_enIE = "\"" + fieldPropertiesItem.Label_enIE + "\"";
                fieldProperties.LabelValue_deDE = "\"" + fieldPropertiesItem.Label_deDE + "\"";
                fieldProperties.LabelValue_esEs = "\"" + fieldPropertiesItem.Label_esEs + "\"";
            }

            PopulatePropertyGrid();

            this.labelFieldProperties.Text = "Field properties of: " + fieldItem.FieldName;

            this.buttonDeleteField.Enabled = true;
        }

        private void UpdatePropertyValues()
        {
            fieldItem.FieldName = fieldProperties.FieldName;
            fieldItem.FieldId = fieldProperties.FieldId;
            fieldItem.FieldLength = fieldProperties.FieldLength;
            fieldItem.FieldDerivedType = fieldProperties.FieldType;
            if (fieldItem.FieldDerivedType.Contains("BFTextField"))
            {
                fieldItem.FieldType = "BFTextField";
            }
            else
            {
                fieldItem.FieldType = fieldItem.FieldDerivedType;
            }

            fieldItem.FieldPropertiesName = fieldProperties.FieldPropertyName;
            fieldPropertiesItem.FieldType = fieldProperties.FieldPropertyType;
            fieldPropertiesItem.FieldLength = fieldProperties.FieldLength.ToString();
            fieldPropertiesItem.FieldMinimumLength = fieldProperties.FieldMinimumLength.ToString();
            fieldPropertiesItem.FieldDecimals = fieldProperties.FieldDecimals.ToString();

            string maskChooserFunction = DesktopModelObject.masksDictionary.First(pair => pair.Value.MaskName == fieldProperties.MaskName).Value.MaskChooser;
            fieldPropertiesItem.MaskChooserFunction = maskChooserFunction;

            fieldPropertiesItem.DefaultValueStringFunctionName = fieldProperties.DefaultValueString;
            fieldPropertiesItem.DefaultValueIntegerFunctionName = fieldProperties.DefaultValueInteger;
            fieldPropertiesItem.DefaultValueDoubleFunctionName = fieldProperties.DefaultValueDouble;
            fieldPropertiesItem.LabelFunctionName = fieldProperties.FieldLabel;
            fieldPropertiesItem.FieldNameIsDeprecated = fieldProperties.FieldNameIsDeprecated;
            fieldPropertiesItem.AllowNulls = fieldProperties.AllowNulls.ToString().ToLower();
            fieldPropertiesItem.Justification = fieldProperties.Justification;

            string strChoserFunctionName = fieldProperties.SubstitutionSet;
            if (strChoserFunctionName != "NULL" && strChoserFunctionName != "")
            {
                strChoserFunctionName = DesktopModelObject.distinctSubstitutionsList.Find(s => s.Name == strChoserFunctionName).KeysName.Replace("aKeys", "chooser_ss");
                strChoserFunctionName = strChoserFunctionName.Remove(strChoserFunctionName.Length - 12);
            }
            fieldPropertiesItem.Chooser_ss_function = strChoserFunctionName;

            if (strChoserFunctionName != "NULL" && strChoserFunctionName != "")
            {
                fieldPropertiesItem.SubstitutionSetSuperChooser = "subset_super_chooser_2_" + fieldItem.FieldShortId;
            }
            else
            {
                fieldPropertiesItem.SubstitutionSetSuperChooser = "NULL";
            }

            fieldPropertiesItem.languageCountryIds.Clear();
            int count = fieldPropertiesItem.languageCountryIds.Count;

            if (fieldProperties.LabelValue_enUS != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_enUS.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("enUS"));
            }
            if (fieldProperties.LabelValue_enCA != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_enCA.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("enCA"));
            }
            if (fieldProperties.LabelValue_frFR != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_frFR.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("frFR"));
            }
            if (fieldProperties.LabelValue_frCA != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_frCA.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("frCA"));
            }
            if (fieldProperties.LabelValue_enIE != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_enIE.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("enIE"));
            }
            if (fieldProperties.LabelValue_deDE != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_deDE.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("deDE"));
            }
            if (fieldProperties.LabelValue_esEs != "\"\"")
            {
                fieldPropertiesItem.SetLabel(fieldProperties.LabelValue_esEs.Replace("\"", ""), DesktopModelObject.GetLanguageIdBasedOnLanguageCountryName("esEs"));
            }

            fieldPropertiesItem.DefaultValueString_enUS = fieldProperties.StringDefaultValue_enUS.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_enCA = fieldProperties.StringDefaultValue_enCA.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_frFR = fieldProperties.StringDefaultValue_frFR.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_frCA = fieldProperties.StringDefaultValue_frCA.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_enIE = fieldProperties.StringDefaultValue_enIE.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_deDE = fieldProperties.StringDefaultValue_deDE.Replace("\"", "");
            fieldPropertiesItem.DefaultValueString_esEs = fieldProperties.StringDefaultValue_esEs.Replace("\"", "");

            fieldPropertiesItem.DefaultValueDouble_enUS = fieldProperties.DoubleDefaultValue_enUS;
            fieldPropertiesItem.DefaultValueDouble_enCA = fieldProperties.DoubleDefaultValue_enCA;
            fieldPropertiesItem.DefaultValueDouble_frFR = fieldProperties.DoubleDefaultValue_frFR;
            fieldPropertiesItem.DefaultValueDouble_frCA = fieldProperties.DoubleDefaultValue_frCA;
            fieldPropertiesItem.DefaultValueDouble_enIE = fieldProperties.DoubleDefaultValue_enIE;
            fieldPropertiesItem.DefaultValueDouble_deDE = fieldProperties.DoubleDefaultValue_deDE;
            fieldPropertiesItem.DefaultValueDouble_esEs = fieldProperties.DoubleDefaultValue_esEs;

            fieldPropertiesItem.DefaultValueInteger_enUS = fieldProperties.IntegerDefaultValue_enUS;
            fieldPropertiesItem.DefaultValueInteger_enCA = fieldProperties.IntegerDefaultValue_enCA;
            fieldPropertiesItem.DefaultValueInteger_frFR = fieldProperties.IntegerDefaultValue_frFR;
            fieldPropertiesItem.DefaultValueInteger_frCA = fieldProperties.IntegerDefaultValue_frCA;
            fieldPropertiesItem.DefaultValueInteger_enIE = fieldProperties.IntegerDefaultValue_enIE;
            fieldPropertiesItem.DefaultValueInteger_deDE = fieldProperties.IntegerDefaultValue_deDE;
            fieldPropertiesItem.DefaultValueInteger_esEs = fieldProperties.IntegerDefaultValue_esEs;
        }

        private void ButtonGenerateCode_Click(object sender, EventArgs e)
        {
            try
            {
                if (ValidateFieldProperties())
                {
                    UpdatePropertyValues();

                    if (fieldItem.isNewField)
                    {
                        GenerateNewField();
                    }
                    else
                    {
                        GenerateModifiedExistingField();
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred while generating files. Error: " + ex, "Generator Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool ValidateFieldProperties()
        {
            bool areFieldPropertiesValid = true;

            if (fieldProperties.FieldType == null || fieldProperties.FieldPropertyType == null)
            {
                MessageBox.Show("Type related property is not defined.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                areFieldPropertiesValid = false;
            }
            else
            {
                if (!fieldProperties.FieldType.ToLower().Contains(fieldProperties.FieldPropertyType.ToLower()))
                {
                    MessageBox.Show("Type related properties don't match.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    areFieldPropertiesValid = false;
                }
            }

            // Not needed, since strings can be empty
            //if (fieldProperties.StringDefaultValue_enUS == "\"\"" &&
            //    fieldProperties.StringDefaultValue_enCA == "\"\"" &&
            //    fieldProperties.StringDefaultValue_frFR == "\"\"" &&
            //    fieldProperties.StringDefaultValue_frCA == "\"\"" &&
            //    fieldProperties.StringDefaultValue_enIE == "\"\"" &&
            //    fieldProperties.StringDefaultValue_deDE == "\"\"" &&
            //    fieldProperties.StringDefaultValue_esEs == "\"\"")
            //{
            //    MessageBox.Show("All default value strings are empty.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            //    areFieldPropertiesValid = false;
            //}

            if (fieldProperties.LabelValue_enUS == "\"\"" &&
                fieldProperties.LabelValue_enCA == "\"\"" &&
                fieldProperties.LabelValue_frFR == "\"\"" &&
                fieldProperties.LabelValue_frCA == "\"\"" &&
                fieldProperties.LabelValue_enIE == "\"\"" &&
                fieldProperties.LabelValue_deDE == "\"\"" &&
                fieldProperties.LabelValue_esEs == "\"\"")
            {
                MessageBox.Show("All labels are empty.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                areFieldPropertiesValid = false;
            }

            // Not needed, since values can be empty
            if (fieldProperties.DefaultValueDouble != "NULL")
            {
                if (fieldProperties.DoubleDefaultValue_enUS == null &&
                    fieldProperties.DoubleDefaultValue_enCA == null &&
                    fieldProperties.DoubleDefaultValue_frFR == null &&
                    fieldProperties.DoubleDefaultValue_frCA == null &&
                    fieldProperties.DoubleDefaultValue_enIE == null &&
                    fieldProperties.DoubleDefaultValue_deDE == null &&
                    fieldProperties.DoubleDefaultValue_esEs == null)
                {
                    MessageBox.Show("All default double values are empty.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    areFieldPropertiesValid = false;
                }
            }

            if (fieldProperties.DefaultValueInteger != "NULL")
            {
                if (fieldProperties.IntegerDefaultValue_enUS == null &&
                    fieldProperties.IntegerDefaultValue_enCA == null &&
                    fieldProperties.IntegerDefaultValue_frFR == null &&
                    fieldProperties.IntegerDefaultValue_frCA == null &&
                    fieldProperties.IntegerDefaultValue_enIE == null &&
                    fieldProperties.IntegerDefaultValue_deDE == null &&
                    fieldProperties.IntegerDefaultValue_esEs == null)
                {
                    MessageBox.Show("All default integer values are empty.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    areFieldPropertiesValid = false;
                }
            }

            return areFieldPropertiesValid;
        }

        private void GenerateModifiedExistingField()
        {
            OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - START");

            string fileFullPathName = DataImplFolderPath + "\\" + fieldPropertiesItem.FileName;
            string strFieldPropertyStart = "// Field s_FldProp_" + fieldItem.FieldName + " (" + fieldItem.FieldShortId + ")";

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.Contains(strFieldPropertyStart) || line.Contains("// Field s_FldProp_") || line.StartsWith("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            var lineWherePropertyDefinitionStarts = from line in lines
                                                    where line.Contains(strFieldPropertyStart)
                                                    select new
                                                    {
                                                        Line = line,
                                                        Index = lines.IndexOf(line)
                                                    };

            int countPropertyLines = lineWherePropertyDefinitionStarts.Count();

            if (count >= 3 && countPropertyLines > 0)
            {
                // Generate field properties file
                ReplaceFieldPropsCpp_RuntimeTextTemplate page = new ReplaceFieldPropsCpp_RuntimeTextTemplate();
                page.modelDesktopInterface = DesktopModelObject;
                page.fieldItem = fieldItem;
                page.fieldPropertiesItem = fieldPropertiesItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfPropertyDefinitionStartLine = lineWherePropertyDefinitionStarts.ToList().ElementAt(0).Index;
                int nextItemAfterDefinition = significantLines.ToList().FindIndex(s => s.Line.Contains(strFieldPropertyStart)) + 1;
                page.indexOfRemainingCodeNextLine = significantLines.ToList().ElementAt(nextItemAfterDefinition).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldPropsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fieldPropertiesItem.FileName;
                System.IO.File.WriteAllText(strIfastFieldPropsCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldPropsCppFileName, Color.Green);

                OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - END");
                OutputWindow_WriteEmptyLine();
            }

            if (IsFieldUsedInDataSets(fieldItem.FieldName))
            {
                GenerateViewsWhichContainModifiedField(fieldItem);
            }
        }

        private void GenerateViewsWhichContainModifiedField(FieldItem fieldItem)
        {
            // Generate Desktop views
            GenerateMultipleDesktopViewsHandler generateMultipleDesktopViews = new GenerateMultipleDesktopViewsHandler();

            List<string> listOfFilesWithDataSetsWhereFieldIsUsed = GetAllDataSetsWhereIsFieldUsed(fieldItem.FieldName);
            generateMultipleDesktopViews.listOfFilesWithDataSetsWhereFieldIsUsed = listOfFilesWithDataSetsWhereFieldIsUsed;

            generateMultipleDesktopViews.DesktopModelObject = DesktopModelObject;
            generateMultipleDesktopViews.MainFormInterface = this.MainFormInterface;
            generateMultipleDesktopViews.DataImplFolderPath = DataImplFolderPath;

            generateMultipleDesktopViews.GenerateFilesAffectedByFieldChange(fieldItem.FieldName);

            // Generate Progress views
            MainForm form = (MainForm)this.ParentForm;
            form.SetProgressModelDataForFieldsEditor(this);

            if (String.IsNullOrEmpty(ViewFolderPath))
            {
                MessageBox.Show("Cannot generate Progress files which contain modified field!\nPath of \"view\" folder is not set.\n\nYou must load data from \"view\" and \"java\" folders in order to generate views containing the modified field.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (String.IsNullOrEmpty(JavaFolderPath))
            {
                MessageBox.Show("Cannot generate Java/Html files which contain modified field!\nPath of \"java\" folder is not set.\n\nYou must load data from \"view\" and \"java\" folders in order to generate views containing the modified field.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (ProgressModelObject.distinctResponseItemList.Count == 0 && ProgressModelObject.distinctTransactionItemList.Count == 0)
            {
                MessageBox.Show("You must load data from \"view\" and \"java\" folders in order to generate views containing the modified field.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            string progressFieldTypeFormat = ProgressModelObject.GetProgressFieldTypeFormat(fieldItem);

            GenerateMultipleProgressViewsHandler generateMultipleProgressViews = new GenerateMultipleProgressViewsHandler();
            generateMultipleProgressViews.listOfProgressViewIdsAndIndexesWhereFieldIsUsed = generateMultipleDesktopViews.listOfWhereIsUsedFieldInfo;

            generateMultipleProgressViews.ProgressModelObject = ProgressModelObject;
            generateMultipleProgressViews.MainFormInterface = this.MainFormInterface;
            generateMultipleProgressViews.ViewFolderPath = ViewFolderPath;
            generateMultipleProgressViews.JavaFolderPath = JavaFolderPath;

            generateMultipleProgressViews.SetProgressFieldFormat(progressFieldTypeFormat);
            generateMultipleProgressViews.GenerateViewsAffectedByFieldChange(fieldItem.FieldName);
        }

        private void GenerateNewField()
        {
            OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - START");

            GenerateNewFieldFactoryFile();
            GenerateNewFieldIdsCppFile();
            GenerateNewFieldIdsHppFile();
            GenerateNewFieldPropertiesHppFile();
            GenerateNewFieldPropertiesCppFile();

            OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private void GenerateNewFieldFactoryFile()
        {
            var fileName = DesktopModelObject.fieldItemList.Where(x => x.isNewField == false).OrderBy(x => Convert.ToInt32(x.FieldId)).Last().FieldFactoryFileName;

            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.Contains("BFDataField* createField") || line.Contains("return pField;"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            var dataFieldPropertyLines = from line in lines
                                           where line.Contains("BFDataFieldProperties")
                                           select new
                                           {
                                               Line = line,
                                               Index = lines.IndexOf(line)
                                           };

            int countPropertyLines = dataFieldPropertyLines.Count();

            if (count == 3 && countPropertyLines > 0)
            {
                // Generate field properties file
                FieldFactoryCpp_RuntimeTextTemplate page = new FieldFactoryCpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfLastPropertyDeclarationLine = significantLines.ToList().ElementAt(1).Index;
                page.indexOfReturnFieldLine = significantLines.ToList().ElementAt(2).Index;
                page.indexOfLastFieldDeclarationLine = dataFieldPropertyLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldFactoryCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strIfastFieldFactoryCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldFactoryCppFileName, Color.Green);
            }
        }

        private void GenerateNewFieldIdsCppFile()
        {
            string lastExistingFieldId = DesktopModelObject.fieldItemList.Where(x => x.isNewField == false).OrderBy(x => Convert.ToInt32(x.FieldId)).Last().FieldId;

            var files = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                        where file.Contains("ifast_fieldids")
                        from line in File.ReadLines(file, Encoding.Default)
                        where line.Contains(lastExistingFieldId)
                        select new
                        {
                            File = file,
                            Line = line
                        }).Single();

            string fileName = Path.GetFileName(files.File);
            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                    where (line.Contains("namespace ifds") || line.StartsWith("}"))
                                    select new
                                    {
                                        Line = line,
                                        Index = lines.IndexOf(line)
                                    };

            int count = significantLines.Count();

            if (count == 2)
            {
                // Generate field properties file
                FieldIdsCpp_RuntimeTextTemplate page = new FieldIdsCpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfIfdsNamespaceClosingBraceLine = significantLines.ToList().ElementAt(1).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldIdsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strIfastFieldIdsCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldIdsCppFileName, Color.Green);
            }
        }

        private void GenerateNewFieldIdsHppFile()
        {
            string fileFullPathName = DataImplFolderPath + "\\ifast_fieldids.hpp";

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.StartsWith("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 2)
            {
                // Generate field properties file
                FieldIdsHpp_RuntimeTextTemplate page = new FieldIdsHpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfIfdsNamespaceClosingBraceLine = significantLines.ToList().ElementAt(1).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldIdsHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_fieldids.hpp";
                System.IO.File.WriteAllText(strIfastFieldIdsHppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldIdsHppFileName, Color.Green);
            }
        }

        private void GenerateNewFieldPropertiesHppFile()
        {
            string fileFullPathName = DataImplFolderPath + "\\ifast_fieldprops.hpp";

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.StartsWith("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            if (count == 2)
            {
                // Generate field properties file
                FieldPropertiesHpp_RuntimeTextTemplate page = new FieldPropertiesHpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfIfdsNamespaceClosingBraceLine = significantLines.ToList().ElementAt(1).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldPropertiesHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + "ifast_fieldprops.hpp";
                System.IO.File.WriteAllText(strIfastFieldPropertiesHppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldPropertiesHppFileName, Color.Green);
            }
        }

        private void GenerateNewFieldPropertiesCppFile()
        {
            FieldItem lastFieldItem = DesktopModelObject.fieldItemList.Where(x => x.isNewField == false).OrderBy(x => Convert.ToInt32(x.FieldId)).Last();
            string lastExistingShortFieldId = lastFieldItem.FieldShortId;
            string lastExistingFieldName = lastFieldItem.FieldName;

            var files = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                         where file.Contains("ifast_fieldprops")
                         from line in File.ReadLines(file, Encoding.Default)
                         where (line.Contains("// Field s_FldProp_") && line.Contains("(" + lastExistingShortFieldId + ")"))
                         select new
                         {
                             File = file,
                             Line = line
                         }).Single();

            string fileName = Path.GetFileName(files.File);
            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.StartsWith("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            var dataFieldPropertyLines = from line in lines
                                         where (line.Contains("extern const") && line.Contains(lastExistingFieldName))
                                         select new
                                         {
                                             Line = line,
                                             Index = lines.IndexOf(line)
                                         };

            int countDataFieldPropertyLines = dataFieldPropertyLines.Count();

            if (count == 2 && countDataFieldPropertyLines > 0)
            {
                // Generate field properties file
                FieldPropertiesCpp_RuntimeTextTemplate page = new FieldPropertiesCpp_RuntimeTextTemplate();
                page.modelDesktopInterface = DesktopModelObject;
                page.fieldItem = fieldItem;
                page.fieldPropertiesItem = fieldPropertiesItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfIfdsNamespaceClosingBraceLine = significantLines.ToList().ElementAt(1).Index;
                page.indexOfLastPropertyDeclarationLine = dataFieldPropertyLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldPropertiesCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strIfastFieldPropertiesCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldPropertiesCppFileName, Color.Green);
            }
        }

        private void buttonAddField_Click(object sender, EventArgs e)
        {
            AddFieldForm addFieldForm = new AddFieldForm();
            addFieldForm.model = DesktopModelObject;

            DialogResult result = addFieldForm.ShowDialog(this);
            if (result == DialogResult.OK)
            {
                LoadFieldsUI();
                objectListViewAllFields.Focus();
                objectListViewAllFields.EnsureModelVisible(addFieldForm.newFieldItem);
                objectListViewAllFields.SelectObject(addFieldForm.newFieldItem);
            }
        }

        private void buttonDeleteField_Click(object sender, EventArgs e)
        {
            if (fieldItem != null && fieldPropertiesItem != null)
            {
                if (IsFieldUsedInDataSets(fieldItem.FieldName))
                {
                    MessageBox.Show("Selected field is used in Data Sets and cannot be deleted.", FieldsEditorErrorBoxCaption, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                GenerateFilesToDeleteSelectedField();

                int indexOfSelectedItem = DesktopModelObject.fieldItemList.IndexOf(fieldItem);
                DesktopModelObject.fieldItemList.Remove(fieldItem);
                FieldItem itemToSelect = DesktopModelObject.fieldItemList.ElementAt(indexOfSelectedItem);
                if (itemToSelect == null && indexOfSelectedItem > 0)
                {
                    itemToSelect = DesktopModelObject.fieldItemList.ElementAt(indexOfSelectedItem - 1);
                }

                LoadFieldsUI();
                objectListViewAllFields.Focus();

                if (itemToSelect != null)
                {
                    objectListViewAllFields.EnsureModelVisible(itemToSelect);
                    objectListViewAllFields.SelectObject(itemToSelect);
                }
            }
        }

        private bool IsFieldUsedInDataSets(string fieldName)
        {
            bool bIsFieldUsedInDataSets = false;

            List<string> listOfDataSetsWhereFieldIsUsed = GetAllDataSetsWhereIsFieldUsed(fieldName);

            if (listOfDataSetsWhereFieldIsUsed.Count() > 0)
            {
                bIsFieldUsedInDataSets = true;
            }

            return bIsFieldUsedInDataSets;
        }

        private List<string> GetAllDataSetsWhereIsFieldUsed(string fieldName)
        {
            List<string> listOfDataSetsWhereFieldIsUsed = new List<string>();

            string fieldNameToSearch = " " + fieldName + ";";

            if (Directory.Exists(DataImplFolderPath))
            {
                var files = from file in Directory.EnumerateFiles(DataImplFolderPath, "*.hpp", SearchOption.TopDirectoryOnly)
                            where file.Contains("dse_dstc")
                            from line in File.ReadLines(file, Encoding.Default)
                            where line.Contains(fieldNameToSearch)
                            select new
                            {
                                File = file,
                                Line = line
                            };

                listOfDataSetsWhereFieldIsUsed = files.Select(p => p.File).ToList();
            }

            return listOfDataSetsWhereFieldIsUsed;
        }

        private void GenerateFilesToDeleteSelectedField()
        {
            OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - START");

            GenerateDeleteFieldFromFactoryFile();
            GenerateDeleteFieldFromIdsCppFile();
            GenerateDeleteFieldFromIdsHppFile();
            GenerateDeleteFieldFromPropertiesHppFile();
            GenerateDeleteFieldFromPropertiesCppFile();

            OutputWindow_WriteLine(fieldProperties.FieldName + " - GENERATE CODE - END");
            OutputWindow_WriteEmptyLine();
        }

        private void GenerateDeleteFieldFromFactoryFile()
        {
            var fileName = DesktopModelObject.fieldItemList.Where(x => x.FieldName == fieldItem.FieldName).First().FieldFactoryFileName;

            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

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
                DeleteFieldFromFieldFactoryCpp_RuntimeTextTemplate page = new DeleteFieldFromFieldFactoryCpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strFieldFactoryCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strFieldFactoryCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strFieldFactoryCppFileName, Color.Green);
            }
        }

        private void GenerateDeleteFieldFromIdsCppFile()
        {
            var files = from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                        where file.Contains("ifast_fieldids")
                        from line in File.ReadLines(file, Encoding.Default)
                        where line.Contains(fieldItem.FieldId)
                        select new
                        {
                            File = file,
                            Line = line
                        };

            if (files.Count() == 1)
            {
                string fileName = Path.GetFileName(files.ToList()[0].File);
                string fileFullPathName = DataImplFolderPath + "\\" + fileName;

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
                    DeleteFieldFromFieldIdsCpp_RuntimeTextTemplate page = new DeleteFieldFromFieldIdsCpp_RuntimeTextTemplate();
                    page.fieldItem = fieldItem;
                    page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                    page.lines = lines.ToList();
                    String pageContent = page.TransformText();
                    string strFieldIdsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                    System.IO.File.WriteAllText(strFieldIdsCppFileName, pageContent);

                    OutputWindow_WriteIndentedLine("Generated file: " + strFieldIdsCppFileName, Color.Green);
                }
            }
        }

        private void GenerateDeleteFieldFromIdsHppFile()
        {
            var fileName = "ifast_fieldids.hpp";

            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

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
                DeleteFieldFromFieldIdsHpp_RuntimeTextTemplate page = new DeleteFieldFromFieldIdsHpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strFieldIdsHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strFieldIdsHppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strFieldIdsHppFileName, Color.Green);
            }
        }

        private void GenerateDeleteFieldFromPropertiesHppFile()
        {
            var fileName = "ifast_fieldprops.hpp";

            string fileFullPathName = DataImplFolderPath + "\\" + fileName;

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
                DeleteFieldFromFieldPropsHpp_RuntimeTextTemplate page = new DeleteFieldFromFieldPropsHpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strFieldPropsHppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fileName;
                System.IO.File.WriteAllText(strFieldPropsHppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strFieldPropsHppFileName, Color.Green);
            }
        }

        private void GenerateDeleteFieldFromPropertiesCppFile()
        {
            string fileFullPathName = DataImplFolderPath + "\\" + fieldPropertiesItem.FileName;
            string strFieldPropertyStart = "// Field s_FldProp_" + fieldItem.FieldName + " (" + fieldItem.FieldShortId + ")";

            var lines = File.ReadAllLines(fileFullPathName, Encoding.Default).Select(l => l.TrimEnd()).ToList();

            var significantLines = from line in lines
                                   where (line.Contains("namespace ifds") || line.Contains(strFieldPropertyStart) || line.Contains("// Field s_FldProp_") || line.StartsWith("}"))
                                   select new
                                   {
                                       Line = line,
                                       Index = lines.IndexOf(line)
                                   };

            int count = significantLines.Count();

            var lineWherePropertyDefinitionStarts = from line in lines
                                                    where line.Contains(strFieldPropertyStart)
                                                    select new
                                                    {
                                                        Line = line,
                                                        Index = lines.IndexOf(line)
                                                    };

            int countPropertyLines = lineWherePropertyDefinitionStarts.Count();

            if (count >= 3 && countPropertyLines > 0)
            {
                // Generate field properties file
                DeleteFieldPropsCpp_RuntimeTextTemplate page = new DeleteFieldPropsCpp_RuntimeTextTemplate();
                page.fieldItem = fieldItem;
                page.fieldPropertiesItem = fieldPropertiesItem;
                page.indexOfIfdsNamespaceLine = significantLines.ToList().ElementAt(0).Index;
                page.indexOfPropertyDefinitionStartLine = lineWherePropertyDefinitionStarts.ToList().ElementAt(0).Index;
                int nextItemAfterDefinition = significantLines.ToList().FindIndex(s => s.Line.Contains(strFieldPropertyStart)) + 1;
                page.indexOfRemainingCodeNextLine = significantLines.ToList().ElementAt(nextItemAfterDefinition).Index;
                page.lines = lines.ToList();
                String pageContent = page.TransformText();
                string strIfastFieldPropsCppFileName = DataImplFolderPath + MainFormInterface.GetGeneratedFilesOutputFolder + fieldPropertiesItem.FileName;
                System.IO.File.WriteAllText(strIfastFieldPropsCppFileName, pageContent);

                OutputWindow_WriteIndentedLine("Generated file: " + strIfastFieldPropsCppFileName, Color.Green);
            }
        }

        private void ObjectListViewAllFields_Leave(object sender, EventArgs e)
        {
            this.buttonDeleteField.Enabled = false;
        }

        private void ObjectListViewAllFields_Enter(object sender, EventArgs e)
        {
            fieldItem = (FieldItem)this.objectListViewAllFields.SelectedObject;

            if (fieldItem != null)
            {
                this.buttonDeleteField.Enabled = true;
            }
        }

        private void PropertyGridFields_Leave(object sender, EventArgs e)
        {
            if (fieldItem != null && fieldPropertiesItem != null)
            {
                UpdatePropertyValues();
                objectListViewAllFields.RefreshObject(fieldItem);
            }
        }

        private void PropertyGridFields_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            GridItem item = e.ChangedItem;

            if (item.Label == "Field type")
            {
                string strValue = item.Value.ToString();
                SetFieldPropertyTypeForSelectedFieldType(strValue);
            }
        }

        private void SetFieldPropertyTypeForSelectedFieldType(string strValue)
        {
            if (strValue == "BFBigDecimalField")
            {
                fieldProperties.FieldPropertyType = "bigdecimal";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue == "BFDecimalField")
            {
                fieldProperties.FieldPropertyType = "decimal";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue == "BFDateField")
            {
                fieldProperties.FieldPropertyType = "date";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue == "BFIntegerField")
            {
                fieldProperties.FieldPropertyType = "integer";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue == "BFNumericField")
            {
                fieldProperties.FieldPropertyType = "numeric";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue == "BFTimeField")
            {
                fieldProperties.FieldPropertyType = "time";
                fieldProperties.FieldLength = 0;
            }
            else if (strValue.Contains("BFTextField"))
            {
                fieldProperties.FieldPropertyType = "text";

                // For text property also set length if it is available as a part of type
                string strLength = new String(strValue.Where(Char.IsDigit).ToArray());
                fieldProperties.FieldLength = Convert.ToInt32(strLength);
            }
        }
    }
}
