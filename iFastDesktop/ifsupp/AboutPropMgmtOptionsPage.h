#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

#include "AboutPropPage.hpp"

// AboutPropMgmtOptionsPage dialog

class MgmtCo;
class BFCBO;
class BFDataId;

#include <map>
#include <vector>
#include <bfdata\bffieldid.hpp>

class IFSUPP_LINKAGE AboutPropMgmtOptionsPage : public CPropertyPage, public AboutPropPage
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
   CListCtrl m_optionList;

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropMgmtOptionsPage)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   int m_optionCount;
   MgmtCo* pMgmtCo_;
   void AddTextField( const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField );
   void AddTextFields( const BFDataId& dataID, BFCBO* pCBO);
   void AddTextSeparator( const DString& dstrCol0, const DString& dstrCol1 );
   void AddTextBlankLineSeparator( );
   void ReportTextField( std::wstringstream& ss, const DString& dstrName, BFCBO* pCBO, const BFFieldId& idField );
   void ReportTextFields( std::wstringstream& ss, const BFDataId& dataID, BFCBO* pCBO);

};
