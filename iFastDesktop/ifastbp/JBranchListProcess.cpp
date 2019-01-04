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
// ^FILE   : JBranchListProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 22/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BranchListProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <time.h>
#include "jbranchlistprocess.hpp"
#include <ifastdataimpl\dse_dstc0091_req.hpp>
#include "jbranchlistprocessincludes.h"
#include <ifastcbo\jbranchlist.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JBRANCHLIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BranchListProcess > processCreator( CMD_BPROC_JBRANCHLIST );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BranchListProcess" );

   const I_CHAR *pBROKERCODE = I_( "BrokerCode" );
   const I_CHAR *pBRANCHCODE = I_( "BranchCode" );
}

namespace BRANCHLISTLIT  //stands for account details literals
{
   const I_CHAR * const BROKERCODE = I_( "BrokerCode" );  
   const I_CHAR * const BRANCHCODE = I_( "BranchCode" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319BranchListProcess::BranchListProcess() : 
BranchListProcess::BranchListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJBranchList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::BRANCH_LIST, true);

   addFieldDetails( ifds::NextKey, IFASTBP_PROC::BRANCH_LIST );

   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrLine1, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrLine2, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrLine3, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrLine4, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrLine5, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::AddrCntryCode, IFASTBP_PROC::BRANCH_LIST );
   addFieldDetails( ifds::PhoneNumber, IFASTBP_PROC::BRANCH_LIST );
}

//******************************************************************************

BranchListProcess::~BranchListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJBranchList;
   _rpChildGI = NULL;
}

bool BranchListProcess::doGetData(
                                 GenericInterface * ,
                                 BFData * 
                                 ) const
{
   _pJBranchList->getMore();
   BranchListProcess * _pAbsPr = const_cast < BranchListProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::BRANCH_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::BRANCH_LIST, _pJBranchList );

   return(true);
}

bool BranchListProcess::doMoreRecordsExist(
                                          GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer 
                                          )
{
   return( _pJBranchList->doMoreRecordsExist() );
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY BranchListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _BrokerCode,_BranchCode,_SlsRep,tmp;
   try
   {
      getParameter( pBROKERCODE, _BrokerCode );
      getParameter( pBRANCHCODE, _BranchCode );

      _pJBranchList = new JBranchList( *getBFWorkSession() );

      sevRtn = _pJBranchList->init( _BrokerCode, _BranchCode);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::BRANCH_LIST, _pJBranchList );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

//******************************************************************************

E_COMMANDRETURN BranchListProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}
void BranchListProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                  ) const
{
   if( idField == ifds::NextKey )
   {
      _pJBranchList->getField(idField, strValueOut, getDataGroupId(), bFormatted );
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}
//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JBranchListProcess.cpp-arc  $
 * 
 *    Rev 1.14   Mar 21 2003 17:43:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Mar 07 2003 11:56:30   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.12   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 16:45:02   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.10   Aug 29 2002 12:54:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:24:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:55:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   15 May 2001 15:38:46   YINGZ
 * data group id clean up
 * 
 *    Rev 1.6   03 May 2001 14:05:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 23 2001 15:17:44   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.4   15 Dec 2000 12:43:36   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Mar 30 2000 15:46:56   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:54   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.2   Mar 10 2000 09:56:50   FENGYONG
// For Nextkey
// 
//    Rev 1.0   Feb 25 2000 16:17:36   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 */


