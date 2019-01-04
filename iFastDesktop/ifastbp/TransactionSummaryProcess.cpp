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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TransactionSummaryProcess.cpp
// ^AUTHOR :  Yongmei Feng
// ^DATE   : 03/11/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TransactionSummaryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\fundmasterlist.hpp>
#include "transactionsummaryprocess.hpp"
#include <ifastcbo\transactionsummarylist.hpp>
#include "transactionsummaryprocessincludes.h"
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSACTION_SUMMARY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TransactionSummaryProcess > processCreator( CMD_BPROC_TRANSACTION_SUMMARY );
#include <ifastcbo\mgmtco.hpp>
namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TransactionSummaryProcess" );

}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FLongName;
}
namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

namespace TRANSSUMMARYLIT //entity search literals
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" ); 
   const I_CHAR * const FROM_DATE = I_( "FromDate" ); 
   const I_CHAR * const TO_DATE = I_( "ToDate" );
   const I_CHAR * const NEXTORPREVIOUS = I_( "NextOrPrevious" );
   const I_CHAR * const SORTORDER = I_( "SortOrder" );
   const I_CHAR * const NEXT_KEY = I_( "NextKey" );
   const I_CHAR * const FUND_CODE = I_( "FundCode" );
   const I_CHAR * const BAYCOM = I_( "Baycom" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319TransactionSummaryProcess::TransactionSummaryProcess() : 
TransactionSummaryProcess::TransactionSummaryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTransactionSummaryList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::TRANS_SUMMARY_LIST, true, BF::NullContainerId, false, I_( "TransactionSummaryList" ) );
   addContainer( IFASTBP_PROC::TRANS_SUMMARY_LIST_DETAILS, false, BF::NullContainerId, false, I_( "TransactionSummaryListDetails" ) );

// from list vw 117
   addFieldDetails( ifds::ElongName1, IFASTBP_PROC::TRANS_SUMMARY_LIST  );
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::TransId, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::TransNum, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::TradeDate, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::SettleDate, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::Settled, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::UnitPrice, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::Units, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::UnitBalance, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::TranStatus, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::SlsrepCode, IFASTBP_PROC::TRANS_SUMMARY_LIST );
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::TRANS_SUMMARY_LIST );

   addFieldDetails( ifds::TotalRecords, IFASTBP_PROC::TRANS_SUMMARY_LIST_DETAILS, SUBCLASS_PROCESS );
}

//******************************************************************************

TransactionSummaryProcess::~TransactionSummaryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pTransactionSummaryList )
   {
      delete _pTransactionSummaryList;
      _pTransactionSummaryList = NULL;
   }
   _rpChildGI = NULL;
}


//******************************************************************************

SEVERITY TransactionSummaryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      DString ShareholderNum,NextOrPrevious,SortOrder,FromDate,ToDate,FundCode,NextKey,Baycom;
      DString dstrTrack,dstrActivity;
      getParameter( TRANSSUMMARYLIT::ACCOUNT_NUM, AccountNum );
      getParameter( TRANSSUMMARYLIT::FROM_DATE, FromDate );
      getParameter( TRANSSUMMARYLIT::TO_DATE, ToDate );
      getParameter( TRANSSUMMARYLIT::NEXTORPREVIOUS, NextOrPrevious );
      getParameter( TRANSSUMMARYLIT::SORTORDER, SortOrder );
      getParameter( TRANSSUMMARYLIT::NEXT_KEY, NextKey );
      getParameter( TRANSSUMMARYLIT::FUND_CODE, FundCode );
      getParameter( TRANSSUMMARYLIT::BAYCOM, Baycom );

      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      AccountNum.stripAll();
      NextOrPrevious.stripAll();
      SortOrder.stripAll();
      NextKey.stripAll();
      FundCode.stripAll();
      if( FundCode == I_( "ALL" ) )
         FundCode = NULL_STRING;

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      _pTransactionSummaryList = new TransactionSummaryList( *dstcWorkSession );

      if( NextOrPrevious == NULL_STRING )
         NextOrPrevious = I_( "Y" );

      if( SortOrder == NULL_STRING )
         SortOrder = I_( "D" );

      sevRtn = _pTransactionSummaryList->init( AccountNum,Baycom,
                                               FromDate, ToDate, NextOrPrevious, SortOrder, FundCode, NextKey, dstrTrack, dstrActivity );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANS_SUMMARY_LIST, _pTransactionSummaryList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN TransactionSummaryProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;

   return(rtn);
}

void TransactionSummaryProcess::doGetField(
                                          const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          DString &strValueOut,
                                          bool bFormatted
                                          ) const
{  

   if( idField == ifds::TotalRecords && idContainer == IFASTBP_PROC::TRANS_SUMMARY_LIST_DETAILS )
   {
      DString strTotalRecords;
      _pTransactionSummaryList->getField( ifds::TotalRecords, strTotalRecords, BF::HOST, true );
      strValueOut = strTotalRecords.strip();
   }
   if( idField == ifds::ElongName1)
   {
	   DString dstLocaleStr = ClientLocaleContext::get().getLocale();
	   if(dstLocaleStr != I_("frCA"))
			_pTransactionSummaryList->getField( ifds::ElongName1, strValueOut, BF::HOST, true );
	   else
	   {
		    DString strFundCode = NULL_STRING;
		    _pTransactionSummaryList->getField( ifds::FundCode, strFundCode, BF::HOST, true );
		   	FundMasterList *pFundMasterList;
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo().getFundMasterList( pFundMasterList );
            if( pFundMasterList )
            {
				   pFundMasterList->getFundName (strFundCode, ifds::FLongName, strValueOut);
            }
	   }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionSummaryProcess.cpp-arc  $
// 
//    Rev 1.15   Nov 17 2004 15:19:06   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.14   Mar 21 2003 17:49:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Mar 06 2003 09:50:14   FENGYONG
// french fundname
// 
//    Rev 1.12   Feb 12 2003 12:50:30   FENGYONG
// pts ticket: 10013444
// 
//    Rev 1.11   Oct 09 2002 23:53:42   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Aug 29 2002 16:45:18   SMITHDAV
// Condition split.
// 
//    Rev 1.9   Aug 29 2002 12:54:44   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   22 May 2002 18:25:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   Apr 26 2002 10:43:16   FENGYONG
// Add Baycom as a request field
// 
//    Rev 1.6   27 Mar 2002 19:56:16   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.5   Mar 20 2002 10:46:40   FENGYONG
// Add Baycom
// 
//    Rev 1.4   Aug 16 2001 17:43:10   VASILEAD
// Added tracking support
// 
//    Rev 1.3   11 May 2001 16:33:38   YINGZ
// code sync up
// 
//    Rev 1.2   Apr 27 2001 13:44:48   VASILEAD
// Added FundCode
// 
//    Rev 1.1   Mar 18 2001 18:18:12   VASILEAD
// Fixes for UAT release
 * 
 *    Rev 1.20   Feb 28 2001 11:24:02   VASILEAD
 * Added string descriptions for containers
 * 
 */
