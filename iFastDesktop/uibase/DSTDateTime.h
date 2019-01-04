#pragma once

// DSTDateTime.h : header file
//
#include <uibase\BaseControl.hpp>
#include <afxdtctl.h>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTDateTime window

#pragma warning( disable: 4275 )
class WIN32UIBASE_LINKAGE DSTDateTime : public CDateTimeCtrl, public BaseControl
{
// Construction
public:
   DSTDateTime(
              BaseDlg *rpParent,
              UINT controlID,
              DString Type = I_("D")
              );

// Attributes
public:

// Operations
   public:

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DSTDateTime)
   public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void PreSubclassWindow();
   //}}AFX_VIRTUAL

// Implementation
public:
   void SetToToday();
   void GetDateInHostFormat( CString &strOut) const;
   virtual ~DSTDateTime();
   BOOL IsDroppedDown () { return IsDropdown; };
   // Generated message map functions
protected:
   //{{AFX_MSG(DSTDateTime)
   afx_msg void OnKillFocus(CWnd* pNewWnd);
   afx_msg void OnCloseUp(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnDropdown(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   //}}AFX_MSG
   LRESULT OnMouseLeave(WPARAM a=0L, LPARAM b=0L);

   DECLARE_MESSAGE_MAP()

   virtual void DoGetText(
                         DString &strValueOut,
                         int index=0
                         ) const;
   bool doSetCtrlReadOnly(bool bReadOnly);

   /**
     * This method is called from BaseControl::Init to allow us to get new 
     * properties.
     * This may be called more than once (to allow the same control to be tied
     * to different fields, depending on context).
     */
   virtual void DoInit();
   /**
     * This method is called from BaseControl::SetText and is expected to sets
     * the value of the control to the specified value. 
     * @param strValueIn - value to set.
     * @param index - not used by this class
     * @returns flag with true = success, false = failure, check conditions
     */
   virtual bool DoSetText(
                         const DString &strValueIn,
                         int index=0
                         );
   virtual void DoClear();

private:
   BOOL IsDropdown;
   DString OriginalStr;
   void SetTo9999();
   void SetTimeTo0000();
   CString m_strFormat;
   void ValidateAndSetDate();
   DString m_Type;
};

/////////////////////////////////////////////////////////////////////////////

