﻿// ------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version: 11.0.0.0
//  
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
// ------------------------------------------------------------------------------
namespace ViewsGenerator.Templates.Java
{
    using System.Linq;
    using System.Text;
    using System.Collections.Generic;
    using System;
    
    /// <summary>
    /// Class to produce the template output
    /// </summary>
    
    #line 1 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "11.0.0.0")]
    public partial class JavaClassResponseHtml_RuntimeTextTemplate : JavaClassResponseHtml_RuntimeTextTemplateBase
    {
#line hidden
        /// <summary>
        /// Create the template output
        /// </summary>
        public virtual string TransformText()
        {
            this.Write("<HTML>\r\n  <HEAD>\r\n    <TITLE>");
            
            #line 8 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(ViewName));
            
            #line default
            #line hidden
            this.Write(" - View </TITLE>\r\n  </HEAD>\r\n  <BODY>\r\n    <H1>");
            
            #line 11 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(ViewDescription));
            
            #line default
            #line hidden
            this.Write(" (");
            
            #line 11 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(ViewName));
            
            #line default
            #line hidden
            this.Write(@")</H1>
    <H2>Resp Type -- Error occured</H2>
    <TABLE BORDER=""1"">
    <TR>
      <TD><STRONG>Section ID</STRONG></TD>
      <TD><STRONG>Field ID</STRONG></TD>
      <TD><STRONG>Field Name</STRONG></TD>
      <TD><STRONG>Field Description</STRONG></TD>
      <TD><STRONG>Field Type</STRONG></TD>
    </TR>
");
            
            #line 21 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
	CreateLists();

	for (int i = 0; i < responseTypeErrorOccuredFieldItemList.Count(); i++)
	{ 
            
            #line default
            #line hidden
            this.Write("      <TR>\r\n        <TD>");
            
            #line 26 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeErrorOccuredFieldItemList[i].SectionId));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 27 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeErrorOccuredFieldItemList[i].FieldId));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 28 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeErrorOccuredFieldItemList[i].FieldName));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 29 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeErrorOccuredFieldItemList[i].FieldDescription));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 30 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(GetFieldType(responseTypeErrorOccuredFieldItemList[i].FieldName)));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n      </TR>\r\n");
            
            #line 32 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
  } 
            
            #line default
            #line hidden
            this.Write(@"    </TABLE>
    <P>* indicates the section is repeating.</P>
    <H2>Resp Type -- Data</H2>
    <TABLE BORDER=""1"">
    <TR>
      <TD><STRONG>Section ID</STRONG></TD>
      <TD><STRONG>Field ID</STRONG></TD>
      <TD><STRONG>Field Name</STRONG></TD>
      <TD><STRONG>Field Description</STRONG></TD>
      <TD><STRONG>Field Type</STRONG></TD>
    </TR>
");
            
            #line 44 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
 	for (int i = 0; i < responseTypeNonRepeatingDataFieldItemList.Count(); i++)
	{ 
            
            #line default
            #line hidden
            this.Write("      <TR>\r\n        <TD>");
            
            #line 47 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeNonRepeatingDataFieldItemList[i].SectionId));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 48 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeNonRepeatingDataFieldItemList[i].FieldId));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 49 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeNonRepeatingDataFieldItemList[i].FieldName));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 50 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeNonRepeatingDataFieldItemList[i].FieldDescription));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 51 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(GetFieldType(responseTypeNonRepeatingDataFieldItemList[i].FieldName)));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n      </TR>\r\n");
            
            #line 53 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
  } 
            
            #line default
            #line hidden
            
            #line 54 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
	for (int i = 0; i < responseTypeRepeatingDataFieldItemList.Count(); i++)
	{ 
            
            #line default
            #line hidden
            this.Write("      <TR>\r\n        <TD>");
            
            #line 57 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeRepeatingDataFieldItemList[i].SectionId));
            
            #line default
            #line hidden
            this.Write("*</TD>\r\n        <TD>");
            
            #line 58 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeRepeatingDataFieldItemList[i].FieldId));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 59 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeRepeatingDataFieldItemList[i].FieldName));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 60 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(responseTypeRepeatingDataFieldItemList[i].FieldDescription));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n        <TD>");
            
            #line 61 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
            this.Write(this.ToStringHelper.ToStringWithCulture(GetFieldType(responseTypeRepeatingDataFieldItemList[i].FieldName)));
            
            #line default
            #line hidden
            this.Write("</TD>\r\n      </TR>\r\n");
            
            #line 63 "E:\dev\views\ViewsGenerator\ViewsGenerator\Templates\Java\JavaClassResponseHtml_RuntimeTextTemplate.tt"
  } 
            
            #line default
            #line hidden
            this.Write("    </TABLE>\r\n    <P>* indicates the section is repeating.</P>\r\n");
            return this.GenerationEnvironment.ToString();
        }
    }
    
    #line default
    #line hidden
    #region Base class
    /// <summary>
    /// Base class for this transformation
    /// </summary>
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.TextTemplating", "11.0.0.0")]
    public class JavaClassResponseHtml_RuntimeTextTemplateBase
    {
        #region Fields
        private global::System.Text.StringBuilder generationEnvironmentField;
        private global::System.CodeDom.Compiler.CompilerErrorCollection errorsField;
        private global::System.Collections.Generic.List<int> indentLengthsField;
        private string currentIndentField = "";
        private bool endsWithNewline;
        private global::System.Collections.Generic.IDictionary<string, object> sessionField;
        #endregion
        #region Properties
        /// <summary>
        /// The string builder that generation-time code is using to assemble generated output
        /// </summary>
        protected System.Text.StringBuilder GenerationEnvironment
        {
            get
            {
                if ((this.generationEnvironmentField == null))
                {
                    this.generationEnvironmentField = new global::System.Text.StringBuilder();
                }
                return this.generationEnvironmentField;
            }
            set
            {
                this.generationEnvironmentField = value;
            }
        }
        /// <summary>
        /// The error collection for the generation process
        /// </summary>
        public System.CodeDom.Compiler.CompilerErrorCollection Errors
        {
            get
            {
                if ((this.errorsField == null))
                {
                    this.errorsField = new global::System.CodeDom.Compiler.CompilerErrorCollection();
                }
                return this.errorsField;
            }
        }
        /// <summary>
        /// A list of the lengths of each indent that was added with PushIndent
        /// </summary>
        private System.Collections.Generic.List<int> indentLengths
        {
            get
            {
                if ((this.indentLengthsField == null))
                {
                    this.indentLengthsField = new global::System.Collections.Generic.List<int>();
                }
                return this.indentLengthsField;
            }
        }
        /// <summary>
        /// Gets the current indent we use when adding lines to the output
        /// </summary>
        public string CurrentIndent
        {
            get
            {
                return this.currentIndentField;
            }
        }
        /// <summary>
        /// Current transformation session
        /// </summary>
        public virtual global::System.Collections.Generic.IDictionary<string, object> Session
        {
            get
            {
                return this.sessionField;
            }
            set
            {
                this.sessionField = value;
            }
        }
        #endregion
        #region Transform-time helpers
        /// <summary>
        /// Write text directly into the generated output
        /// </summary>
        public void Write(string textToAppend)
        {
            if (string.IsNullOrEmpty(textToAppend))
            {
                return;
            }
            // If we're starting off, or if the previous text ended with a newline,
            // we have to append the current indent first.
            if (((this.GenerationEnvironment.Length == 0) 
                        || this.endsWithNewline))
            {
                this.GenerationEnvironment.Append(this.currentIndentField);
                this.endsWithNewline = false;
            }
            // Check if the current text ends with a newline
            if (textToAppend.EndsWith(global::System.Environment.NewLine, global::System.StringComparison.CurrentCulture))
            {
                this.endsWithNewline = true;
            }
            // This is an optimization. If the current indent is "", then we don't have to do any
            // of the more complex stuff further down.
            if ((this.currentIndentField.Length == 0))
            {
                this.GenerationEnvironment.Append(textToAppend);
                return;
            }
            // Everywhere there is a newline in the text, add an indent after it
            textToAppend = textToAppend.Replace(global::System.Environment.NewLine, (global::System.Environment.NewLine + this.currentIndentField));
            // If the text ends with a newline, then we should strip off the indent added at the very end
            // because the appropriate indent will be added when the next time Write() is called
            if (this.endsWithNewline)
            {
                this.GenerationEnvironment.Append(textToAppend, 0, (textToAppend.Length - this.currentIndentField.Length));
            }
            else
            {
                this.GenerationEnvironment.Append(textToAppend);
            }
        }
        /// <summary>
        /// Write text directly into the generated output
        /// </summary>
        public void WriteLine(string textToAppend)
        {
            this.Write(textToAppend);
            this.GenerationEnvironment.AppendLine();
            this.endsWithNewline = true;
        }
        /// <summary>
        /// Write formatted text directly into the generated output
        /// </summary>
        public void Write(string format, params object[] args)
        {
            this.Write(string.Format(global::System.Globalization.CultureInfo.CurrentCulture, format, args));
        }
        /// <summary>
        /// Write formatted text directly into the generated output
        /// </summary>
        public void WriteLine(string format, params object[] args)
        {
            this.WriteLine(string.Format(global::System.Globalization.CultureInfo.CurrentCulture, format, args));
        }
        /// <summary>
        /// Raise an error
        /// </summary>
        public void Error(string message)
        {
            System.CodeDom.Compiler.CompilerError error = new global::System.CodeDom.Compiler.CompilerError();
            error.ErrorText = message;
            this.Errors.Add(error);
        }
        /// <summary>
        /// Raise a warning
        /// </summary>
        public void Warning(string message)
        {
            System.CodeDom.Compiler.CompilerError error = new global::System.CodeDom.Compiler.CompilerError();
            error.ErrorText = message;
            error.IsWarning = true;
            this.Errors.Add(error);
        }
        /// <summary>
        /// Increase the indent
        /// </summary>
        public void PushIndent(string indent)
        {
            if ((indent == null))
            {
                throw new global::System.ArgumentNullException("indent");
            }
            this.currentIndentField = (this.currentIndentField + indent);
            this.indentLengths.Add(indent.Length);
        }
        /// <summary>
        /// Remove the last indent that was added with PushIndent
        /// </summary>
        public string PopIndent()
        {
            string returnValue = "";
            if ((this.indentLengths.Count > 0))
            {
                int indentLength = this.indentLengths[(this.indentLengths.Count - 1)];
                this.indentLengths.RemoveAt((this.indentLengths.Count - 1));
                if ((indentLength > 0))
                {
                    returnValue = this.currentIndentField.Substring((this.currentIndentField.Length - indentLength));
                    this.currentIndentField = this.currentIndentField.Remove((this.currentIndentField.Length - indentLength));
                }
            }
            return returnValue;
        }
        /// <summary>
        /// Remove any indentation
        /// </summary>
        public void ClearIndent()
        {
            this.indentLengths.Clear();
            this.currentIndentField = "";
        }
        #endregion
        #region ToString Helpers
        /// <summary>
        /// Utility class to produce culture-oriented representation of an object as a string.
        /// </summary>
        public class ToStringInstanceHelper
        {
            private System.IFormatProvider formatProviderField  = global::System.Globalization.CultureInfo.InvariantCulture;
            /// <summary>
            /// Gets or sets format provider to be used by ToStringWithCulture method.
            /// </summary>
            public System.IFormatProvider FormatProvider
            {
                get
                {
                    return this.formatProviderField ;
                }
                set
                {
                    if ((value != null))
                    {
                        this.formatProviderField  = value;
                    }
                }
            }
            /// <summary>
            /// This is called from the compile/run appdomain to convert objects within an expression block to a string
            /// </summary>
            public string ToStringWithCulture(object objectToConvert)
            {
                if ((objectToConvert == null))
                {
                    throw new global::System.ArgumentNullException("objectToConvert");
                }
                System.Type t = objectToConvert.GetType();
                System.Reflection.MethodInfo method = t.GetMethod("ToString", new System.Type[] {
                            typeof(System.IFormatProvider)});
                if ((method == null))
                {
                    return objectToConvert.ToString();
                }
                else
                {
                    return ((string)(method.Invoke(objectToConvert, new object[] {
                                this.formatProviderField })));
                }
            }
        }
        private ToStringInstanceHelper toStringHelperField = new ToStringInstanceHelper();
        /// <summary>
        /// Helper to produce culture-oriented representation of an object as a string
        /// </summary>
        public ToStringInstanceHelper ToStringHelper
        {
            get
            {
                return this.toStringHelperField;
            }
        }
        #endregion
    }
    #endregion
}
