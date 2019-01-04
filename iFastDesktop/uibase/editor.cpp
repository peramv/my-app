// Machine generated IDispatch wrapper class(es) created with ClassWizard

#define WIN32UIBASE_DLL

#include "stdafx.h"
#include "editor.h"

namespace CND
{
}
#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IEditor properties

BOOL IEditor::GetIsDirty()
{
   BOOL result;
   GetProperty(0x1, VT_BOOL, (void*)&result);
   return(result);
}

void IEditor::SetIsDirty(BOOL propVal)
{
   SetProperty(0x1, VT_BOOL, propVal);
}

BOOL IEditor::GetVisible()
{
   BOOL result;
   GetProperty(0x2, VT_BOOL, (void*)&result);
   return(result);
}

void IEditor::SetVisible(BOOL propVal)
{
   SetProperty(0x2, VT_BOOL, propVal);
}

BOOL IEditor::GetMinimized()
{
   BOOL result;
   GetProperty(0x3, VT_BOOL, (void*)&result);
   return(result);
}

void IEditor::SetMinimized(BOOL propVal)
{
   SetProperty(0x3, VT_BOOL, propVal);
}

BOOL IEditor::GetBold()
{
   BOOL result;
   GetProperty(0x4, VT_BOOL, (void*)&result);
   return(result);
}

void IEditor::SetBold(BOOL propVal)
{
   SetProperty(0x4, VT_BOOL, propVal);
}

CString IEditor::GetFont()
{
   CString result;
   GetProperty(0x5, VT_BSTR, (void*)&result);
   return(result);
}

void IEditor::SetFont(LPCTSTR propVal)
{
   SetProperty(0x5, VT_BSTR, propVal);
}

short IEditor::GetFontSize()
{
   short result;
   GetProperty(0x6, VT_I2, (void*)&result);
   return(result);
}

void IEditor::SetFontSize(short propVal)
{
   SetProperty(0x6, VT_I2, propVal);
}

CString IEditor::GetSelectedText()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return(result);
}

void IEditor::SetSelectedText(LPCTSTR propVal)
{
   SetProperty(0x7, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IEditor operations

short IEditor::FileOpen(LPCTSTR szFilename, short sAction)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR VTS_I2;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szFilename, sAction);
   return(result);
}

short IEditor::FileSave()
{
   short result;
   InvokeHelper(0x9, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
   return(result);
}

short IEditor::FileSaveAs(LPCTSTR szFilename, short sAction)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR VTS_I2;
   InvokeHelper(0xa, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szFilename, sAction);
   return(result);
}

short IEditor::CharRight(short sCount, short sSelect)
{
   short result;
   static BYTE parms[] =
   VTS_I2 VTS_I2;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                sCount, sSelect);
   return(result);
}

short IEditor::ExtendSelection(LPCTSTR szChar)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR;
   InvokeHelper(0xc, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szChar);
   return(result);
}

short IEditor::FilePrintDefault()
{
   short result;
   InvokeHelper(0xd, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
   return(result);
}

short IEditor::FileClose(short sAction)
{
   short result;
   static BYTE parms[] =
   VTS_I2;
   InvokeHelper(0xe, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                sAction);
   return(result);
}

void IEditor::StartOfDocument()
{
   InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IEditor::EditFindClearFormatting()
{
   InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short IEditor::EditFind(LPCTSTR szString)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR;
   InvokeHelper(0x11, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szString);
   return(result);
}

void IEditor::EditClear(short sCount)
{
   static BYTE parms[] =
   VTS_I2;
   InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                sCount);
}

void IEditor::FileNew(short sAction)
{
   static BYTE parms[] =
   VTS_I2;
   InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                sAction);
}

void IEditor::EndOfLine()
{
   InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IEditor::EndOfDocument()
{
   InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short IEditor::InsertFile(LPCTSTR szFilename)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR;
   InvokeHelper(0x16, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szFilename);
   return(result);
}

long IEditor::ReplaceVariables()
{
   long result;
   InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
   return(result);
}

long IEditor::ReplaceVariablesWith(LPCTSTR pszIdiInfo)
{
   long result;
   static BYTE parms[] =
   VTS_BSTR;
   InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                pszIdiInfo);
   return(result);
}

short IEditor::UseCaseObjectKey(LPDISPATCH lpdCaseObjectKey)
{
   short result;
   static BYTE parms[] =
   VTS_DISPATCH;
   InvokeHelper(0x19, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                lpdCaseObjectKey);
   return(result);
}

short IEditor::UseWorkObjectKey(LPDISPATCH lpdWorkObjectKey)
{
   short result;
   static BYTE parms[] =
   VTS_DISPATCH;
   InvokeHelper(0x1a, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                lpdWorkObjectKey);
   return(result);
}

short IEditor::UseWorkObjectValues(LPCTSTR szCRDateTime, LPCTSTR szRecordCode, LPCTSTR szCreateNode)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR VTS_BSTR VTS_BSTR;
   InvokeHelper(0x1b, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szCRDateTime, szRecordCode, szCreateNode);
   return(result);
}

short IEditor::UseCaseObjectValues(LPCTSTR szCRDateTime, LPCTSTR szRecordCode, LPCTSTR szCreateNode)
{
   short result;
   static BYTE parms[] =
   VTS_BSTR VTS_BSTR VTS_BSTR;
   InvokeHelper(0x1c, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
                szCRDateTime, szRecordCode, szCreateNode);
   return(result);
}

void IEditor::SetModifiedFlag(BOOL fDirty)
{
   static BYTE parms[] =
   VTS_BOOL;
   InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                fDirty);
}

long IEditor::RunAsForms(long hReturn, LPCTSTR pszMenuText)
{
   long result;
   static BYTE parms[] =
   VTS_I4 VTS_BSTR;
   InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                hReturn, pszMenuText);
   return(result);
}

long IEditor::DoReplaceVariables(LPDISPATCH lDataObj)
{
   long result;
   static BYTE parms[] =
   VTS_DISPATCH;
   InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                lDataObj);
   return(result);
}

CString IEditor::FileOpenDialog()
{
   CString result;
   InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
   return(result);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/editor.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:50   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:38   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
