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
// ^FILE   : JFundListProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 22/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundListProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jfundlistprocess.hpp"
#include <ifastdataimpl\dse_dstc0023_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0136_vw.hpp>
#include "jfundlistprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JFUNDLIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundListProcess > processCreator( CMD_BPROC_JFUNDLIST );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundListProcess" );
}

namespace FUNDLISTLIT  //stands for account details literals
{
   const I_CHAR * const FUNDCODE = I_( "TXFundCode" );  
   const I_CHAR * const CLASSCODE = I_( "TXClassCode" );  
   const I_CHAR * const FROMDATE= I_( "FromDate" ); 
   const I_CHAR * const TODATE= I_( "ToDate" ); 
   const I_CHAR * const PREVDATEPRESSED= I_( "PrevDatePressed" );
   const I_CHAR * const NEXTDATEPRESSED= I_( "NextDatePressed" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

using namespace FUNDLISTLIT;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundListProcess::FundListProcess() : 
FundListProcess::FundListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundList( NULL ),
_pFundDetailList(NULL),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUND_LIST, true );
   addContainer( IFASTBP_PROC::FUNDSRCH_LIST, true );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDSRCH_LIST );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::ValueAsAt, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUND_LIST );   
   addFieldDetails( ifds::UnitValue, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::UnAllocIncome, IFASTBP_PROC::FUND_LIST );
   addFieldDetails( ifds::ChgFactor, IFASTBP_PROC::FUND_LIST );

   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
}

//******************************************************************************

FundListProcess::~FundListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pFundList;
   _pFundList = NULL;
   //delete _pTranslationList;
   _pTranslationList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************

bool FundListProcess::doGetData(
                               GenericInterface * ,
                               BFData * 
                               ) const
{
   _pFundList->search(false);
   FundListProcess * _pAbsPr = const_cast < FundListProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::FUND_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::FUND_LIST, _pFundList );
   return(true);
}

//******************************************************************************

bool FundListProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer 
                                        )
{
   return( _pFundList->doMoreRecordsExist() );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _FundCode,_ClassCode, _pPrevDatePressed,_pNextDatePressed;
   DString fromDate;
   DString toDate;
   try
   {
      getParameter( FUNDCODE, _FundCode );
      getParameter( CLASSCODE, _ClassCode );
      getParameter( FROMDATE, fromDate );
      getParameter( TODATE, toDate );
      getParameter( PREVDATEPRESSED, _pPrevDatePressed );
      getParameter( NEXTDATEPRESSED, _pNextDatePressed );

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();

      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSRCH_LIST, _pFundDetailList );
      }

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
      }

      MgmtCoOptions*pMgmtCoOptions;
      sevRtn = mgmtCoOut.getMgmtCoOptions( pMgmtCoOptions );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, pMgmtCoOptions );
      }

      DString currdate;
      pMgmtCoOptions->getField( ifds::CurrBusDate, currdate, getDataGroupId(), false );

      if( _pPrevDatePressed == NULL_STRING && currdate == fromDate && currdate == toDate )
         _pPrevDatePressed = I_( "Y" );
      else
         _pPrevDatePressed = I_( "N" );
      if( _pNextDatePressed == NULL_STRING )
      {
         _pNextDatePressed = I_( "N" );
      }

      if( fromDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( fromDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, getDataGroupId() );
      }
      if( toDate == NULL_STRING )
      {
         dstcWorkSession->getDateInHostFormat( toDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, getDataGroupId() );
      }

      _pFundList = new FundList( *dstcWorkSession );
      sevRtn = _pFundList->init( _FundCode, _ClassCode,
                                 fromDate, toDate, _pPrevDatePressed, _pNextDatePressed,dstrTrack,dstrActivity );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUND_LIST, _pFundList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSRCH_LIST, _pFundDetailList );
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

E_COMMANDRETURN FundListProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundListProcess.cpp-arc  $
 * 
 *    Rev 1.25   Mar 21 2003 17:43:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.24   Mar 09 2003 15:55:54   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.23   Mar 07 2003 11:56:52   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.22   Oct 09 2002 23:53:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.21   Aug 29 2002 16:45:02   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.20   Aug 29 2002 12:54:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   22 May 2002 18:24:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:55:14   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   Sep 17 2001 16:23:18   FENGYONG
 * fix current sysdate prblem
 * 
 *    Rev 1.16   03 May 2001 14:05:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.15   Jan 31 2001 16:05:26   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.14   Jan 23 2001 15:17:46   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.13   Jan 17 2001 12:08:14   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.12   15 Dec 2000 12:43:38   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.11   Dec 11 2000 11:53:58   VASILEAD
 * Fixed the fund prices list for a range date bug
 * 
 *    Rev 1.10   Nov 17 2000 14:40:52   FENGYONG
 * change pname and request name for remove DE
 * 
 *    Rev 1.9   Nov 03 2000 11:31:44   YINGBAOL
 * BFBase change sync.
 * 
 *    Rev 1.8   Aug 22 2000 16:54:50   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.7   Aug 03 2000 14:41:54   VASILEAD
 * Added tracking support to VerifConf
 * 
 *    Rev 1.6   Jul 27 2000 17:28:12   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.5   Jul 05 2000 13:45:08   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.4   Jun 28 2000 12:01:44   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.3   Jun 13 2000 09:04:12   DT24433
 * use getDateInHostFormat, cleanup
 * 
 *    Rev 1.2   Mar 30 2000 15:47:24   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:54   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 23 2000 11:58:44   FENGYONG
// change default value
// 
//    Rev 1.3   Mar 10 2000 16:19:02   FENGYONG
// fix bug
// 
//    Rev 1.2   Mar 10 2000 09:57:22   FENGYONG
// For Nextkey
// 
//    Rev 1.1   Mar 06 2000 15:49:32   FENGYONG
// Add FundCode & ClassCode
// 
//    Rev 1.0   Feb 25 2000 16:17:42   FENGYONG
// Initial revision.
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


