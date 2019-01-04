#pragma once

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#include <map>

struct IFDSPaneInfo
{
   int SBIndex;
   int SBPos;
   unsigned int SBPaneFlag;
   unsigned int SBPaneSize;
   DString strPaneKey;
};

typedef std::map< DString, IFDSPaneInfo* > PANE_MAP;
typedef PANE_MAP::iterator                 PANE_MAP_ITER;
typedef PANE_MAP::value_type               PANE_MAP_VALUE_TYPE;

// IFDSStatusBar
class WIN32UIBASE_LINKAGE IFDSStatusBar : public CStatusBar
{
   DECLARE_DYNAMIC(IFDSStatusBar)

public:
   IFDSStatusBar();
   virtual ~IFDSStatusBar();

   virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);


   void SetManagementCodeStatusBar( const I_CHAR *mgmtCd );
   void SetMessageStatusBar( const I_CHAR *msg );
   void SetMessageStatusBar( const int nId );
   void SetProfileStatusBar( const I_CHAR *profile );
   void SetSystemStatusBar( const I_CHAR *sys );
   void SetClientNameStatusBar( const I_CHAR *keyword );
   void SetCompanyCodeStatusBar( const I_CHAR *companyCode ) { _companyCode = companyCode; }

private:

protected:
   // Generated message map functions
   //{{AFX_MSG(ListViewControl)
   afx_msg void OnDestroy();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

private:
   PANE_MAP _paneInfo;
   unsigned int *m_pArray;

public:
   // Other literals
   static const int SB_MESSAGE            = 0;
   static const int SB_PROFILE            = 1;
   static const int SB_SYSTEM             = 2;
   static const int SB_MANAGEMENTCODE     = 3;
   static const int SB_CONNECTION         = 4;
   static const int INDICATOR_COUNT       = 5;

protected:
   virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
   void InitStatusPane(void);
   DString _companyCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/IFDSStatusBar.h-arc  $
//
//   Rev 1.1   Dec 22 2009 05:33:26   dchatcha
//IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 * 
 */


