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
// ^FILE   : JAdvisorInfoProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 18/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AdvisorInfoProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jadvisorinfoprocess.hpp"
#include "jadvisorinfoprocessincludes.h"
#include <ifastcbo\advisorlist.hpp>
#include <ifastcbo\jbrokerlist.hpp>
#include <ifastcbo\jbranchlist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstc0092_req.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADVISORINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AdvisorInfoProcess > processCreator( CMD_BPROC_ADVISORINFO );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AdvisorInfoProcess" );

   const I_CHAR *pBROKERCODE = I_( "BrokerCode" );
   const I_CHAR *pBRANCHCODE = I_( "BranchCode" );
   const I_CHAR *pSLSREP = I_( "Slsrep" );
   const I_CHAR *ADVISORINFO = I_( "SalesRep" );

}

namespace ADVISORINFOLIT  //stands for account details literals
{
   const I_CHAR * const BROKERCODE = I_( "BrokerCode" );  
   const I_CHAR * const BRANCHCODE = I_( "BranchCode" );
   const I_CHAR * const SLSREP = I_( "SlsrRep" );
   const I_CHAR * const ALLRESULT = I_( "Allresult" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AdvisorInfoProcess::AdvisorInfoProcess() : 
AdvisorInfoProcess::AdvisorInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pAdvisorList( NULL ),
_pJBrokerList( NULL ),
_pJBranchList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ADVISORINFO_LIST, true,BF::NullContainerId,true, ADVISORINFO );
   addContainer( IFASTBP_PROC::BROKER_LIST, true );
   addContainer( IFASTBP_PROC::BRANCH_LIST, true );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );

   addFieldDetails( ifds::CurrBusDate, IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::Slsrep, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrLine1, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrLine2, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrLine3, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrLine4, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrLine5, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::AddrCntryCode, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PhoneNumber, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::StopDate, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::TrailEligible, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PayType, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PayTypeDesc, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::CurrencyName, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PayFreq, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PayFreqDesc, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsrepType, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsrepTypeDesc, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SegLicenseProvList, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::NewBusiness, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::PostalCode, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::Email, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsRepCntry, IFASTBP_PROC::ADVISORINFO_LIST );
   addFieldDetails( ifds::SlsRepArea, IFASTBP_PROC::ADVISORINFO_LIST );
//   addFieldDetails( DBR::BrokerName, BROKER_LIST );
//   addFieldDetails( DBR::BranchName, BRANCH_LIST );
}

//******************************************************************************

AdvisorInfoProcess::~AdvisorInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   //delete _pAdvisorList;
   //if(_pJBrokerList) { delete _pJBrokerList; _pJBrokerList = NULL;}
   //if(_pJBranchList) { delete _pJBranchList; _pJBranchList = NULL;}

   _rpChildGI = NULL;
}

bool AdvisorInfoProcess::doGetData(
                                  GenericInterface * ,
                                  BFData * 
                                  ) const
{
   _pAdvisorList->getMore();
   AdvisorInfoProcess * _pAbsPr = const_cast < AdvisorInfoProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORINFO_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORINFO_LIST, _pAdvisorList );
   return(true);
}

bool AdvisorInfoProcess::doMoreRecordsExist(
                                           GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer 
                                           )
{
   return( _pAdvisorList->doMoreRecordsExist() );
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AdvisorInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _BrokerCode,_BranchCode,_SlsRep,_Allresult;
   DString dstrTrack,dstrActivity;
   try
   {
      getParameter( pBROKERCODE, _BrokerCode );
      getParameter( pBRANCHCODE, _BranchCode );
      getParameter( pSLSREP, _SlsRep );
      getParameter( ADVISORINFOLIT::ALLRESULT, _Allresult );


      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getAdvisorList( getDataGroupId(), _pAdvisorList, _BrokerCode, _BranchCode, _SlsRep, _Allresult, dstrTrack, dstrActivity);


      //_pAdvisorList = new AdvisorList( getBFWorkSession() );

      //sevRtn = _pAdvisorList->init( _BrokerCode, _BranchCode, _SlsRep,
      //	_Allresult,dstrTrack,dstrActivity);

      if( WARNING >= sevRtn )
      {
         //register list with base
         setContainer( IFASTBP_PROC::ADVISORINFO_LIST, _pAdvisorList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      MgmtCoOptions *pMgmtCoOption;
      pMgmtCoOption = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCoOptions();

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, pMgmtCoOption );
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

E_COMMANDRETURN AdvisorInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

void AdvisorInfoProcess::setCurrentListItem(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idList,
                                           const DString& strListItemKey
                                           )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
}

void AdvisorInfoProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );
/*   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->popCommitConditions( MYFRAME() );
   if ( GETCURRENTHIGHESTSEVERITY() > WARNING )
   {
      bSuccessFlag = false;      
   }
*/
}
//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorInfoProcess.cpp-arc  $
 * 
 *    Rev 1.23   Mar 21 2003 17:42:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.22   Mar 07 2003 11:56:20   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.21   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.20   Aug 29 2002 16:45:00   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.19   22 May 2002 18:24:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:55:10   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   Feb 22 2002 13:46:58   FENGYONG
 * Add slsrepcntry and slsreparea
 * 
 *    Rev 1.16   Jan 17 2002 14:57:06   FENGYONG
 * make name consistent
 * 
 *    Rev 1.15   Jan 04 2002 17:39:40   FENGYONG
 * can not double delete
 * 
 *    Rev 1.14   Jan 04 2002 12:16:14   FENGYONG
 * change getadvisorlist from worksession
 * 
 *    Rev 1.13   03 May 2001 14:05:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.12   Mar 26 2001 21:59:42   YINGBAOL
 * xml support
 * 
 *    Rev 1.11   Jan 31 2001 16:05:10   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.10   Jan 23 2001 15:17:42   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.9   Jan 17 2001 12:08:14   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.8   15 Dec 2000 12:43:34   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.7   Nov 17 2000 14:40:52   FENGYONG
 * change pname and request name for remove DE
 * 
 *    Rev 1.6   Sep 07 2000 16:14:58   FENGYONG
 * add brokername and branch name to #92
 * 
 *    Rev 1.5   Sep 06 2000 11:47:14   YINGZ
 * get MgmtCoOptions from MgmtCo
 * 
 *    Rev 1.4   Aug 31 2000 11:10:28   FENGYONG
 * set list to NULL when DB not available
 * 
 *    Rev 1.3   Aug 23 2000 12:29:30   FENGYONG
 * Add list
 * 
 *    Rev 1.2   Mar 30 2000 15:46:32   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:52   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 21 2000 14:19:22   FENGYONG
// fix bug
// 
//    Rev 1.3   Mar 10 2000 09:56:24   FENGYONG
// For Nextkey
// 
//    Rev 1.2   Mar 08 2000 14:49:20   FENGYONG
// change fields
// 
//    Rev 1.1   Feb 29 2000 15:27:08   FENGYONG
// Filter fields
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


