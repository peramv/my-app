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
// ^FILE   : AbstractAlloc.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : AbstractAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the allocations 
//
//******************************************************************************
#include "stdafx.h"
#include "abstractalloc.hpp"
#include "abstractalloclist.hpp"
#include "funddetail.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AbstractAlloc" );
   const I_CHAR * const UNITS     = I_( "U" );            // amount type
   const double dSmallValue       = .0000000001;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
	extern const long ERR_VALUE_CANNOT_BE_ZERO;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFNumericFieldId AllocAccountNum;
   extern CLASS_IMPORT const BFTextFieldId SplitCommPAC;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId DistribDetlVer;
   extern CLASS_IMPORT const BFDecimalFieldId DistribDetlRid;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId Level;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::AllocAmount,     BFCBO::NONE, 0 }, 
   { ifds::AllocPercentage, BFCBO::NONE, 0 }, 
   { ifds::AccountNum,      BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate,   BFCBO::NONE, 0 }, 
   { ifds::TransType,       BFCBO::NONE, 0 }, 
   { ifds::Level,           BFCBO::NONE, 0 }, 
   { ifds::AllocAmtType,    BFCBO::NONE, 0 }, 
   { ifds::SplitComm,       BFCBO::NONE, 0 }, 
   { ifds::DistribDetlVer,  BFCBO::NONE, 0 }, 
   { ifds::DistribDetlRid,  BFCBO::NONE, 0 }, 
   { ifds::Currency,		  BFCBO::NONE, 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
AbstractAlloc::AbstractAlloc( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_bSettingAmountField(false),
m_bSettingPercentField(false),
m_bInitDefault(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
}

//******************************************************************************
AbstractAlloc::~AbstractAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY AbstractAlloc::getFundDetail( const DString& strFundCode, 
                                       const DString& strClassCode, 
                                       FundDetail *&pFundDetail )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundDetail" ) );

   getParentList()->getFundDetail(strFundCode, strClassCode, pFundDetail);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

AbstractAllocList* AbstractAlloc::getParentList()
{
   AbstractAllocList* pParent = NULL;
   pParent = dynamic_cast<AbstractAllocList *>(getParent());
   assert(pParent);
   return(pParent);
}

//******************************************************************************

BFCBO *AbstractAlloc::getTopLevelCBO()
{
   return(getParentList()->getTopLevelCBO());
}
//******************************************************************************

SEVERITY AbstractAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::AllocAmount )
      setPercentage(idDataGroup);
   else if( idField == ifds::AllocPercentage )
      setAmount(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AbstractAlloc::setAmount( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAmount" ) );

   DString strParentAmount, strAllocPercentage, strAllocAmount, strTotalAllocPercentage;
   getParentList()->getField(ifds::Amount, strParentAmount, idDataGroup, false);
   getField(ifds::AllocPercentage, strAllocPercentage, idDataGroup, false);

   if( !m_bSettingPercentField && !strParentAmount.strip().empty() && !strAllocPercentage.strip().empty() )
   {
      getParentList()->getTotalPercentage(strTotalAllocPercentage, idDataGroup);
      double dTotalAllocPercentage = DSTCommonFunctions::convertToDouble(strTotalAllocPercentage);
      double dParentAmount = DSTCommonFunctions::convertToDouble(strParentAmount);
      double dAllocPercentage = DSTCommonFunctions::convertToDouble(strAllocPercentage);
      double dAllocAmount = 0.0;
      if( fabs(dTotalAllocPercentage-100) < dSmallValue )
      {
         //if this is the last allocation, because of the roundings:
         DString strOtherAllocTotalAmount;
         getParentList()->getOtherAllocTotalAmount(strOtherAllocTotalAmount, idDataGroup, true, this);
         double dOtherAllocTotalAmount = DSTCommonFunctions::convertToDouble(strOtherAllocTotalAmount);
         dAllocAmount = dParentAmount - dOtherAllocTotalAmount;
         //if something went wrong, just don't do the roundings
         double dTemp = dParentAmount * dAllocPercentage / 100.0;
         if( fabs(dTemp-dAllocAmount)>0.1 )
         {
            dAllocAmount = int(dTemp);
            //assert(0);
         }
      }
      else
         dAllocAmount = dParentAmount * dAllocPercentage / 100.0;

      strAllocAmount = DSTCommonFunctions::doubleToDString( ifds::AllocAmount, dAllocAmount );  
      getTopLevelAllocList()->getFormattedAmount(idDataGroup, strAllocAmount);
      m_bSettingAmountField = true;
      setField( ifds::AllocAmount, strAllocAmount, idDataGroup, true, true );
      m_bSettingAmountField = false;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AbstractAlloc::setPercentage( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setPercentage" ) );

   DString strParentAmount, strAllocPercentage, strAllocAmount, strTotalAllocAmount;
   getParentList()->getField(ifds::Amount, strParentAmount, idDataGroup, false);
   getField(ifds::AllocAmount, strAllocAmount, idDataGroup, false);
   if( !m_bSettingAmountField && !strParentAmount.strip().empty() && !strAllocAmount.strip().empty() )
   {
      double dParentAmount = DSTCommonFunctions::convertToDouble(strParentAmount);
      double dAllocAmount = DSTCommonFunctions::convertToDouble(strAllocAmount);
      if( fabs(dAllocAmount) > dSmallValue && fabs(dParentAmount) > dSmallValue )//if both total amount and alloc amount are not zero, set the alloc percentage
      {
         double dAllocPercentage = 0;
         getParentList()->getTotalAmount(strTotalAllocAmount, idDataGroup);
         double dTotalAllocAmount = DSTCommonFunctions::convertToDouble(strTotalAllocAmount);
         if( fabs(dParentAmount-dTotalAllocAmount) < dSmallValue )
         {
            //if this is the last allocation, because of the roundings:
            DString strOtherAllocTotalPercent;
            getParentList()->getOtherAllocTotalPercentage(strOtherAllocTotalPercent, idDataGroup, false, this);
            double dOtherAllocTotalPercent = DSTCommonFunctions::convertToDouble(strOtherAllocTotalPercent);
            dAllocPercentage = 100.0 - dOtherAllocTotalPercent;
            //if something went wrong, just don't do the roundings
            double dTemp = dAllocAmount / dParentAmount * 100.0;
            if( fabs(dTemp-dAllocPercentage)>0.1 )
            {
               dAllocPercentage = dTemp;
               //assert(0);
            }
         }
         else
            dAllocPercentage = dAllocAmount / dParentAmount * 100.0;

         strAllocPercentage = DSTCommonFunctions::doubleToDString( ifds::AllocPercentage, dAllocPercentage );  
         m_bSettingPercentField = true;
         setField( ifds::AllocPercentage, strAllocPercentage, idDataGroup, true, true );
         m_bSettingPercentField = false;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AbstractAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::AllocPercentage )
      validatePercentage(strValue, idDataGroup);
   else if( idField == ifds::AllocAmount )
      validateAmount(strValue, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AbstractAlloc::validatePercentage ( const DString& strValue, 
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePercentage"));

   double dec_percent = DSTCommonFunctions::convertToDouble (strValue);

   if (dec_percent == 0)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
   }
   else
   {
      if (dec_percent < 0 - dSmallValue || dec_percent > 100 + dSmallValue)
      {
         ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);
      }	
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AbstractAlloc::validateAmount(const DString& strAmount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );

   DString strTotalAmount;
   BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
   getParentList()->getField(ifds::Amount, strTotalAmount, idDataGroup, false);

   /*
    * INC0030155 : When we access the split commission from 'Transaction History' screen, 
	* the 'strAmount' in the function parameter is a formatted amount. But 'strTotalAmount' is not formatted.
	* Both should be in the same format, otherwise it will leads to the ALLOCAMOUNT_GREATER_THAN_TOTAL error
    */
   
   getTopLevelAllocList()->getFormattedAmount(idDataGroup, strTotalAmount); 
   BigDecimal dTotalAmount = DSTCommonFunctions::convertToBigDecimal(strTotalAmount);
   BigDecimal dAllocAmount = DSTCommonFunctions::convertToBigDecimal(strAmount);
   if( dAllocAmount - dTotalAmount > bdZero )
      ADDCONDITIONFROMFILE( CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL ); 
   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************

AbstractAllocList* AbstractAlloc::getTopLevelAllocList()
{
   return(getParentList()->getTopLevelAllocList());  
}
//*******************************************************************************
SEVERITY AbstractAlloc::initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefault" ) );

   m_bInitDefault = true;
   DString str;

   //because we want a smooth reset, we won't set this object new and then call initDefault again in 
   //doInitWithDefaultValues using idDataGroup
   //we'll set all these fields using BF::HOST

   pDefaultAlloc->getField(ifds::AccountNum, str, idDataGroup, false);
   //OOPS: new allocations have been added which don't follow the allocation design
   //if we're using these non AbstractAllocs to init default, they might not contain the account
   //number; basically, if account number is empty, get it from the parent 
   if (str.strip().empty())
      getParentList()->getField(ifds::AccountNum, str, idDataGroup, false);
   setFieldNoValidate(ifds::AccountNum, str, BF::HOST, false, false);

   setFieldNoValidate(ifds::DistribDetlRid, I_("0"), BF::HOST, false);

   pDefaultAlloc->getField(ifds::AllocPercentage, str, idDataGroup, false);
   m_bSettingPercentField = true;
   setFieldNoValidate(ifds::AllocPercentage, str, BF::HOST, false, false);
   m_bSettingPercentField = false;


   getParentList()->getField(ifds::TransType, str, idDataGroup, false);
   setFieldNoValidate(ifds::TransType, str, BF::HOST, false);
   getParentList()->getField(ifds::EffectiveDate, str, idDataGroup, false);
   setFieldNoValidate(ifds::EffectiveDate, str, BF::HOST, false);
   getParentList()->getField(ifds::AllocAmtType, str, idDataGroup, false);
   setFieldNoValidate(ifds::AllocAmtType, str, BF::HOST, false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void AbstractAlloc::modelOffer(AbstractAlloc *pModel, const BFDataGroupId& idDataGroup)
{
   BFData* pTempData = NULL;
   pTempData = getDataForModelOffer();
   assert(pTempData);

   BFDataFieldIter dIter( *pTempData );
   DString str;
   for( ;dIter; ++dIter )
   {
      const BFFieldId& idField = dIter().getId();
      if( idField != ifds::AllocAmount )
      {
         pModel->getField( idField, str, idDataGroup, false );
         if( idField == ifds::DistribDetlRid || idField == ifds::DistribDetlVer )
            setFieldNoValidate(idField, I_("0"), idDataGroup, false, true);
         else setFieldNoValidate(idField, str, idDataGroup, false, false);
      }
   };
   clearUpdatedFlags( idDataGroup );
   delete pTempData;
}
//******************************************************************************

void AbstractAlloc::getField( const BFFieldId& idField, DString & strValue, const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   if( idField==ifds::AllocAmount && formattedReturn )
   {
      getField( idField, strValue, idDataGroup, false );
      const_cast<AbstractAlloc*>(this)->getTopLevelAllocList()->getFormattedAmount(idDataGroup, strValue);
   }
   else
      MFCanBFCbo::getField( idField, strValue, idDataGroup, formattedReturn );
}
//******************************************************************************

void AbstractAlloc::setAllocFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly)
{
   setFieldReadOnly( ifds::AllocPercentage, idDataGroup, bReadOnly );
   setFieldReadOnly( ifds::AllocAmount, idDataGroup, bReadOnly );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractAlloc.cpp-arc  $
// 
//    Rev 1.19   Jan 15 2007 15:17:40   popescu
// Incident #787615 - Fix 0 percent issue
// 
//    Rev 1.18   Dec 28 2006 15:28:54   ZHANGCEL
// Incident #787615 - Fix 0 percent issue
// 
//    Rev 1.17   Feb 08 2006 15:27:36   fengyong
// Incident 540005 - fix rounding issue
// 
//    Rev 1.16   Nov 14 2004 14:23:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.15   Nov 01 2004 15:20:46   YINGBAOL
// PTS10045342: Fix Round up issue for amount
// 
//    Rev 1.14   Mar 21 2003 17:53:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Nov 29 2002 10:43:42   KOVACSRO
// data group changes
// 
//    Rev 1.12   Oct 09 2002 23:53:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 12:54:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Aug 20 2002 10:59:20   KOVACSRO
// modelOffer shouldn't copy DistribdetlRid and DistribDetlVer.
// 
//    Rev 1.9   Aug 19 2002 15:19:48   KOVACSRO
// Added 1. getField and 2. setAllocFieldsReadOnly
// 
//    Rev 1.8   Aug 06 2002 09:59:24   KOVACSRO
// Release 48. Added modelOffer
// 
//    Rev 1.7   Jul 31 2002 16:39:56   KOVACSRO
// small change.
//
//    Rev 1.6   Jun 27 2002 17:18:12   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.5   24 May 2002 15:42:28   KOVACSRO
// removed an assert()
// 
//    Rev 1.4   22 May 2002 18:25:58   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:48:08   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:17:12   KOVACSRO
// Added initDefault(), other...
// 
//    Rev 1.1   12 Apr 2002 16:50:26   KOVACSRO
// More implementation.
 * 
 * 
 */