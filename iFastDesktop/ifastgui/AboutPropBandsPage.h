#pragma once

#include <uibase/ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropBandsPage dialog

class DSTCUserSession;

class AboutPropBandsPage : public CPropertyPage, public AboutPropPage
{
   DECLARE_DYNAMIC(AboutPropBandsPage)

public:
   AboutPropBandsPage();
   virtual ~AboutPropBandsPage();
   virtual void generateReport( std::wstringstream& ss );
   bool hasBands() const;

// Dialog Data
   enum { IDD = IDD_ABOUT_BANDS };

protected:
   ListViewControl m_bandList;

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   void addConfigEntry( const I_CHAR* lpcszConfig, const I_CHAR* lpcszKey, const I_CHAR* lpcszValue );
   void addReportItem( std::wstringstream& ss, const I_CHAR* lpcszConfig, const I_CHAR* lpcszKey, const I_CHAR* lpcszValue );

   //{{AFX_MSG(AboutPropBandsPage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   int m_bandCount;
   DSTCUserSession* pUserSession_;
   DString dstrMgmtCo_;
   void AddBand( const std::wstring& dstrName, const std::wstring& dstrBand, bool bHasAccessList );
   void ReportBand( std::wstringstream& ss,
                    const std::wstring& dstrName, 
                    const std::wstring& dstrBand, 
                    bool bHasAccessList );

};
