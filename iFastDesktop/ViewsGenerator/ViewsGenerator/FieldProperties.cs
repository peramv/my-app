using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator
{
    class FieldPropertiesUI
    {
        ///////////////////////////////////////////////////////////////////////////////////////////
        // Field 
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Name of the filed.")]             // sample hint1
        [Category("Field")]                   // Category that I want
        [DisplayName("Field name")]       // I want to say more, than just DisplayInt
        public string FieldName { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Field Id.")]             // sample hint1
        [Category("Field")]                   // Category that I want
        [DisplayName("Field Id")]       // I want to say more, than just DisplayInt
        public string FieldId { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Field type.")]             // sample hint1
        [Category("Field")]                   // Category that I want
        [DisplayName("Field type")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(ExactFieldTypeValueConverter))]
        public string FieldType { get; set; }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // Field properties
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Field property name.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field property name")]       // I want to say more, than just DisplayInt
        public string FieldPropertyName { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Field property type.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field property type")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(BaseFieldTypeValueConverter))]
        public string FieldPropertyType { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Field length.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field length")]       // I want to say more, than just DisplayInt
        public int FieldLength { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Field minimum length.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field minimum length")]       // I want to say more, than just DisplayInt
        public int FieldMinimumLength { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Field decimals.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field decimals")]       // I want to say more, than just DisplayInt
        public decimal FieldDecimals { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Mask name.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Mask name")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(MaskFieldTypeValueConverter))]
        public string MaskName { get; set; }

        [Browsable(false)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Mask chooser function.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Mask chooser function")]       // I want to say more, than just DisplayInt
        public string MaskChooserFunction { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Default value function for string.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Default value function for string")]       // I want to say more, than just DisplayInt
        public string DefaultValueString { get; set; }

        //[Browsable(true)]                         // this property should be visible
        //[ReadOnly(false)]                          // but just read only
        //[Description("Integer default value.")]             // sample hint1
        //[Category("Field properties")]                   // Category that I want
        //[DisplayName("Integer default value")]       // I want to say more, than just DisplayInt
        //public int IntegerDefaultValue { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Default value function for integer. Not used in existing source code.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Default value function for integer")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(DefaultValueIntegerConverter))]
        public string DefaultValueInteger { get; set; }

        //[Browsable(true)]                         // this property should be visible
        //[ReadOnly(false)]                          // but just read only
        //[Description("Double default value.")]             // sample hint1
        //[Category("Field properties")]                   // Category that I want
        //[DisplayName("Double default value")]       // I want to say more, than just DisplayInt
        //public double DoubleDefaultValue { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Default value function for double.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Default value function for double")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(DefaultValueDoubleConverter))]
        public string DefaultValueDouble { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Field label function.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field label function")]       // I want to say more, than just DisplayInt
        public string FieldLabel { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Field name is deprecated.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Field name is deprecated")]       // I want to say more, than just DisplayInt
        public string FieldNameIsDeprecated { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Allow Nulls.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Allow Nulls")]       // I want to say more, than just DisplayInt
        public bool AllowNulls { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(true)]                          // but just read only
        [Description("Justification. In all field properties value is 'None'.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Justification")]       // I want to say more, than just DisplayInt
        public string Justification { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Substitution set.")]             // sample hint1
        [Category("Field properties")]                   // Category that I want
        [DisplayName("Substitution set")]       // I want to say more, than just DisplayInt
        [TypeConverter(typeof(SubstituitionSetTypeValueConverter))]
        public string SubstitutionSet { get; set; }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // String default value(s) 
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (enUS).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (enUS)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_enUS { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (enCA).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (enCA)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_enCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (frFR).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (frFR)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_frFR { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (frCA).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (frCA)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_frCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (enIE).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (enIE)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_enIE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (deDE).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (deDE)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_deDE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("String default value  (esEs).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - string default value(s)")]                   // Category that I want
        [DisplayName("String default value (esEs)")]       // I want to say more, than just DisplayInt
        public string StringDefaultValue_esEs { get; set; }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // Integer default value(s) 
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (enUS). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (enUS)")]       // I want to say more, than just DisplayInt
        [DefaultValueAttribute(false)]
        public string IntegerDefaultValue_enUS { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (enCA). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (enCA)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_enCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (frFR). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (frFR)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_frFR { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (frCA). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (frCA)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_frCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (enIE). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (enIE)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_enIE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (deDE). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (deDE)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_deDE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Integer default value  (esEs). Not used in existing source code.")]             // sample hint1
        [Category("Field properties - integer default value(s)")]                   // Category that I want
        [DisplayName("Integer default value (esEs)")]       // I want to say more, than just DisplayInt
        public string IntegerDefaultValue_esEs { get; set; }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // Double default value(s) 
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (enUS).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (enUS)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_enUS { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (enCA).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (enCA)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_enCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (frFR).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (frFR)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_frFR { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (frCA).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (frCA)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_frCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (enIE).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (enIE)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_enIE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (deDE).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (deDE)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_deDE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Double default value  (esEs).")]             // sample hint1
        [Category("Field properties - double default value(s)")]                   // Category that I want
        [DisplayName("Double default value (esEs)")]       // I want to say more, than just DisplayInt
        public string DoubleDefaultValue_esEs { get; set; }

        ///////////////////////////////////////////////////////////////////////////////////////////
        // Label default value(s) 
        ///////////////////////////////////////////////////////////////////////////////////////////

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (enUS).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (enUS)")]       // I want to say more, than just DisplayInt
        public string LabelValue_enUS { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (enCA).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (enCA)")]       // I want to say more, than just DisplayInt
        public string LabelValue_enCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (frFR).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (frFR)")]       // I want to say more, than just DisplayInt
        public string LabelValue_frFR { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (frCA).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (frCA)")]       // I want to say more, than just DisplayInt
        public string LabelValue_frCA { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (enIE).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (enIE)")]       // I want to say more, than just DisplayInt
        public string LabelValue_enIE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (deDE).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (deDE)")]       // I want to say more, than just DisplayInt
        public string LabelValue_deDE { get; set; }

        [Browsable(true)]                         // this property should be visible
        [ReadOnly(false)]                          // but just read only
        [Description("Label value (esEs).\nOnly non empty strings will be processed.")]             // sample hint1
        [Category("Field properties - label value(s)")]                   // Category that I want
        [DisplayName("Label value (esEs)")]       // I want to say more, than just DisplayInt
        public string LabelValue_esEs { get; set; }



        ///////////////////////////////////////////////////////////////////////////////////////////
        // Type converters
        ///////////////////////////////////////////////////////////////////////////////////////////
        public class DefaultValueIntegerConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        public class DefaultValueDoubleConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        public class ExactFieldTypeValueConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        public class BaseFieldTypeValueConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        public class MaskFieldTypeValueConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        public class SubstituitionSetTypeValueConverter : StringConverter
        {
            public static string[] value;

            public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
            {
                //true means show a combobox
                return true;
            }

            public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
            {
                //true will limit to list. false will show the list, but allow free-form entry
                return true;
            }

            public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
            {
                return new StandardValuesCollection(value);
            }
        }

        [Browsable(false)]
        public string[] AvailableDefaultValueIntegerValues
        {
            set { DefaultValueIntegerConverter.value = value; }
        }

        [Browsable(false)]
        public string[] AvailableDefaultValueDoubleValues
        {
            set { DefaultValueDoubleConverter.value = value; }
        }

        [Browsable(false)]
        public string[] AvailableExactFieldTypeValues
        {
            set { ExactFieldTypeValueConverter.value = value; }
        }

        [Browsable(false)]
        public string[] AvailableBaseFieldTypeValues
        {
            set { BaseFieldTypeValueConverter.value = value; }
        }

        [Browsable(false)]
        public string[] AvailableMaskFieldTypeValues
        {
            set { MaskFieldTypeValueConverter.value = value; }
        }

        [Browsable(false)]
        public string[] AvailableSubstituitionSetTypeValues
        {
            set { SubstituitionSetTypeValueConverter.value = value; }
        }
    }
}
