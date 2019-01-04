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
// ^FILE   : JAdvisorSummProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 24/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AdvisorSummProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jadvisorsummprocess.hpp"
#include <ifastdataimpl\dse_dstc0094_req.hpp>
#include "jadvisorsummprocessincludes.h"
#include <ifastcbo\jadvisorsumm.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JADVISORSUMM;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AdvisorSummProcess > processCreator( CMD_BPROC_JADVISORSUMM );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AdvisorSummProcess" );

   const I_CHAR *pBROKERCODE = I_( "BrokerCode" );
   const I_CHAR *pBRANCHCODE = I_( "BranchCode" );
   const I_CHAR *pSLSREP = I_( "SlsRep" );
   const I_CHAR *ADVISORSUM = I_( "AdvisorSum" );


}

namespace ADVISORSUMMLIT  //stands for account details literals
{
   const I_CHAR * const BROKERCODE = I_( "BrokerCode" );  
   const I_CHAR * const BRANCHCODE = I_( "BranchCode" );
   const I_CHAR * const SLSREP = I_( "SlsRep" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AdvisorSummProcess::AdvisorSummProcess() : 
AdvisorSummProcess::AdvisorSummProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJAdvisorSumm( NULL ),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ADVISORSUMM_LIST, true,BF::NullContainerId,true, ADVISORSUM );

   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundPercent, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::UnitValue, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundUnits, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundAmt, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundProdPercent, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundProdUnits, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::FundProdAmt, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::ValueAsAt, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::ADVISORSUMM_LIST );
   addFieldDetails( ifds::CurrTotal, IFASTBP_PROC::ADVISORSUMM_LIST );

   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
}

//******************************************************************************

AdvisorSummProcess::~AdvisorSummProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJAdvisorSumm;
   _rpChildGI = NULL;
}

bool AdvisorSummProcess::doGetData(
                                  GenericInterface * ,
                                  BFData * 
                                  ) const
{
   _pJAdvisorSumm->getMore();
   AdvisorSummProcess * _pAbsPr = const_cast < AdvisorSummProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORSUMM_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::ADVISORSUMM_LIST, _pJAdvisorSumm );
   return(true);
}

bool AdvisorSummProcess::doMoreRecordsExist(
                                           GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer 
                                           )
{
   return( _pJAdvisorSumm->doMoreRecordsExist() );
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AdvisorSummProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _BrokerCode,_BranchCode,_SlsRep;
   try
   {
      getParameter( pBROKERCODE, _BrokerCode );
      getParameter( pBRANCHCODE, _BranchCode );
      getParameter( pSLSREP, _SlsRep );
      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");
      _pJAdvisorSumm = new JAdvisorSumm( *getBFWorkSession() );

      sevRtn = _pJAdvisorSumm->init( _BrokerCode, _BranchCode, _SlsRep, dstrTrack,dstrActivity);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ADVISORSUMM_LIST, _pJAdvisorSumm );
      }

      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();
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

E_COMMANDRETURN AdvisorSummProcess::doProcess()
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorSummProcess.cpp-arc  $
 * 
 *    Rev 1.17   Mar 21 2003 17:43:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Mar 07 2003 11:56:24   PURDYECH
 * Documentation cleanup
 * 
 *    Rev 1.15   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 16:45:00   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.13   Aug 29 2002 12:54:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 18:24:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   27 Mar 2002 19:55:10   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.10   03 May 2001 14:05:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Mar 26 2001 21:59:44   YINGBAOL
 * xml support
 * 
 *    Rev 1.8   Jan 31 2001 16:05:10   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.7   Jan 23 2001 15:17:42   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.6   15 Dec 2000 12:43:34   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Aug 22 2000 16:54:48   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.4   Jul 27 2000 17:28:12   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.3   Jul 05 2000 13:45:18   VASILEAD
 * Added ShortName from TranslationList
 * 
 *    Rev 1.2   Mar 30 2000 15:46:40   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:52   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Mar 10 2000 09:56:32   FENGYONG
// For Nextkey
// 
//    Rev 1.0   Feb 25 2000 16:17:30   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 */


