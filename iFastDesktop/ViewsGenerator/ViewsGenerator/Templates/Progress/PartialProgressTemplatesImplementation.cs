using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator.Templates.Progress
{
    public partial class TransactionViewDefinitions_RuntimeTextTemplate : TransactionViewDefinitions_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
        public List<TransactionItem> transactionItemList = null;
    }

    public partial class ResponseViewDefinitions_RuntimeTextTemplate : ResponseViewDefinitions_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
        public List<ResponseItem> responseType1ItemList = null;
        public List<ResponseItem> responseType2ItemList = null;
    }

    public partial class BusinessLogicForTransaction_RuntimeTextTemplate : BusinessLogicForTransaction_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
    }

    public partial class ViewAPIHandler_RuntimeTextTemplate : ViewAPIHandler_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
        public List<string> lines = null;
        public int indexOfHistoryCommentLastLine { get; set; }
        public int indexOfEndCaseLine { get; set; }
        public string smartViewFileName { get; set; }
    }

    public partial class ViewNASUHandler_RuntimeTextTemplate : ViewNASUHandler_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
        public List<string> lines = null;
        public int indexOfHistoryCommentLastLine { get; set; }
        public int indexOfEndCaseLine { get; set; }
        public string smartViewFileName { get; set; }
    }

    public partial class SmartViewServicingRoutine_RuntimeTextTemplate : SmartViewServicingRoutine_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewId { get; set; }
        public List<string> lines = null;
        public int indexOfHistoryCommentLastLine { get; set; }
        public int indexOfFirstDefineInputLine { get; set; }
        public string smartViewFileName { get; set; }
        public List<TransactionItem> transactionItemList = null;
        public List<ResponseItem> responseItemList = null;
        private List<ResponseItem> filteredResponseItemList = new List<ResponseItem>();
        private List<ResponseItem> filteredRepeatsResponseItemList = new List<ResponseItem>();

        private string GetTransactionTypeShortForm(string variableType)
        {
            string transactionTypeShortForm = "Str";

            if (variableType.Contains("logical"))
            {
                transactionTypeShortForm = "Log";
            }
            else if (variableType.Contains("decimal"))
            {
                transactionTypeShortForm = "Dec";
            }
            else if (variableType.Contains("date"))
            {
                transactionTypeShortForm = "Date";
            }
            else if (variableType.Contains("integer"))
            {
                transactionTypeShortForm = "Int";
            }
            else if (variableType.Contains("recid"))
            {
                transactionTypeShortForm = "Rid";
            }

            return transactionTypeShortForm;
        }

        private string GetResponseTypeShortForm(string variableType)
        {
            string responseTypeShortForm = "String";

            if (variableType.Contains("logical"))
            {
                responseTypeShortForm = "Log";
            }
            else if (variableType.Contains("decimal"))
            {
                responseTypeShortForm = "Dec";
            }
            else if (variableType.Contains("date"))
            {
                responseTypeShortForm = "Date";
            }
            else if (variableType.Contains("integer"))
            {
                responseTypeShortForm = "Int";
            }
            else if (variableType.Contains("recid"))
            {
                responseTypeShortForm = "Rid";
            }

            return responseTypeShortForm;
        }

        private bool IsResponseItemUpdateStatusPresent()
        {
            var responseItemMoreAvailable = responseItemList.Where(x => x.ResponseVariableName == "UpdateStatus");

            if (responseItemMoreAvailable.Count() > 0)
            {
                return true;
            }

            return false;
        }

        private bool IsResponseItemMoreAvailablePresent()
        {
            var responseItemMoreAvailable = responseItemList.Where(x => x.ResponseVariableName == "MoreAvailable");

            if (responseItemMoreAvailable.Count() > 0)
            {
                return true;
            }

            return false;
        }

        private bool IsResponseItemRepeatCountPresent()
        {
            var responseItemRepeatCount = responseItemList.Where(x => x.ResponseVariableName == "RepeatCount");

            if (responseItemRepeatCount.Count() > 0)
            {
                return true;
            }

            return false;
        }

        private bool IsTransactionItemRepeatCountPresent()
        {
            var transactionItemRepeatCount = transactionItemList.Where(x => x.TransactionVariableName == "RepeatCount");

            if (transactionItemRepeatCount.Count() > 0)
            {
                return true;
            }

            return false;
        }

        private int GetTransactionRepeatCountItemIndex()
        {
            int index = transactionItemList.FindIndex(x => x.TransactionVariableName == "RepeatCount");

            return index;
        }

        private void SplitResponseItemListIfThereAreRepeats()
        {
            if (IsResponseItemRepeatCountPresent())
            {
                filteredResponseItemList = responseItemList.TakeWhile(x => x.ResponseVariableName != "RepeatCount").ToList();
                filteredRepeatsResponseItemList = responseItemList.SkipWhile(x => x.ResponseVariableName != "RepeatCount").ToList();
            }
            else
            {
                filteredResponseItemList = responseItemList;
            }
        }

        private void CreateFilteredResponseItemList()
        {
            List<string> responseItemsToFileterOut = new List<string>()
            {
                "ErrorCode",
                "ErrorDesc",
                "MoreAvailable",
                "RepeatCount",
                "MaxRepeatCount"
            };

            filteredResponseItemList = filteredResponseItemList.Where(x => !responseItemsToFileterOut.Contains(x.ResponseVariableName)).ToList();
            filteredRepeatsResponseItemList = filteredRepeatsResponseItemList.Where(x => !responseItemsToFileterOut.Contains(x.ResponseVariableName)).ToList();
        }
    }

    public partial class ResponseProgressFilesWithDescription_RuntimeTextTemplate : ResponseProgressFilesWithDescription_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewDescription { get; set; }
        public string ViewId { get; set; }
        public List<ResponseItem> responseType1ItemList = null;
        public List<ResponseItem> responseType2ItemList = null;
        public List<ResponseFieldTableItem> responseFieldTableItemsForView = null;

        private string GetSectionIdForVariable(string variableName)
        {
            string sectionId = "";

            bool exists = responseFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                sectionId = responseFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).SectionId ?? "";
            }

            return sectionId;
        }

        private string GetFieldIdForVariable(string variableName)
        {
            string fieldId = "";

            bool exists = responseFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                fieldId = responseFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).FieldId ?? "";
            }

            return fieldId;
        }

        private string GetFieldDescriptionForVariable(string variableName)
        {
            string fieldDescription = "";

            bool exists = responseFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                fieldDescription = responseFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).FieldDescription ?? "";
            }

            return fieldDescription;
        }
    }

    public partial class TransactionProgressFilesWithDescription_RuntimeTextTemplate : TransactionProgressFilesWithDescription_RuntimeTextTemplateBase
    {
        public string strDataTimeFormat = "dddd, MMMM dd, yyyy HH:mm:ss";
        public string ViewItemName { get; set; }
        public string ViewFileName { get; set; }
        public string ViewDescription { get; set; }
        public string ViewId { get; set; }
        public List<TransactionItem> transactionItemList = null;
        public List<TransactionFieldTableItem> transactionFieldTableItemsForView = null;

        private string GetSectionIdForVariable(string variableName)
        {
            string sectionId = "";

            bool exists = transactionFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                sectionId = transactionFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).SectionId ?? "";
            }

            return sectionId;
        }

        private string GetFieldIdForVariable(string variableName)
        {
            string fieldId = "";

            bool exists = transactionFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                fieldId = transactionFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).FieldId ?? "";
            }

            return fieldId;
        }

        private string GetFieldDescriptionForVariable(string variableName)
        {
            string fieldDescription = "";

            bool exists = transactionFieldTableItemsForView.Any(x => x.FieldName.Equals(variableName));

            if (exists)
            {
                fieldDescription = transactionFieldTableItemsForView.Find(x => x.FieldName.Equals(variableName)).FieldDescription ?? "";
            }

            return fieldDescription;
        }
    }
}
