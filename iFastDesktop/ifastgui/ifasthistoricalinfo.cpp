//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : IFastHistoricalInfo.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ----------------------------------------------------------
//
// ^CLASS    : IFastBaseHistoricalInfo
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  

//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"

#include "ifasthistoricalinfo.hpp"
#include <ifastbp\ifasthistoricalparameters.hpp>
#include <bfproc\abstractprocess.hpp>
#include <ifastgui\basemaindlg.h>
#include <ifastbp\mfcaninterprocparam.hpp>

#include <ifastbp\historicalinfoprocessincludes.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_INFO;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "IFastBaseMainDlg" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


//******************************************************************************

bool IFastHistoricalInfo::operator()( BaseMainDlg* pDlg, const BFContainerId& idContainer, DString dstrType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "()( BaseMainDlg *, long )" ) );
   CWaitCursor wait;
   IFastHistoricalParameters* pParent = dynamic_cast< IFastHistoricalParameters* >( pDlg->getParent() );
   //the parent process that calls this method should be a 
   //IFastHistoricalParameters class
   if (pParent == NULL) 
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   std::vector< HistoricalElement > vectorHistoricalElements, *pVectorHistoricalElements;
   pVectorHistoricalElements = &vectorHistoricalElements;
   DString dstrVectorPtr = asString( (int) pVectorHistoricalElements );

   DString tableId, recId, dstrKeys;
   BFFieldId recordIdField;

   AbstractProcess* pParentProc = dynamic_cast< AbstractProcess* >( pParent );
   assert( NULL != pParentProc );

   pDlg->setParameter( I_("TYPE"), dstrType );
   if( dstrType == I_("MULTI") || dstrType == I_("ACTRDR"))
   {
      pParent->getHistoricalParameters(idContainer, vectorHistoricalElements);
      pDlg->setParameter( I_("HISTORICAL_VECTOR"), dstrVectorPtr );
   }
   else if( dstrType == I_("SINGLE") )
   {
      pParent->getHistoricalParameters(idContainer, recordIdField, tableId, dstrKeys);
      if( recordIdField != ifds::NullFieldId )
      {
         pParentProc->getField( pDlg, idContainer, recordIdField, recId);
      }
      pDlg->setParameter(MFCAN_IP_PARAM::RECID, recId);
      pDlg->setParameter(MFCAN_IP_PARAM::TABLEID, tableId);
      pDlg->setParameter(MFCAN_IP_PARAM::KEYS, dstrKeys);
   }
   //call the historical process
   try
   {
      E_COMMANDRETURN eRtn;
      pDlg->SetMessageStatusBar(TXT_LOAD_HISTORICAL_INFO);
      eRtn = pDlg->indirectInvokeCommand( pParentProc, 
                                   CMD_BPROC_HISTORICAL_INFO, 
                                   PROC_NO_TYPE,
                                   true /*modal*/, 
                                   NULL );
      pDlg->SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            {
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            }
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   return( true );
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ifasthistoricalinfo.cpp-arc  $
// 
//    Rev 1.8   Feb 28 2004 16:02:44   HERNANDO
// PET965 FN11 - Additional historical enhancement.  Support for single or multiple view calls.
// 
//    Rev 1.7   Aug 19 2003 13:50:14   HERNANDO
// Get recordIdField value only if recordIdField isn't NullFieldId.
// 
//    Rev 1.6   Aug 19 2003 13:17:54   HERNANDO
// Use dstrKeys from getHistoricalParameters.
// 
//    Rev 1.5   Jun 30 2003 16:59:02   popescu
// added historical info search to the Broker Features search;
// moved some param names to the mfcaniterprocparam namespace
// 
//    Rev 1.4   Jun 04 2003 09:59:44   popescu
// fix a system crash, moved the makerframe2 at the top of the method
// 
//    Rev 1.3   Mar 21 2003 18:38:18   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Mar 11 2003 15:09:40   popescu
// Fixed some compilation errors in regards with teh latest base code changes
// 
//    Rev 1.1   Mar 05 2003 10:56:46   PURDYECH
// Make this a function object for cleaner design.
// 
//    Rev 1.2   Feb 03 2003 11:56:56   popescu
// Displaying the history button only when the item is not new, and adding some txt message for the status bar
// 
//    Rev 1.1   Jan 28 2003 13:16:38   popescu
// Historical Info feature implementation
// 
//    Rev 1.0   Jan 26 2003 13:45:52   popescu
// Initial Revision
// 
*/

