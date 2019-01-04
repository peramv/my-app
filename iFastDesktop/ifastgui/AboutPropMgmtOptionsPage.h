#pragma once

#include <uibase/ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropMgmtOptionsPage dialog

class MgmtCo;

class AboutPropMgmtOptionsPage : public CPropertyPage, public AboutPropPage
{
   DECLARE_DYNAMIC(AboutPropMgmtOptionsPage)

public:
   AboutPropMgmtOptionsPage();
   virtual ~AboutPropMgmtOptionsPage();
   virtual void generateReport( std::wstringstream& ss );
   bool hasOptions() const;

// Dialog Data
   enum { IDD = IDD_ABOUT_MGMT_OPTIONS };

protected:
   ListViewControl m_optionList;

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropMgmtOptionsPage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   int m_optionCount;
   MgmtCo* pMgmtCo_;
   void AddTextField( const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField );
   void ReportTextField( std::wstringstream& ss, const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField );

};
