using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewsGenerator
{
    public class ViewDataSetItem
    {
        public int ViewId { get; set; }
        public string ViewName { get; set; }
        public string ViewDescription { get; set; }
        public string ViewDataFileName { get; set; }
        public string ViewFileType { get; set; }
    }

    public class TransactionResponseItemBase
    {
        public string ViewId { get; set; }
        public string VariableDescription { get; set; }
        public string Format { get; set; }
        public string Scope { get; set; }
        public bool isNewField { get; set; }

        public TransactionResponseItemBase()
        {
            isNewField = false;
        }

        protected string GetVariableType(string variableTypeDeclaration)
        {
            string variableType = "";

            if (variableTypeDeclaration.Contains("character"))
            {
                variableType = "String";
            }
            else if (variableTypeDeclaration.Contains("integer"))
            {
                variableType = "Integer";
            }
            else if (variableTypeDeclaration.Contains("date"))
            {
                variableType = "Date";
            }
            else if (variableTypeDeclaration.Contains("decimal"))
            {
                variableType = "String";
            }
            else if (variableTypeDeclaration.Contains("logical"))
            {
                variableType = "Boolean";
            }
            else if (variableTypeDeclaration.Contains("recid"))
            {
                variableType = "Integer";
            }

            return variableType;
        }
    }

    // Generated from Java source code
    public class ResponseItem : TransactionResponseItemBase
    {
        public string ResponseType { get; set; }
        public string ResponseVariableName { get; set; }
        public string ResponseVariableTypeDeclaration { get; set; }

        public string GetVariableType()
        {
            string variableType = GetVariableType(ResponseVariableTypeDeclaration);
            return variableType;
        }
    }

    // Generated from Java source code
    public class TransactionItem : TransactionResponseItemBase
    {
        public string TransactionVariableName { get; set; }
        public string TransactionVariableTypeDeclaration { get; set; }

        public string GetVariableType()
        {
            string variableType = GetVariableType(TransactionVariableTypeDeclaration);
            return variableType;
        }
    }

    // Generated from ViewMap.txt
    public class ViewMapItem
    {
        public string ViewId { get; set; }
        public string ViewName { get; set; }
        public string ViewDescription { get; set; }
        public bool isNewView { get; set; }
        public bool isValid { get; set; }
    }

    // Generated from RespFieldTable.csv
    public class ResponseFieldTableItem
    {
        public string ViewId { get; set; }
        public string ResponseType { get; set; }
        public string SectionId { get; set; }
        public string FieldId { get; set; }
        public string FieldName { get; set; }
        public string FieldDescription { get; set; }
    }

    // Generated from TransFieldTable.csv
    public class TransactionFieldTableItem
    {
        public string ViewId { get; set; }
        public string SectionId { get; set; }
        public string FieldId { get; set; }
        public string FieldName { get; set; }
        public string FieldDescription { get; set; }
    }

    public enum ResultCodeEnum
    {
        ResultIsOK = 0,
        FolderPathIsNotDefined = 1,
        FolderDoesntExist = 2,
        ItemIsUsedInFiles = 3
    }

    public class FileAndLineHelper
    {
        public string File { get; set; }
        public string Line { get; set; }
    }
}
