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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : DefAcctAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/03/02
//
// ^CLASS    : DefAcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Default account allocation
//
//******************************************************************************
#include "stdafx.h"
#include "defacctalloc.hpp"
#include "deffundalloclist.hpp"
#include "dynamicsublistholder.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "shralloctype.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME                  = I_( "DefAcctAlloc" );
   const I_CHAR * const YES                        = I_( "Y" );
   const I_CHAR * const NO                         = I_( "N" );
   const I_CHAR * const ACCT_LEVEL                 = I_( "2" );

   const I_CHAR * const PURCHASE_CODE              = I_( "ED" );     // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE            = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const EXCHANGE_TRANSFER_CODE     = I_( "TR" );     // trade trans type Transfer 
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out
   const I_CHAR * const FOREIGN_CONTENT_REBALANCING= I_( "XS" );
   const I_CHAR * const MANAGEMENT_FEE_CODE        = I_( "MF" );

   const I_CHAR * const PURCHASECODELIST           = I_( "ED,DD,GP" );
   const I_CHAR * const REDEMPTIONCODELIST         = I_( "PW,AW,RF,LF,LR,AF" );
   const I_CHAR * const TRANSFERCODELIST           = I_( "TR,AT" );

   const I_CHAR * const IDI_TAX_TRANS              = I_("TAX_TRANS");

   //because of the templated method, we have to use the same name for all the FundAllocationLists in the classes derived from AccountAlloc
   extern const I_CHAR * const FUNDALLOCATIONLIST;

}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION;
   extern const long ERR_ACCOUNT_CODED_AS_ASSIGNED;
   extern const long ERR_ASSIGNNED_ACCOUNT;
   extern const long ERR_STOP_FLAG_ACTIVE_IGNORED;
   extern const long ERR_STOP_FLAG_ACTIVE;
   extern const long ERR_NOT_CONF_FOR_REBALANCING;
   extern const long ERR_INVALID_TAXTYPE_FOR_PAC_ALLOC;
   extern const long ERR_ALLOC_FOR_ACCT_TYPE06;
   extern const long ERR_ALLOC_FOR_INACTIVE_ACCT;
   extern const long ERR_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_ACCT_ALLOC_ONE_ACCOUNT_ONLY;
   extern const long ERR_PERCENT_VALUE_INVALID;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId TaxTransTypes;
   extern CLASS_IMPORT const BFTextFieldId rxTransTypeJapanese;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId XSFundsValidate;
   extern CLASS_IMPORT const BFTextFieldId FundGroupCE;
   extern CLASS_IMPORT const BFDecimalFieldId RebalPrcnt;
   extern CLASS_IMPORT const BFTextFieldId AMSCurrency;
}
//******************************************************************************

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::FundGroup, BFCBO::NONE, 0 }, 
      //cross edits
   { ifds::TaxTransTypes, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundGroupCE, BFCBO::NONE, 0 }, 
   { ifds::RebalPrcnt, BFCBO::NONE, 0 }, 
   { ifds::AMSCurrency, BFCBO::NONE, 0 }, 

};

//******************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
DefAcctAlloc::DefAcctAlloc( BFAbstractCBO &parent ) 
: AcctAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );

   //cross edit for TransType, AccountNum and EffectiveDate
   addCrossEdit(ifds::TaxTransTypes, ifds::TransType);
   addCrossEdit(ifds::TaxTransTypes, ifds::AccountNum);
   addCrossEdit(ifds::TaxTransTypes, ifds::EffectiveDate);

   //cross edit for TransType and FundGroup 
   addCrossEdit(ifds::FundGroupCE, ifds::TransType);
   addCrossEdit(ifds::FundGroupCE, ifds::FundGroup);
}

//******************************************************************************
DefAcctAlloc::~DefAcctAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY DefAcctAlloc::initNew( const BFDataGroupId& idDataGroup,
                                const DString& dstrTrack ,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setFieldNoValidate(ifds::AccountNum, I_("0"), BF::HOST, false, false);//zero is an invalid value

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 

   loadSubstitutions( BF::HOST );

   //have to create the default fund allocation list
   DefFundAllocList* pDefFundAllocList = new DefFundAllocList( *this );
   if( pDefFundAllocList->initExisting() <= WARNING )
      setObject(pDefFundAllocList, FUNDALLOCATIONLIST);
   else
      delete pDefFundAllocList;

   setFieldReadOnly( ifds::AllocPercentage, BF::HOST, true );
	
	setFieldReadOnly( ifds::AccountNum, BF::HOST, true );
   
	clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void DefAcctAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   setFieldNoValidate(ifds::Level, ACCT_LEVEL, idDataGroup, false);
   setFieldRequired(ifds::TransType, idDataGroup, true);
   setFieldRequired(ifds::EffectiveDate, idDataGroup, true);
   setFieldNoValidate( ifds::AllocPercentage, I_( "100" ), idDataGroup, false, false, true );
   setFieldReadOnly( ifds::AllocPercentage, idDataGroup, true );

   AcctAlloc::doInitWithDefaultValues(idDataGroup);
}
//******************************************************************************

SEVERITY DefAcctAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AcctAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField != ifds::TransType && idField != ifds::EffectiveDate && idField != ifds::AccountNum
      && idField != ifds::AllocPercentage && idField != ifds::FundGroup && idField != ifds::RebalPrcnt && idField != ifds::AMSCurrency )
      setUpdatedFlag(idField, idDataGroup, false);

   if (idField == ifds::TransType)
      transTypeRelChanges(idDataGroup);

   if( idField == ifds::FundGroup )
   {
      FundAllocList *pFundAllocList = NULL;
      getFundAllocationList(pFundAllocList, idDataGroup, false, false);
      if( pFundAllocList )
      {
         DString strValue;
         getField(idField, strValue, idDataGroup, false);
            pFundAllocList->setField(idField, strValue, idDataGroup, false);
      }
   }
	if( idField == ifds::AccountNum )
	{
		DString dstrAccount;
		getField(idField,dstrAccount,idDataGroup,false );
		dstrAccount.strip().stripLeading('0');
		getParent()->getParent()->setField(idField,dstrAccount,idDataGroup,false);
	
	}
	
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( AcctAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::AccountNum )
      validateAccountNum( strValue, idDataGroup );
   else if( idField == ifds::TaxTransTypes )
      validateAccountNumTransType( idDataGroup );
   else if( idField == ifds::FundGroupCE )
      validateFundGroupType( idDataGroup );
   else if( idField == ifds::AllocPercentage )
      validateAllocPercentage( idDataGroup );
   else if( idField == ifds::RebalPrcnt )
      validateRebalancePercent( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAlloc::validateRebalancePercent( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRebalancePercent" ) );

   DString dstrRebalPrcnt;
   getField( ifds::RebalPrcnt, dstrRebalPrcnt, idDataGroup, false );

   double dRebalPrcnt = DSTCommonFunctions::convertToDouble ( dstrRebalPrcnt );
   if( dRebalPrcnt < 0.0 || dRebalPrcnt > 100.0 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_PERCENT_VALUE_INVALID );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAlloc::validateAllocPercentage( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAllocPercentage" ) );

   DString dstrTransType, dstrAllocPercentage;
   getField( ifds::TransType, dstrTransType, idDataGroup, false );

   if(   dstrTransType == FOREIGN_CONTENT_REBALANCING ||
         dstrTransType == MANAGEMENT_FEE_CODE )
   {
      getField( ifds::AllocPercentage, dstrAllocPercentage, idDataGroup, false );
      double dAllocPercentage = DSTCommonFunctions::convertToDouble ( dstrAllocPercentage );
      if( dAllocPercentage != 100.0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_ALLOC_ONE_ACCOUNT_ONLY ); // Transaction Type requires 1 entry only of 100%
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAlloc::validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAccountNum" ) );
   //validation for null string and for valid existing account number is done in base classes
   //here we'll do only default account allocation specific validations
   //******!!VERY IMPORTANT!!****** All validations that require the TransType and EffectiveDate should be done in validateAccountNumTransType()

   MFAccount *pMFAccount=NULL;
   if( getMFAccount( pMFAccount, idDataGroup ) > WARNING || !pMFAccount )
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrAcctType, dstrAcctStatus;     

   pMFAccount->getField( ifds::AcctStatus, dstrAcctStatus, idDataGroup );

   if( dstrAcctStatus.strip() != I_( "10" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ALLOC_FOR_INACTIVE_ACCT );
   }

   pMFAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup );

   if( dstrAcctType.strip() == I_( "06" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ALLOC_FOR_ACCT_TYPE06 );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DefAcctAlloc::validateFundGroupType( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundGroup" ) );

   if (isFundGroupApplicable(idDataGroup))
   {
      DString dstrFundGroup;
      getField( ifds::FundGroup, dstrFundGroup, idDataGroup, false );
      if (dstrFundGroup.strip().empty())
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_SELECT );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAlloc::validateAccountNumTransType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNumTransType" ) );

   DString dstrTransType, dstrTaxType;
   DString dstrStopFCrebal, dstrFCOverrides, dstrAllLocked, dstrLockedIn, dstrEscrow, dstrForeignContConfig(I_("")); 

   getField( ifds::TransType, dstrTransType, idDataGroup );
   dstrTransType.strip().upperCase();

   MFAccount *pMFAccount=NULL;
   if( getMFAccount( pMFAccount, idDataGroup ) > WARNING || !pMFAccount )
      return(GETCURRENTHIGHESTSEVERITY());


   //*********** TaxType related **************//

   pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );
   dstrTaxType.strip().upperCase();
   DString strTagTaxType, dstrFormattedTaxType;
   pMFAccount->getField ( ifds::TaxType, dstrFormattedTaxType, idDataGroup, true);
   addIDITagValue( strTagTaxType, IDI_TAX_TRANS, dstrFormattedTaxType );


   if( dstrTransType == I_("LF") )
   {
      if( (dstrTaxType != I_("5")) && (!getWorkSession ().isLIFLike (dstrTaxType)) )
         ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
   else if( dstrTransType == I_("LR") )
   {
      if( dstrTaxType != I_("L") )
         ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
   else if( dstrTransType == I_("RG") )
   {
      if( (dstrTaxType != I_("9")) && (dstrTaxType != I_("M")) )
         ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
   else if( dstrTransType == I_("RF") )
   {
      if( (dstrTaxType != I_("2")) && (dstrTaxType != I_("5")) && (!getWorkSession ().isLIFLike (dstrTaxType)) )
         ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
   else if( DSTCommonFunctions::codeInList (dstrTransType, I_("RP,RR,RN,RE")) ) // RP-RDSP Grant, RR-RDSP Grant Return, RN-RDSP Bond, RE-RDSP Bond Return 
   {
	   if( dstrTaxType != I_("RS") )
		   ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
	/*************************** PTS 10030683 - TaxType validation is done anyway by VEWB4A.I for FCConfig
	// If TaxType not setup in foreign-content.taxtypes, then FCCOnfig will be No
   else if( dstrTransType == I_("XS") ) // Foreign content excess rebalancing
   {
      if( dstrTaxType != I_("1") && dstrTaxType != I_("2") && dstrTaxType != I_("C") &&
          !getWorkSession ().isLIFLike (dstrTaxType) && dstrTaxType != I_("L") )
         ADDCONDITIONFROMFILEIDI( CND::ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION, strTagTaxType );
   }
	***************************/

   //*********** Effective Date related **************//

   DString dstrEffectiveDate, dstrTradeType = NULL_STRING;
   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   if( DSTCommonFunctions::codeInList( dstrTransType, PURCHASECODELIST ) )
   {
      dstrTradeType = PURCHASE_CODE;
      if( pMFAccount->canPurchase( dstrEffectiveDate, idDataGroup ) <= WARNING )
         pMFAccount->escrowPurchase( dstrEffectiveDate, idDataGroup );
   }
   else if( DSTCommonFunctions::codeInList( dstrTransType, REDEMPTIONCODELIST ) )
   {
      dstrTradeType = REDEMPTION_CODE;
      if( pMFAccount->canRedeem ( dstrEffectiveDate, idDataGroup ) <= WARNING )
         pMFAccount->escrowRedeem ( dstrEffectiveDate, idDataGroup );
   }
   else if( DSTCommonFunctions::codeInList( dstrTransType, TRANSFERCODELIST ) )
   {
      dstrTradeType = EX_FER_IN_CODE;

      // check against Stop Transfer In flag since the allocation is applicable to 'To Account' rather than 'From Account'
      pMFAccount->canTrfExchIn ( dstrEffectiveDate, idDataGroup );
      //sevRtn = pMFAccount->canTrfExchOut ( dstrEffectiveDate, idDataGroup );
   }

   //*********** TransType related **************//

   if( dstrTransType == I_( "ED" ) )
   {
      DString taxTypeForPAC = I_( "0,1,4,S,T,X" );
      bool bIsLIRALike = getWorkSession ().isLIRALike (dstrTaxType); // C, CR, U

      if( DSTCommonFunctions::codeInList( dstrTaxType, taxTypeForPAC) == false 
		  || !bIsLIRALike)
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_TAXTYPE_FOR_PAC_ALLOC );
   }

   // Foreign Content Rebalancing
   pMFAccount->getField( ifds::FCConfig, dstrForeignContConfig, idDataGroup );
   dstrForeignContConfig.strip();

   if( dstrTransType == I_( "XS" ) )
   {
      if( dstrForeignContConfig == NO )
      {
         DString msg( I_( "TAX_TYPE=" ) );
         msg += dstrTaxType;
         ADDCONDITIONFROMFILEIDI( CND::ERR_NOT_CONF_FOR_REBALANCING, msg.c_str() );
      }

      pMFAccount->getField( ifds::StopFCrebal, dstrStopFCrebal, idDataGroup );
      pMFAccount->getField( ifds::FCOverrides, dstrFCOverrides, idDataGroup );

      dstrStopFCrebal.strip();
      dstrFCOverrides.strip();

      if( dstrStopFCrebal == YES && dstrFCOverrides == YES )
      {
         ADDCONDITIONFROMFILE( CND::ERR_STOP_FLAG_ACTIVE );
      }

      if( dstrStopFCrebal == YES && dstrFCOverrides == NO )
      {
         ADDCONDITIONFROMFILE( CND::ERR_STOP_FLAG_ACTIVE_IGNORED );
      }
   }
   if( DSTCommonFunctions::codeInList( dstrTransType, REDEMPTIONCODELIST ) )
   {
      pMFAccount->getField( ifds::AllLocked, dstrAllLocked, idDataGroup );
      pMFAccount->getField( ifds::LockedIn, dstrLockedIn, idDataGroup );
      pMFAccount->getField( ifds::Escrow, dstrEscrow, idDataGroup );

      dstrAllLocked.strip();
      dstrLockedIn.strip();  
      dstrEscrow.strip();

      if( dstrEscrow == YES && dstrAllLocked == YES )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ASSIGNNED_ACCOUNT );
      }

      if( dstrEscrow == YES && dstrLockedIn == YES )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_CODED_AS_ASSIGNED );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAlloc::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransTypeJapanese );
   else  // for Canada and any other market
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransType);

   if (isFundGroupApplicable(idDataGroup))
      loadFundGroupSubst(idDataGroup);
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DefAcctAlloc::transTypeRelChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "transTypeRelChanges" ) );

   //if fund group is applicable for the current trans type, have to set the substitution list
   //else have to clear this field
   if (isFundGroupApplicable(idDataGroup))
   {
      //set substitution set for FundGroup field
      loadFundGroupSubst(idDataGroup);
   }
   else
   {
      //no substitution set for FundGroup field
      setFieldAllSubstituteValues(ifds::FundGroup, idDataGroup, NULL_STRING);
      setFieldNoValidate(ifds::FundGroup, NULL_STRING, idDataGroup, false, true, true);//FundGroup has to be cleared 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAlloc::loadFundGroupSubst(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadFundGroupSubst" ) );

   DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
   assert(pDynamicSubListHolder);
   DString strSubstList = pDynamicSubListHolder->getFundGroupSubList(I_("REBAL"));
   setFieldAllSubstituteValues(ifds::FundGroup, idDataGroup, strSubstList);
   //have to force validation, because substitute values have changed
   setValidFlag( ifds::FundGroup, idDataGroup, false );   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool DefAcctAlloc::isFundGroupApplicable(const BFDataGroupId& idDataGroup)
{
   //XSFundsValidate has to be set to YES
   DString strFundGroupApplic = NO;
   getWorkSession().getOption( ifds::XSFundsValidate , strFundGroupApplic, BF::HOST, false );
   if (strFundGroupApplic.strip() != YES)
      return false;

   //allocation type has to be FOREIGN_CONTENT_REBALANCING
   DString strTransType;
   getField( ifds::TransType, strTransType, idDataGroup, false);
   if (strTransType.strip() != FOREIGN_CONTENT_REBALANCING)
      return false;

   return true;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefAcctAlloc.cpp-arc  $
// 
//    Rev 1.22   Nov 28 2008 14:03:10   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.21   Nov 25 2008 11:16:10   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.20   Oct 08 2007 12:16:06   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.19   Jul 26 2005 11:18:40   AGUILAAM
// IN 356897 - disable the update of account number for existing default allocation
// 
//    Rev 1.18   Nov 14 2004 14:30:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Sep 08 2004 18:08:30   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.16   May 31 2004 14:40:20   VADEANUM
// PTS 10030683 - Foreign Content Rebalancing on Default Allocations
// 
//    Rev 1.15   Feb 12 2004 15:53:40   YINGBAOL
// PTS 10021233: Multi allocation at account level is not been supported
// 
//    Rev 1.14   Apr 28 2003 15:09:44   HERNANDO
// PTS 10016054 - Added validatedRebalancePercent.
// 
//    Rev 1.13   Apr 25 2003 14:27:30   HERNANDO
// Prudential Broker Level Fee - PET792.FN07.2 - modified validateAllocPercentage.
// 
//    Rev 1.12   Apr 22 2003 14:31:28   FENGYONG
// change 100.0000 to 100
// 
//    Rev 1.11   Apr 12 2003 18:46:02   HERNANDO
// Sync 1.78.1.0; PTS 10015039 / PTS 10014759
// 
//    Rev 1.10   Mar 21 2003 18:02:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Mar 18 2003 17:38:06   HERNANDO
// [updated] Dev-level revision for AMS.
// 
//    Rev 1.8   Jan 12 2003 18:34:18   KOVACSRO
// Added FundGroup logic for FC rebalancing.
// 
//    Rev 1.7   Oct 09 2002 23:54:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:55:16   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Aug 06 2002 10:00:58   KOVACSRO
// Release 48.
// 
//    Rev 1.4   Jul 09 2002 11:10:22   ZHANGCEL
// PTS ticket 1000887: Allowing XS set up for the TaxType "1,2,C,B,L" .
// 
//    Rev 1.3   22 May 2002 18:26:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   08 May 2002 16:51:58   KOVACSRO
// More implementation.
// 
//    Rev 1.1   12 Apr 2002 16:53:26   KOVACSRO
// More implementation.
 * 
 * 
 */