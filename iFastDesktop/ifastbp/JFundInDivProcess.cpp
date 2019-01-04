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
// ^FILE   : JFundInDivProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 25/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundInDivProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jfundindivprocess.hpp"
#include <ifastdataimpl\dse_dstc0104_req.hpp>
#include "jfundindivprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\jfundindiv.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JFUNDINDIV;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundInDivProcess > processCreator( CMD_BPROC_JFUNDINDIV );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundInDivProcess" );
}

namespace FUNDINDIVLIT  //stands for account details literals
{
   const I_CHAR * const FUNDCODE = I_( "TXFundCode" );  
   const I_CHAR * const CLASSCODE = I_( "TXClassCode" );  
   const I_CHAR * const FROMDATE= I_( "FromDate" ); 
   const I_CHAR * const TODATE= I_( "ToDate" ); 
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

using namespace FUNDINDIVLIT;

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundInDivProcess::FundInDivProcess() : 
FundInDivProcess::FundInDivProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJFundInDiv( NULL ),
_pFundDetailList(NULL),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUNDINDIV_LIST, true );
   addContainer( IFASTBP_PROC::FUNDSRCH_LIST, true );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDSRCH_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDSRCH_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDINDIV_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDINDIV_LIST );
   addFieldDetails( ifds::RecordDate, IFASTBP_PROC::FUNDINDIV_LIST );   
   addFieldDetails( ifds::Currency, IFASTBP_PROC::FUNDINDIV_LIST );   
   addFieldDetails( ifds::DividendRate, IFASTBP_PROC::FUNDINDIV_LIST );   
   addFieldDetails( ifds::ReinvestPrice, IFASTBP_PROC::FUNDINDIV_LIST );   
   addFieldDetails( ifds::PayDate, IFASTBP_PROC::FUNDINDIV_LIST );   

   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
}

//******************************************************************************

FundInDivProcess::~FundInDivProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJFundInDiv;
   _pJFundInDiv = NULL;
   //delete _pTranslationList;
   _pTranslationList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************

bool FundInDivProcess::doGetData(
                                GenericInterface * ,
                                BFData * 
                                ) const
{
   _pJFundInDiv->search(false);
   FundInDivProcess * _pAbsPr = const_cast < FundInDivProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::FUNDINDIV_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::FUNDINDIV_LIST, _pJFundInDiv );
   return(true);
}

//******************************************************************************

bool FundInDivProcess::doMoreRecordsExist(
                                         GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer 
                                         )
{
   return( _pJFundInDiv->doMoreRecordsExist() );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundInDivProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _FundCode,_ClassCode;
   DString fromDate;
   DString toDate;

   try
   {
      getParameter( FUNDCODE, _FundCode );
      getParameter( CLASSCODE, _ClassCode );
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
      _pJFundInDiv = new JFundInDiv( *getBFWorkSession() );
      sevRtn = _pJFundInDiv->init( _FundCode, _ClassCode, fromDate, toDate,dstrTrack, dstrActivity);
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDINDIV_LIST, _pJFundInDiv );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      MgmtCo &mgmtCoOut =dstcWorkSession->getMgmtCo();
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

E_COMMANDRETURN FundInDivProcess::doProcess()
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundInDivProcess.cpp-arc  $
 * 
 *    Rev 1.22   Mar 21 2003 17:43:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Mar 07 2003 11:56:48   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.20   Oct 09 2002 23:53:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   Aug 29 2002 16:45:02   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.18   Aug 29 2002 12:54:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.17   22 May 2002 18:24:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   27 Mar 2002 19:55:14   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.15   Sep 17 2001 16:23:12   FENGYONG
 * fix current sysdate prblem
 * 
 *    Rev 1.14   03 May 2001 14:05:32   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.13   Jan 31 2001 16:05:26   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.12   Jan 23 2001 15:17:46   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.11   15 Dec 2000 12:43:36   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
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
 *    Rev 1.5   Jul 05 2000 13:45:10   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.4   Jun 28 2000 12:01:44   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.3   Jun 13 2000 09:10:04   DT24433
 * use getDateInHostFormat, cleanup
 * 
 *    Rev 1.2   Mar 30 2000 15:47:18   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:54   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.3   Mar 10 2000 09:57:14   FENGYONG
// For Nextkey
// 
//    Rev 1.2   Mar 08 2000 14:49:00   FENGYONG
// change fields
// 
//    Rev 1.1   Feb 29 2000 15:27:44   FENGYONG
// Filter fileds
// 
// Initial revision.
 * 
 */


