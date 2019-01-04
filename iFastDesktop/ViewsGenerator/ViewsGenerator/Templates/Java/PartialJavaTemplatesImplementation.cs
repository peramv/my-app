using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace ViewsGenerator.Templates.Java
{
    public partial class GenerateJavaRequestClass_RuntimeTextTemplate : GenerateJavaRequestClass_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string JavaClassName { get; set; }
        public string JavaFileName { get; set; }
        public string ViewId { get; set; }
        public List<TransactionItem> transactionItemList = null;
        private List<TransactionItem> filteredTransactionItemList = null;
        private List<TransactionItem> singleRecordTransactionItemList = new List<TransactionItem>();
        private List<TransactionItem> multipleRecordTransactionItemList = new List<TransactionItem>();
        private List<TransactionItem> filteredSingleRecordTransactionItemList = new List<TransactionItem>();
        private List<TransactionItem> filteredMultipleRecordTransactionItemList = new List<TransactionItem>();

        private bool IsReqRepeatCountFieldPresent()
        {
            string repeatCountField = "ReqRepeatCount";

            bool isPresent = transactionItemList.Any(s => s.TransactionVariableName.Equals(repeatCountField));

            return isPresent;
        }

        private bool IsMultipleRecordTransactionItem(string variableName)
        {
            bool isPresent = multipleRecordTransactionItemList.Any(s => s.TransactionVariableName.Equals(variableName));

            return isPresent;
        }

        private void CreateFilteredTransactionsItemList()
        {
            List<string> transactionItemsToFileterOut = new List<string>()
            {
                "NextKey",
                "Track",
                "Activity",
                "OverrideRepeats",
                "MaxReqRepeatCount"
            };

            filteredTransactionItemList = transactionItemList.Where(x => !transactionItemsToFileterOut.Contains(x.TransactionVariableName)).ToList() ?? new List<TransactionItem>();
        }

        private void CreateSingleAndMultipleRecordResponseItemLists()
        {
            // Get all fields before ReqRepeatCount field
            singleRecordTransactionItemList = transactionItemList.TakeWhile(x => !x.TransactionVariableName.Equals("ReqRepeatCount")).ToList();

            int indexRepeatCountField = transactionItemList.FindIndex(x => x.TransactionVariableName.Equals("ReqRepeatCount"));

            // Get all fields after RepeatCount field
            if (indexRepeatCountField != -1)
            {
                multipleRecordTransactionItemList = transactionItemList.Skip(indexRepeatCountField + 1).ToList();
            }
        }

        private void CreateFilteredSingleAndMultipleRecordResponseItemLists()
        {
            // Get all fields before ReqRepeatCount field
            filteredSingleRecordTransactionItemList = filteredTransactionItemList.TakeWhile(x => !x.TransactionVariableName.Equals("ReqRepeatCount")).ToList();

            int indexRepeatCountField = filteredTransactionItemList.FindIndex(x => x.TransactionVariableName.Equals("ReqRepeatCount"));

            // Get all fields after RepeatCount field
            if (indexRepeatCountField != -1)
            {
                filteredMultipleRecordTransactionItemList = filteredTransactionItemList.Skip(indexRepeatCountField + 1).ToList();
            }
        }

        private string GetEncodedStringLine(string variableName, bool isMultipleRecord)
        {
            string encodedVariableNameLine = "";

            if (variableName.Equals("LanguageCode"))
            {
                encodedVariableNameLine = "encodeLanguageCodeField( _LanguageCode, requestBuffer )";
                return encodedVariableNameLine;
            }

            List<string> transactionItemsToFileterOut = new List<string>()
            {
                "NextKey",
                "Track",
                "Activity",
                "OverrideRepeats"
            };

            bool match = transactionItemsToFileterOut.Any(s => s.Equals(variableName));

            if (match)
            {
                encodedVariableNameLine = "encode" + variableName + "Field( requestBuffer )";
            }
            else
            {
                if (isMultipleRecord)
                {
                    encodedVariableNameLine = "requestBuffer.appendField( _" + variableName + "[x]" + " )";
                }
                else
                {
                    encodedVariableNameLine = "requestBuffer.appendField( _" + variableName + " )";
                }
            }

            return encodedVariableNameLine;
        }

        private string GetMemberVariableComment(string variableName)
        {
            string memberVariableCommentLine = "";

            if (variableName.Equals("RecordType"))
            {
                memberVariableCommentLine = "Field indicating if vew returns pending, processed or both trades. Member variable.";
            }
            else
            {
                variableName = variableName.Replace("_", "");
                variableName = string.Join(" ", Regex.Split(variableName, @"([A-Z][a-z]*)")).Trim();
                variableName = variableName.Replace("  ", " ");
                memberVariableCommentLine = variableName + " member variable.";
            }

            return memberVariableCommentLine;
        }

        private string GetFieldType(string fieldName)
        {
            string transactionFieldType = "String";

            TransactionItem transactionItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(fieldName));

            if (transactionItem != null)
            {
                transactionFieldType = transactionItem.GetVariableType();
            }

            if (fieldName.Equals("ReqRepeatCount"))
            {
                transactionFieldType = "int";
            }

            return transactionFieldType;
        }

        private string GetFieldDefaultValue(string fieldName)
        {
            string transactionFieldDefaultValue = "\"\"";

            TransactionItem transactionItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(fieldName));

            if (transactionItem != null)
            {
                string transactionFieldType = transactionItem.GetVariableType();
                string transactionDeclarationType = transactionItem.TransactionVariableTypeDeclaration;

                if (transactionFieldType.Equals("String"))
                {
                    if (transactionDeclarationType.Contains("decimal"))
                    {
                        transactionFieldDefaultValue = "\"0\"";
                    }
                    else
                    {
                        transactionFieldDefaultValue = "\"\"";
                    }
                }
                else if (transactionFieldType.Equals("Integer"))
                {
                    transactionFieldDefaultValue = "null";
                }
                else if (transactionFieldType.Equals("Date"))
                {
                    transactionFieldDefaultValue = "null";
                }
                else if (transactionFieldType.Equals("Boolean"))
                {
                    transactionFieldDefaultValue = "new Boolean(false)";
                }
            }

            return transactionFieldDefaultValue;
        }

        private string GetArrayIndexBlock(string variableName)
        {
            string arrayIndexBlock = "";

            if (IsMultipleRecordTransactionItem(variableName))
            {
                arrayIndexBlock = "[index]";
            }

            return arrayIndexBlock;
        }

        private string GetArrayIndexInputParameter(string variableName)
        {
            string arrayIndexInputParameter = "";

            if (IsMultipleRecordTransactionItem(variableName))
            {
                arrayIndexInputParameter = "int index, ";
            }

            return arrayIndexInputParameter;
        }

        private string GetNumberOfRepeats(string variableName)
        {
            string numberOfRepeats = "0";

            if (IsMultipleRecordTransactionItem(variableName))
            {
                TransactionItem transactionItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(variableName));
                string declaration = transactionItem.TransactionVariableTypeDeclaration;

                numberOfRepeats = Regex.Match(declaration, @"\d+").Value; 
            }

            return numberOfRepeats;
        }
    }

    public partial class GenerateJavaViewClass_RuntimeTextTemplate : GenerateJavaViewClass_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string JavaClassName { get; set; }
        public string JavaFileName { get; set; }
        public string ViewId { get; set; }
        public List<ResponseItem> responseItemList = null;
        public List<ResponseFieldTableItem> responseFieldItemList = null;
        public List<ResponseFieldTableItem> filteredResponseFieldItemList = null;
        public List<ResponseFieldTableItem> filteredSingleRecordResponseFieldItemList = null;
        public List<ResponseFieldTableItem> filteredMultipleRecordResponseFieldItemList = new List<ResponseFieldTableItem>();

        private bool IsRepeatCountFieldPresent()
        {
            string repeatCountField = "RepeatCount";

            bool isPresent = responseItemList.Any(s => s.ResponseVariableName.Equals(repeatCountField));

            return isPresent;
        }

        private bool IsMoreAvailableFieldPresent()
        {
            string moreAvailableField = "MoreAvailable";

            bool isPresent = responseItemList.Any(s => s.ResponseVariableName.Equals(moreAvailableField));

            return isPresent;
        }

        private void CreateFilteredResponseItemList()
        {
            List<string> responseFieldItemsToFileterOut = new List<string>()
            {
                "ErrorCode",
                "ErrorDesc",
                "MoreAvailable",
                "MaxRepeatCount",
                "NextKey"
            };

            filteredResponseFieldItemList = responseFieldItemList.Where(x => !responseFieldItemsToFileterOut.Contains(x.FieldName)).ToList() ?? new List<ResponseFieldTableItem>();
        }

        private void CreateFilteredSingleAndMultipleRecordResponseItemLists()
        {
            // Get all fields before RepeatCount field
            filteredSingleRecordResponseFieldItemList = filteredResponseFieldItemList.TakeWhile(x => !x.FieldName.Equals("RepeatCount")).ToList();

            int indexRepeatCountField = filteredResponseFieldItemList.FindIndex(x => x.FieldName.Equals("RepeatCount"));

            // Get all fields after RepeatCount field
            if (indexRepeatCountField != -1)
            {
                filteredMultipleRecordResponseFieldItemList = filteredResponseFieldItemList.Skip(indexRepeatCountField + 1).ToList();
            }
        }

        private string GetFieldType(string fieldName)
        {
            string fieldType = "String";

            ResponseItem responseItem = responseItemList.Find(x => x.ResponseVariableName.Equals(fieldName));

            if (responseItem != null)
            {
                fieldType = responseItem.GetVariableType();
            }

            return fieldType;
        }

        private string GetFieldPrimitiveType(string fieldName)
        {
            string fieldType = "String";

            ResponseItem responseItem = responseItemList.Find(x => x.ResponseVariableName.Equals(fieldName));

            if (responseItem != null)
            {
                fieldType = responseItem.GetVariableType();

                if (fieldType.Equals("Boolean"))
                {
                    fieldType = "boolean";
                }
                else if (fieldType.Equals("Integer"))
                {
                    fieldType = "int";
                }
            }

            return fieldType;
        }

        private string GetFieldValueFunctionForFieldsWithPrimitiveType(string fieldName)
        {
            string fieldValueFunction = "";

            string fieldType = GetFieldPrimitiveType(fieldName);

            if (fieldType.Equals("boolean"))
            {
                fieldValueFunction = ".booleanValue()";
            }
            else if (fieldType.Equals("int"))
            {
                fieldValueFunction = ".intValue()";
            }

            return fieldValueFunction;
        }
    }

    public partial class JavaClassResponseHtml_RuntimeTextTemplate : JavaClassResponseHtml_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string ViewId { get; set; }
        public string ViewDescription { get; set; }
        public List<ResponseItem> responseItemList = null;
        public List<ResponseFieldTableItem> responseFieldItemList = null;
        public List<ResponseFieldTableItem> responseTypeErrorOccuredFieldItemList = null;
        public List<ResponseFieldTableItem> responseTypeNonRepeatingDataFieldItemList = null;
        public List<ResponseFieldTableItem> responseTypeRepeatingDataFieldItemList = null;

        private void CreateLists()
        {
            CreateResponseTypeErrorOccuredList();

            var responseFieldTableItems = responseFieldItemList.Where(p => p.ResponseType.Equals("2") && p.SectionId != "").GroupBy(p => p.SectionId).Select(s => s.First()).ToList();

            if (responseFieldTableItems.Count == 2)
            {
                CreateResponseTypeNonRepeatingDataList(responseFieldTableItems[0].SectionId);
                CreateResponseTypeRepeatingDataList(responseFieldTableItems[1].SectionId);
            }
            else if (responseFieldTableItems.Count == 1)
            {
                int indexRepeatCountField = responseFieldItemList.FindIndex(x => x.FieldName.Equals("RepeatCount"));

                if (indexRepeatCountField == -1)
                {
                    CreateResponseTypeNonRepeatingDataList(responseFieldTableItems[0].SectionId);
                    responseTypeRepeatingDataFieldItemList = new List<ResponseFieldTableItem>();
                }
                else
                {
                    responseTypeNonRepeatingDataFieldItemList = new List<ResponseFieldTableItem>();
                    CreateResponseTypeRepeatingDataList(responseFieldTableItems[0].SectionId);
                }
            }
            else
            {
                responseTypeNonRepeatingDataFieldItemList = new List<ResponseFieldTableItem>();
                responseTypeRepeatingDataFieldItemList = new List<ResponseFieldTableItem>();
            }
        }

        private void CreateResponseTypeErrorOccuredList()
        {
            responseTypeErrorOccuredFieldItemList = responseFieldItemList.TakeWhile(x => x.ResponseType.Equals("1")).ToList();
        }

        private void CreateResponseTypeNonRepeatingDataList(string sectionId)
        {
            responseTypeNonRepeatingDataFieldItemList = responseFieldItemList.Where(x => x.SectionId.Equals(sectionId)).ToList();
        }

        private void CreateResponseTypeRepeatingDataList(string sectionId)
        {
            responseTypeRepeatingDataFieldItemList = responseFieldItemList.Where(x => x.SectionId.Equals(sectionId)).ToList();
        }

        private string GetFieldType(string fieldName)
        {
            string responseFieldType = "String";

            ResponseItem responseItem = responseItemList.Find(x => x.ResponseVariableName.Equals(fieldName));

            if (responseItem != null)
            {
                responseFieldType = responseItem.GetVariableType();
            }

            return responseFieldType;
        }
    }

    public partial class JavaClassRequestHtml_RuntimeTextTemplate : JavaClassRequestHtml_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string ViewId { get; set; }
        public string ViewDescription { get; set; }
        public List<TransactionItem> transactionItemList = null;
        public List<TransactionFieldTableItem> transactionFieldItemList = null;

        private string GetFieldType(string fieldName)
        {
            string transactionFieldType = "String";

            TransactionItem transactionItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(fieldName));

            if (transactionItem != null)
            {
                transactionFieldType = transactionItem.GetVariableType();
            }

            return transactionFieldType;
        }
    }

    public partial class GenerateJavaHtmlTest_RuntimeTextTemplate : GenerateJavaHtmlTest_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string ViewId { get; set; }
        public string ViewDescription { get; set; }
        public List<TransactionItem> transactionItemList = null;
        private List<TransactionItem> filteredTransactionItemList = null;
        public List<TransactionFieldTableItem> transactionFieldItemList = null;

        private void CreateFilteredTransactionsItemList()
        {
            List<string> transactionItemsToFileterOut = new List<string>()
            {
                "NextKey",
                "Track",
                "Activity",
                "OverrideRepeats"
            };

            filteredTransactionItemList = transactionItemList.Where(x => !transactionItemsToFileterOut.Contains(x.TransactionVariableName)).ToList() ?? new List<TransactionItem>();
        }

        private string GetFieldType(string fieldName)
        {
            string transactionFieldType = "String";

            TransactionItem transactionItem = transactionItemList.Find(x => x.TransactionVariableName.Equals(fieldName));

            if (transactionItem != null)
            {
                transactionFieldType = transactionItem.GetVariableType();
            }

            if (transactionFieldType.Equals("Boolean"))
            {
                transactionFieldType = "Boolean (true/false)";
            }
            else if (transactionFieldType.Equals("Date"))
            {
                transactionFieldType = "Date (dd/mm/yy)";
            }

            return transactionFieldType;
        }
    }

    public partial class GenerateJavaJspTest_RuntimeTextTemplate : GenerateJavaJspTest_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewName { get; set; }
        public string ViewId { get; set; }
        public string ViewDescription { get; set; }
        public List<TransactionItem> transactionItemList = null;
        private List<TransactionItem> filteredTransactionItemList = null;
        public List<TransactionFieldTableItem> transactionFieldItemList = null;
        public List<ResponseFieldTableItem> filteredResponseFieldItemList = null;
        public List<ResponseFieldTableItem> responseFieldItemList = null;
        public List<ResponseItem> characterAndLogicalResponseItemList = null;
        public List<ResponseFieldTableItem> characterAndLogicalResponseFieldItemList = null;

        private void CreateFilteredTransactionsItemList()
        {
            List<string> transactionItemsToFileterOut = new List<string>()
            {
                "NextKey",
                "Track",
                "Activity",
                "OverrideRepeats"
            };

            filteredTransactionItemList = transactionItemList.Where(x => !transactionItemsToFileterOut.Contains(x.TransactionVariableName)).ToList() ?? new List<TransactionItem>();
        }

        private void CreateFilteredResponseItemList()
        {
            List<string> responseFieldItemsToFileterOut = new List<string>()
            {
                "ErrorCode",
                "ErrorDesc",
                "MoreAvailable",
                "MaxRepeatCount",
                "NextKey",
                "RepeatCount"
            };

            filteredResponseFieldItemList = responseFieldItemList.Where(x => !responseFieldItemsToFileterOut.Contains(x.FieldName)).ToList() ?? new List<ResponseFieldTableItem>();
        }

        private void CreateCharacterAndLogicalFieldList()
        {
            List<string> names = characterAndLogicalResponseItemList.Select(x => x.ResponseVariableName).Distinct().ToList();

            characterAndLogicalResponseFieldItemList = filteredResponseFieldItemList.Where(x => names.Contains(x.FieldName)).ToList() ?? new List<ResponseFieldTableItem>();

            if (IsRepeatCountFieldPresent())
            {
                string repeatCountField = "RepeatCount";

                // Find sectionId of RepeatCOunt field
                string sectionId = responseFieldItemList.Find(s => s.FieldName.Equals(repeatCountField)).SectionId;

                characterAndLogicalResponseFieldItemList.RemoveAll(x => x.SectionId == sectionId);
            }
        }

        private bool IsRepeatCountFieldPresent()
        {
            string repeatCountField = "RepeatCount";

            bool isPresent = responseFieldItemList.Any(s => s.FieldName.Equals(repeatCountField));

            return isPresent;
        }
    }
}
