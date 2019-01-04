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
// ^FILE   : TradeAcctAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeAcctAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade, PendingTradeDetails and TransactionDetails account allocation
//
//******************************************************************************
#include "stdafx.h"
#include "tradeacctalloc.hpp"
#include "tradefundalloclist.hpp"
#include "mfaccount.hpp"

namespace
{
   const I_CHAR * const CLASSNAME                  = I_( "TradeAcctAlloc" );
   const I_CHAR * const YES                        = I_( "Y" );
   const I_CHAR * const NO                         = I_( "N" );

   const I_CHAR * const PURCHASE_CODE              = I_( "ED" );    // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE            = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const TRANSFER_CODE              = I_( "TR" );

   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out

   //because of the templated method, we have to use the same name for all the FundAllocationLists in the classes derived from AccountAlloc
   extern const I_CHAR * const FUNDALLOCATIONLIST;


}

namespace CND
{  // Conditions used
   /* extern const long ERR_INVALID_RXTRANSTYPE_TAXTYPE_COMBINATION;
    extern const long ERR_ALLOC_FOR_INACTIVE_ACCT;*/

}

namespace ifds
{  
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFDecimalFieldId DistribDetlRid;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFDecimalFieldId AcctPrcnt;
   extern CLASS_IMPORT const BFIntegerFieldId AcctLvlRid;
   extern CLASS_IMPORT const BFIntegerFieldId AcctLvlVer;
   extern CLASS_IMPORT const BFDecimalFieldId DistribDetlVer;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					      Group Flags
   {ifds::AcctLvlRid,        BFCBO::NONE, 0}, 
   {ifds::AcctLvlVer,         BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TradeAcctAlloc::TradeAcctAlloc( BFAbstractCBO &parent ) 
: AcctAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING ); 
   registerMemberData(NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL );
 

}

//******************************************************************************
TradeAcctAlloc::~TradeAcctAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY TradeAcctAlloc::initNew( const BFDataGroupId& idDataGroup,
                                  const DString& dstrTrack ,
                                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();
   setFieldNoValidate(ifds::AccountNum, I_("0"), BF::HOST, false, false);//zero is an invalid value

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TradeAcctAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 

   DString str;
   data.getElementValue( ifds::AcctPrcnt, str );
   //because AcctLvlPercent is not in view 60, we have to set it here - this is done by doApplyRelatedChanges for AllocPercentage
   setFieldNoValidate(ifds::AllocPercentage, str, BF::HOST, false, true);
   data.getElementValue( ifds::AcctLvlRid, str );
   setFieldNoValidate(ifds::DistribDetlRid, str, BF::HOST, false, true);
   data.getElementValue( ifds::AcctLvlVer, str );
   setFieldNoValidate(ifds::DistribDetlVer, str, BF::HOST, false, true);
   setAllocFields(BF::HOST);
   //have to create the trade fund allocation list
   TradeFundAllocList* pTradeFundAllocList = new TradeFundAllocList(*this);
   setObject(pTradeFundAllocList, FUNDALLOCATIONLIST);
   pTradeFundAllocList->initExisting();

   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void TradeAcctAlloc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   AcctAlloc::doInitWithDefaultValues(idDataGroup);
   setFieldNoValidate( ifds::AllocPercentage, I_("100"), idDataGroup, false );//after we'll allow multiple account allocations, delete this line

   clearUpdatedFlags( idDataGroup );
}
//******************************************************************************

SEVERITY TradeAcctAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AcctAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY TradeAcctAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( AcctAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY TradeAcctAlloc::copyDataFromParent(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   //it only makes sense to copy data for a 100% allocation
   setField( ifds::AllocPercentage, I_("100"), idDataGroup, false);//this will also set the amount field

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************
void TradeAcctAlloc::changeFieldsForRebook()
{
   setFieldNoValidate( ifds::AcctLvlRid, NULL_STRING, BF::HOST, false,true,false,false ); // no related changes
   setFieldNoValidate( ifds::AcctLvlVer, NULL_STRING, BF::HOST, false,true,false,false ); // no related changes

   TradeFundAllocList* pFundAllocationList = NULL;
   getFundAllocationList (pFundAllocationList, BF::HOST);
   if( pFundAllocationList )
   {
      pFundAllocationList->changeFieldsForRebook();   
   }
   clearUpdatedFlags( BF::HOST ); // the object should not be dirty 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeAcctAlloc.cpp-arc  $
// 
//    Rev 1.11   Jul 15 2005 09:20:44   Yingbaol
// PET1235,FN01: Add Record ID ro field info
// 
//    Rev 1.10   Jul 08 2005 09:33:04   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.9   Nov 14 2004 14:57:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Apr 22 2003 14:29:28   FENGYONG
// change 100.0000 and 100.00 to 100
// 
//    Rev 1.7   Mar 21 2003 18:26:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:55:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:56:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jun 27 2002 17:20:48   KOVACSRO
// small change
// 
//    Rev 1.3   24 May 2002 15:48:22   KOVACSRO
// small change
// 
//    Rev 1.2   22 May 2002 18:30:04   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   08 May 2002 17:00:50   KOVACSRO
// More implementation.
// 
//    Rev 1.0   29 Apr 2002 16:57:48   KOVACSRO
// Initial revision.
 * 
 * 
 */