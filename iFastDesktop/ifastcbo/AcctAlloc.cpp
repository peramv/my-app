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
// ^FILE   : AcctAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : AcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the account allocations 
//
//******************************************************************************
#include "stdafx.h"
#include "acctalloc.hpp"
#include "fundalloclist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctAlloc" );

}

namespace CND
{  // Conditions used
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId Currency;
}


//******************************************************************************
AcctAlloc::AcctAlloc( BFAbstractCBO &parent ) 
: AbstractAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
AcctAlloc::~AcctAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY AcctAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AbstractAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::AccountNum || idField == ifds::EffectiveDate || idField == ifds::AllocAmtType
       || idField == ifds::TransType || idField == ifds::AllocAmount ||
		 idField == ifds::Currency )
   {
      FundAllocList *pFundAllocList = NULL;
      getFundAllocationList(pFundAllocList, idDataGroup, false, false);
      if( pFundAllocList )
      {
         DString strValue;
         getField(idField, strValue, idDataGroup, false);
         if( idField == ifds::AllocAmount )
            pFundAllocList->setField(ifds::Amount, strValue, idDataGroup, false);
         else
            pFundAllocList->setField(idField, strValue, idDataGroup, false);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( AbstractAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::AccountNum )
      validateAccountNum( strValue, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAlloc::validateAccountNum( const DString& strValue, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAccountNum" ) );

   DString dstrAccountNum( strValue );
   dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
   if( dstrAccountNum == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   MFAccount *pMFAccount=NULL;
   if( getMFAccount(pMFAccount, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAlloc::getMFAccount( MFAccount *&pAcctOut, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMFAccount" ) );

   pAcctOut = NULL;
   DString strAccountNum;
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   if( strAccountNum.strip().stripLeading('0').empty() )//account num hasn't been entered yet
      return(GETCURRENTHIGHESTSEVERITY());

   getWorkSession().getMFAccount( idDataGroup, strAccountNum, pAcctOut, I_("N"), NULL_STRING, true, true  );//validate account num

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAlloc::setAllocFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAllocFields" ) );

   AbstractAllocList *pParentList = getParentList();
   DString str;
   pParentList->getField(ifds::TransType, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::TransType, str, idDataGroup, false);
   pParentList->getField(ifds::EffectiveDate, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::EffectiveDate, str, idDataGroup, false);
   pParentList->getField(ifds::AllocAmtType, str, idDataGroup, false);
   if( !str.strip().empty() )
      setField(ifds::AllocAmtType, str, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AcctAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   loadSubstitutions( idDataGroup );
   setAllocFields(idDataGroup);
   setAmount(idDataGroup);
}

//******************************************************************************

SEVERITY AcctAlloc::getFundAllocationList(FundAllocList *&pFundAllocList, const BFDataGroupId& idDataGroup, bool bCreate, bool bGetDefault )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundAllocationList" ) );

   pFundAllocList = dynamic_cast<FundAllocList *>( BFCBO::getObject( FUNDALLOCATIONLIST, idDataGroup ) );
   if( !pFundAllocList && bCreate )
      assert(0);//never try to instantiate FundAllocList abstract class!

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAlloc::hasInternationalWireFundAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                                  bool &bIsInternationalWire, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "hasInternationalWireAlloc" ) );

   FundAllocList* pFundAllocList = NULL;
   getFundAllocationList(pFundAllocList, idDataGroup, false, false);
   if( pFundAllocList )
      pFundAllocList->hasInternationalWireAlloc(strSettleCurrency, strCountryCode, bIsInternationalWire, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctAlloc.cpp-arc  $
// 
//    Rev 1.11   Nov 01 2004 15:20:44   YINGBAOL
// PTS10045342: Fix Round up issue for amount
// 
//    Rev 1.10   Mar 21 2003 17:55:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:54:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Aug 06 2002 10:00:30   KOVACSRO
// Release 48. 
// 
//    Rev 1.6   Jun 27 2002 17:18:56   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.5   Jun 07 2002 17:41:36   KOVACSRO
// International Wire modifications.
// 
//    Rev 1.4   22 May 2002 18:26:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:49:34   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:20:32   KOVACSRO
// Added Amount field in doApplyRelatedChanges()
// 
//    Rev 1.1   12 Apr 2002 16:51:54   KOVACSRO
// More implementation.
 * 
 * 
 */