using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Collections;
using System.Xml.Linq;
using System.Drawing;

namespace ViewsGenerator
{
    public class ModelDesktop : IModelDesktopInterface
    {
        public IMainFormInterface MainFormInterface { get; set; }
        public string DataImplFolderPath { get; set; }
        private readonly string dataSetIdsFileName = "ifast_dataids.cpp";
        // private readonly string masksFileName = "ifast_masks.cpp";
        private readonly string masksXmlFileName = "masks.xml";

        public List<DataSetItem> dataSetItemList = new List<DataSetItem>();

        public Dictionary<string, FieldPropertiesItem> fieldPropertiesDictionary = new Dictionary<string, FieldPropertiesItem>();
        public Dictionary<string, string> dataSetNameAndIDsDictionary = new Dictionary<string, string>();
        public Dictionary<string, FieldItem> fieldsDictionary = new Dictionary<string, FieldItem>();
        public List<FieldItem> fieldItemList = new List<FieldItem>();
        public List<string> distinctExactFieldItemTypes = new List<string>();
        public List<string> distinctBaseFieldItemTypes = new List<string>();

        public Dictionary<string, MaskItem> masksDictionary = new Dictionary<string, MaskItem>();
        public List<string> maskNamesList = new List<string>();
        public List<SubstitutionSetItem> substitutionsList = new List<SubstitutionSetItem>();
        public List<SubstitutionSetItem> distinctSubstitutionsList = new List<SubstitutionSetItem>();
        public Dictionary<string, string> uniqueIdToCountryLanguageDictionary = new Dictionary<string, string>();
        public Dictionary<string, string> uniqueCountryLanguageToIdDictionary = new Dictionary<string, string>();
        public List<MarketItem> marketClientItemList = new List<MarketItem>();

        private String logErrorMessage = "";


        public ModelDesktop()
        {
            this.MainFormInterface = null;
        }

        public async void LoadData()
        {
            if (string.IsNullOrEmpty(DataImplFolderPath))
            {
                MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            LoadDataSetIDs();

            await Task.Run(() => LoadLanguageCountryData());
            await Task.Run(() => LoadMarketClientData());
            await Task.Run(() => LoadMasks());
            await Task.Run(() => LoadFieldProperties());
            await Task.Run(() => LoadFields());
            await Task.Run(() => LoadSubstitutionSets());

            MainFormInterface.EnableLoadDesktopDataButton();

            if (!String.IsNullOrEmpty(logErrorMessage))
            {
                LogErrorMessageAfterLoading();
                logErrorMessage = "";
            }
        }

        public void LoadLanguageCountryData()
        {
            uniqueIdToCountryLanguageDictionary.Clear();
            uniqueCountryLanguageToIdDictionary.Clear();

            if (string.IsNullOrEmpty(DataImplFolderPath))
            {
                MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = DataImplFolderPath + "\\languages.xml";

            if (File.Exists(strFullFileNameWithPath))
            {
                var languages = from lang in XElement.Load(strFullFileNameWithPath).Elements("Language")
                                select new
                                {
                                    Id = lang.Attribute("Language_Id").Value,
                                    Country = lang.Attribute("Country").Value,
                                    Language = lang.Attribute("Language").Value,
                                };

                foreach (var lang in languages)
                {
                    string id = lang.Id;
                    string languageCountry = lang.Language + lang.Country;
                    uniqueIdToCountryLanguageDictionary.Add(id, languageCountry);
                }

                uniqueCountryLanguageToIdDictionary = uniqueIdToCountryLanguageDictionary.ToDictionary(x => x.Value, x => x.Key);
            }
            else
            {
                MessageBox.Show("File languages.xml doesn't exist in " + DataImplFolderPath, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void LoadMarketClientData()
        {
            marketClientItemList.Clear();

            if (string.IsNullOrEmpty(DataImplFolderPath))
            {
                MessageBox.Show("Path to \"ifastdataimpl\" folder is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = DataImplFolderPath + "\\clients.xml";

            if (File.Exists(strFullFileNameWithPath))
            {
                try
                {
                    XDocument doc = XDocument.Load(strFullFileNameWithPath);

                    var markets = doc.Descendants("Market");

                    foreach (var market in markets)
                    {
                        MarketItem marketItem = new MarketItem();
                        marketItem.MarketId = market.Attribute("Market_Id").Value;
                        marketItem.MarketName = market.Attribute("Market_Name").Value;

                        var clients = market.Descendants("Client");

                        foreach (var client in clients)
                        {
                            ClientItem clientItem = new ClientItem();
                            clientItem.ClientId = client.Attribute("Client_Id").Value;
                            clientItem.ClientName = client.Value;

                            marketItem.clientInMarketItemList.Add(clientItem);
                        }

                        marketClientItemList.Add(marketItem);
                    }
                }
                catch (IOException ex)
                {
                    MessageBox.Show("An error occurred while loading clients xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("File clients.xml doesn't exist in " + DataImplFolderPath, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void LoadMasks()
        {
            if (string.IsNullOrEmpty(DataImplFolderPath))
            {
                MessageBox.Show("File path is not valid!", "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string strFullFileNameWithPath = DataImplFolderPath + "\\" + masksXmlFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                masksDictionary.Clear();
                maskNamesList.Clear();

                try
                {
                    XDocument doc = XDocument.Load(strFullFileNameWithPath);

                    var masks = doc.Descendants("Mask");

                    foreach (var mask in masks)
                    {
                        MaskItem maskItem = new MaskItem();
                        maskItem.GroupId = mask.Attribute("Group_Id").Value;
                        maskItem.MaskId = mask.Attribute("Mask_Id").Value;
                        maskItem.MaskName = mask.Attribute("Mask_Name").Value;
                        maskItem.MaskChooser = "mask_chooser_" + maskItem.GroupId + "_" + maskItem.MaskId;

                        var languageMasks = mask.Descendants("Language_Mask");

                        foreach (var languageMask in languageMasks)
                        {
                            LanguageMaskItem languageMaskItem = new LanguageMaskItem();
                            languageMaskItem.LanguageId = languageMask.Attribute("Language_Id").Value;
                            languageMaskItem.Mask = languageMask.Value;

                            maskItem.languageMaskItemList.Add(languageMaskItem);
                        }

                        masksDictionary[maskItem.MaskName] = maskItem;
                    }

                    // sort dictionary based on key value in ascending order
                    masksDictionary = masksDictionary.OrderBy(x => x.Key).ToDictionary(x => x.Key, x => x.Value);
                    maskNamesList = masksDictionary.Select(x => x.Value.MaskName).Distinct().ToList();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("An error occurred while loading masks xml file. Error: " + ex, "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Masks xml file doesn't exist in the specified location.", "Loading Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void LoadFieldProperties()
        {
            if (Directory.Exists(DataImplFolderPath))
            {
                distinctBaseFieldItemTypes.Clear();

                List<FileAndLineHelper> lines = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                                        where file.Contains("ifast_fieldprops")
                                        from line in File.ReadLines(file, Encoding.Default)
                                        where (line.Contains("extern CLASS_EXPORT const BFDataFieldProperties") || line.Contains("BFDataFieldProperties::Type::") || line.Contains("   ,") || line.Contains("return chooser_ss_") ||
                                               line.Contains("static const DString") || line.Contains("_s_DVF(") || line.Contains("_i_DVF(") || line.Contains("_d_DVF(") || line.Contains("_FLF("))
                                        select new FileAndLineHelper
                                        {
                                            File = file,
                                            Line = line
                                        }).ToList();

                CreateFieldPropertiesFromLines(lines);
            }
        }

        private void CreateFieldPropertiesFromLines(List<FileAndLineHelper> lines)
        {
            string fieldPropertyName = string.Empty;
            int count = lines.Count();

            for (int i = 0; i < count; i = i + 15)
            {
                FieldPropertiesItem fieldPropertiesItem = new FieldPropertiesItem();

                fieldPropertiesItem.FileName = Path.GetFileName(lines[i].File);

                if (lines[i].Line.Contains("_s_DVF("))
                {
                    i++;

                    while (lines[i].Line.Contains("static const DString"))
                    {
                        string value = lines[i].Line.Split('\"')[1];
                        string language = lines[i].Line.Split('_')[2].RemoveTextAfterFirstChar('(');

                        fieldPropertiesItem.SetValueString(value, language);
                        i++;
                    }
                }

                if (lines[i].Line.Contains("_i_DVF("))
                {
                    fieldPropertiesItem.SetValueIntegerBasedOnStringValues();
                    i++;
                }

                if (lines[i].Line.Contains("_d_DVF("))
                {
                    fieldPropertiesItem.SetValueDoubleBasedOnStringValues();
                    i++;
                }

                if (lines[i].Line.Contains("_FLF("))
                {
                    i++;

                    while (lines[i].Line.Contains("static const DString"))
                    {
                        string value = lines[i].Line.Split('\"')[1];
                        string language = lines[i].Line.Split('_')[2].RemoveTextAfterFirstChar('(');

                        fieldPropertiesItem.SetLabel(value, language);
                        i++;
                    }
                }

                if (lines[i].Line.Contains("return chooser_ss_"))
                {
                    fieldPropertyName = lines[i].Line.Replace("return", "").RemoveTextAfterFirstChar(';').Trim();
                    fieldPropertiesItem.Chooser_ss_function = fieldPropertyName;
                    i++;
                }

                while (!lines[i].Line.Contains("extern CLASS_EXPORT const BFDataFieldProperties "))
                {
                    i++;
                }

                if (lines[i].Line.Contains("extern CLASS_EXPORT const BFDataFieldProperties "))
                {
                    fieldPropertyName = lines[i].Line.Replace("extern CLASS_EXPORT const BFDataFieldProperties ", "").Replace("(", "").Trim();
                    fieldPropertiesItem.FieldName = fieldPropertyName;
                }

                if (lines[i + 1].Line.Contains("BFDataFieldProperties::Type::"))
                {
                    fieldPropertiesItem.FieldType = lines[i + 1].Line.Replace("BFDataFieldProperties::Type::", "").RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 2].Line.Contains(" // fieldId"))
                {
                    fieldPropertiesItem.FieldName = lines[i + 2].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 3].Line.Contains(" // length"))
                {
                    fieldPropertiesItem.FieldLength = lines[i + 3].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 4].Line.Contains(" // minimum length"))
                {
                    fieldPropertiesItem.FieldMinimumLength = lines[i + 4].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 5].Line.Contains(" // dec"))
                {
                    fieldPropertiesItem.FieldDecimals = lines[i + 5].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 6].Line.Contains(" // mask chooser function"))
                {
                    fieldPropertiesItem.MaskChooserFunction = lines[i + 6].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 7].Line.Contains(" // default value"))
                {
                    fieldPropertiesItem.DefaultValueStringFunctionName = lines[i + 7].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 8].Line.Contains(" // default value"))
                {
                    fieldPropertiesItem.DefaultValueIntegerFunctionName = lines[i + 8].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 9].Line.Contains(" // default value"))
                {
                    fieldPropertiesItem.DefaultValueDoubleFunctionName = lines[i + 9].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 10].Line.Contains(" // label"))
                {
                    fieldPropertiesItem.LabelFunctionName = lines[i + 10].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 11].Line.Contains(" // field name is deprecated"))
                {
                    fieldPropertiesItem.FieldNameIsDeprecated = lines[i + 11].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 12].Line.Contains(" // allow Nulls"))
                {
                    fieldPropertiesItem.AllowNulls = lines[i + 12].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 13].Line.Contains(" // justification"))
                {
                    fieldPropertiesItem.Justification = lines[i + 13].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (lines[i + 14].Line.Contains(" substitution "))
                {
                    fieldPropertiesItem.SubstitutionSetSuperChooser = lines[i + 14].Line.RemoveTextAfterFirstChar('/').Replace(",", "").Trim();
                }

                if (fieldPropertyName != "" && fieldPropertiesItem != null)
                {
                    fieldPropertiesDictionary[fieldPropertyName] = fieldPropertiesItem;
                }
            }

            distinctBaseFieldItemTypes = fieldPropertiesDictionary.Select(x => x.Value.FieldType).Distinct().ToList();
            distinctBaseFieldItemTypes.Sort();
        }

        private void LoadFields()
        {
            if (Directory.Exists(DataImplFolderPath))
            {
                fieldItemList.Clear();

                var files = from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                            where file.Contains("ifast_fieldfactory")
                            from line in File.ReadLines(file, Encoding.Default)
                            where (line.Contains("case") && line.Contains("new") && line.Contains("break"))
                            select new
                            {
                                File = file,
                                Line = line
                            };

                string[] separators = { "case", ": pField = new", "(", ",", ")" };

                foreach (var file in files)
                {
                    string[] split = file.Line.Split(separators, StringSplitOptions.None);

                    FieldItem fieldItem = new FieldItem();

                    fieldItem.FieldFactoryFileName = Path.GetFileName(file.File);

                    fieldItem.FieldId = split[1].Trim();
                    fieldItem.FieldShortId = fieldItem.FieldId.Remove(0, 1).TrimStart('0');

                    fieldItem.FieldDerivedType = split[2].Trim();

                    if (fieldItem.FieldDerivedType.Contains("BFTextField"))
                    {
                        fieldItem.FieldType = "BFTextField";
                    }
                    else
                    {
                        fieldItem.FieldType = fieldItem.FieldDerivedType;
                    }

                    fieldItem.FieldName = split[3].Trim();
                    string strPropName = split[4].Trim();
                    fieldItem.FieldPropertiesName = strPropName.Replace("&", "");

                    FieldPropertiesItem fieldPropertiesItem = null;
                    fieldPropertiesDictionary.TryGetValue(fieldItem.FieldPropertiesName, out fieldPropertiesItem);
                    if (fieldPropertiesItem != null)
                    {
                        fieldItem.FieldLength = Convert.ToInt32(fieldPropertiesItem.FieldLength);
                    }

                    fieldItemList.Add(fieldItem);
                    fieldsDictionary[fieldItem.FieldName] = fieldItem;
                }

                int count = fieldItemList.Count();

                distinctExactFieldItemTypes = fieldItemList.Select(x => x.FieldDerivedType).Distinct().ToList();
                distinctExactFieldItemTypes.Sort();

                CheckForFieldsWithDuplicateIDs();
            }
        }

        private void LoadDataSetIDs()
        {
            dataSetNameAndIDsDictionary.Clear();

            string strFullFileNameWithPath = DataImplFolderPath + "\\" + dataSetIdsFileName;

            if (File.Exists(strFullFileNameWithPath))
            {
                var lines = from file in Directory.EnumerateFiles(DataImplFolderPath, dataSetIdsFileName, SearchOption.TopDirectoryOnly)
                            from line in File.ReadLines(file, Encoding.Default)
                            where line.Contains("extern IFAST_DATAIMPL_LINKAGE const BFDataId")
                            select new
                            {
                                File = file,
                                Line = line
                            };

                foreach (var line in lines)
                {
                    string dataSetNameAndId = line.Line.Substring(line.Line.IndexOf('(')).TrimStart();
                    dataSetNameAndId = Regex.Replace(dataSetNameAndId, @"[();\s+]", "").Replace("I_", "").Replace("_", "").Replace("\"", "");
                    string[] split = dataSetNameAndId.Split(new char[] { ',' });

                    if (split.Length == 2)
                    {
                        dataSetNameAndIDsDictionary[split[1]] = split[0];
                    }
                }

                // sort dictionary based on ID value in ascending order
                dataSetNameAndIDsDictionary = dataSetNameAndIDsDictionary.OrderBy(x => x.Value).ToDictionary(x => x.Key, x => x.Value);
            }
        }

        private void LoadSubstitutionSets()
        {
            substitutionsList.Clear();

            if (Directory.Exists(DataImplFolderPath))
            {
                List<FileAndLineHelper> lines = (from file in Directory.EnumerateFiles(DataImplFolderPath, "*.cpp", SearchOption.TopDirectoryOnly)
                                where (file.Contains("ifast_substitutions") && !file.Contains("chooser"))
                                from line in File.ReadLines(file, Encoding.Default)
                                where (line.Contains("// Substitution set") || line.Contains("static const I_CHAR* aKeys") || line.Contains("static const I_CHAR* aValues") || line.Contains("I_(") || line.Contains("extern const BFSubstitutionSet"))
                                select new FileAndLineHelper
                            {
                                File = file,
                                Line = line
                            }).ToList();

                CreateSubstitutionSetsFromLines(lines);
            }
        }

        private void CreateSubstitutionSetsFromLines(List<FileAndLineHelper> lines)
        {
            string[] separators = { ".", ",", ":" };

            int count = lines.Count();

            for (int i = 0; i < count; i++)
            {
                SubstitutionSetItem item = new SubstitutionSetItem();

                if (lines[i].Line.Contains("// Substitution set"))
                {
                    string strSubstitutionSet = lines[i].Line.Replace("// Substitution set", "");

                    string[] split = strSubstitutionSet.Split(separators, StringSplitOptions.RemoveEmptyEntries);

                    item.Group = "2";
                    item.FileName = Path.GetFileName(lines[i].File);

                    if (split.Count() >= 1)
                    {
                        item.Name = split[0].Trim();
                    }
                    else
                    {
                        item.Name = string.Empty;
                    }

                    if (split.Count() >= 3)
                    {
                        item.Language = split[2].Trim();
                    }
                    else
                    {
                        item.Language = string.Empty;
                    }

                    if (split.Count() >= 5)
                    {
                        item.MarketId = split[4].Trim();
                        item.MarketName = GetMarketName(item.MarketId);
                    }
                    else
                    {
                        item.MarketId = string.Empty;
                        item.MarketName = GetMarketName(item.MarketId);
                    }

                    if (split.Count() >= 7)
                    {
                        item.ClientId = split[6].Trim();
                        item.ClientName = GetClientName(item.MarketId, item.ClientId);
                    }
                    else
                    {
                        item.ClientId = string.Empty;
                        item.ClientName = GetClientName(item.MarketId, item.ClientId);
                    }

                    i++;
                }

                if (lines[i].Line.Contains("static const I_CHAR* aKeys"))
                {
                    string aKeysName = lines[i].Line.Replace("static const I_CHAR*", "").Replace("[] = {", "").Trim();
                    item.KeysName = aKeysName;
                    item.SubstitutionSetId = aKeysName.Replace("aKeys_", "");

                    string[] split = item.SubstitutionSetId.Split(new char[] { '_' });

                    if (split.Length == 5)
                    {
                        item.SubstitutionSetCreationIndex = split[1];
                        item.SubstitutionSetCreationIndexInt = Convert.ToInt32(item.SubstitutionSetCreationIndex.TrimStart('0'));
                        item.SubstitutionSetShortId = split[1] + "_" + split[2];
                        item.SubstitutionSetChooserFunction = "chooser_ss_" + item.SubstitutionSetShortId;
                    }

                    i++;
                }

                while (lines[i].Line.Contains("I_("))
                {
                    string aKeysArrayItem = lines[i].Line.Replace("I_(", "").Replace("),", "").Replace("\"", "").Trim();
                    item.KeysArray.Add(aKeysArrayItem);
                    i++;
                }

                if (lines[i].Line.Contains("static const I_CHAR* aValues"))
                {
                    string aValuesName = lines[i].Line.Replace("static const I_CHAR*", "").Replace("[] = {", "").Trim();
                    item.ValuesName = aValuesName;
                    i++;
                }

                while (lines[i].Line.Contains("I_("))
                {
                    string aValuesArrayItem = lines[i].Line.Replace("I_(", "").Replace("),", "").Replace("\"", "").Trim();
                    item.ValuesArray.Add(aValuesArrayItem);
                    i++;
                }

                if (item.Name != null && item.Name != string.Empty)
                {
                    substitutionsList.Add(item);
                }
            }

            distinctSubstitutionsList = substitutionsList.GroupBy(x => x.Name).Select(o => o.First()).OrderBy(x => x.Name).ToList();
            // This is loaded now from the language XML file
            // uniqueCountryLanguageList = substitutionsList.GroupBy(x => x.Language).Select(o => o.First()).OrderBy(x => x.Language).Select(item => item.Language).ToList();
        }

        public string GetFullNameOfNewDataSet(string dataSet, string dataSetType)
        {
            dataSet = dataSet.Replace("_REQ", "").Replace("_VW", "").Replace("Repeat_Record", "");

            string fullDataSetName = string.Empty;
            if (dataSetType == "Request")
            {
                fullDataSetName = dataSet.ToUpper() + ".REQ";
            }
            else if (dataSetType == "View")
            {
                fullDataSetName = dataSet.ToUpper() + ".VW";
            }
            else if (dataSetType == "View Repeat Record")
            {
                fullDataSetName = dataSet.ToUpper() + ".VWRepeatRecord";
            }
            else if (dataSetType == "Request Repeat Record")
            {
                fullDataSetName = dataSet.ToUpper() + ".REQRepeatRecord";
            }

            return fullDataSetName;
        }

        public void AddNewDataSetToDictionary(string fullDataSetName)
        {
            int maxDataSetId = Convert.ToInt32(dataSetNameAndIDsDictionary.Max(x => x.Value));
            int maxFieldId = Convert.ToInt32(fieldItemList.Max(x => x.FieldId));

            int newDataSetId = Math.Max(maxDataSetId, maxFieldId) + 1;

            if (fullDataSetName != string.Empty)
            {
                dataSetNameAndIDsDictionary[fullDataSetName] = newDataSetId.ToString();

                // sort dictionary based on ID value in ascending order
                dataSetNameAndIDsDictionary = dataSetNameAndIDsDictionary.OrderBy(x => x.Value).ToDictionary(x => x.Key, x => x.Value);
            }
        }

        public string GetMarketName(string marketId)
        {
            string marketName = string.Empty;

            if (marketClientItemList.Count > 0 && marketId != string.Empty)
            {
                marketName = marketClientItemList.First(x => x.MarketId == marketId).MarketName;
            }

            return marketName;
        }

        public string GetClientName(string marketId, string clientId)
        {
            string clientName = string.Empty;

            if (marketClientItemList.Count > 0 && marketId != string.Empty && clientId != string.Empty)
            {
                clientName = marketClientItemList.First(x => x.MarketId == marketId).clientInMarketItemList.Find(y => y.ClientId == clientId).ClientName;
            }

            return clientName;
        }

        public string GetLanguageIdBasedOnLanguageCountryName(string languageCountry)
        {
            string languageId = string.Empty;

            if (uniqueCountryLanguageToIdDictionary.Count() > 0 && languageCountry != string.Empty)
            {
                // Find the value based on case insensitive key since country names in source code are not consistant (esEs vs esES)
                languageId = uniqueCountryLanguageToIdDictionary.Single(x => x.Key.ToLower() == languageCountry.ToLower()).Value;
            }

            return languageId;
        }

        public string GetLanguageCountryString(string languageId)
        {
            string languageCountry = string.Empty;

            if (uniqueIdToCountryLanguageDictionary.Count() > 0 && languageId != string.Empty)
            {
                languageCountry = uniqueIdToCountryLanguageDictionary.Single(x => x.Key == languageId).Value;
            }

            return languageCountry;
        }

        private void CheckForFieldsWithDuplicateIDs()
        {
            var duplicateIDs = fieldItemList.GroupBy(item => item.FieldId).Where(grp => grp.Skip(1).Any());

            if (duplicateIDs.Count() > 0)
            {
                String msg = "Fields with duplicate IDs found:" + Environment.NewLine + Environment.NewLine;

                foreach (var group in duplicateIDs)
                {
                    foreach (var duplicateID in group)
                    {
                        FieldItem fieldItem = (FieldItem)duplicateID;
                        msg += fieldItem.FieldId.ToString() + ", " + fieldItem.FieldName.ToString() + ", " + fieldItem.FieldFactoryFileName.ToString() + ", " + Environment.NewLine;
                    }

                    msg += Environment.NewLine;
                }

                msg += Environment.NewLine + Environment.NewLine;

                MessageBox.Show(msg, "Views Generator", MessageBoxButtons.OK, MessageBoxIcon.Error);

                logErrorMessage = msg;
            }
        }

        private void LogErrorMessageAfterLoading()
        {
            MainFormInterface.OutputWindow_WriteLine("ERROR", Color.Red);
            MainFormInterface.OutputWindow_WriteLine(logErrorMessage, Color.Red);
        }
    }
}
