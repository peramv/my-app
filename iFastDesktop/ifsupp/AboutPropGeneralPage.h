#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

#include "AboutPropPage.hpp"
// AboutPropGeneralPage dialog

class IFSUPP_LINKAGE AboutPropGeneralPage : public CPropertyPage, public AboutPropPage
{
   DECLARE_DYNAMIC(AboutPropGeneralPage)

public:
   AboutPropGeneralPage();
   virtual ~AboutPropGeneralPage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
   enum { IDD = IDD_ABOUT_GENERAL };
   CString m_strBuildTime;
   CString m_strBuildLabel;
   CString m_strUsingAWD;
   int m_PID;
   CString m_strCWD;
   CString m_strMarket;
   CString m_strVaalMode;
   CString m_strRevisionNum;


protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropGeneralPage)
   virtual BOOL OnInitDialog();
//   virtual void OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   CString GetModuleBuildInfo( HINSTANCE inst, const short infoType );

};
