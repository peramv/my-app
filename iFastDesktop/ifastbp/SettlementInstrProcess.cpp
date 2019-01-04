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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : SettlementInstrProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SettlementInstrProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mfcaninterprocparam.hpp"
#include "SettlementInstrProcess.hpp"
#include "SettlementInstrProcessincludes.h"

#include <ifastcbo\acctsettlementinstrlist.hpp>
#include <ifastcbo\fundmgmtsettlementinstrlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\SysLvlSettlementInstr.hpp>
#include <ifastcbo\SysLvlSettlementInstrList.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>



namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ATLOC;
   extern CLASS_IMPORT I_CHAR * const ATSET;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
	extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "SettlementInstrProcess" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************
SettlementInstrProcess::SettlementInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ),
_accountNum (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
	addContainer( IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, true,  BF::NullContainerId, true, I_("FundMgmtSettlementInstructionList") );
	addContainer( IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST,    true,  BF::NullContainerId, true, I_("SettlementInstructionList") );
   
	/******************Fund Management Settlement Instrcutions List**************************************/
   // Fund Management Settlement Instructions List	
	//addSubstituteList(ifds::FundMgmtSettleInstrHeadingSet );	
	//addSubstituteList(ifds::SettlementInstrHeadingSet );	

//	addFieldDetails( ifds::FundMgmtSettleInstrHeadingSet, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
	addFieldDetails( ifds::SettleLocationCode, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
	addFieldDetails( ifds::SettleLocationDesc, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );	
	addFieldDetails( ifds::SettleAccountNum, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
	addFieldDetails( ifds::Default, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
    addFieldDetails( ifds::InternalSettlementAccount, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );



	// Add Clearing Method

   // Admin/Dates details
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
   addFieldDetails( ifds::Username,    IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
   addFieldDetails( ifds::ModDate,     IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
   addFieldDetails( ifds::ModUser,     IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
   addFieldDetails( ifds::RecId,       IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );

	/******************Settlement Instructions List*******************************************************/
	addFieldDetails( ifds::SettlementInstrCode,         IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
	addFieldDetails( ifds::DeliveryTo,					    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
	addFieldDetails( ifds::ForAccount,                  IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
	addFieldDetails( ifds::InFavourOf,                  IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
 
    addFieldDetails( ifds::CSDLocation,                  IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
    addFieldDetails( ifds::CSDAcctNum,                  IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
	
	addFieldDetails( ifds::DefaultSettlementInstr,      IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::ProcessDate,                IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::Username,                   IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::ModDate,                    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::ModUser,                    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::SettlementInstrRid,         IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );

   addFieldDetails( ifds::EffectiveDate,              IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::StopDate,                   IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::AcctClearingMethod,         IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::CashMsgType,                IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::IntermediaryBank,           IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::ReceivingBank,              IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::Beneficiary,                IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
   addFieldDetails( ifds::SpecialInstructions,        IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );

}

//******************************************************************************
SettlementInstrProcess::~SettlementInstrProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY SettlementInstrProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   getParameter (I_("AccountNum"), _accountNum);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool SettlementInstrProcess::doModelessChildComplete( const Command &cmd )
{
	return true;
}


//******************************************************************************
bool SettlementInstrProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI );
      if( isValidModelessInterface( m_rpChildGI ) )
      {
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( bRtn );
}

//******************************************************************************
E_COMMANDRETURN SettlementInstrProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   return( rtn );
}


//******************************************************************************
void* SettlementInstrProcess::getPtrForContainer( const BFContainerId& idContainer, 
												  const BFDataGroupId& idDataGroup 
												)
{
   void *ptr = NULL;

   return(ptr);
}

//******************************************************************************
bool SettlementInstrProcess::doOk(GenericInterface *rpGICaller)
{
   return( true );
}

//******************************************************************************
SEVERITY SettlementInstrProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SettlementInstrProcess::getHistoricalParameters(	const BFContainerId& idContainer, 
															BFFieldId &recordIdField, 
															DString& tableId, 
															DString& dstrKey) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );
   
   if ( idContainer == IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST )
   {
      recordIdField = ifds::RecId;
      tableId = AUDITTYPE::ATLOC;
      dstrKey = NULL_STRING;
   }
	else if ( idContainer == IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST )
   {
      recordIdField = ifds::SettlementInstrRid;
      tableId = AUDITTYPE::ATSET;
      dstrKey = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY SettlementInstrProcess::getHistoricalParameters(	const BFContainerId& idContainer, 
															HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/SettlementInstrProcess.cpp-arc  $
// 
//    Rev 1.7   Nov 07 2007 11:58:06   daechach
// PET 5614 FN 01 - Acct Level Override for Clearing Settle Method
// 
//    Rev 1.6   May 04 2007 13:41:20   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.5   Dec 09 2004 15:31:48   vadeanum
// PET1117_FN21: settlement instructions - added doValidateAll().
// 
//    Rev 1.4   Dec 01 2004 14:49:44   aguilaam
// PET1117_FN21: settlement instructions -admin fields
// 
//    Rev 1.3   Dec 01 2004 13:48:30   aguilaam
// PET1117_FN21: changed ATLOC to ATSET for settlement instructions (ClearingSettleInstr); ATLOC for fund mgmt settlement instructions
// 
//    Rev 1.2   Nov 26 2004 16:56:16   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.1   Nov 19 2004 17:32:16   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0   Oct 13 2004 15:17:38   VADEANUM
// Initial revision.
//
