#if !defined(AFX_DISCARDMSGDLG_H__FBAAAAC7_C796_11D3_B722_00105AA1A578__INCLUDED_)
   #define AFX_DISCARDMSGDLG_H__FBAAAAC7_C796_11D3_B722_00105AA1A578__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000
// DiscardMsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DiscardMsgDlg dialog

class DiscardMsgDlg : public CDialog
{
// Construction
public:
   DiscardMsgDlg(CWnd* pParent, UINT msgA, UINT msgB, UINT btnCaption);   // standard constructor
   DiscardMsgDlg(CWnd* pParent, UINT msgA, UINT msgB, UINT btn1Caption, UINT btn2Caption);   // standard constructor

// Dialog Data
   //{{AFX_DATA(DiscardMsgDlg)
   enum
   {
      IDD = IDD_DISCARD
   };
   CStatic m_Icon;
   CString m_MessageA;
   CString m_MessageB;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DiscardMsgDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(DiscardMsgDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   private:
   CString  btn1;
   CString btn2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCARDMSGDLG_H__FBAAAAC7_C796_11D3_B722_00105AA1A578__INCLUDED_)
