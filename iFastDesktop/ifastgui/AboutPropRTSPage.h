#pragma once


#include "AboutPropPage.hpp"

// AboutPropRTSPage dialog

class AboutPropRTSPage : public CPropertyPage, public AboutPropPage
{
	DECLARE_DYNAMIC(AboutPropRTSPage)

public:
	AboutPropRTSPage();
	virtual ~AboutPropRTSPage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
	enum { IDD = IDD_ABOUT_RTS };
   CString m_strHost;
   int m_iPort;
   int m_iTimeout;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropGeneralPage)
   afx_msg void OnPbPing();
   afx_msg void OnPbCheck();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
