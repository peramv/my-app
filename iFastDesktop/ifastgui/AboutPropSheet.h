#pragma once

// AboutPropSheet
class AboutPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(AboutPropSheet)

private:
   CButton  m_btnReport;

   void OnReport();

public:
	AboutPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	AboutPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~AboutPropSheet();
   virtual BOOL OnInitDialog();

   static void Display( const I_CHAR* pszCaption = I_("iFAST/Desktop Diagnostics") );

protected:
	DECLARE_MESSAGE_MAP()
};


