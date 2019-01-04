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
// ^FILE   : JFundSrchProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundSrchProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jfundsrchprocess.hpp"
#include <ifastdataimpl\dse_dstc0056_req.hpp>
#include <ifastdataimpl\dse_dstc0136_vw.hpp>
#include "jfundsrchprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDSRCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundSrchProcess > processCreator( CMD_BPROC_FUNDSRCH );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundSrchProcess" );
}

namespace FUNDSRCHLIT  //stands for account details literals
{
   const I_CHAR * const FUND_CODE = I_( "TXFundCode" ); 
   const I_CHAR * const CLASS_CODE = I_( "TXClassCode" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundSrchProcess::FundSrchProcess() : 
FundSrchProcess::FundSrchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundDetailList( NULL ),
_pmgmtcooptions(NULL),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUNDSRCH_LIST, true );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassE, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassF, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::AdditionalDays, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinInitPurAmt, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinSubPurAmt, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinInitRedAmt, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinSubRedAmt, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinPAC, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinSWP, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinFndClsBal, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::MinAcctBal, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::StopPurchase, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::StopRed, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::StopXferIn, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::StopXferOut, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::OverrideDSCAllow, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::FixedPrice, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::FixedRate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::CurrencyName, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::LastValDate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::LastDivDate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::CusipNum, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::RSPflag, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::RIFflag, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::StopDate, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::LoadType, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Domestic, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::WireElig, IFASTBP_PROC::FUNDSRCH_LIST );

   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails( ifds::G1G2TrackType, IFASTBP_PROC::FUNDSRCH_LIST );
}

//******************************************************************************

FundSrchProcess::~FundSrchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   //delete _pFundDetailList;
   //delete _pmgmtcooptions;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundSrchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();

      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSRCH_LIST, _pFundDetailList );
      }

      sevRtn = mgmtCoOut.getMgmtCoOptions( _pmgmtcooptions );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, _pmgmtcooptions );
      }

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
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

//******************************************************************************

E_COMMANDRETURN FundSrchProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundSrchProcess.cpp-arc  $
 * 
 *    Rev 1.18   Mar 21 2003 17:44:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 11 2003 13:49:54   PURDYECH
 * Fixes to help the DataGroupId source code converters work more smoothly.
 * 
 *    Rev 1.16   Oct 09 2002 23:53:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 16:45:04   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.14   Aug 29 2002 12:54:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:24:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   27 Mar 2002 19:55:14   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.11   03 May 2001 14:05:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Jan 23 2001 15:17:48   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.9   Jan 17 2001 12:08:12   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.8   15 Dec 2000 12:43:42   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.7   Nov 17 2000 14:40:54   FENGYONG
 * change pname and request name for remove DE
 * 
 *    Rev 1.6   Aug 22 2000 16:54:52   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.5   Jul 27 2000 17:28:14   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.4   Jul 26 2000 11:45:50   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.3   Jun 28 2000 12:01:46   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.2   Mar 30 2000 15:47:36   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:56   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 23 2000 11:44:24   FENGYONG
// fix
// 
//    Rev 1.3   Mar 13 2000 11:26:12   FENGYONG
// Fix Bug
// 
//    Rev 1.2   Mar 10 2000 16:18:48   FENGYONG
// fix bug
// 
//    Rev 1.1   Feb 29 2000 15:28:06   FENGYONG
// Add Current Date
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


