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
// ^FILE   : SystematicFeeProcess.cpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : Nov 20, 1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SystematicFeeProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "systematicfeeprocess.hpp"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include "systematicfeeprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SYSTEMATIC_FEE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SYSTEMATIC_FEE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SystematicFeeProcess > processCreator( CMD_BPROC_SYSTEMATIC_FEE );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace
{
   // Trace literals
   const I_CHAR *        CLASSNAME      = I_("SystematicFeeProcess");
   const I_CHAR * const  PERFORMSEARCH  = I_("performSearch");
}

namespace SYSTEMATICFEELIT
{
   const I_CHAR * const ACCOUNT_NUM    = I_("AccountNum");
   const I_CHAR * const LIST_KEY       = I_("ListKey");
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319SystematicFeeProcess::SystematicFeeProcess() : 
SystematicFeeProcess::SystematicFeeProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMFAccount( NULL ),
_pSystematicList( NULL ), 
_rpChildGI( NULL ),
_pFundDetailList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer(IFASTBP_PROC::SYSTEMATIC_LIST,    true, BF::NullContainerId, true);
   addContainer(IFASTBP_PROC::FUND_DETAIL_LIST,   true);

   //for parameter transfer purpose
   addFieldDetails(ifds::AccountNum,                         BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::NullFieldId,                        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::ShrNum,                             BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICFEELIT::PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails(ifds::FundCode,  IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails(ifds::Currency,  IFASTBP_PROC::FUND_DETAIL_LIST );

   //Systematic List
   addFieldDetails( ifds::TransType,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PACSWPId,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankDetlVer,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BrokerCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BranchCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SalesRepCode,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BrokerName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BranchName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SlsrepName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Amount,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AmountType,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AmountTypeDesc,  IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::GrossOrNet,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Fee,             IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FlatPercent,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FeeCurrency,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FeeCurrDesc,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeAmt,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeCurr,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeCurrDesc,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayType,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayTypeDesc,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::InstCode,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SwiftCode,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::RefNumber,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransitNo,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctNum,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctName,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SourceOfBankAcct,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctCurrency,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankCurrDesc,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctType,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctTypeDesc,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SrcOfFund,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SrcOFundDesc,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::January,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::February,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::March,           IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::April,           IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::May,             IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::June,            IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::July,            IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::August,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::September,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::October,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::November,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::December,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EndOfMonth,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::DayOfWeek,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::LastProcessDate, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrCode,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::StatusCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ProcessDate,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ModDate,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::StopDate,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Username,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ModUser,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine1,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine2,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine3,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine4,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine5,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PostalCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::InstName,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SlsrepAltName,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FundCode,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ClassCode,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayReason1,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayReason2,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FundToCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ClassToCode,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AccountTo,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BELFee,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchUser,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchName,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchTrace,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchDate,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransferType,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Frequency,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FlatPercentDesc, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FrequencyDesc,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransTypeDesc,   IFASTBP_PROC::SYSTEMATIC_LIST );
}

//******************************************************************************

SystematicFeeProcess::~SystematicFeeProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void SystematicFeeProcess::doGetField(
                                     const GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idField,
                                     const BFDataGroupId& idDataGroup,
                                     DString &strValueOut,
                                     bool bFormatted
                                     ) const
{
   if( idField == ifds::AccountNum )
   {
      strValueOut = _dstrAccountNum;
   }
   else if( idField == ifds::NullFieldId )                  //current systematic list key
   {
      strValueOut = _dstrSystematicListKey;
   }
   else if( idField == ifds::ShrNum )
   {
      strValueOut = _dstrShrNum;
   }
   else if( idField == SYSTEMATICFEELIT::PRIMARY_ACCOUNT_OWNER )
   {
      strValueOut = _dstrEntityName;
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************

SEVERITY SystematicFeeProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      MgmtCo &mgmtCoOut = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();
      sevRtn = mgmtCoOut.getFundDetailList(_pFundDetailList);
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer(IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList);

      getParameter(SYSTEMATICFEELIT::ACCOUNT_NUM, _dstrAccountNum);
      //Get the current systematic list key passed by the Systematic Screen
      getParameter(SYSTEMATICFEELIT::LIST_KEY, _dstrSystematicListKey);

      sevRtn = performSearch( this, BF::AllContainerIds, SEARCH_START );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(sevRtn);
}

//******************************************************************************

bool SystematicFeeProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_SYSTEMATIC_FEE);
}

//******************************************************************************

bool SystematicFeeProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
   // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;
   DString dstrAccountNum, dstrTransType;

   getParameter(SYSTEMATICFEELIT::ACCOUNT_NUM, dstrAccountNum);
   getParameter(SYSTEMATICFEELIT::LIST_KEY, _dstrSystematicListKey);
   if( dstrAccountNum != _dstrAccountNum )
   {
      _dstrAccountNum = dstrAccountNum;
      performSearch(this, BF::AllContainerIds, SEARCH_START);
   }

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      setParameter(SYSTEMATICFEELIT::ACCOUNT_NUM,        _dstrAccountNum);
      setParameter(SYSTEMATICFEELIT::LIST_KEY,           _dstrSystematicListKey);
      bRtn = _rpChildGI->refresh(this, NULL);
      bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN SystematicFeeProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(SYSTEMATICFEELIT::ACCOUNT_NUM,  _dstrAccountNum);
      setParameter(SYSTEMATICFEELIT::LIST_KEY,     _dstrSystematicListKey);
      rtn = invokeCommand(this, CMD_GUI_SYSTEMATIC_FEE, getProcessType(), isModal(), &_rpChildGI);
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}



//******************************************************************************

SEVERITY SystematicFeeProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                              E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
   SEVERITY sevRtn = SEVERE_ERROR;
   const BFDataGroupId& idDataGroup = getDataGroupId();

   /*
    if (_rpChildGI)
       idDataGroup = getGroupID(_rpChildGI);
    else
       idDataGroup = getDataGroupId();
     */

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount ); 
      if( sevRtn > WARNING )
         return(sevRtn);

      _pMFAccount->getField(ifds::ShrNum, _dstrShrNum, idDataGroup, false);
      dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), _dstrAccountNum, _dstrEntityName );

      sevRtn = _pMFAccount->getSystematicList( _pSystematicList, idDataGroup );
      if( sevRtn <= WARNING )
         setContainer( IFASTBP_PROC::SYSTEMATIC_LIST, _pSystematicList  );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************

SEVERITY SystematicFeeProcess::doValidateAll(BFAbstractCBO *rpWSD,const BFDataGroupId& idDataGroup)
{
   return(NO_CONDITION);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SystematicFeeProcess.cpp-arc  $
 * 
 *    Rev 1.16   Feb 14 2006 14:11:56   porteanm
 * Incident 543959 - Two lines of instructions (Pay Reason).
 * 
 *    Rev 1.15   Mar 21 2003 17:48:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Mar 09 2003 15:56:42   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.13   Jan 18 2003 17:13:20   WINNIE
 * Correct field name for batch: sync up update and inquiry view
 * 
 *    Rev 1.12   Oct 09 2002 23:53:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 16:45:16   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.10   Aug 29 2002 12:54:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jun 03 2002 16:55:36   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.8   22 May 2002 18:25:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:55:42   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   Jun 07 2001 11:24:36   YINGBAOL
 * remove doRefresh
 * 
 *    Rev 1.5   15 May 2001 15:38:56   YINGZ
 * data group id clean up
 * 
 *    Rev 1.4   03 May 2001 14:05:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   15 Dec 2000 12:43:54   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.2   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Mar 16 2000 12:02:02   DT24433
 * added revision log, removed unused headers and subsitut list
 * 
 */
