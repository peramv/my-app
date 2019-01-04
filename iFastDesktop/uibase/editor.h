// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IEditor wrapper class

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE IEditor : public COleDispatchDriver
{
public:
   IEditor() {}    // Calls COleDispatchDriver default constructor
   IEditor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   IEditor(const IEditor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   BOOL GetIsDirty();
   void SetIsDirty(BOOL);
   BOOL GetVisible();
   void SetVisible(BOOL);
   BOOL GetMinimized();
   void SetMinimized(BOOL);
   BOOL GetBold();
   void SetBold(BOOL);
   CString GetFont();
   void SetFont(LPCTSTR);
   short GetFontSize();
   void SetFontSize(short);
   CString GetSelectedText();
   void SetSelectedText(LPCTSTR);

// Operations
public:
   short FileOpen(LPCTSTR szFilename, short sAction);
   short FileSave();
   short FileSaveAs(LPCTSTR szFilename, short sAction);
   short CharRight(short sCount, short sSelect);
   short ExtendSelection(LPCTSTR szChar);
   short FilePrintDefault();
   short FileClose(short sAction);
   void StartOfDocument();
   void EditFindClearFormatting();
   short EditFind(LPCTSTR szString);
   void EditClear(short sCount);
   void FileNew(short sAction);
   void EndOfLine();
   void EndOfDocument();
   short InsertFile(LPCTSTR szFilename);
   long ReplaceVariables();
   long ReplaceVariablesWith(LPCTSTR pszIdiInfo);
   short UseCaseObjectKey(LPDISPATCH lpdCaseObjectKey);
   short UseWorkObjectKey(LPDISPATCH lpdWorkObjectKey);
   short UseWorkObjectValues(LPCTSTR szCRDateTime, LPCTSTR szRecordCode, LPCTSTR szCreateNode);
   short UseCaseObjectValues(LPCTSTR szCRDateTime, LPCTSTR szRecordCode, LPCTSTR szCreateNode);
   void SetModifiedFlag(BOOL fDirty);
   long RunAsForms(long hReturn, LPCTSTR pszMenuText);
   long DoReplaceVariables(LPDISPATCH lDataObj);
   CString FileOpenDialog();
};
