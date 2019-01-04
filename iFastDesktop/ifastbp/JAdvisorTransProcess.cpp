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
// ^FILE   : JAdvisorTransProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 23/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AdvisorTransProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jadvisortransprocess.hpp"
#include "jadvisortransprocessincludes.h"
#include <ifastdataimpl\dse_dstc0093_req.hpp>
#include <ifastcbo\jadvisortrans.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JADVISORTRANS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AdvisorTransProcess > processCreator( CMD_BPROC_JADVISORTRANS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AdvisorTransProcess" );
}

namespace ADVISORTRANSLIT  //stands for account details literals
{
   const I_CHAR * const BROKERCODE = I_( "BrokerCode" );  
   const I_CHAR * const BRANCHCODE = I_( "BranchCode" );
   const I_CHAR * const SLSREP = I_( "SlsRep" );
   const I_CHAR * const FROMDATE = I_( "FromDate" );
   const I_CHAR * const TODATE = I_( "ToDate" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

using namespace ADVISORTRANSLIT;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AdvisorTransProcess::AdvisorTransProcess() : 
AdvisorTransProcess::AdvisorTransProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJAdvisorTrans( NULL ),
_pmgmtcooptions(NULL),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ADVISORTRANS_LIST, true );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::TransNum, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::TradeDate, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::SettleCurrency, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::Units, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::NetAmt, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::Settled, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::OnStmt, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::UnitValue, IFASTBP_PROC::ADVISORTRANS_LIST );
   addFieldDetails( ifds::TransId, IFASTBP_PROC::ADVISORTRANS_LIST );

   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
}

//******************************************************************************

AdvisorTransProcess::~AdvisorTransProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJAdvisorTrans;
   _pJAdvisorTrans = NULL;
   delete _pmgmtcooptions;
   _pmgmtcooptions = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************

bool AdvisorTransProcess::doGetData(
                                   GenericInterface * ,
                                   BFData * 
                                   ) const
{
   _pJAdvisorTrans->getMore();
   AdvisorTransProcess * _pAbsPr = const_cast < AdvisorTransProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORTRANS_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORTRANS_LIST, _pJAdvisorTrans );
   return(true);
}

//******************************************************************************

bool AdvisorTransProcess::doMoreRecordsExist(
                                            GenericInterface *rpGICaller,
                                            const BFContainerId& idContainer 
                                            )
{
   return( _pJAdvisorTrans->doMoreRecordsExist() );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AdvisorTransProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _BrokerCode;
   DString _BranchCode;
   DString _SlsRep;
   DString fromDate;
   DString toDate;

   try
   {
      getParameter( BROKERCODE, _BrokerCode );
      getParameter( BRANCHCODE, _BranchCode );
      getParameter( SLSREP, _SlsRep );
      getParameter( FROMDATE, fromDate );
      getParameter( TODATE, toDate );
      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( fromDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( fromDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, getDataGroupId() );
      }
      if( toDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( toDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, getDataGroupId() );
      }
      _pJAdvisorTrans = new JAdvisorTrans( *dstcWorkSession );

      sevRtn = _pJAdvisorTrans->init( _BrokerCode, _BranchCode, _SlsRep, fromDate, toDate, dstrTrack, dstrActivity);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ADVISORTRANS_LIST, _pJAdvisorTrans );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      _pmgmtcooptions = new MgmtCoOptions( *dstcWorkSession );
      sevRtn = _pmgmtcooptions->init();
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, _pmgmtcooptions );
      }

      sevRtn = dstcWorkSession->getMgmtCo().getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
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

E_COMMANDRETURN AdvisorTransProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************

// Why is this method overridden?  Need different implementation, or no longer
//  needed?

void AdvisorTransProcess::setCurrentListItem(
                                            const GenericInterface *rpGICaller,
                                            const BFContainerId& idList,
                                            const DString& strListItemKey
                                            )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
   DString _dstrbrokercode,_dstrbranchcode,_BrokerName,_RequestType;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorTransProcess.cpp-arc  $
 * 
 *    Rev 1.18   Mar 21 2003 17:43:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 07 2003 11:56:26   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.16   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 16:45:00   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.14   Aug 29 2002 12:54:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:24:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   27 Mar 2002 19:55:10   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.11   Sep 17 2001 16:22:54   FENGYONG
 * fix current sysdate prblem
 * 
 *    Rev 1.10   03 May 2001 14:05:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Jan 31 2001 16:05:10   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.8   Jan 23 2001 15:17:42   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.7   15 Dec 2000 12:43:34   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.6   Aug 22 2000 16:54:50   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.5   Jul 27 2000 17:28:12   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.4   Jul 05 2000 13:45:16   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.3   Jun 13 2000 09:23:02   DT24433
 * use getDateInHostFormat, cleanup
 * 
 *    Rev 1.2   Mar 30 2000 15:46:48   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:52   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 13 2000 11:26:00   FENGYONG
// Fix Bug
// 
//    Rev 1.3   Mar 10 2000 16:20:20   FENGYONG
// fix bug
// 
//    Rev 1.2   Mar 10 2000 09:56:40   FENGYONG
// For Nextkey
// 
//    Rev 1.1   Feb 29 2000 15:27:28   FENGYONG
// Add Current Date
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


