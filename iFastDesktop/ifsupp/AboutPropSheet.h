#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

// AboutPropSheet
class IFSUPP_LINKAGE AboutPropSheet : public CPropertySheet
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


