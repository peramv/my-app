#pragma once

#include <uibase\bfcontrolfactory.hpp>
#include <bfproc\bfcontainerid.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE BFDefaultControlFactory : public BFControlFactory
{
public:
   virtual BaseControl* createControl( E_CONTROLTYPE eType, 
                                       BaseDlg* pParent,
                                       UINT controlID );

   virtual DSTListCtrl* createListControl( BaseDlg* pParent,
                                           const I_CHAR* dialogName,
                                           UINT idControl,
                                           UINT idParentControl,
                                           UINT flags,
                                           bool bShowSelAlways );


   virtual DSTTabCtrl* createTabControl( BaseDlg* pParent,
                                         const I_CHAR* dialogName,
                                         UINT idControl,
                                         UINT idParentControl,
                                         UINT flags );

   virtual DSTGridWnd* createGridControl( BaseDlg* pParent,
                                          const I_CHAR* dialogName,
                                          UINT idControl,
                                          UINT idControlGroup,
                                          const I_CHAR* gridName,
                                          const BFContainerId& idContainer,
                                          UINT flags );

   static BFControlFactory* getInstance();
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/uibase/bfdefaultcontrolfactory.hpp-arc  $
//
//   Rev 1.3   Oct 01 2004 18:15:12   popescu
//PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
//
//   Rev 1.2   Jan 06 2003 16:46:14   PURDYECH
//BFDataGroupId and BFContainerId changeover
//
//   Rev 1.1   Nov 13 2002 11:43:56   PURDYECH
//Extended BFControlFactory to include list controls, tab controls and grid windows.
//
//   Rev 1.0   Oct 21 2002 13:44:50   PURDYECH
//Initial Revision
//
