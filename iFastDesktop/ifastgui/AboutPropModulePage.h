#pragma once

#include <uibase\ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropModulePage dialog

class AboutPropModulePage : public CPropertyPage, public AboutPropPage
{
	DECLARE_DYNAMIC(AboutPropModulePage)

public:
	AboutPropModulePage();
	virtual ~AboutPropModulePage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
	enum { IDD = IDD_ABOUT_MODULES };

   ListViewControl m_infoList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropModulePage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
   CString LoadModuleInfo( CString moduleName );
   void LoadDependentInfo( CString dependentName );

   BOOL WalkTheProcess( CString moduleName );
   BOOL ShowImports( PIMAGE_DOS_HEADER dosHeader );
   PIMAGE_SECTION_HEADER GetSectionHeader( PSTR name, PIMAGE_NT_HEADERS pNTHeader );

   static void GetLatestBuildDate( CString& latestDate, const CString& compareDate );
   static CString GetModuleBuildInfo( HINSTANCE inst, const short infoType );

   int m_itemCount;
};
