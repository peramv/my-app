#if !defined(AFX_ANACCOUNTDETAILSDLG_H__0B3606A1_5FC8_11D3_B95E_00C04F572654__INCLUDED_)
   #define AFX_ANACCOUNTDETAILSDLG_H__0B3606A1_5FC8_11D3_B95E_00C04F572654__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000
// ANAccountDetailsDlg.h : header file
//
   #include <ifastgui\BaseAccountDetailsDlg.h>

/////////////////////////////////////////////////////////////////////////////
// CANAccountDetailsDlg dialog

class CANAccountDetailsDlg : public BaseAccountDetailsDlg
{
// Construction
public:
   CANAccountDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(CANAccountDetailsDlg)
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CANAccountDetailsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual void fillShrAddressList();
   virtual void ItemchangedLvAccounts(int index);
   //virtual bool doRefresh(
   //   GenericInterface * /*rpGICaller*/, 
   //   const I_CHAR * /*szOriginalCommand*/
   //   );


   // Generated message map functions
   //{{AFX_MSG(CANAccountDetailsDlg)
   // NOTE: the ClassWizard will add member functions here
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANACCOUNTDETAILSDLG_H__0B3606A1_5FC8_11D3_B95E_00C04F572654__INCLUDED_)
