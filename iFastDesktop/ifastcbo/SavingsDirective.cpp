//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SavingsDirective.cpp
// ^AUTHOR : 
// ^DATE   : 15 Nov 2005
//
// ^CLASS    : SavingsDirective
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SavingsDirective.hpp"


#include "funddetaillist.hpp"
#include "transactionlist.hpp"
#include <ifastcbo\mgmtco.hpp>

#include <ifastdataimpl\dse_dstc0358_req.hpp>
#include <ifastdataimpl\dse_dstc0358_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>


namespace  
{
   const I_CHAR * const CLASSNAME		= I_( "SavingsDirective" );
   const I_CHAR * const CARRY_OVER		= I_( "01" );
   const I_CHAR * const MANUAL          = I_( "02" );
   const I_CHAR * const NOT_APPLICABLE  = I_( "03" );
   const I_CHAR * const NO_OVERRIDE     = I_( "04" );
}

namespace ifds
{   

}

namespace CND
{  // Conditions used
	extern const long ERR_INVALID_TIS_COST_TYPE ;	
	extern const long ERR_SAVINGS_DIRECTIVE_SUBSEQUENT_MONEY_OUT_EXISTS;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SAVINGS_DIRECTIVE;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                State Flags,                Group Flags    
   { ifds::TISType,				BFCBO::REQUIRED,			0 }, 
   { ifds::TIS,					BFCBO::REQUIRED,			0 },   
   { ifds::CostType,			BFCBO::NONE,				0 },
   { ifds::Cost ,				BFCBO::NONE,				0 },
   { ifds::EUSDOverrideVersion,	BFCBO::NONE,				0 },
   { ifds::TransId,				BFCBO::NONE,				0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//**********************************************************************************
SavingsDirective::SavingsDirective( BFAbstractCBO &parent )
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

}
//***********************************************************************************
SavingsDirective::~SavingsDirective()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************************
SEVERITY SavingsDirective::init( const DString &dstrTransid,
								 const DString &dstrAccountNum,
								 const DString &dstrFund,
								 const DString &dstrClass,
								 const DString &dstrTradeDate,
								 const DString &dstrTISType,
								 const DString &dstrTIS,
								 const DString &dstrCostType,
								 const DString &dstrCost,
								 const DString &dstrVersion,
								 const BFDataGroupId &idDataGroup,
								 const DString &dstrTrack,
                                 const DString &dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	_transId = dstrTransid;
	_accountNum = dstrAccountNum;
	_fundCode = dstrFund;
	_classCode = dstrClass;
	_tradeDate = dstrTradeDate;
	_tisType = dstrTISType;
	_tis = dstrTIS;
	_costType = dstrCostType;
	_cost = dstrCost;
	_eusdOverrideVer = dstrVersion;
 
   setFieldNoValidate (ifds::TIS, _tis, idDataGroup, false );
	setFieldNoValidate (ifds::TISType, _tisType, idDataGroup, false, true, true, false );
	setFieldNoValidate (ifds::Cost, _cost, idDataGroup, false );
	setFieldNoValidate (ifds::CostType, _costType, idDataGroup, false, true, true, false );
	setFieldNoValidate (ifds::EUSDOverrideVersion, _eusdOverrideVer, idDataGroup, false );
	setFieldNoValidate (ifds::TransId, _transId, idDataGroup, false );

	setFieldReadOnly (ifds::TIS, idDataGroup, true);
	setFieldReadOnly (ifds::TISType, idDataGroup, true);
	setFieldReadOnly (ifds::Cost, idDataGroup, true);
	setFieldReadOnly (ifds::CostType, idDataGroup, true);

	setSavingsDirectiveFields (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY SavingsDirective::setSavingsDirectiveFields(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setSavingsDirectiveFields"));

	DString costType, tisType;
	getField (ifds::CostType, costType, idDataGroup, false);
	getField (ifds::TISType, tisType, idDataGroup, false);

	FundDetailList *pFundDetailList = NULL;
   MgmtCo &mgmtCo = getMgmtCo();
   mgmtCo.getFundDetailList(pFundDetailList);

	if (pFundDetailList != NULL)
	{
		bool bSavingsDirectiveElig =  getWorkSession().hasUpdatePermission (UAF::SAVINGS_DIRECTIVE);

		if ( pFundDetailList->isInScope(_fundCode, _classCode, _tradeDate) && bSavingsDirectiveElig ) 
		{			
			setFieldReadOnly (ifds::CostType, idDataGroup, false);
			setFieldReadOnly (ifds::Cost, idDataGroup, costType != MANUAL);		
		}

		if ( pFundDetailList->isLookThru(_fundCode, _classCode, _tradeDate) && bSavingsDirectiveElig ) 
		{	
			setFieldReadOnly (ifds::TISType, idDataGroup, false);
			setFieldReadOnly (ifds::TIS, idDataGroup, tisType != MANUAL);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
void SavingsDirective::doReset(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doReset"));

	/* IN 512857 - reset to old values; setSavingsDirectiveFields resets to current/new values */

	setFieldNoValidate (ifds::TIS, _tis, idDataGroup, false );
	setFieldNoValidate (ifds::TISType, _tisType, idDataGroup, false, true, true, false );
	setFieldNoValidate (ifds::Cost, _cost, idDataGroup, false );
	setFieldNoValidate (ifds::CostType, _costType, idDataGroup, false, true, true, false );

}

//***********************************************************************************
SEVERITY SavingsDirective::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   validateEUSD(idDataGroup) ;

	return GETCURRENTHIGHESTSEVERITY();

}

//****************************************************************************
SEVERITY SavingsDirective::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	if (idField == ifds::TISType || idField == ifds::CostType)
	{
		if (strValue != MANUAL )
		{
			ADDCONDITIONFROMFILE( CND::ERR_INVALID_TIS_COST_TYPE );
		}		
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SavingsDirective::validateEUSD(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateEUSD"));
	
   DString currentBusinessDate;

   getWorkSession().getOption ( ifds::CurrBusDate, currentBusinessDate, BF::HOST, false);


	DString dstrKey = I_( "TransactionHistoryList" )
							+ _accountNum
							+ _fundCode
							+ _classCode
							+ _tradeDate
							+ currentBusinessDate;

	TransactionList *pTransactionList = dynamic_cast<TransactionList*>(BFCBO::getObject( dstrKey, idDataGroup ) );

	if ( NULL == pTransactionList )
	{
		pTransactionList = new TransactionList (*this);
		if (pTransactionList->init( _accountNum,
											_fundCode,
											_classCode,
											I_( "" ),                // NumEntry  ????????????????
											I_( "N" ),               // AllFundsMode
											NULL_STRING,             // ReqTransid        
											I_("N"),                 // UseDateFlag    
											_tradeDate,           // FromDate       
											currentBusinessDate,    // ToDate          
											I_("N"),                 // Track           
											NULL_STRING,             // PageName        
											NULL_STRING,             // NextKey         
											I_( "Y" ),               // Exclude Reversal
											I_( "PW,AW,TO" ),        // Trans Type
											I_( "1" ),               // EUSD Scope         
											I_( "TransType" )        // SearchType
				) <= WARNING )
		{
			setObject ( pTransactionList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
		}
		else
		{
			delete pTransactionList;
			pTransactionList = NULL;
		}
	}

	if ( NULL != pTransactionList )
	{
		BFObjIter iter ( *pTransactionList, 
							idDataGroup, 
							true);
		if (!iter.end())
		{
			// Subsequent money out trade already exists. Manual override is not allowed.			
			ADDCONDITIONFROMFILE( CND::ERR_SAVINGS_DIRECTIVE_SUBSEQUENT_MONEY_OUT_EXISTS );			
		}
	}
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************
SEVERITY SavingsDirective::doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{

	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

	if (idField == ifds::TISType || idField == ifds::CostType )
   {
		setSavingsDirectiveFields(idDataGroup);

	}

	return GETCURRENTHIGHESTSEVERITY();

}

//*****************************************************************************************
void SavingsDirective::clearUpdateFlags(const BFDataGroupId& idDataGroup)
{
   clearUpdatedFlags( idDataGroup );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SavingsDirective.cpp-arc  $
// 
//    Rev 1.3   Jan 20 2006 11:10:10   AGUILAAM
// IN 512857 - fixed reset functionality
// 
//    Rev 1.2   Dec 09 2005 15:49:16   porteanm
// PET 1228 FN01 - Added ERR_SAVINGS_DIRECTIVE_SUBSEQUENT_MONEY_OUT_EXISTS.
// 
//    Rev 1.1   Dec 06 2005 16:51:20   porteanm
// PET_1228_FN02: EUSD Phase 2
// 
//    Rev 1.0   Nov 29 2005 16:59:40   AGUILAAM
// Initial revision.
// 
*/