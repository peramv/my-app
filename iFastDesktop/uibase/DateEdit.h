#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997-98 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DateEdit.h
// ^AUTHOR : Steve Tarver
// ^DATE   : 5/22/98
//
// ^CLASS  : CDateEdit
// ^PARENT :
//
// ^CLASS DESCRIPTION :
//    This class provides an MFC CEdit control with date handling.
//
//	Use:
//    Include this file and the implementation in your project.
//
//    1. Draw an editbox on your dialog.
//    2. Add a member variable for the edit control.
//    3. Call SubclassDlgItem() in your dialog's OnInitDialog()
//          m_myCtl.SubclassDlgItem( IDC_TXT_MY_CTL, m_hWnd );
//
//    You cannot use DDX_Control functions from DoDataExchange because we
//    do not inherit from our base class publicly. Note that this
//    means you can't declare string variables that are tied to the control.
//
//    If you require the user enter date, use GetText(). Note that there is
//    a GetText() that will format the value using a supplied format instead
//    of the one you specified.
//
//    If you want to test validity of the value, call IsEmpty() to see if
//    the control contains text and then GetText() to see if we could parse it.
//    Although the control parses text when it loses focus, you could be asked
//    to process the value before the control loses focus and parses the date.
//    This is less clear, but faster than providing an IsValid() since that
//    would imply parsing the text twice.
//
//******************************************************************************

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

//******************************************************************************
//
//	CDateEdit
//		Note: We use protected inheritance because we want to limit access to
//		base class methods that are not virtual. These methods would not provide
//		the expected response.
//
//******************************************************************************
#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE CDateEdit : protected CEdit
{
public:
//******************************************************************************
// Custom Types
//******************************************************************************
   // An underbar is a placeholder for a slash. We restrict the formats to
   // the following to ensure our parser works.
   enum DisplayFormatType
   {
      e_INVALID = 0,      // Place holder for invalid formats
      e_MMDD,
      e_MM_DD,
      e_MMDDYYYY,
      e_MM_DD_YYYY
   };

public:
   CDateEdit();
   virtual ~CDateEdit();

   BOOL EnableWindow(
                    BOOL bEnable = TRUE
                    )
   {
      return(CEdit::EnableWindow( bEnable ));
   }

   HWND GetHWND()
   {
      return(m_hWnd);
   }

   // Returns our value using our format. We return an empty string if it is
   // invalid so you should also check that the control is not empty. This
   // scheme is cheaper than providing an IsValid().
   CString &GetText(
                   CString &text);

   DString &GetText(
                   DString &text
                   );

   // Returns our value using provided format. We return an empty string if it is
   // invalid so you should also check that the control is not empty. This
   // scheme is cheaper than providing an IsValid().
   CString &GetText(
                   CString &text,
                   DisplayFormatType useThisFormat
                   );

   DString &GetText(
                   DString &text,
                   DisplayFormatType useThisFormat
                   );

   // Returns whether our control contains text. This is used in conjunction with
   // GetText() since it will return an empty string if the text is not valid.
   // When we lose focus, we parse the window text so a non-focused window
   // should always have valid text. If you GetText() when the window has focus,
   // it could contain invalid text and GetText() would return an empty string.
   // Note: single line edit control is assumed.
   bool IsEmpty()
   {
      return(LineLength() == 0);
   }
   // Returns whether the current value is different than the initial value.
   bool IsModified();
   CWnd *SetFocus()
   {
      return(CEdit::SetFocus());
   }
   bool SetFormat(
                 DisplayFormatType newFormat
                 );
   // Call this only after our window is created.
   // LOOK: Override OnCreate() and set window text - fix steve
   bool SetInitialValue(
                       const I_CHAR *text
                       );
   // Returns false if we couldn't make a date out of text
   bool SetText(
               const CString &text
               );
   bool SetText(
               const DString &text
               );
   bool SetText(
               const I_CHAR *text
               );
   BOOL ShowWindow(
                  bool bShow
                  )
   {
      return(CEdit::ShowWindow( bShow ? SW_SHOW : SW_HIDE ));
   }
   BOOL SubclassDlgItem(
                       UINT nID,
                       CWnd *pParent
                       )
   {
      return(CEdit::SubclassDlgItem( nID, pParent ));
   }

/////////////////////////
// Implementation
protected:
   // Parses our display text and replaces it with our formatted text. Does
   // not modifiy window text if it hasn't changed.
   void OnKillFocus(
                   CWnd *focusedWnd
                   );

private:
   DisplayFormatType m_format;
   CString m_initialValue;

   CDateEdit(
            const CDateEdit &other
            );
   CDateEdit & operator=(
                        const CDateEdit &other
                        );

   bool Format(
              COleDateTime &date,
              CString &text,
              DisplayFormatType format
              );
   CString &Format(
                  CString &text,
                  DisplayFormatType format
                  );
   CString &Format(
                  CString &text
                  );
   CString Format();
   const I_CHAR *GetFormatString(
                                DisplayFormatType format
                                );

   // All strings must pass through here for conversion to internal format
   bool ParseString(
                   CString &text
                   );
   bool ParseString(
                   CString &text,
                   DisplayFormatType format);

   DECLARE_MESSAGE_MAP()
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/DateEdit.h-arc  $
 * 
 *    Rev 1.4   Nov 13 2002 11:43:14   PURDYECH
 * Fixed up C4275 warning error.
 * 
 *    Rev 1.3   Nov 08 2002 10:00:30   PURDYECH
 * Use #pragma warning(...) to remove warning C4275 (non-Dll interface class used as base for interface class).
 * 
 *    Rev 1.2   Oct 09 2002 17:42:38   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   19 Mar 2002 13:36:24   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.0   Feb 15 2000 11:00:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
