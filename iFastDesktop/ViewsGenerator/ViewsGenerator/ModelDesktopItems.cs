using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator
{
    public class FieldItem
    {
        public string FieldId { get; set; }
        public string FieldShortId { get; set; }
        public string FieldType { get; set; }
        public string FieldDerivedType { get; set; }
        public string FieldName { get; set; }
        public string FieldPropertiesName { get; set; }
        public int FieldLength { get; set; }
        public string FieldFactoryFileName { get; set; }
        public bool isNewField = false;
    }

    public class FieldItemLocationInfo
    {
        public int ViewId { get; set; }
        public int IndexOfFieldinView { get; set; }
        public string ProgressFieldFormat { get; set; }

        public FieldItemLocationInfo ()
        {
            ProgressFieldFormat = "";
        }
    }

    public class FieldPropertiesItem
    {
        public string FieldName { get; set; }
        public string FieldType { get; set; }
        public string FieldLength { get; set; }
        public string FieldMinimumLength { get; set; }
        public string FieldDecimals { get; set; }
        public string MaskChooserFunction { get; set; }
        public string FieldNameIsDeprecated { get; set; }
        public string AllowNulls { get; set; }
        public string Justification { get; set; }
        public string SubstitutionSetSuperChooser { get; set; }
        public string Chooser_ss_function { get; set; }
        public string FileName { get; set; }
        // default label strings
        public string LabelFunctionName { get; set; }
        public string Label_enUS { get; set; }
        public string Label_enCA { get; set; }
        public string Label_frFR { get; set; }
        public string Label_frCA { get; set; }
        public string Label_enIE { get; set; }
        public string Label_deDE { get; set; }
        public string Label_esEs { get; set; }
        // default values strings
        public string DefaultValueStringFunctionName { get; set; }
        public string DefaultValueString_enUS { get; set; }
        public string DefaultValueString_enCA { get; set; }
        public string DefaultValueString_frFR { get; set; }
        public string DefaultValueString_frCA { get; set; }
        public string DefaultValueString_enIE { get; set; }
        public string DefaultValueString_deDE { get; set; }
        public string DefaultValueString_esEs { get; set; }
        // default values integers
        public string DefaultValueIntegerFunctionName { get; set; }
        public string DefaultValueInteger_enUS { get; set; }
        public string DefaultValueInteger_enCA { get; set; }
        public string DefaultValueInteger_frFR { get; set; }
        public string DefaultValueInteger_frCA { get; set; }
        public string DefaultValueInteger_enIE { get; set; }
        public string DefaultValueInteger_deDE { get; set; }
        public string DefaultValueInteger_esEs { get; set; }
        // default values doubles
        public string DefaultValueDoubleFunctionName { get; set; }
        public string DefaultValueDouble_enUS { get; set; }
        public string DefaultValueDouble_enCA { get; set; }
        public string DefaultValueDouble_frFR { get; set; }
        public string DefaultValueDouble_frCA { get; set; }
        public string DefaultValueDouble_enIE { get; set; }
        public string DefaultValueDouble_deDE { get; set; }
        public string DefaultValueDouble_esEs { get; set; }
        // List of languageCountries
        public List<string> languageCountryIds = new List<string>();

        // call these directly from templates to see how many items to display
        public int GetNumberOfNonEmptyLabels()
        {
            int numberOfLabels = 0;

            if (Label_enUS != null && Label_enUS != "")
            {
                numberOfLabels++;
            }
            if (Label_enCA != null && Label_enCA != "")
            {
                numberOfLabels++;
            }
            if (Label_frFR != null && Label_frFR != "")
            {
                numberOfLabels++;
            }
            if (Label_frCA != null && Label_frCA != "")
            {
                numberOfLabels++;
            }
            if (Label_enIE != null && Label_enIE != "")
            {
                numberOfLabels++;
            }
            if (Label_deDE != null && Label_deDE != "")
            {
                numberOfLabels++;
            }
            if (Label_esEs != null && Label_esEs != "")
            {
                numberOfLabels++;
            }

            return numberOfLabels;
        }

        public void SetLabel(string value, string languageId)
        {
            if (languageId == "1")
            {
                Label_enUS = value;
            }
            else if (languageId == "3")
            {
                Label_enCA = value;
            }
            else if (languageId == "4")
            {
                Label_frFR = value;
            }
            else if (languageId == "5")
            {
                Label_frCA = value;
            }
            else if (languageId == "6")
            {
                Label_enIE = value;
            }
            else if (languageId == "7")
            {
                Label_deDE = value;
            }
            else if (languageId == "8")
            {
                Label_esEs = value;
            }

            languageCountryIds.Add(languageId);
        }

        public string GetLabel(string languageId)
        {
            string label = "";

            if (languageId == "1")
            {
                label = Label_enUS;
            }
            else if (languageId == "3")
            {
                label = Label_enCA;
            }
            else if (languageId == "4")
            {
                label = Label_frFR;
            }
            else if (languageId == "5")
            {
                label = Label_frCA;
            }
            else if (languageId == "6")
            {
                label = Label_enIE;
            }
            else if (languageId == "7")
            {
                label = Label_deDE;
            }
            else if (languageId == "8")
            {
                label = Label_esEs;
            }

            return label;
        }

        public void SetValueString(string value, string languageId)
        {
            if (languageId == "1")
            {
                DefaultValueString_enUS = value;
            }
            else if (languageId == "3")
            {
                DefaultValueString_enCA = value;
            }
            else if (languageId == "4")
            {
                DefaultValueString_frFR = value;
            }
            else if (languageId == "5")
            {
                DefaultValueString_frCA = value;
            }
            else if (languageId == "6")
            {
                DefaultValueString_enIE = value;
            }
            else if (languageId == "7")
            {
                DefaultValueString_deDE = value;
            }
            else if (languageId == "8")
            {
                DefaultValueString_esEs = value;
            }
        }

        public string GetValueString(string languageId)
        {
            string valueString = "";

            if (languageId == "1")
            {
                valueString = DefaultValueString_enUS;
            }
            else if (languageId == "3")
            {
                valueString = DefaultValueString_enCA;
            }
            else if (languageId == "4")
            {
                valueString = DefaultValueString_frFR;
            }
            else if (languageId == "5")
            {
                valueString = DefaultValueString_frCA;
            }
            else if (languageId == "6")
            {
                valueString = DefaultValueString_enIE;
            }
            else if (languageId == "7")
            {
                valueString = DefaultValueString_deDE;
            }
            else if (languageId == "8")
            {
                valueString = DefaultValueString_esEs;
            }

            return valueString;
        }

        public void SetValueIntegerBasedOnStringValues()
        {
            DefaultValueInteger_enUS = DefaultValueString_enUS;
            DefaultValueInteger_enCA = DefaultValueString_enCA;
            DefaultValueInteger_frFR = DefaultValueString_frFR;
            DefaultValueInteger_frCA = DefaultValueString_frCA;
            DefaultValueInteger_enIE = DefaultValueString_enIE;
            DefaultValueInteger_deDE = DefaultValueString_deDE;
            DefaultValueInteger_esEs = DefaultValueString_esEs;
        }

        public string GetValueInteger(string languageId)
        {
            string integerValueAsString = "";

            if (languageId == "1")
            {
                integerValueAsString = DefaultValueInteger_enUS;
            }
            else if (languageId == "3")
            {
                integerValueAsString = DefaultValueInteger_enCA;
            }
            else if (languageId == "4")
            {
                integerValueAsString = DefaultValueInteger_frFR;
            }
            else if (languageId == "5")
            {
                integerValueAsString = DefaultValueInteger_frCA;
            }
            else if (languageId == "6")
            {
                integerValueAsString = DefaultValueInteger_enIE;
            }
            else if (languageId == "7")
            {
                integerValueAsString = DefaultValueInteger_deDE;
            }
            else if (languageId == "8")
            {
                integerValueAsString = DefaultValueInteger_esEs;
            }

            return integerValueAsString;
        }

        public void SetValueDoubleBasedOnStringValues()
        {
            DefaultValueDouble_enUS = DefaultValueString_enUS;
            DefaultValueDouble_enCA = DefaultValueString_enCA;
            DefaultValueDouble_frFR = DefaultValueString_frFR;
            DefaultValueDouble_frCA = DefaultValueString_frCA;
            DefaultValueDouble_enIE = DefaultValueString_enIE;
            DefaultValueDouble_deDE = DefaultValueString_deDE;
            DefaultValueDouble_esEs = DefaultValueString_esEs;
        }

        public string GetValueDouble(string languageId)
        {
            string doubleValueAsString = "";

            if (languageId == "1")
            {
                doubleValueAsString = DefaultValueDouble_enUS;
            }
            else if (languageId == "3")
            {
                doubleValueAsString = DefaultValueDouble_enCA;
            }
            else if (languageId == "4")
            {
                doubleValueAsString = DefaultValueDouble_frFR;
            }
            else if (languageId == "5")
            {
                doubleValueAsString = DefaultValueDouble_frCA;
            }
            else if (languageId == "6")
            {
                doubleValueAsString = DefaultValueDouble_enIE;
            }
            else if (languageId == "7")
            {
                doubleValueAsString = DefaultValueDouble_deDE;
            }
            else if (languageId == "8")
            {
                doubleValueAsString = DefaultValueDouble_esEs;
            }

            return doubleValueAsString;
        }

        public string GetSubstitutionSetComment()
        {
            return SubstitutionSetSuperChooser == "NULL" ? "// no substitution set" : "// substitution set super chooser";
        }
    }

    public class MaskItem
    {
        public List<LanguageMaskItem> languageMaskItemList = new List<LanguageMaskItem>();

        public string GroupId { get; set; }
        public string MaskId { get; set; }
        public string MaskName { get; set; }
        public string MaskChooser { get; set; }
    }

    public class LanguageMaskItem
    {
        public string LanguageId { get; set; }
        public string Mask { get; set; }
    }

    public class SubstitutionSetItem
    {
        public ArrayList KeysArray = new ArrayList();
        public ArrayList ValuesArray = new ArrayList();

        public string FileName { get; set; }
        public string Name { get; set; }
        public string Group { get; set; }
        public string Language { get; set; }
        public string MarketId { get; set; }
        public string MarketName { get; set; }
        public string ClientId { get; set; }
        public string ClientName { get; set; }
        public string KeysName { get; set; }
        public string ValuesName { get; set; }
        public string SubstitutionSetShortId { get; set; }
        public string SubstitutionSetId { get; set; }
        public string SubstitutionSetCreationIndex { get; set; }
        public int SubstitutionSetCreationIndexInt { get; set; }
        public string SubstitutionSetChooserFunction { get; set; }
        public bool isNewSubstitutionSet = false;
    }

    public class MarketItem
    {
        public List<ClientItem> clientInMarketItemList = new List<ClientItem>();

        public string MarketId { get; set; }
        public string MarketName { get; set; }
    }

    public struct ClientItem
    {
        public string ClientId { get; set; }
        public string ClientName { get; set; }
    }
}
