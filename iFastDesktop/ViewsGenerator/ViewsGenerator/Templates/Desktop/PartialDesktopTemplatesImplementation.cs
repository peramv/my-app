using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator.Templates.Desktop
{
    public partial class DataImplExistsCpp_RuntimeTextTemplate : DataImplExistsCpp_RuntimeTextTemplateBase
    {
        public Dictionary<string, string> dataSetNameAndIDsDictionary = null;
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
    }

    public partial class DataImplFactoryCpp_RuntimeTextTemplate : DataImplFactoryCpp_RuntimeTextTemplateBase
    {
        public Dictionary<string, string> dataSetNameAndIDsDictionary = null;
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
    }

    public partial class DataIdsCpp_RuntimeTextTemplate : DataIdsCpp_RuntimeTextTemplateBase
    {
        public Dictionary<string, string> dataSetNameAndIDsDictionary = null;
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
    }

    public partial class DataIdsHpp_RuntimeTextTemplate : DataIdsHpp_RuntimeTextTemplateBase
    {
        public Dictionary<string, string> dataSetNameAndIDsDictionary = null;
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
    }

    public partial class DseHpp_RuntimeTextTemplate : DseHpp_RuntimeTextTemplateBase
    {
        public string DataSetItemName { get; set; }
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<FieldItem> fieldItemList = null;
        public string RepeatsFile { get; set; }
    }

    public partial class DsiH_RuntimeTextTemplate : DsiH_RuntimeTextTemplateBase
    {
        public string DataSetItemName { get; set; }
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<FieldItem> fieldItemList = null;
    }

    public partial class DsiCpp_RuntimeTextTemplate : DsiCpp_RuntimeTextTemplateBase
    {
        public string DataSetItemName { get; set; }
        public string HeaderDataSetFileName { get; set; }
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<FieldItem> fieldItemList = null;
        public Dictionary<string, string> dataSetNameAndIDsDictionary = null;

        private bool IsViewDataSet()
        {
            if (DataSetItemName.Contains("_VW") && !DataSetItemName.Contains("Repeat_Record"))
            {
                return true;
            }

            return false;
        }

        private bool IsRequestDataSet()
        {
            if (DataSetItemName.Contains("_REQ") && !DataSetItemName.Contains("Repeat_Record"))
            {
                return true;
            }

            return false;
        }

        private bool IsRepeatRecordDataSet()
        {
            if (DataSetItemName.Contains("Repeat_Record"))
            {
                return true;
            }

            return false;
        }

        private string GetIdOfDataSet(string dataSetName)
        {
            string dataSetId = "";

            // Convert dataSetName string to format saved in dictionary
            if (dataSetName.Contains("_"))
            {
                dataSetName = dataSetName.ReplaceFirst("_", ".");
            }

            if (IsRepeatRecordDataSet())
            {
                dataSetName = dataSetName.Replace("_", "");
            }

            if (!dataSetNameAndIDsDictionary.TryGetValue(dataSetName, out dataSetId))
            {
                dataSetId = "";
            }

            return dataSetId;
        }

        private string GetRepeatsFileDataSetIdIfAvailable()
        {
            string repeatsId = "";

            if (IsViewDataSet() || IsRequestDataSet())
            {
                string repeatsDataSetName = "";

                if (!DataSetItemName.Contains("RepeatRecord"))
                {
                    repeatsDataSetName = DataSetItemName + "RepeatRecord";
                }

                repeatsId = GetIdOfDataSet(repeatsDataSetName);
            }

            return repeatsId;
        }

        private string GetLargestDefinedField()
        {
            string largestLength = "0";

            if (fieldItemList.Count > 0)
            {
                largestLength = fieldItemList.Select(i => Convert.ToInt32(i.FieldLength)).Max().ToString();
            }

            return largestLength;
        }

        private string GetDefinedByteLength()
        {
            string totalLength = "0";

            if (fieldItemList.Count > 0)
            {
                totalLength = fieldItemList.Sum(t => Convert.ToInt32(t.FieldLength)).ToString();
            }

            return totalLength;
        }
    }

    public partial class ReplaceFieldPropsCpp_RuntimeTextTemplate : ReplaceFieldPropsCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public FieldItem fieldItem = null;
        public FieldPropertiesItem fieldPropertiesItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfPropertyDefinitionStartLine { get; set; }
        public int indexOfRemainingCodeNextLine { get; set; }
        public List<string> lines = null;
        public IModelDesktopInterface modelDesktopInterface { get; set; }
    }

    public partial class FieldFactoryCpp_RuntimeTextTemplate : FieldFactoryCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfLastFieldDeclarationLine { get; set; }
        public int indexOfLastPropertyDeclarationLine { get; set; }
        public int indexOfReturnFieldLine { get; set; }
    }

    public partial class FieldIdsCpp_RuntimeTextTemplate : FieldIdsCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfIfdsNamespaceClosingBraceLine { get; set; }
    }

    public partial class FieldIdsHpp_RuntimeTextTemplate : FieldIdsHpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfIfdsNamespaceClosingBraceLine { get; set; }
    }

    public partial class FieldPropertiesHpp_RuntimeTextTemplate : FieldPropertiesHpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfIfdsNamespaceClosingBraceLine { get; set; }
    }

    public partial class FieldPropertiesCpp_RuntimeTextTemplate : FieldPropertiesCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public FieldPropertiesItem fieldPropertiesItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfLastPropertyDeclarationLine { get; set; }
        public int indexOfIfdsNamespaceClosingBraceLine { get; set; }
        public IModelDesktopInterface modelDesktopInterface { get; set; }
    }

    public partial class DeleteFieldFromFieldFactoryCpp_RuntimeTextTemplate : DeleteFieldFromFieldFactoryCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
    }

    public partial class DeleteFieldFromFieldIdsCpp_RuntimeTextTemplate : DeleteFieldFromFieldIdsCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
    }

    public partial class DeleteFieldFromFieldIdsHpp_RuntimeTextTemplate : DeleteFieldFromFieldIdsHpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
    }

    public partial class DeleteFieldFromFieldPropsHpp_RuntimeTextTemplate : DeleteFieldFromFieldPropsHpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public FieldItem fieldItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
    }

    public partial class DeleteFieldPropsCpp_RuntimeTextTemplate : DeleteFieldPropsCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public FieldItem fieldItem = null;
        public FieldPropertiesItem fieldPropertiesItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfPropertyDefinitionStartLine { get; set; }
        public int indexOfRemainingCodeNextLine { get; set; }
        public List<string> lines = null;
    }

    public partial class ReplaceSubstitutionsSetCpp_RuntimeTextTemplate : ReplaceSubstitutionsSetCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfArrayKeysLine { get; set; }
        public int indexOfArrayValuesLine { get; set; }
        public int indexOfSubstitutionSetLine { get; set; }
        public List<string> lines = null;
    }

    public partial class SubstitutionsH_RuntimeTextTemplate : SubstitutionsH_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public List<string> distinctLines = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfSubSetEmptyLine { get; set; }
        public int indexOfIfdsNamespaceCloseLine { get; set; }

        private void CreateDistinctLines()
        {
            distinctLines = lines.Distinct().ToList();
        }

        private bool IsSubstitutionSetChooserFunctionAlreadyPresent()
        {
            var foundLines = lines.Where(x => x.Contains(substitutionSetItem.SubstitutionSetChooserFunction)).ToList();

            if (foundLines.Count() > 0)
            {
                return true;
            }

            return false;
        }
    }

    public partial class SubstitutionsCpp_RuntimeTextTemplate : SubstitutionsCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfPreviousItemLastLine { get; set; }
    }

    public partial class AddNewChooserCpp_RuntimeTextTemplate : AddNewChooserCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfIfdsNamespaceCloseLine { get; set; }
    }

    public partial class ReplaceChooserCpp_RuntimeTextTemplate : ReplaceChooserCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public List<SubstitutionSetItem> substitutionSetItemList = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfReplaceStartLine { get; set; }
        public int indexOfReplaceEndLine { get; set; }
        public List<string> usedLanguagesInSetsChooser { get; set; }
        private List<string> linesRest = new List<string>();
        private int startIndexLinesRest = 0;

        public void SetUsedLanguagesInSetsChooser()
        {
            usedLanguagesInSetsChooser = substitutionSetItemList.GroupBy(x => x.Language).Select(x => x.First().Language).ToList();
        }

        public List<SubstitutionSetItem> GetSubstitutionSetsWithUniqueMarketsForGivenLanguage(string language)
        {
            List<SubstitutionSetItem> uniqueMarketsForLanguage = substitutionSetItemList.Where(x => x.Language == language && x.MarketId != null && x.MarketId != "")
                                                                                        .GroupBy(x => x.MarketId).Select(x => x.First()).ToList();

            return uniqueMarketsForLanguage;
        }

        public SubstitutionSetItem GetDefaultSubstitutionSetItemForGivenLanguage(string language)
        {
            SubstitutionSetItem defaultSubstitutionItem = null;

            var items = substitutionSetItemList.Where(x => x.Language == language && x.MarketId == "");

            if (items.Count() > 0)
            {
                defaultSubstitutionItem = items.ElementAt(0);
            }

            return defaultSubstitutionItem;
        }

        public List<SubstitutionSetItem> GetSubstitutionSetsWithUniqueClientsForGivenLanguageAndMarket(string language, string marketId)
        {
            List<SubstitutionSetItem> uniqueClients = new List<SubstitutionSetItem>();

            if (marketId != null && marketId != "")
            {
                uniqueClients = substitutionSetItemList.Where(x => x.Language == language && x.MarketId == marketId && x.ClientId != "").GroupBy(x => x.ClientId).Select(x => x.First()).ToList();
            }

            return uniqueClients;
        }

        public SubstitutionSetItem GetDefaultSubstitutionSetItemForGivenLanguageAndMarket(string language, string marketId)
        {
            SubstitutionSetItem defaultSubstitutionItem = null;

            var items = substitutionSetItemList.Where(x => x.Language == language && x.MarketId == marketId && x.ClientId == "");

            if (items.Count() > 0)
            {
                defaultSubstitutionItem = items.ElementAt(0);
            }

            return defaultSubstitutionItem;
        }

        private void FindRemainingLines()
        {
            linesRest = lines.Skip(indexOfReplaceEndLine).ToList();
            startIndexLinesRest = linesRest.Select((item, i) => new { Item = item, Index = i }).First(x => (x.Item.Contains("// Chooser function") || x.Item.StartsWith("}"))).Index;
        }
    }

    public partial class GenerateIfastMasksH_RuntimeTextTemplate : GenerateIfastMasksH_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<MaskItem> maskItemList = null;
    }

    public partial class GenerateIfastMasksCpp_RuntimeTextTemplate : GenerateIfastMasksCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<MaskItem> maskItemList = null;
        public Dictionary<string, string> uniqueIdToCountryLanguageDictionary = null;

        private string GetLanguageCountryForGivenId(string languageId)
        {
            string languageCountry = "";
            uniqueIdToCountryLanguageDictionary.TryGetValue(languageId, out languageCountry);

            return languageCountry;
        }
    }

    public partial class GenerateDeleteSubstitutionSetH_RuntimeTextTemplate : GenerateDeleteSubstitutionSetH_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
    }

    public partial class GenerateDeleteSubstitutionSetCpp_RuntimeTextTemplate : GenerateDeleteSubstitutionSetCpp_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public List<string> lines = null;
        public SubstitutionSetItem substitutionSetItem = null;
        public int indexOfIfdsNamespaceLine { get; set; }
        public int indexOfAkeysLine { get; set; }
        public int indexOfAkeysAvaluesLine { get; set; }
    }
}
           