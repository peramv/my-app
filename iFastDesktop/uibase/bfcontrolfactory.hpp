#pragma once

#include <commonport.h>
#include <uibase\basedlgconstants.h>
#include <bfproc\bfcontainerid.hpp>
class BaseDlg;
class BaseControl;
class DSTListCtrl;
class DSTTabCtrl;
class DSTGridWnd;
class BFContainerId;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE BFControlFactory
{
public:
   virtual BaseControl* createControl( E_CONTROLTYPE eType, 
                                       BaseDlg* pParent,
                                       UINT controlID ) = 0;

   virtual DSTListCtrl* createListControl( BaseDlg* pParent,
                                           const I_CHAR* dialogName,
                                           UINT idControl,
                                           UINT idParentControl,
                                           UINT flags,
                                           bool bShowSelAlways ) = 0;

   virtual DSTTabCtrl* createTabControl( BaseDlg* pParent,
                                         const I_CHAR* dialogName,
                                         UINT idControl,
                                         UINT idParentControl,
                                         UINT flags ) = 0;

   virtual DSTGridWnd* createGridControl( BaseDlg* pParent,
                                          const I_CHAR* dialogName,
                                          UINT idControl,
                                          UINT idControlGroup,
                                          const I_CHAR* gridName,
                                          const BFContainerId& idContainer,
                                          UINT flags ) = 0;



};

