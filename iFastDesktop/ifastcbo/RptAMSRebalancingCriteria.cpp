//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : RptAMSRebalancingCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RptAMSRebalancingCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "rptamsrebalancingcriteria.hpp"

#include "amslmtoverridelist.hpp"
#include "amsmstrlist.hpp"
#include "amsmstrinfo.hpp"
#include "errmsgruleslist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "rptamsrebalancingcriterialist.hpp"


#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0223_req.hpp>
#include <ifastdataimpl\dse_dstc0223_vw.hpp>
#include <ifastdataimpl\dse_dstc0297_req.hpp>
#include <ifastdataimpl\dse_dstc0297_vw.hpp>


namespace
{
   const I_CHAR * const CLASSNAME = I_( "RptAMSRebalancingCriteria" );
   const I_CHAR * const FIX_RECORD = I_( "F" );
   const I_CHAR * const REPEAT_RECORD = I_( "R" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const REBALANCE = I_( "RB" );
   const I_CHAR * const CLIENT = I_( "1" );
   const I_CHAR * const AMS_REBALANCE = I_("IFAST.AMSREBAL");
   const I_CHAR * const AMS_HYPOCALC_REBALANCE = I_("IFAST.AMSHYPOCALCREBAL");
}

namespace CND
{
	extern const long ERR_INVALID_AMS_ACCOUNT;
	extern const long ERR_INVALID_AMSCODE;
	extern const long ERR_ACCT_HAS_ALREADY_REBALANCE;
	extern const long ERR_ACCOUNT_DELETED;
	extern const long ERR_INVALID_AMSCODE_REBALANCING_ASSET_MIX;
	extern const long ERR_UNSETTLED_TRADES_WITH_AMS;
	extern const long ERR_PENDING_TRADES_WITH_AMS;
	extern const long ERR_CANNOT_INCLUDE_PENDING_TRADES_FOR_ONLINE_REBALALANCING;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_ACCOUNT_CHECK;
   extern CLASS_IMPORT const DSTCRequest CHQNAMEINQUIRY;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId AMSCode;
    extern CLASS_IMPORT const BFTextFieldId Name;
    extern CLASS_IMPORT const BFTextFieldId InclPending;
    extern CLASS_IMPORT const BFDateFieldId StartDate;
    extern CLASS_IMPORT const BFTextFieldId Description;
    extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
    extern CLASS_IMPORT const BFTextFieldId RecordType;
    extern CLASS_IMPORT const BFTextFieldId IncludeExclude;
    extern CLASS_IMPORT const BFTextFieldId CriteriaType;
	extern CLASS_IMPORT const BFTextFieldId CriteriaValue;
    extern CLASS_IMPORT const BFTextFieldId AMSRebalancingCriteria;
    extern CLASS_IMPORT const BFTextFieldId AMSHypocalcRebalCriteria;
	extern CLASS_IMPORT const BFDateFieldId LiveRunDate;
	extern CLASS_IMPORT const BFTextFieldId UnsettleWithAMSFund;
	extern CLASS_IMPORT const BFTextFieldId PendingWithAMSFund;
	extern CLASS_IMPORT const BFTextFieldId AMSType;

	extern CLASS_IMPORT const BFTextFieldId ReportMode;
	extern CLASS_IMPORT const BFTextFieldId ReportType;
	extern CLASS_IMPORT const BFTextFieldId ReportName;

	extern CLASS_IMPORT const BFTextFieldId GlobalLevelRebal;
	extern CLASS_IMPORT const BFTextFieldId AccountLevelRebal;

	extern CLASS_IMPORT const BFTextFieldId IsEnabledBtnAlloc;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,			     State Flags,   Group Flags 
	{ ifds::AMSCode,             BFCBO::NONE,			  0 },  
	{ ifds::InclPending,         BFCBO::NONE,			  0 },  
	{ ifds::StartDate,           BFCBO::NONE,			  0 },

	{ ifds::LiveRunDate,         BFCBO::NONE,			  0 },
	{ ifds::UnsettleWithAMSFund, BFCBO::NONE,			  0 },
	{ ifds::PendingWithAMSFund,  BFCBO::NONE,			  0 },
	{ ifds::GlobalLevelRebal,    BFCBO::NONE,			  0 },
	{ ifds::AccountLevelRebal,   BFCBO::NONE,			  0 },
	{ ifds::Description,         BFCBO::NONE,			  0 },

	{ ifds::IsEnabledBtnAlloc,	 BFCBO::NONE,			  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor
//*****************************************************************************

SEVERITY RptAMSRebalancingCriteria::doGetCriteriaList( DString &dstrCriteriaList, BFFieldId& bfCriteriaField ,const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doGetCriteriaList" ) );
	BFProperties *pProperties = getFieldProperties (bfCriteriaField, idDataGroup);
	
	DString dstrAMSCode;
	bool bIsGlobalLevelRebal = false , bIsAccountLevelRebal = false;
	if( pProperties )
	{
		pProperties->getAllSubstituteValues (dstrCriteriaList);
	}

	BFCBO *p = getParent();
	RptAMSRebalancingCriteriaList* pRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*> (p);
	
	
	BFObjIter bfIter( *pRptAMSRebalancingCriteriaList, idDataGroup /*, BFObjIter::ITERTYPE::NON_DELETED*/);

	for(bfIter.begin();!bfIter.end();bfIter++)
	{
		RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast <RptAMSRebalancingCriteria*> (bfIter.getObject());
		if ( !pRptAMSRebalancingCriteria )
			continue;
		DString dstrCriteriaType, dstrValue;
		pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);

		if ( dstrCriteriaType == NULL_STRING )
			continue;

		if ( dstrCriteriaType == I_("AMSCode") )
		{
			pRptAMSRebalancingCriteria->getField(ifds::AMSCode, dstrAMSCode, idDataGroup);
		}
		else if( dstrCriteriaType == I_("GlobalLevelRebal") )
		{
			pRptAMSRebalancingCriteria->getField(ifds::GlobalLevelRebal, dstrValue, idDataGroup);
			if( dstrValue == I_("Y") )
			{
				bIsGlobalLevelRebal = true;
			}
		}
		else if( dstrCriteriaType == I_("AccountLevelRebal") )
		{
			pRptAMSRebalancingCriteria->getField(ifds::AccountLevelRebal, dstrValue, idDataGroup);
			if( dstrValue == I_("Y") )
			{
				bIsAccountLevelRebal = true;
			}
		}
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, dstrCriteriaType);
	}

	if ( dstrAMSCode == I_("0001") )
	{
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("GlobalLevelRebal"));
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("AccountLevelRebal"));
	}
	else if ( !bIsGlobalLevelRebal && !bIsAccountLevelRebal )
	{
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("AccountNum"));
	}

	if ( bIsGlobalLevelRebal )
	{
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("AccountLevelRebal"));
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("AccountNum"));
	}

	if ( bIsAccountLevelRebal )
	{
		dstrCriteriaList = removeItemFromSubtList(dstrCriteriaList, I_("GlobalLevelRebal"));
	}


	return GETCURRENTHIGHESTSEVERITY();
}
RptAMSRebalancingCriteria::RptAMSRebalancingCriteria( DString dstrRptName, BFAbstractCBO &parent, const BFDataGroupId& idDataGroup )
:  ifastReportCriteria( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );      
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   BFFieldId bfCriteriaField;
   DString dstrSubList1;
   if ( dstrRptName == AMS_REBALANCE )
   {
	   bfCriteriaField = ifds::AMSRebalancingCriteria;
	   setFieldAllSubstituteValues( ifds::CriteriaType, idDataGroup , bfCriteriaField );
   }
   else if ( dstrRptName == AMS_HYPOCALC_REBALANCE )
   {
	   bfCriteriaField = ifds::AMSHypocalcRebalCriteria;	
	   doGetCriteriaList(dstrSubList1, bfCriteriaField, idDataGroup);
	   setFieldAllSubstituteValues( ifds::CriteriaType, idDataGroup , dstrSubList1 );
   }
}
//*****************************************************************************
// Destructor
//*****************************************************************************

RptAMSRebalancingCriteria::~RptAMSRebalancingCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// doValidateFields will validate the AccountNum and AMSCode.  It will call
// the helper methods validateAMSCode and validateAccountNum to do the
// validation.
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          const BFDataGroupId& idDataGroup - current group id.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteria::doValidateField( const BFFieldId& idField, 
																	  const DString& strValue, 
																	  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   
	if ( idField == ifds::AccountNum ) 
	{
      validateAccountNum ( strValue, idDataGroup );
	} 
	else if ( idField == ifds::AMSCode ) 
	{
      DString dstrAmsType = REBALANCE;
      validateAMSCode (strValue, dstrAmsType, idDataGroup );
	} 
	else if ( idField == ifds::InclPending )
	{
		DString dstrReportMode, dstrReportType;
		getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );	
		getParent()->getParent()->getField( ifds::ReportType, dstrReportType, idDataGroup );	

		if ( I_( "Y" ) == dstrReportMode.strip().upperCase()  &&   // Report/Update
		     I_( "Y" ) == dstrReportType.strip().upperCase() )     // Cycle
		{

			DString dstrInclPending = strValue;
			if ( I_( "Y" ) == dstrInclPending.strip().upperCase() )
			{
				ADDCONDITIONFROMFILE( CND::ERR_CANNOT_INCLUDE_PENDING_TRADES_FOR_ONLINE_REBALALANCING );						  				
			}
		}
	}
	else if ( idField == ifds::UnsettleWithAMSFund )
	{
		DString dstrReportMode;
		getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );			

		if ( I_( "Y" ) == dstrReportMode.strip().upperCase() )   // Report/Update mode
		{		
			// If corresponding Rej-Err is set to error and user changed the value of the field to Yes, then
			// raise error
			if ( I_( "Y" ) == strValue )
			{
				ErrMsgRulesList *pErrMsgRulesList = NULL;
				if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
					  NULL != pErrMsgRulesList )
				{			
					DString dstrErrValue;
					pErrMsgRulesList->getEWIValue( I_( "406" ), idDataGroup, dstrErrValue );
						
					dstrErrValue.strip().upperCase();
					if ( dstrErrValue == I_("E") )
					{
						// Accounts with unsettled trades are not eligible for AMS rebalancing
						ADDCONDITIONFROMFILE( CND::ERR_UNSETTLED_TRADES_WITH_AMS );	
					}			
				}
			}
		}	
		
		// If field value is Yes and we are in report mode, make sure there is no Account with 
		// unsettled AMS trades
		if ( I_( "Y") == strValue )
		{		
			DString dstrReportMode;
			getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );	

			if ( I_( "N" ) == dstrReportMode.strip().upperCase() )   // Report Mode
			{
				RptAMSRebalancingCriteriaList *pRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*>( getParent( ) );      
				BFObjIter iter( *pRptAMSRebalancingCriteriaList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				while ( !iter.end() ) 
				{
					RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = dynamic_cast < RptAMSRebalancingCriteria *> (iter.getObject ());
					if ( NULL != pRptAMSRebalancingCriteria )
					{
						DString dstrCriteriaType;
						BFFieldId curFieldId;
						pRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
						curFieldId = BFFieldId::getId ( dstrCriteriaType );
						if ( curFieldId == ifds::AccountNum ) 
						{
							pRptAMSRebalancingCriteria->setValidFlag( ifds::AccountNum , idDataGroup, false);						
						}
					}
					++iter;
				}
			}
		}		
	}
	else if ( idField == ifds::PendingWithAMSFund )
	{
		DString dstrReportMode;
		getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );			

		if ( I_( "Y" ) == dstrReportMode.strip().upperCase() )   // Report/Update mode
		{	
			// If corresponding Rej-Err is set to error and user changed the value of the field to Yes, then
			// raise error
			if ( I_( "Y" ) == strValue )
			{
				ErrMsgRulesList *pErrMsgRulesList = NULL;
				if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
					  NULL != pErrMsgRulesList )
				{			
					DString dstrErrValue;
					pErrMsgRulesList->getEWIValue( I_( "405" ), idDataGroup, dstrErrValue );
						
					dstrErrValue.strip().upperCase();
					if ( dstrErrValue == I_("E") )
					{
						// Accounts with pending trades are not eligible for AMS rebalancing.
						ADDCONDITIONFROMFILE( CND::ERR_PENDING_TRADES_WITH_AMS );			
					}			
				}
			}
		}
		
		// If field value is Yes and we are in report mode, make sure there is no Account with 
		// pending AMS trades
		if ( I_( "Y") == strValue )
		{		
			DString dstrReportMode;
			getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );	

			if ( I_( "N" ) == dstrReportMode.strip().upperCase() )   // Report Mode
			{
				RptAMSRebalancingCriteriaList *pRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*>( getParent( ) );      
				BFObjIter iter( *pRptAMSRebalancingCriteriaList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				while ( !iter.end() ) 
				{
					RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = dynamic_cast < RptAMSRebalancingCriteria *> (iter.getObject ());
					if ( NULL != pRptAMSRebalancingCriteria )
					{
						DString dstrCriteriaType;
						BFFieldId curFieldId;
						pRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
						curFieldId = BFFieldId::getId ( dstrCriteriaType );
						if ( curFieldId == ifds::AccountNum ) 
						{
							pRptAMSRebalancingCriteria->setValidFlag( ifds::AccountNum , idDataGroup, false);						
						}
					}
					++iter;
				}
			}
		}		
	}
	else 
	{
      ifastReportCriteria::doValidateField ( idField, strValue, idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY RptAMSRebalancingCriteria::doReportModeRelatedChanges ( BFFieldId fieldId, 
																					  const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doReportModeRelatedChanges" ) );

	setValidFlag ( fieldId, idDataGroup, false );   

	DString dstrValue;
	getField( fieldId, dstrValue, idDataGroup );
	doValidateField( fieldId, dstrValue, idDataGroup );

	notifyObservers( fieldId, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will blank out the Description field and validate the AMSCode
// entered for the AMS Code criteria type.   The validation is successful upon
// a successful creation of the AMSMstrList.  
// @param   const DString& dstrBrokerCode - broker code to check
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY - Error from creation of AMSMstrList.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteria::validateAMSCode( const DString& strValue, const DString& dstrAMSType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAMSCode" ) );

   AMSMstrList* pAMSMstrList;
   AmsMstrInfo* pAMSMstrInfo = NULL;
   DString dstrEffectiveDate = NULL;
   getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   

   getWorkSession().getAMSMstrList( pAMSMstrList, dstrAMSType, NULL, dstrEffectiveDate, idDataGroup );
   DString dstrAMSCode (strValue);
	DString strAMSType(dstrAMSType);
   if ( pAMSMstrList ) {
      pAMSMstrList->getAMSMstrInfo ( dstrAMSType, dstrAMSCode, dstrEffectiveDate, pAMSMstrInfo, idDataGroup );

      // isAMSCodeValid used to check to see if the current ams code is valid or not.
      // However this functionality seem to have changed to check for duplicate AMS Code hence this check 
      // no longer works.  The logic has been changed to see if it is possible to retrieve the current 
      // ams code given its effective date.   If the ams code retrieval failed then we will display
      // an error indicating the AMS Code entered is invalid.

      //if ( !pAMSMstrList->isAMSCodeValid( strAMSType, dstrAMSCode, dstrEffectiveDate, idDataGroup, true ) )  {
      if ( !pAMSMstrInfo ) {
         ADDCONDITIONFROMFILE ( CND::ERR_INVALID_AMSCODE_REBALANCING_ASSET_MIX );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will make a view call 223 to validate the account number.  View
// 223 will return valid for AMS accounts only, error otherwise.  When the 
// view is successfull the Description field will be populated with the 
// shareholder name, NULL_STRING otherwise.
// @param   const DString& dstrBrokerCode - broker code to check
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY - Error from view call.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteria::validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNum" ) );
   /*if ( strValue == I_("0") ) {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMS_ACCOUNT );      
      return GETCURRENTHIGHESTSEVERITY();
   }*/

  MFAccount *pMFAccount =  NULL;
  DString acctDesignation;
  DString dstrShrCName;

  if ( getWorkSession().getMFAccount( idDataGroup, strValue, pMFAccount ) <= WARNING &&
			  NULL != pMFAccount )
  {
	  
	  pMFAccount->getField( ifds::AcctDesignation, acctDesignation, idDataGroup, false );

	  if (acctDesignation == CLIENT)
	  {
		BFData requestData1(ifds::DSTC0297_REQ);
		BFData response1(ifds::DSTC0297_VW);

		DString mgmtCoIdOut;
		requestData1.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
		requestData1.setElementValue( ifds::AccountNum, strValue );
		requestData1.setElementValue( ifds::Track, I_( "N" ) );
		requestData1.setElementValue( ifds::Activity, NULL_STRING );

		SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::CHQNAMEINQUIRY,
                                                            requestData1, 
                                                            response1, 
                                                           DSTCRequestor( getSecurity(), true ) );

         dstrShrCName = response1.getElementValue ( ifds::Name1 );

	  }
  }

   BFData requestData(ifds::DSTC0223_REQ);
   BFData response(ifds::DSTC0223_VW);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::AccountNum, strValue );
   requestData.setElementValue( ifds::Track, I_( "N" ) );
   requestData.setElementValue( ifds::Activity, NULL_STRING );

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::AMS_ACCOUNT_CHECK,
                                                            requestData, 
                                                            response, 
                                                            DSTCRequestor( getSecurity(), true ) );
   bool bAccountValid = false;
   if ( sevRtn <= WARNING ) {
      //BFData* repeat = new BFData( response.getRepeat( 0 ));
      // This flag indicates whether the account has been schedule for rebalancing, if it has
      // Rebalancing again should give an error.
      DString dstrAcctExists = response.getElementValue ( ifds::AcctExists );
      if ( dstrAcctExists != YES ) { 
		  DString dstrShrName = acctDesignation == CLIENT ? dstrShrCName : response.getElementValue ( ifds::Name );
		 dstrShrName.strip ();
		 setFieldNoValidate ( ifds::Description, dstrShrName, idDataGroup, true, true, true, false );       
         bAccountValid = true;
      } else {
         //"The Account has already been scheduled for Rebalancing."
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_HAS_ALREADY_REBALANCE );                 
      }
      DString dstrAMSAccount, dstrAccountDeleted;
      dstrAMSAccount = response.getElementValue ( ifds::AMSAccount );
      dstrAccountDeleted = response.getElementValue ( ifds::AccountDeleted );
      if ( dstrAMSAccount != YES ) {
         // "Invalid AMS Account."
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_AMS_ACCOUNT );
      }
      if ( dstrAccountDeleted == YES ) {
         //The account has a deleted status.
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_DELETED );
      }


		//MFAccount *pMFAccount =  NULL;
		if ( getWorkSession().getMFAccount( idDataGroup, strValue, pMFAccount ) <= WARNING &&
			  NULL != pMFAccount )
		{
			// Check if this is an escrow Account
			if ( pMFAccount->validateAMSRBForEscrow (idDataGroup ) <= WARNING )
			{
				DString dstrReportMode;
				getParent()->getParent()->getField( ifds::ReportMode, dstrReportMode, idDataGroup );			
				if ( I_( "Y" ) == dstrReportMode.strip().upperCase() )        // Report/Update mode
				{
					pMFAccount->validateUnsettledUnitsForAMSEligibleFunds( idDataGroup );
					pMFAccount->validatePendingTradesForAMSEligibleFunds( idDataGroup );
				}
				else if ( I_( "N" ) == dstrReportMode.strip().upperCase() )   // Report mode
				{			
					DString dstrUnsettleWithAMSFund, dstrPendingWithAMSFund;
		
					RptAMSRebalancingCriteriaList *pRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*>( getParent( ) );      
					BFObjIter iter( *pRptAMSRebalancingCriteriaList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
					while ( !iter.end() ) 
					{
						RptAMSRebalancingCriteria *pRptAMSRebalancingCriteria = dynamic_cast < RptAMSRebalancingCriteria *> (iter.getObject ());
						if ( NULL != pRptAMSRebalancingCriteria )
						{
							DString dstrCriteriaType;
							BFFieldId curFieldId;
							pRptAMSRebalancingCriteria->getField ( ifds::CriteriaType, dstrCriteriaType, idDataGroup );
							curFieldId = BFFieldId::getId ( dstrCriteriaType );
							if ( curFieldId == ifds::UnsettleWithAMSFund ) 
							{
								pRptAMSRebalancingCriteria->getField( ifds::UnsettleWithAMSFund, dstrUnsettleWithAMSFund, idDataGroup );   									
							}
							if ( curFieldId == ifds::PendingWithAMSFund ) 
							{
								pRptAMSRebalancingCriteria->getField( ifds::PendingWithAMSFund, dstrPendingWithAMSFund, idDataGroup );   					
							}
									
							if ( 0 != dstrUnsettleWithAMSFund.strip().length() &&
								  0 != dstrPendingWithAMSFund.strip().length() )
								  break;
						}		

						++iter;
					}

					if ( I_( "Y" ) == dstrUnsettleWithAMSFund )
					{
						pMFAccount->validateUnsettledUnitsForAMSEligibleFunds( idDataGroup );
					}
					if ( I_( "Y") == dstrPendingWithAMSFund )
					{
						pMFAccount->validatePendingTradesForAMSEligibleFunds( idDataGroup );
					}
				}

				SEVERITY sev = GETCURRENTHIGHESTSEVERITY();

				// Check if the Account has pending trades and unsettled units for AMS eligible funds
				if ( sev <= WARNING )
				{               
					DString dstrEffectiveDate;
					getWorkSession().getDateInHostFormat( dstrEffectiveDate, 
						                                   DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
																	  idDataGroup );   
					AMSMstrList *pAMSMstrList = NULL;
					if ( pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate ) <= WARNING &&
						  NULL != pAMSMstrList )
					{
						DString dstrAMSType, dstrAMSCode;
						pMFAccount->getField( ifds::AMSType, dstrAMSType, idDataGroup, false );
						pMFAccount->getField( ifds::AMSCode, dstrAMSCode, idDataGroup, false );

						AmsMstrInfo *pAMSMstrInfo = NULL;
						pAMSMstrList->getAMSMstrInfo( dstrAMSType, 
							                           dstrAMSCode, 
																dstrEffectiveDate, 
																pAMSMstrInfo, 
																idDataGroup );  // it returns void!
						if ( NULL != pAMSMstrInfo )
						{
							AmsLmtOverrideList *pAMSLmtOverrideList = NULL;
							if ( pAMSMstrInfo->getAmsLmtOverrideList( pAMSLmtOverrideList, idDataGroup ) <= WARNING &&
								  NULL != pAMSLmtOverrideList )
							{
								pAMSLmtOverrideList->canRebalanceAccount( strValue, idDataGroup );
							}
						}
					}															
				}
			}
		}
   }

   if ( !bAccountValid )
      setFieldNoValidate ( ifds::Description, NULL_STRING, idDataGroup, true, true, true, false );

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will make the fieldId passed in, required, readonly and initialize
// with default values.   Currently the fieldIds StartDate / InclPending are
// processed as required, all others ignored.
// @param   BFFieldId fieldId - field Id to setup as required.
// @returns SEVERITY.
//*****************************************************************************
SEVERITY RptAMSRebalancingCriteria::setupRequiredRecord( BFFieldId fieldId, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initRequiredRecord" ) );   
   
   DString dstrRptName;
   getParent()->getParent()->getField(ifds::ReportName, dstrRptName, idDataGroup);
   bool bIsAMSHypocalc = (dstrRptName == AMS_HYPOCALC_REBALANCE ? true : false);

	//Field default values
   if ( fieldId == ifds::StartDate || fieldId == ifds::LiveRunDate ) 
   {
      // Current Business Date is used as default date for StartDate/LiveRunDate
      DString dstrCurBusDate;      
      getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
      setFieldNoValidate ( fieldId, dstrCurBusDate, idDataGroup, true, true,true, false );
	  setFieldReadOnly( fieldId, idDataGroup, bIsAMSHypocalc);
   } 	
   else if ( fieldId == ifds::InclPending )
   {
      // Include Pending Trade is defaulted to No.
      setFieldNoValidate ( ifds::InclPending, NO, idDataGroup, true, true,true, false );
	  setFieldReadOnly( fieldId, idDataGroup, bIsAMSHypocalc);
   } 
   else if ( fieldId == ifds::UnsettleWithAMSFund ) 
   {
      ErrMsgRulesList *pErrMsgRulesList = NULL;
		if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
			  NULL != pErrMsgRulesList )
		{
			// For the fields below, if the corresponding Rej-Error is set to error, default the criteria to 'No', else
			// if Rej-Error code is set to Warning then default criteria to Yes
			DString dstrErrValue;
			pErrMsgRulesList->getEWIValue( I_( "406" ), idDataGroup, dstrErrValue );
				
			dstrErrValue.strip().upperCase();
			if ( dstrErrValue == I_("E") )
			{
				setFieldNoValidate ( ifds::UnsettleWithAMSFund, I_( "N" ), idDataGroup, true, true,true, false );		
			}
			else if (dstrErrValue == I_("W") )
			{
				setFieldNoValidate ( ifds::UnsettleWithAMSFund, I_( "Y" ), idDataGroup, true, true,true, false );		
			}			
		}

		// Include Pending Trade is defaulted to No.
      setFieldNoValidate ( ifds::InclPending, NO, idDataGroup, true, true,true, false );
   } 
   else if ( fieldId == ifds::PendingWithAMSFund ) 
   {
      ErrMsgRulesList *pErrMsgRulesList = NULL;
		if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
			  NULL != pErrMsgRulesList )
		{
			// For the fields below, if the corresponding Rej-Error is set to error, default the criteria to 'No', else
			// if Rej-Error code is set to Warning then default criteria to Yes
			DString dstrErrValue;
			pErrMsgRulesList->getEWIValue( I_( "405" ), idDataGroup, dstrErrValue );
				
			dstrErrValue.strip().upperCase();
			if ( dstrErrValue == I_("E") )
			{
				setFieldNoValidate ( ifds::PendingWithAMSFund, I_( "N" ), idDataGroup, true, true,true, false );		
			}
			else if (dstrErrValue == I_("W") )
			{
				setFieldNoValidate ( ifds::PendingWithAMSFund, I_( "Y" ), idDataGroup, true, true,true, false );		
			}			
		}

		// Include Pending Trade is defaulted to No.
      setFieldNoValidate ( ifds::InclPending, NO, idDataGroup, true, true,true, false );
   }
   else if ( fieldId == ifds::AMSCode )
   {
	  setFieldNoValidate ( ifds::AMSCode, I_("0001"), idDataGroup, true, true, true, false );   }
   else 
   {
      return GETCURRENTHIGHESTSEVERITY();
   }

   setFieldNoValidate ( ifds::CriteriaType, fieldId.getName() , idDataGroup, true, true, true, false );   
   setFieldReadOnly ( ifds::CriteriaType, idDataGroup, true );

   // Record Types are set to type "F" for required fields and IncludeExclude to Yes.
   setFieldNoValidate ( ifds::RecordType, FIX_RECORD, idDataGroup, true, true,true, false );
   setFieldNoValidate ( ifds::IncludeExclude, YES, idDataGroup, true, true,true, false );
   setFieldReadOnly ( ifds::IncludeExclude, idDataGroup, true );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
//*****************************************************************************
void RptAMSRebalancingCriteria::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrCurBusDate;      
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, BF::HOST, false );
   setFieldNoValidate ( ifds::StartDate,   dstrCurBusDate, idDataGroup, true, true,true, false );
	setFieldNoValidate ( ifds::LiveRunDate, dstrCurBusDate, idDataGroup, true, true,true, false );


	ErrMsgRulesList *pErrMsgRulesList = NULL;
	if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
		  NULL != pErrMsgRulesList )
	{
		// For the fields below, if the corresponding Rej-Error is set to error, default the criteria to 'No', else
		// if Rej-Error code is set to Warning then default criteria to Yes
		DString dstrErrValue;
		pErrMsgRulesList->getEWIValue( I_( "406" ), idDataGroup, dstrErrValue );
			
		dstrErrValue.strip().upperCase();
		if ( dstrErrValue == I_("E") )
		{
			setFieldNoValidate ( ifds::UnsettleWithAMSFund, I_( "N" ), idDataGroup, true, true,true, false );		
		}
		else if (dstrErrValue == I_("W") )
		{
			setFieldNoValidate ( ifds::UnsettleWithAMSFund, I_( "Y" ), idDataGroup, true, true,true, false );		
		}			
		
		pErrMsgRulesList->getEWIValue( I_( "405" ), idDataGroup, dstrErrValue );			
		dstrErrValue.strip().upperCase();
		if ( dstrErrValue == I_("E") )
		{
			setFieldNoValidate ( ifds::PendingWithAMSFund, I_( "N" ), idDataGroup, true, true,true, false );		
		}
		else if (dstrErrValue == I_("W") )
		{
			setFieldNoValidate ( ifds::PendingWithAMSFund, I_( "Y" ), idDataGroup, true, true,true, false );		
		}			
	}

   ifastReportCriteria::doInitWithDefaultValues ( idDataGroup );
}

//******************************************************************************
SEVERITY RptAMSRebalancingCriteria::doApplyRelatedChanges( const BFFieldId& idField, 
                                                           const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   
	if ( ifastReportCriteria::doApplyRelatedChanges( idField, idDataGroup ) <= WARNING )
	{
		if ( idField == ifds::AccountNum ) 
		{      
			DString dstrAccountNum, dstrShrName;
			getField( ifds::AccountNum, dstrAccountNum, idDataGroup );

			MFAccount *pMFAccount =  NULL;
			DString acctDesignation;
			bool bClientDesignation = false;

			if ( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
			  NULL != pMFAccount )
			{
	  
				pMFAccount->getField( ifds::AcctDesignation, acctDesignation, idDataGroup, false );


				if (acctDesignation == CLIENT)
				{
					bClientDesignation = true;
				}

				BFObjIter iter(*getParent(), idDataGroup);
				
				DString dstrAMSCode, dstrEnableBtnAlloc;
				bool bAccountLevelRebal = false;

				for(iter.begin();!iter.end();iter++)
				{
					RptAMSRebalancingCriteria* pRptAMSRebalancingCriteria = dynamic_cast<RptAMSRebalancingCriteria*> (iter.getObject());
					DString dstrCriteriaVal, dstrCriteriaType;
					if ( !pRptAMSRebalancingCriteria )
						continue;

					pRptAMSRebalancingCriteria->getField(ifds::CriteriaType, dstrCriteriaType, idDataGroup);
					if ( dstrCriteriaType == I_("AccountLevelRebal") )
					{
						pRptAMSRebalancingCriteria->getField(ifds::AccountLevelRebal, dstrCriteriaVal, idDataGroup);
						if ( dstrCriteriaVal == I_("Y") )
							bAccountLevelRebal = true;
					}
					else if ( dstrCriteriaType == I_("AMSCode") )
					{
						pRptAMSRebalancingCriteria->getField(ifds::AMSCode, dstrAMSCode, idDataGroup);
					}
				}

				if ( bAccountLevelRebal || dstrAMSCode == I_("0001") )
					dstrEnableBtnAlloc = I_("Y");
				else
					dstrEnableBtnAlloc = I_("N");
				
				getParent()->setField(ifds::IsEnabledBtnAlloc, dstrEnableBtnAlloc, idDataGroup);
			}
			
			if ( !dstrAccountNum.stripAll().empty() )
			{
				MFAccount *pMFAccount =  NULL;
				if ( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
					NULL != pMFAccount && !bClientDesignation)
				{
					DString dstrBeneficialOwner;
					pMFAccount->getField( ifds::BeneficialOwner, dstrBeneficialOwner, idDataGroup );
					setFieldNoValidate( ifds::Description, dstrBeneficialOwner, idDataGroup, true, true, true, false );
				
				}
			}
		}

		else if ( idField == ifds::CriteriaType ) 
		{
			DString dstrCriteriaType;
			getField( ifds::CriteriaType, dstrCriteriaType, idDataGroup );

			if ( dstrCriteriaType == I_("GlobalLevelRebal") )
			{
				setFieldNoValidate( ifds::GlobalLevelRebal, I_("Y"), idDataGroup );
				setFieldReadOnly( ifds::GlobalLevelRebal, idDataGroup, true );
				RptAMSRebalancingCriteriaList* pRptAMSRebalancingCriteriaList = dynamic_cast<RptAMSRebalancingCriteriaList*> (getParent());
				pRptAMSRebalancingCriteriaList->setField( ifds::IsEnabledBtnAlloc, I_("Y"), idDataGroup);
			}
			else if ( dstrCriteriaType == I_("AccountLevelRebal") )
			{
				setFieldNoValidate( ifds::AccountLevelRebal, I_("Y"), idDataGroup );
				setFieldReadOnly( ifds::AccountLevelRebal, idDataGroup, true );
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RptAMSRebalancingCriteria.cpp-arc  $
// 
//    Rev 1.28   May 29 2008 11:25:06   jankovii
// IN  774181 - add logic for client accounts.
// 
//    Rev 1.27   Aug 03 2007 09:35:06   smithdav
// PET 2360 FN02
// 
//    Rev 1.26   May 10 2007 10:11:30   porteanm
// Incident 774181 - Display name for account held by nominees/intermediaries.
// 
//    Rev 1.25   Nov 14 2004 14:52:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.24   Jul 08 2004 13:41:54   VADEANUM
// PTS 10032106 - Accounts validation when in Report Mode and Include AMS Pending or Unsettled Trades.
// 
//    Rev 1.23   Jul 05 2004 16:17:54   VADEANUM
// PTS 10031917 - Backed out changes for this ticket as DOD does not require any validation for AMS Trade/Live Run Date.
// 
//    Rev 1.22   Jul 05 2004 15:55:42   VADEANUM
// PTS 10031917 - AMS Trade/Live Run Date validation.
// 
//    Rev 1.21   Jun 29 2004 17:30:46   VADEANUM
// PTS 10031151 - InclPending.
// 
//    Rev 1.20   Jun 29 2004 16:50:08   VADEANUM
// PTS 10031437 - Exclude edit check for errors 405 and 406 for Account Validation - backed out changes for PTS 10031151 - InclPending.
// 
//    Rev 1.19   Jun 28 2004 15:24:36   VADEANUM
// PTS 10031151 - InclPending.
// 
//    Rev 1.18   Jun 28 2004 15:13:58   VADEANUM
// PTS 10031840 - If an Account has both unsettled and pending trades, show both error messsages. Backed out changes for PTS 10031151 - InclPending validation.
// 
//    Rev 1.17   Jun 21 2004 12:22:48   VADEANUM
// PTS 10031151 - InclPending validation.
// 
//    Rev 1.16   Jun 21 2004 10:16:22   VADEANUM
// PTS 10031437 - Exclude the edit check for error number 405 and 406 when user is running the option in 'Report' mode.
// 
//    Rev 1.15   Apr 09 2004 11:53:00   VADEANUM
// PET1005 FN11 - AMS Gaps.
// 
//    Rev 1.14   Nov 03 2003 14:44:24   HSUCHIN
// PTS 10023601 - bug fix with AMS Code validation
// 
//    Rev 1.13   Jul 23 2003 11:05:56   linmay
// modified validateamscode
// 
//    Rev 1.12   Jun 24 2003 09:40:04   HSUCHIN
// PTS 10018531 - Change the error message to be more descriptive.
// 
//    Rev 1.11   Apr 21 2003 09:48:06   YINGBAOL
// change isAMSCode valid sync.
// 
//    Rev 1.10   Mar 21 2003 18:22:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Feb 25 2003 13:35:18   HSUCHIN
// removed hardcode ams code 0001
// 
//    Rev 1.8   Feb 25 2003 12:48:12   HSUCHIN
// hardcoded ams code 0001 to be valid
// 
//    Rev 1.7   Jan 28 2003 13:58:22   HSUCHIN
// 0001 ams code is now a valid code
// 
//    Rev 1.6   Jan 22 2003 13:17:54   HSUCHIN
// added 2 more bus rules for account validation
// 
//    Rev 1.5   Jan 07 2003 14:45:04   HSUCHIN
// fixed ams account verification, wrong condition message
// 
//    Rev 1.4   Jan 02 2003 13:44:40   HSUCHIN
// bug fix for dovalidatefield
// 
//    Rev 1.3   Dec 27 2002 11:29:26   linmay
// modified doValidateField and ValidateAMSCode, added AMSType.
// 
//    Rev 1.2   Dec 08 2002 21:50:36   HSUCHIN
// fixed doinit to init to datagroup rather than host
// 
//    Rev 1.1   Nov 29 2002 14:19:14   HSUCHIN
// rename and bug fix for ams account check
// 
//    Rev 1.0   Nov 29 2002 13:38:32   HSUCHIN
// Initial revision.
// 
//    Rev 1.1   Nov 29 2002 13:16:00   HSUCHIN
// added ams code check
// 
//    Rev 1.0   Nov 27 2002 11:39:12   HSUCHIN
// Initial Revision
*/
