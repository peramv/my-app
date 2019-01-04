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
// ^FILE   : RRIFFundAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : RRIFFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : RRIF fund allocation
//
//******************************************************************************
#include "stdafx.h"
#include "rriffundalloc.hpp"
//#include "acctalloc.hpp"
//#include "funddetail.hpp"
#include "mfaccount.hpp"
#include "abstractalloclist.hpp"
//#include "splitcommissionlist.hpp"
#include <ifastdataimpl\dse_dstc0068_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME              = I_( "RRIFFundAlloc" );
   const I_CHAR * const NO                     = I_( "N" );
   const I_CHAR * const YES                    = I_( "Y" );
   const I_CHAR * const REDEMPTION_CODE        = I_( "PW" );      // trade trans type Redemption
   const double dSmallValue                    = .0000000001;

}

namespace CND
{  // Conditions used
   extern const long ERR_WARN_FUND_IN_FOREIGN_CURRENCY;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;
   extern const long ERR_FULL_WITHDRAW_FOR_OMNIBUS_ACCT;
   extern const long ERR_RIF_NON_FRACTIONAL;               
   extern const long ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT;   
   extern const long ERR_RIF_ZERO_ALLOC_AMOUNT;            


}

namespace ifds
{  
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId RRIFTransType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;

}
//******************************************************************************

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					      Group Flags
   { ifds::FundClass, BFCBO::IMMEDIATE_VALIDATION, 0 }
};

/*const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );*/

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
RRIFFundAlloc::RRIFFundAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,
                       /*NUM_OBJECTS*/NULL, /*(const CLASS_OBJECT_INFO *)&classObjectInfo*/NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
}

//******************************************************************************
RRIFFundAlloc::~RRIFFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY RRIFFundAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void RRIFFundAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   FundAlloc::doInitWithDefaultValues( idDataGroup );
   DString strStatus;
   getTopLevelCBO()->getField(ifds::GoodBad,strStatus,idDataGroup,false);
   if( strStatus.strip()!=YES )
      setAllocFieldsReadOnly(idDataGroup);
}

//******************************************************************************

SEVERITY RRIFFundAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   setFundNumber(BF::HOST);//because ToFundNumber doesn't come from the host

   loadSubstitutions(BF::HOST);
   setAllocFields(BF::HOST);

   DString strStatus;
   getTopLevelCBO()->getField(ifds::GoodBad,strStatus,BF::HOST,false);
   if( strStatus.strip()!=YES )
      setAllocFieldsReadOnly(BF::HOST);

   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIFFundAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());


   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundCode )
      validateFundCode( strValue, idDataGroup );
   else if( idField == ifds::ClassCode )
      validateClassCode( strValue, idDataGroup );
   else if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );
   else if( idField == ifds::AllocAmount )
      validateAmount( strValue, idDataGroup );
   else if( idField == ifds::AllocPercentage )
      validatePercentage(strValue, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAlloc::validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   //validation for blank fund and isFundExist in FundMasterList is already done by FundAlloc superclass

   DString dstrFundCode( strValue );

   //cash fund code is invalid for default fund allocations
   if( dstrFundCode.strip().upperCase() == I_( "CASH" ) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAlloc::validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClassCode" ) );

   //validation for blank class code is done by FundAlloc

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIFFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );
   DString dstrClassCode, dstrFundCode, dstrTransNum;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

   //if ( !(getFundDetail( dstrFundCode, dstrClassCode, pFundDetail )) )
   //   ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES ); ------->  done by FundAlloc superclass
   //only validation that doesn't require the account number, should go in here
   //everything else should go into validateTransTypeFundClass()

   DString dstrEffectiveDate;
   DString AMSCode_4;
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   dstrEffectiveDate.strip();

   DString dstrTransTypeParam = REDEMPTION_CODE;

   MFAccount *pMFAccount = NULL;

   if( getMFAccount(pMFAccount, idDataGroup)<=WARNING && pMFAccount )
   {
      pMFAccount->canTradeFundClass (dstrFundCode, dstrClassCode, dstrTransTypeParam, dstrEffectiveDate, idDataGroup);
      pMFAccount->AMSFundAllow ( dstrFundCode, dstrClassCode, idDataGroup );
   }


   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAlloc::initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefault" ) )

   FundAlloc::initDefault(pDefaultAlloc, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAlloc::copyDataFromParent(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   BFCBO* pBFCBO = getTopLevelCBO();
   DString strTemp, strTransType;

   pBFCBO->getField(ifds::AccountNum, strTemp, idDataGroup, false);
   setFieldNoValidate(ifds::AccountNum, strTemp, idDataGroup, false, false);

   pBFCBO->getField ( ifds::rxFundCode, strTemp, idDataGroup, false );
   setFieldNoValidate( ifds::FundCode, strTemp, idDataGroup, false, false );

   pBFCBO->getField ( ifds::rxClassCode, strTemp, idDataGroup, false );
   setFieldNoValidate( ifds::ClassCode, strTemp, BF::HOST, false );     // TODO:  Should be idDataGroup???

   pBFCBO->getParent()->getField ( ifds::Currency, strTemp, idDataGroup, false );//get Currency from MFAccount
   setFieldNoValidate( ifds::SettleCurrency, strTemp, BF::HOST, false );   // TODO:  Should be idDataGroup???

   //set the fund number
   setFundNumber(idDataGroup);

   //setFieldNoValidate( ifds::TransSeq, I_("0"), false, false );

   //it only makes sense to copy data from the parent for a 100% allocation
   setField( ifds::AllocPercentage, I_("100"), idDataGroup, false);//this will also set the amount field

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIFFundAlloc::validateAmount( const DString& strValue, 
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );
   // validation for amount not to exceed total is done by AbstractAlloc class
   // if trade total amount is zero, there is no need to do the validation

   DString dstrTotalAmount;
   getParentList()->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount.strip());
   if( dTotalAmount <= dSmallValue )
      return(NO_CONDITION);

   DString dstrAmount(strValue);
   dstrAmount.strip().stripAll(I_CHAR(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);

   ////// Amount must be > 0 , cannot be  negative for all transtype; must be <= 12 digits /////
   if( dAmount < 0 )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_RIF_OUT_OF_LIMITS_ALLOC_AMOUNT, I_( "FIELDNAME=AllocAmount " ) );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if( dAmount > 999999999999 )
   {
      DString FieldName(I_("999,999,999,999.00"));
	  DSTCommonFunctions::DisplayFormat( FieldName, ifds::Amount );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AMOUNT_EXCEED_MAX_LIMIT, (I_("Amount=")+FieldName).c_str() );
      return(GETCURRENTHIGHESTSEVERITY());;
   }
   else if( dAmount <= dSmallValue )
   {
      // warning: When Accounts Amount is zero, only funds percent is allowed.
      ADDCONDITIONFROMFILE( CND::ERR_RIF_ZERO_ALLOC_AMOUNT );
   }

   validateFractional(strValue, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************

SEVERITY RRIFFundAlloc::validatePercentage( const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCrossAmount"));

   validateFractional(strValue, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************************************

SEVERITY RRIFFundAlloc::validateFractional(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCrossAmount"));

   DString dstrFundCode, dstrClassCode, strVal(strValue);
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   DString dstrCurrency;
   CurrencyClass::getFundCurrency( getWorkSession(), dstrFundCode, dstrClassCode, dstrCurrency );

   int precision =  CurrencyClass::getPrecision(getWorkSession(), dstrCurrency);

   if( precision == 0 )
   {
      double dValue = DSTCommonFunctions::convertToDouble(strVal);
      if( dValue != floor( dValue ) )
      {
         // Error: Fractional values not allowed when Precision = 0.
         ADDCONDITIONFROMFILE( CND::ERR_RIF_NON_FRACTIONAL );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

BFData * RRIFFundAlloc::getDataForModelOffer()
{
   return(new BFData(ifds::DSTC0068_VWRepeat_Record));
}
//******************************************************************************

SEVERITY RRIFFundAlloc::getSplitCommissionList ( SplitCommissionList *&pSplitCommissionList, const BFDataGroupId& idDataGroup, 
                                                 bool bCreate /*= true*/,
                                                 bool bGetDefault /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSplitCommissionList" ) );

   pSplitCommissionList=NULL;//no split commissions for rrif allocations

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIFFundAlloc::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFFundAlloc.cpp-arc  $
// 
//    Rev 1.10   Jul 11 2005 17:24:18   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.9   Nov 14 2004 14:53:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Nov 06 2004 00:42:32   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.7   Apr 22 2003 14:30:56   FENGYONG
// change 100.00 to 100
// 
//    Rev 1.6   Mar 21 2003 18:22:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:56:32   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   Aug 20 2002 10:49:54   KOVACSRO
// just return a NULL pointer for split commissions; 
// 
//    Rev 1.2   Aug 19 2002 15:27:34   KOVACSRO
// 1. introduced RRIFTransType
// 2. checking RRIF status to enable/disable alloc fields
// 
//    Rev 1.1   Aug 06 2002 11:25:16   KOVACSRO
// Removed RifId
// 
//    Rev 1.0   Aug 06 2002 10:50:18   KOVACSRO
// Initial revision.
 * 
 * 
 */