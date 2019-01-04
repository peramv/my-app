#pragma once

#include <uibase/ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropRegistryPage dialog

class AboutPropRegistryPage : public CPropertyPage, public AboutPropPage
{
	DECLARE_DYNAMIC(AboutPropRegistryPage)

public:
	AboutPropRegistryPage();
	virtual ~AboutPropRegistryPage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
	enum { IDD = IDD_ABOUT_REGISTRY };

protected:
   ListViewControl m_registryList;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   void addConfigEntry( const I_CHAR* lpcszConfig, const I_CHAR* lpcszKey, const I_CHAR* lpcszValue );
   void addReportItem( std::wstringstream& ss, const I_CHAR* lpcszConfig, const I_CHAR* lpcszKey, const I_CHAR* lpcszValue );

   //{{AFX_MSG(AboutPropRegistryPage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   int m_registryCount;
};
