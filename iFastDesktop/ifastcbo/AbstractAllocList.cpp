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
// ^FILE   : AbstractAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 24/03/02
//
// ^CLASS    : AbstractAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the allocation lists
//
//******************************************************************************
#include "stdafx.h"
#include "abstractalloc.hpp"
#include "abstractalloclist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include "splitcommissionlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AbstractAllocList" );
   const I_CHAR * const UNITS     = I_( "U" );            // amount type
   const I_CHAR * const YES       = I_( "Y" );           
   const I_CHAR * const NO        = I_( "N" );           
   const double dSmallValue       = .0000000001;


}

namespace CND
{
   extern const long ERR_SUM_OF_ALLOC_PERCENTAGES_NOT_100;
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
   extern const long ERR_ALLOCAMOUNT_LESS_THAN_TOTAL; //IN1923112
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;


}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::AccountNum,    BFCBO::NONE, 0 }, 
   { ifds::TransType,     BFCBO::NONE, 0 }, 
   { ifds::Amount,        BFCBO::NONE, 0 }, 
   { ifds::AllocAmtType,  BFCBO::NONE, 0 }, 
   { ifds::Currency,      BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate, BFCBO::NONE, 0 }, 
   { ifds::FromFund,      BFCBO::NONE, 0 }, 
   { ifds::FromClass,     BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
AbstractAllocList::AbstractAllocList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_strKeyForNewItem(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
}

//******************************************************************************
AbstractAllocList::~AbstractAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY AbstractAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   assert( 0 );//should not be called for the current design for allocations

   throw;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AbstractAllocList::doCreateNewObject( BFCBO *& pBase, 
                                               DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   assert( 0 );//should not be called for an abstract class

   throw;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AbstractAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   double dTotalPercent = 0, dTotalAmt = 0, cnt = 0;
   DString strTotAmount, strTotPercent, strParentAmount;

	// Incident 730719 -- We shouldn't check TotPercent if Fund/Class are empty
	bool checkTotPercent = false;
	BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
		DString dstrFundCode, dstrClassCode;
      iter.getObject()->getField(ifds::FundCode, dstrFundCode, idDataGroup);
      dstrFundCode.strip();

      iter.getObject()->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
      dstrClassCode.strip();
		if ( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
		{
			checkTotPercent = true;
			break;
		}
		++iter;
	}
		
   getTotalPercentage(strTotPercent, idDataGroup, false);

	if( checkTotPercent )
   {
		dTotalPercent = DSTCommonFunctions::convertToDouble(strTotPercent);
		if( fabs (dTotalPercent - 100 ) > dSmallValue )
		{
			//ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
			DString allocationTypeDescription, idiStr;
			iter.getObject()->getField(ifds::TransType, allocationTypeDescription, idDataGroup, true);

			if ( allocationTypeDescription != NULL_STRING )
			{
				addIDITagValue( idiStr, I_("ALLOCDESCR"), allocationTypeDescription);
				ADDCONDITIONFROMFILEIDI (CND::ERR_SUM_OF_ALLOC_PERCENTAGES_NOT_100, idiStr);
			}
			else
			{
				ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
			}
		}

		getField(ifds::Amount, strParentAmount, idDataGroup, false);	
		if( !strParentAmount.strip().empty() )
		{
			getTotalAmount(strTotAmount, idDataGroup, false);
			//dTotalAmt = DSTCommonFunctions::convertToDouble(strTotAmount);
			BigDecimal bdTotalAmt = DSTCommonFunctions::convertToBigDecimal(strTotAmount);
			//double dParentAmount = DSTCommonFunctions::convertToDouble(strParentAmount);
			BigDecimal bdParentAmount = DSTCommonFunctions::convertToBigDecimal(strParentAmount);
			//if( dTotalAmt - dParentAmount > dSmallValue )
			//IN1923112
			if( bdTotalAmt != bdParentAmount)
			{
				if( bdTotalAmt > bdParentAmount)
				{
					ADDCONDITIONFROMFILE( CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL );
				}
				else
				{
					ADDCONDITIONFROMFILE( CND::ERR_ALLOCAMOUNT_LESS_THAN_TOTAL );
				}
			}
		}
	}


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AbstractAllocList::getAllocation(const DString& strKey, 
                                      AbstractAlloc *& pAbstractAlloc, 
                                      const BFDataGroupId& idDataGroup)
{
   pAbstractAlloc = NULL;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.positionByKey( strKey ) )
      pAbstractAlloc = static_cast<AbstractAlloc *>( iter.getObject());
}

//******************************************************************************

SEVERITY AbstractAllocList::getFundDetail( const DString& strFundCode, 
                                           const DString& strClassCode, 
                                           FundDetail *&pFundDetail )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   pFundDetail = NULL;
   FundDetailList * pFundDetailList = NULL;

   getMgmtCo().getFundDetailList(  pFundDetailList );

   if( pFundDetailList )
      pFundDetailList->getFundDetail( strFundCode, strClassCode, BF::HOST, pFundDetail);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

AbstractAlloc *AbstractAllocList::getParentAllocation()
{
   return(dynamic_cast<AbstractAlloc *>(getParent()));
}

//******************************************************************************

BFCBO *AbstractAllocList::getTopLevelCBO()
{
   AbstractAlloc* pParentAlloc = NULL;
   pParentAlloc = getParentAllocation();
   if( pParentAlloc )
      return(pParentAlloc->getTopLevelCBO());
   else
   {
      assert(dynamic_cast<BFCBO *>(getParent()));//an allocation list should always have a BFBase parent
      return( dynamic_cast<BFCBO *>(getParent()) );
   }
}
//******************************************************************************

SEVERITY AbstractAllocList::doApplyRelatedChanges( const BFFieldId& fieldId, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( fieldId == ifds::Amount )
   {
      setAmount( idDataGroup );
   }
   else if( fieldId == ifds::AccountNum || fieldId == ifds::EffectiveDate || fieldId == ifds::AllocAmtType
            || fieldId == ifds::TransType || fieldId == ifds::Currency )
   {
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         DString strValue;
         getField(fieldId, strValue, idDataGroup, false);
         iter.getObject()->setField(fieldId, strValue, idDataGroup, false);
         ++iter; 
      }
   }

   setUpdatedFlag(fieldId, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AbstractAllocList::setAmount( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAmount" ) );

   DString strTotalAmount;
   getField(ifds::Amount, strTotalAmount, idDataGroup, false);
   double dTotalAmount = atof(strTotalAmount.strip().asA().c_str());
   double dTotalPercentage = 0;
   double dTotalAllocAmount(0);

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   int iAllocCnt = 0;
   int iAllocNum = iter.getNumberOfItemsInList();
   while( !iter.end() )
   {
      ++iAllocCnt;
      DString strAllocPercent, dstrAllocAmount;
      AbstractAlloc* pAbstractAlloc = dynamic_cast<AbstractAlloc*>(iter.getObject());
      assert(pAbstractAlloc);
      pAbstractAlloc->getField( ifds::AllocPercentage, strAllocPercent, idDataGroup, false );
      double dAllocPercent = DSTCommonFunctions::convertToDouble(strAllocPercent);
      dTotalPercentage += dAllocPercent;
      double dAllocAmount(0);
      if( iAllocCnt < iAllocNum )//if not the last allocation
         dAllocAmount = dAllocPercent * dTotalAmount / 100.0;//alloc amount is calculated as a percentage of the total amount
      else
         dAllocAmount = dTotalAmount - dTotalAllocAmount;//because of the roundings

      dstrAllocAmount = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, dAllocAmount);
      getFormattedAmount(idDataGroup, dstrAllocAmount);
      //don't want to touch the percentage field here
      pAbstractAlloc->m_bSettingAmountField = true;
      pAbstractAlloc->setField(ifds::AllocAmount, dstrAllocAmount, idDataGroup, true, true);
      pAbstractAlloc->m_bSettingAmountField = false;
      dAllocAmount = DSTCommonFunctions::convertToDouble(dstrAllocAmount);
      dTotalAllocAmount += dAllocAmount;

      ++iter; 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void AbstractAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
   DString strCurrency, strAmountType;

   getField(ifds::AllocAmtType, strAmountType, idDataGroup, false);

   if( strAmountType.strip() != UNITS )
      formatAmtUsingCurrency( idDataGroup, dstrValue );
   else
      formatAmtUsingFromFund( idDataGroup, dstrValue );
}
//******************************************************************************

void AbstractAllocList::formatAmtUsingCurrency(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
   DString strCurrency, strAmountType;

   getField(ifds::Currency, strCurrency, idDataGroup, false); 
   getField(ifds::AllocAmtType, strAmountType, idDataGroup, false);

   CurrencyClass::getFormattedValue( getWorkSession(), dstrValue, strCurrency, strAmountType);
}
//******************************************************************************

void AbstractAllocList::formatAmtUsingFromFund(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
   DString dstrUnitsPrecision, dstrFundCode, dstrClassCode, strAmountType;

   getField(ifds::AllocAmtType, strAmountType, idDataGroup, false);
   //we only keep FromFund and FromClass in the top level alloc list
   AbstractAllocList* pTopLevelAlloc = getTopLevelAllocList();
   pTopLevelAlloc->getField(ifds::FromFund, dstrFundCode, idDataGroup, false);
   pTopLevelAlloc->getField(ifds::FromClass, dstrClassCode, idDataGroup, false);
   FundDetail *pFundDetail = NULL;
   if( getFundDetail(dstrFundCode.strip().upperCase(), dstrClassCode.strip().upperCase(), pFundDetail)
       >WARNING || !pFundDetail )
      return;

   if( strAmountType.strip() != UNITS )
   {
      DString strCurrency;
      pFundDetail->getField( ifds::Currency, strCurrency, BF::HOST, false  );
      CurrencyClass::getFormattedValue( getWorkSession(), dstrValue, strCurrency, strAmountType);
   }
   else
   {
      int iUnitsPrecision = 0;

      pFundDetail->getField( ifds::UnitsPrecision, dstrUnitsPrecision, BF::HOST, false  );
      iUnitsPrecision = dstrUnitsPrecision.asInteger(); 
      const BFFieldId& fieldId = ifds::USDollar;
      DSTCommonFunctions::formattedField( fieldId, iUnitsPrecision, dstrValue ); 
   }
}

//******************************************************************************

void AbstractAllocList::getTotalAmount(DString &strTotalAmount, const BFDataGroupId& idDataGroup, bool bFormatted)
{
   getTotalValue(ifds::AllocAmount, strTotalAmount, idDataGroup);
   if( bFormatted )
      getFormattedAmount(idDataGroup, strTotalAmount);
}

//******************************************************************************

void AbstractAllocList::getTotalPercentage(DString &strTotalPercentage, const BFDataGroupId& idDataGroup, bool bFormatted)
{
   getTotalValue(ifds::AllocPercentage, strTotalPercentage, idDataGroup);
}
//******************************************************************************

void AbstractAllocList::getTotalValue( const BFFieldId& fieldId, DString &strTotalValue, const BFDataGroupId& idDataGroup, AbstractAlloc* pCallingAlloc )
{
   assert(fieldId == ifds::AllocAmount || fieldId == ifds::AllocPercentage);
   double dTotalValue = 0;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocValue;
      if( iter.getObject() != (BFAbstractCBO*) pCallingAlloc )
      {
         iter.getObject()->getField( fieldId, strAllocValue, idDataGroup, false );
         double dAllocValue = DSTCommonFunctions::convertToDouble( strAllocValue.strip() );

         dTotalValue += dAllocValue;
      }
      ++iter; 
   }
   strTotalValue = DSTCommonFunctions::doubleToDString(fieldId, dTotalValue);   
}
//******************************************************************************

void AbstractAllocList::GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm )
{
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      iter.getObject()->getField( ifds::SplitComm, dstrSplitComm, idDataGroup );
      if( dstrSplitComm == YES )
         return;
      ++iter;
   }
   dstrSplitComm = NO;
}
//******************************************************************************

SEVERITY AbstractAllocList::setField( const BFFieldId& fieldId,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup,
                                      bool lFormatted,
                                      bool lSideEffect,
                                      bool bCheckCurrentValue)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   int nNoOfCond = CONDITIONCOUNT();
   BFCBO::setFieldNoValidate(fieldId, strValue, idDataGroup, lFormatted, true, lSideEffect);
   //we don't want to promote errors from lower levels to higher levels of allocations (each CBO has to do its own validations)
   int nNewNoOfCond = CONDITIONCOUNT();
   for( int i=nNoOfCond; i<nNewNoOfCond; i++ )
      CLEARCONDITION( i );

   return(NO_SEVERITY);
}
//******************************************************************************

AbstractAllocList* AbstractAllocList::getParentList()
{
   AbstractAlloc* pParent = NULL;
   AbstractAllocList* pParentList = NULL;
   pParent = dynamic_cast<AbstractAlloc *>(getParent());
   if( !pParent )
      return(NULL);

   pParentList = pParent->getParentList();
   return(pParentList);
}
//******************************************************************************

AbstractAllocList* AbstractAllocList::getTopLevelAllocList()
{
   AbstractAllocList* pParentList = getParentList();
   if( pParentList )
      return(pParentList->getTopLevelAllocList());
   else
      return(this);
}
//******************************************************************************

SEVERITY AbstractAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   loadSubstitutions(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AbstractAllocList::setFieldFromCBO(BFCBO* pCBO, const BFFieldId& fromFieldId, const BFFieldId& toFieldId, 
                                            const BFDataGroupId& idDataGroup, DString& strValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFieldFromCBO" ) );

   getField( toFieldId, strValue, idDataGroup, false );
   if( strValue.strip().empty() )
   {
      pCBO->getField( fromFieldId, strValue, idDataGroup, false );
      if( !strValue.strip().empty() )
         setField( toFieldId, strValue, idDataGroup, false );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void AbstractAllocList::getOtherAllocTotalAmount(DString &strTotalAmount, const BFDataGroupId& idDataGroup, bool bFormatted , AbstractAlloc* pCallingAlloc )
{
   getTotalValue(ifds::AllocAmount, strTotalAmount, idDataGroup, pCallingAlloc);
   if( bFormatted )
      getFormattedAmount(idDataGroup, strTotalAmount);
}
//******************************************************************************
void AbstractAllocList::getOtherAllocTotalPercentage(DString &strTotalPercentage, const BFDataGroupId& idDataGroup, bool bFormatted , AbstractAlloc* pCallingAlloc )
{
   getTotalValue(ifds::AllocPercentage, strTotalPercentage, idDataGroup, pCallingAlloc);
}

//******************************************************************************

bool AbstractAllocList::isMultiCurrency()
{
   DString strMultiCurrency;
   getWorkSession().getOption( ifds::MultiCurrency, strMultiCurrency, BF::HOST, false );
   return(strMultiCurrency.strip() == YES);
}
//******************************************************************************

void AbstractAllocList::getStrKeyForNewItem( DString & strKey )
{
   if( !m_strKeyForNewItem.empty() )
      strKey = m_strKeyForNewItem;
   else
      BFCBO::getStrKeyForNewItem( strKey );
}
//******************************************************************************

void AbstractAllocList::modelOffer(AbstractAllocList *pModel, const BFDataGroupId& idDataGroup)
{
   //just in case we already have something here, be sure to clean-up first
   clearAllocations(idDataGroup);

   AbstractAlloc* pAbstractAlloc;
   BFObjectKey objKey;

   for( BFObjIter Iter( *pModel, idDataGroup ); !Iter.end(); ++Iter )
   {
      DString dstrAddCopy = Iter.getStringKey();
      pAbstractAlloc = dynamic_cast< AbstractAlloc * >(getNewListItem( objKey ));
      pAbstractAlloc->modelOffer(dynamic_cast< AbstractAlloc * >( Iter.getObject( ) ), idDataGroup);
   }
}
//******************************************************************************

int AbstractAllocList::getAllocNum(const BFDataGroupId& idDataGroup)
{
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.end() )
      return(0);
   return(iter.getNumberOfItemsInList());
}

//******************************************************************************
void AbstractAllocList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AbstractAllocList.cpp-arc  $
// 
//    Rev 1.21   Sep 02 2010 03:42:22   panatcha
// IN1923112_PET0156612FN00_R96 fixed showing error msg on the allocation amount
// 
//    Rev 1.20   Jun 18 2010 10:23:58   jankovii
// IN 1923112 -  R96_RRIF Transfer_Error Msg displays when Sum of allocation 
// 
//    Rev 1.19   Dec 12 2006 14:08:18   ZHANGCEL
// Incident 730719 -- Fix bug regarding TotPercentages validation
// 
//    Rev 1.18   Nov 14 2004 14:24:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Nov 01 2004 15:20:44   YINGBAOL
// PTS10045342: Fix Round up issue for amount
// 
//    Rev 1.16   Mar 21 2003 17:53:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Nov 28 2002 13:36:00   KOVACSRO
// removed the empty list or dummy item logic from validateAll, since it was causing problems.
// 
//    Rev 1.14   Oct 09 2002 23:53:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.13   Sep 04 2002 15:17:00   KOVACSRO
// In setAmount() notify observers.
// 
//    Rev 1.12   Aug 29 2002 12:54:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   Aug 19 2002 15:26:10   KOVACSRO
// bug fixed in getTotalValue()
// 
//    Rev 1.10   Aug 14 2002 10:26:16   KOVACSRO
// Added getAllocNum
// 
//    Rev 1.9   Aug 06 2002 09:59:40   KOVACSRO
// Release 48. Converted allocations.
// 
//    Rev 1.8   Aug 01 2002 11:18:36   KOVACSRO
// get FromFund, FromClass from the top level alloc list
// 
//    Rev 1.7   Jul 31 2002 14:25:36   KOVACSRO
// Added getStrKeyForNewItem
// 
//    Rev 1.6   Jun 27 2002 17:18:36   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.5   Jun 20 2002 13:35:40   KOVACSRO
// Added is multicurrency
// 
//    Rev 1.4   22 May 2002 18:26:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:48:54   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:19:10   KOVACSRO
// Added a couple of methods.
// 
//    Rev 1.1   12 Apr 2002 16:51:10   KOVACSRO
// More implementation.
 * 
 * 
 */