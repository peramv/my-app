#pragma once

#include <uibase/ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropMgmtPage dialog

class MgmtCo;

class AboutPropMgmtPage : public CPropertyPage, public AboutPropPage
{
   DECLARE_DYNAMIC(AboutPropMgmtPage)

public:
   AboutPropMgmtPage();
   virtual ~AboutPropMgmtPage();
   virtual void generateReport( std::wstringstream& ss );
   bool hasMgmtCo() const;

// Dialog Data
   enum { IDD = IDD_ABOUT_MGMT };
   CString m_strCompanyID;
   CString m_strClientID;
   CString m_strName;
   CString m_strURL;

protected:
   ListViewControl m_optionList;

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropMgmtPage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   MgmtCo* pMgmtCo_;
   void AddTextField( const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField );

};
