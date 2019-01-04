#pragma once

// TelEdit.h : header file
//
#include <imm.h>

/////////////////////////////////////////////////////////////////////////////
// CTelEdit window

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE CTelEdit : public CEdit
{
// Construction
public:
   CTelEdit();

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CTelEdit)
   //}}AFX_VIRTUAL

// Implementation
   public:
   void SetMaxCharNum(long n);
   void SetAllowedChars(LPCTSTR AllowedChars);
   virtual ~CTelEdit();

   // Generated message map functions
protected:
   //{{AFX_MSG(CTelEdit)
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnSetfocus();
   afx_msg void OnKillfocus();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   private:
   long MaxCharNum;
   CString _AllowedChars;
   HIMC current;
   BOOL OpenStatus;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/TelEdit.h-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Jul 28 1999 10:41:12   YINGZ
 * add max char feature
 * 
 *    Rev 1.3   Jul 20 1999 14:51:58   YINGZ
 * ?
 * 
 *    Rev 1.2   Jul 20 1999 13:53:22   YINGZ
 * new ime support
 * 
 *    Rev 1.1   Jul 08 1999 10:05:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
