#include "stdafx.h"
#include "bfdefaultcontrolfactory.hpp"
#include "dstdatetime.h"
#include "dstedit.h"
#include "dstcombobox.h"
#include "dstbutton.h"
#include "dststatic.h"
#include "dstgridwnd.h"
#include "dsttabctrl.h"
#include "dstlistctrl.h"
#include "dsttimerlistctrl.h"

BaseControl* BFDefaultControlFactory::createControl( E_CONTROLTYPE eType, 
                                                     BaseDlg* pParent,
                                                     UINT controlID )
{
   BaseControl* pCtrl = NULL;
   switch( eType )
   {  // Create corresponding control
      case CTRL_EDIT:
         pCtrl = new DSTEdit( pParent, controlID );
         break;
      case CTRL_COMBO:
         pCtrl = new DSTComboBox( pParent, controlID );
         break;
      case CTRL_DATE:
         pCtrl = new DSTDateTime( pParent, controlID, I_("D") );
         break;
      case CTRL_CHECKBOX:
         pCtrl = new DSTButton( pParent, controlID );
         break;
      case CTRL_STATIC:
         pCtrl = new DSTStatic( pParent, controlID );
         break;
	  case CTRL_BUTTON:
		 pCtrl = new DSTButton( pParent, controlID );
		 break;
      case CTRL_TIME:
         pCtrl = new DSTDateTime( pParent, controlID, I_("T") );
         break;
      default:
         assert( 0 );
         break;
   }
   return( pCtrl );
}


DSTListCtrl* BFDefaultControlFactory::createListControl( BaseDlg* pParent,
                                                         const I_CHAR* dialogName,
                                                         UINT idControl,
                                                         UINT idParentControl,
                                                         UINT flags,
                                                         bool bShowSelAlways )
{
   DSTListCtrl* pCtrl = NULL;
   if( flags & LISTFLAG_TIMER )
   {
      pCtrl = new DSTTimerListCtrl( pParent, dialogName, idControl,
                                    idParentControl, flags, bShowSelAlways );
   }
   else
   {
      pCtrl = new DSTListCtrl( pParent, dialogName, idControl,
                               idParentControl, flags, bShowSelAlways );
   }
   return( pCtrl );
}



DSTTabCtrl* BFDefaultControlFactory::createTabControl( BaseDlg* pParent,
                                                       const I_CHAR* dialogName,
                                                       UINT idControl,
                                                       UINT idParentControl,
                                                       UINT flags )
{
   DSTTabCtrl* pCtrl = new DSTTabCtrl( pParent, dialogName, idControl, idParentControl, flags );
   return( pCtrl );
}

DSTGridWnd* BFDefaultControlFactory::createGridControl( BaseDlg* pParent,
                                                        const I_CHAR* dialogName,
                                                        UINT idControl,
                                                        UINT idControlGroup,
                                                        const I_CHAR* gridName,
                                                        const BFContainerId& idContainer,
                                                        UINT flags )
{
   DSTGridWnd *pGrid = new DSTGridWnd( pParent, dialogName, idControl, gridName, idContainer, idControlGroup, flags );
   return( pGrid );
}


BFControlFactory* BFDefaultControlFactory::getInstance()
{
   static BFDefaultControlFactory instance;
   return( &instance );
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/uibase/bfdefaultcontrolfactory.cpp-arc  $
//
//   Rev 1.5   Jul 06 2005 13:56:22   hernando
//PET1250 FN01 - Added CTRL_TIME.
//
//   Rev 1.4   Nov 30 2004 16:29:58   Fengyong
//Add CTRL_BUTTON
//
//   Rev 1.3   Oct 01 2004 18:15:12   popescu
//PET 1117/06, SSB Germany - Added 'flags' parameter to the grid control - not very useful for the moment
// 
//    Rev 1.2   Jan 06 2003 16:46:08   PURDYECH
// BFDataGroupId and BFContainerId changeover
// 
//    Rev 1.1   Nov 13 2002 11:43:58   PURDYECH
// Extended BFControlFactory to include list controls, tab controls and grid windows.
// 
//    Rev 1.0   Oct 21 2002 13:43:16   PURDYECH
// Initial Revision
//

