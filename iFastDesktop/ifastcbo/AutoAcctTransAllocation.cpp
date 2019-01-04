//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : AutoAcctTransAllocation.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AutoAcctTransAllocation
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "autoaccttransallocation.hpp"
#include "autoaccttransallocationlist.hpp"
#include "autotransallocationlist.hpp"
#include "autotransallocation.hpp"

#include "dstcommonfunction.hpp"
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0084_req.hpp>
#include <ifastdataimpl\dse_dstc0095_req.hpp>
#include <ifastdataimpl\dse_dstc0098_vwrepeat_record.hpp>
#include "systematic.hpp"
#include "dstcworksession.hpp"
#include "mfaccount.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AutoAcctTransAllocation" );
   const I_CHAR * const AUTO_TRANS_ALLOCATION_LIST = I_("AutoTransAllocationList");
   const I_CHAR * const NO = I_("N");
   const I_CHAR * const YES = I_("Y");
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::RunMode,         BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::TransType,       BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::PACSWPId,        BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::FundCode,        BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::ClassCode,       BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::Percentage,      BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::AllocAmount,     BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::SettleCurrency,  BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::DistribDetlVer,  BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::DistribDetlRid,  BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::Level,           BFCBO::INIT_TO_DEFAULT, 0 }, 
   { ifds::AllocAccountNum, BFCBO::INIT_TO_DEFAULT, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AutoAcctTransAllocation::AutoAcctTransAllocation( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _pAtAllocationList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
}

//******************************************************************************
AutoAcctTransAllocation::~AutoAcctTransAllocation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AutoAcctTransAllocation::getAtAllocationList(AutoTransAllocationList *&pAtAllocationList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getATFundAllocationList" ) );
   pAtAllocationList = _pAtAllocationList;
   return(GETCURRENTHIGHESTSEVERITY());

}

//****************************************************************************
SEVERITY AutoAcctTransAllocation::initAtAlloc(const BFDataGroupId& idDataGroup, 
   const BFData &pViewData, const DString& strKey, const DString& strAccount,
   bool bHasAcct)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAtAlloc" ) );

   _pAtAllocationList = new AutoTransAllocationList(*this);
   _pAtAllocationList->setSystematicPtr(getSystematicPtr());
   _pAtAllocationList->init(this, idDataGroup, strKey, strAccount, pViewData, bHasAcct);
   setObject(_pAtAllocationList, AUTO_TRANS_ALLOCATION_LIST, OBJ_ACTIVITY_NONE, BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY  AutoAcctTransAllocation::initNewAtAllocation( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AutoAcctTransAllocation" ) );   

   _pAtAllocationList = new AutoTransAllocationList(*this);
   _pAtAllocationList->setSystematicPtr(getSystematicPtr());
   _pAtAllocationList->initNew(this, idDataGroup);
   setObject( _pAtAllocationList, AUTO_TRANS_ALLOCATION_LIST, OBJ_ACTIVITY_NONE, BF::HOST );
   _pAtAllocationList->setSystematicPtr(getSystematicPtr());

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AutoAcctTransAllocation::init(const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

   attachDataObject(const_cast<BFData&>(viewData), false, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AutoAcctTransAllocation::init( const DString& strAcct, const DString& strFundTo, 
   const DString& strClassTo, const DString& strAmount)
{
   setFieldNoValidate(ifds::FundCode, strFundTo,BF::HOST,false,false,true);
   setFieldNoValidate(ifds::ClassCode, strClassTo,BF::HOST,false,false,true);
   setFieldNoValidate(ifds::AllocAccountNum, strAcct,BF::HOST,false,false,true);
   setFieldNoValidate(ifds::Percentage, I_("100"), BF::HOST, false, false, true);
   setFieldNoValidate(ifds::AllocAmount, strAmount, BF::HOST, false, false, true);
}

//******************************************************************************
void AutoAcctTransAllocation::getField(const BFFieldId& idField, DString &dstrFieldValue, 
   const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField(idField, dstrFieldValue, idDataGroup, formattedReturn);
   if (idField == ifds::AllocAmount && formattedReturn)
   {
      BFCBO::getField( idField, dstrFieldValue, idDataGroup,false );  
      getSystematicPtr()->getFormattedAmount(idDataGroup,dstrFieldValue);
   }
   else if (idField == ifds::Percentage || idField == ifds::AllocAccountNum)
   {
      dstrFieldValue.stripLeading('+');
      //if(idField == ifds:: AllocAccountNum)dstrFieldValue.stripLeading('0');
   }
}

//******************************************************************************
SEVERITY AutoAcctTransAllocation::setField( const BFFieldId& idField, 
                                            const DString& dstrValue,
                                            const BFDataGroupId& idDataGroup, 
                                            bool bFormatted, 
                                            bool bSideEffect,
                                            bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );
   DString oldValue;
   if( idField == ifds::AllocAccountNum || idField == ifds::Percentage )
   {
      getField(idField,oldValue,idDataGroup);
      oldValue.strip().stripLeading('0');
      if( oldValue == dstrValue ) return(GETCURRENTHIGHESTSEVERITY());
   }


   SEVERITY  sevRtn = BFCBO::setField( idField, dstrValue, idDataGroup, 
                                       bFormatted, bSideEffect );
   if( WARNING > sevRtn )
   {
      if( idField == ifds::Percentage )
      {

         DString dstrTotalAmount;
         getSystematicPtr()->getField( ifds::Amount, dstrTotalAmount, 
                                       idDataGroup, false);

         double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

         if( dTotalAmount <= .00000000001 )
            return(GETCURRENTHIGHESTSEVERITY());

         DString dstrPercentage( dstrValue );


         double dPercentage = DSTCommonFunctions::convertToDouble(dstrPercentage);
         double dAmount = dTotalAmount * dPercentage / 100; 
         DString dstrAmount = DSTCommonFunctions::doubleToDString( ifds::AllocAmount,dAmount );


			getSystematicPtr()->getFormattedAmount( idDataGroup, dstrAmount);


         BFCBO::setField( ifds::AllocAmount, dstrAmount, idDataGroup, false, 
                          true );

			calculateFieldsForAlloc( idDataGroup );

/*
         // we need to set Fund Level Allocation automatically
         BFObjIter iterFundAlloc( *_pAtAllocationList, idDataGroup, false, 
                                  BFObjIter::ITERTYPE::NON_DELETED );
         DString strValue1;
         dTotalAmount = dAmount;
		   int iNum = iterFundAlloc.getNumberOfItemsInList();
			AutoTransAllocation* pAlloc = NULL;

         if( iNum == 1 )//no allocations
         {
            pAlloc = iterFundAlloc.getObject();
				if( pAlloc )
				{
					pAlloc->parentFieldChangeNotify(ifds::Percentage,idDataGroup, I_("100"),true );
					pAlloc->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup, dstrAmount,true );
				}
         }
         else//multiple allocations
         {
				double dAddAmount = 0;
				double dAddPercent = 0;

				for( int i = 1; i<= iNum; i++ )
				{
					pAlloc = iterFundAlloc.getObject();
					pAlloc->getField(ifds::Percentage,strValue1,idDataGroup,false);
               dPercentage =DSTCommonFunctions::convertToDouble(strValue1);
					dAddPercent += dPercentage;
               dAmount = dTotalAmount * dPercentage / 100;
					if( dAddPercent == 100 && i=iNum )
					{
						dAmount = dTotalAmount - dAddAmount;
					}					
					if( dAmount > .00000000001 )
					{
			         dstrAmount = DSTCommonFunctions::doubleToDString( ifds::AllocAmount,dAmount );            
						getSystematicPtr()->getFormattedAmount( idDataGroup, dstrAmount);
						pAlloc->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup, dstrAmount,true );					
					}
					dAddAmount += dAmount;
					++iterFundAlloc;
				}
         }
			*/
      }
      else if( idField == ifds::AllocAmount )
      {
         DString dstrValue1(dstrValue);
         dstrValue1.strip().stripAll(I_CHAR(','));
         getSystematicPtr()->getFormattedAmount(idDataGroup, dstrValue1);

         BFCBO::setField( idField, dstrValue1, idDataGroup, 
                          bFormatted, bSideEffect );
         DString dstrTotalAmount;
         getSystematicPtr()->getField( ifds::Amount, dstrTotalAmount, 
                                       idDataGroup, false);
         double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);
         if( dTotalAmount <= .00000000001 )
            return(GETCURRENTHIGHESTSEVERITY());

         DString dstrAmount( dstrValue );
         dstrAmount.strip().stripAll( I_CHAR( ',' ) );
         double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
         double dPercentage = dAmount / dTotalAmount * 100; 
         DString dstrPercentage =   DSTCommonFunctions::doubleToDString( ifds::Percentage,dPercentage );

         BFCBO::setField( ifds::Percentage, dstrPercentage, idDataGroup, false, 
                          true );

         calculateFieldsForAlloc( idDataGroup );   
			
			
/*			
			//we need to set fund level allocation
         BFObjIter iterFundAlloc( *_pAtAllocationList, idDataGroup, false, 
                                  BFObjIter::ITERTYPE::NON_DELETED );
         DString strValue1;
         dTotalAmount = dAmount;
         if( iterFundAlloc.getNumberOfItemsInList() == 1 )//no allocations
         {
            iterFundAlloc.getObject()->setField(ifds::AllocAmount, dstrTotalAmount, idDataGroup, false);
         }
         else//multiple allocations
         {
            while( !iterFundAlloc.end() )
            {
               iterFundAlloc.getObject()->getField(ifds::Percentage,
                                                   strValue1,idDataGroup,false);
               dPercentage = DSTCommonFunctions::convertToDouble(strValue1);
               dAmount = dTotalAmount * dPercentage / 100;
               dstrAmount = DSTCommonFunctions::doubleToDString( ifds::AllocAmount,dAmount );

               iterFundAlloc.getObject()->setField( ifds::AllocAmount, dstrAmount, 
                                                    idDataGroup, false, true);

               ++iterFundAlloc;

            }         
         }
			*/
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//***************************************************************************************
// the method will change related allocation amount in Fund level allocation
// Also deal with rounding up issue

SEVERITY  AutoAcctTransAllocation::calculateFieldsForAlloc(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "calculateFieldsForAlloc" ) );
	DString dstrAmount;
	getField( ifds::AllocAmount, dstrAmount, idDataGroup, false );
   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
	BFObjIter iterFundAlloc( *_pAtAllocationList, idDataGroup, false, 
                                  BFObjIter::ITERTYPE::NON_DELETED );
   DString strValue1;
   dTotalAmount;
	int iNum = iterFundAlloc.getNumberOfItemsInList();
	AutoTransAllocation* pAlloc = NULL;

   if( iNum == 1 )//one allocations
   {
      pAlloc = dynamic_cast<AutoTransAllocation* >( iterFundAlloc.getObject() );
		if( pAlloc )
		{
			strValue1 =  I_("100");
			pAlloc->parentFieldChangeNotify(ifds::Percentage,idDataGroup, strValue1,true );
			pAlloc->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup, dstrAmount,true );
		}
   }
   else//multiple allocations
   {
		double dAddAmount = 0;
		double dAddPercent = 0;

		for( int i = 1; i<= iNum; i++ )
		{
			pAlloc = dynamic_cast<AutoTransAllocation* >( iterFundAlloc.getObject() );
			if( pAlloc )
			{
				pAlloc->getField(ifds::Percentage,strValue1,idDataGroup,false);
				double dPercentage =DSTCommonFunctions::convertToDouble(strValue1);
				dAddPercent += dPercentage;
				double dAmount = dTotalAmount * dPercentage / 100;
				if( dAddPercent == 100 && i==iNum )
				{
					dAmount = dTotalAmount - dAddAmount;
				}					
				if( dAmount > .00000000001 )
				{
					dstrAmount = DSTCommonFunctions::doubleToDString( ifds::AllocAmount,dAmount );            
					getSystematicPtr()->getFormattedAmount( idDataGroup, dstrAmount);
					pAlloc->parentFieldChangeNotify(ifds::AllocAmount,idDataGroup, dstrAmount,true );					
				}
				dAddAmount += dAmount;
			}
			++iterFundAlloc;
		}
   }
	return (GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoAcctTransAllocation::doValidateField( const BFFieldId& idField,
                                                   const DString& strValue,
                                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   DString dstr(strValue);
   dstr.strip();
   if( dstr != I_("") )
   {
      getSystematicPtr()->setObjectAsNew();
   }

   if( idField == ifds::Percentage ) 
   {
      ValidatePercentage( strValue, idDataGroup );
   } 
   else if( idField == ifds::AllocAccountNum ) 
   {
      const_cast <DString&>(strValue).stripLeading ('0').strip();
      if (!strValue.empty())
         MFAccount::validateAccountNum (strValue, getWorkSession());       
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AutoAcctTransAllocation::ValidateAmount(const DString& Amount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAmount" ) );

   DString dstrAmount(Amount);
   dstrAmount.stripAll(I_(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);

   DString dstrFundCode, dstrClassCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   _pSystematic = getSystematicPtr(); //dynamic_cast<Systematic *>(getParent()->getParent());
   DString dstrTotalAmount;
   _pSystematic->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
   dstrTotalAmount.stripAll(I_(','));
   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);
   if( dTotalAmount == 0 && dAmount == 0 )
      return;

   _pSystematic->ValidateAmountInitPur(dAmount, dstrFundCode, dstrClassCode, idDataGroup);
}

//******************************************************************************
void AutoAcctTransAllocation::ValidatePercentage( const DString& strValue,
                                                  const BFDataGroupId& idDataGroup ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidatePercentage" ) );
   DString dstrPercentage( strValue );
   dstrPercentage.strip();
   if( dstrPercentage == NULL_STRING )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      return;
   }

   I_CHAR *stopstring;
   double dPercent = wcstod( dstrPercentage.c_str(), &stopstring );

   if( dPercent > 100 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
      return;
   }

   DString dstrPercentageMask = DSTCommonFunctions::getRawMask( ifds::Percentage );
   dstrPercentageMask.strip();
   int iMaskNumDigitsAfterDecimalPoint = dstrPercentageMask.length() 
                                         - dstrPercentageMask.find( I_( "." ) ) - 1;
   double dMinValue = pow( 10.0, -iMaskNumDigitsAfterDecimalPoint );

   if( dPercent < dMinValue )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_CANNOT_BE_ZERO ); 
   }
}

//******************************************************************************
// we are in the target item
void AutoAcctTransAllocation::ModelOffer(AutoAcctTransAllocation *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0007_VWRepeat_Record);

//CP	DataComponentProperties *dcpPtr  = NULL;

   BFDataFieldIter dIter( *tmp );
   DString str;
   for( ;dIter; ++dIter )
   {
//CP      dcpPtr = const_cast< DataComponentProperties * >(dIter().getProperties());
//CP      dcpPtr->getId( idField );
      BFDataField& idField = dIter();
      Model->getField( idField.getId(), str, idDataGroup );
      setFieldNoValidate(idField.getId(), str, idDataGroup, false);
      if( idField.getId() == ifds::Percentage )
      {
         DString str1;
         getField(idField.getId(), str1, idDataGroup);

      }

   }

   delete tmp;

   AutoTransAllocationList *pAtAllocationList, *pModelAtAllocationList;
   Model->getAtAllocationList( pModelAtAllocationList );

   if( pModelAtAllocationList )
   {

      getAtAllocationList( pAtAllocationList );
      pAtAllocationList->ModelOffer(pModelAtAllocationList, idDataGroup);
   }
   clearUpdatedFlags( idDataGroup );

}

//******************************************************************************

void AutoAcctTransAllocation::GetDefaultSplitComm ( const BFDataGroupId& idDataGroup)
{
   if( _pAtAllocationList )
      _pAtAllocationList->GetDefaultSplitComm ( idDataGroup );
}

//******************************************************************************
void AutoAcctTransAllocation::GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm )
{
   if( _pAtAllocationList )
      _pAtAllocationList->GetSplitCommFlag ( idDataGroup, dstrSplitComm );
   else
      dstrSplitComm = NO;
}

//******************************************************************************
// when fields value changed in parent,
// The related fields in this CBO should be changed accordingly.
// Validation should only happen in parent CBO.

void AutoAcctTransAllocation::parentFieldChangeNotify(const BFFieldId& fieldId,
				const BFDataGroupId& idDataGroup, 
				DString& dstrValue,
				bool bFormat)
{
   setFieldNoValidate(fieldId, dstrValue, idDataGroup,bFormat,true,true,false );
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AutoAcctTransAllocation.cpp-arc  $
 // 
 //    Rev 1.40   Mar 08 2005 12:07:52   aguilaam
 // IN 243381 - allow only valid account numbers on allocation screen
 // 
 //    Rev 1.39   Dec 10 2004 17:34:04   hernando
 // PET910 - Changed pow call.
 // 
 //    Rev 1.38   Nov 14 2004 14:26:08   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.37   Feb 25 2004 13:13:26   YINGBAOL
 // PTS10022298: solve rounding of percentage and amount
 // 
 //    Rev 1.36   Feb 06 2004 16:39:14   YINGBAOL
 // PTS10026412 part 2: Add parentFieldChangeNotify method.
 // 
 //    Rev 1.35   Oct 30 2003 16:44:24   HSUCHIN
 // PTS 10023534 - added account validation.
 // 
 //    Rev 1.34   May 13 2003 17:06:24   popescu
 // Split commission re-work, part II
 // 
 //    Rev 1.33   Apr 22 2003 14:28:20   FENGYONG
 // change 100.00 to 100 for multi laguage like germany format
 // 
 //    Rev 1.32   Apr 11 2003 10:09:54   FENGYONG
 // Add amount validation
 // 
 //    Rev 1.31   Mar 21 2003 17:59:28   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.30   Oct 09 2002 23:54:00   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.29   Sep 30 2002 11:01:10   PURDYECH
 // BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 // 
 //    Rev 1.28   Aug 29 2002 12:55:02   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.27   Jul 08 2002 15:02:44   KOVACSRO
 // Bug fixed for AccountNum. Uncomment BFCBO::getField.
 // 
 //    Rev 1.26   Jun 10 2002 11:29:30   ZHANGCEL
 // PTS 10008472: fix bug regarding percentage
 // 
 //    Rev 1.25   May 31 2002 15:04:40   ZHANGCEL
 // Syn up to 1.23.1.0 : 10008340, fix format problem for units
 // 
 //    Rev 1.24   22 May 2002 18:26:26   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.23   13 Feb 2002 14:07:48   KOVACSRO
 // 1. PTS 7076 and 6975. If single fund allocation, set Percentage to 100 and AllocAmount = TotalAmount.
 // 2. ClearUpdatedFlags and setFiledNoValidate in modelOffer (otherwise 'Allocation percentage not 100' error message is issued for a copied item.
 // 
 //    Rev 1.22   18 Oct 2001 14:43:44   KOVACSRO
 // Added bCheckCurrentValue param to setField.
 // 
 //    Rev 1.21   Aug 15 2001 19:09:24   YINGBAOL
 // fix bug
 // 
 //    Rev 1.20   Jul 23 2001 15:54:58   YINGBAOL
 // modify ERR_VALUE_CANNOT_BE_ZERO
 // 
 //    Rev 1.19   Jun 26 2001 12:54:58   PURDYECH
 // Infrastructure Release 1.9 Integration.
 // 
 //    Rev 1.18   09 May 2001 13:35:28   HSUCHIN
 // Sync up with SSB
 // 
 //    Rev 1.16.2.0   14 Apr 2001 10:41:24   HSUCHIN
 // added logic to retrieve default split commission list and minor code cleanup
 // 
 //    Rev 1.16   03 Apr 2001 20:12:08   HSUCHIN
 // Implemented default split commission
 // 
 //    Rev 1.15   Dec 17 2000 20:22:34   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.14   Sep 22 2000 16:42:24   HUANGSHA
 // fixed the problem in setting amount field
 // 
 //    Rev 1.13   Sep 01 2000 15:31:16   YINGBAOL
 // change locale
 // 
 //    Rev 1.12   Aug 24 2000 16:38:52   YINGBAOL
 // clean up file
 // 
 //    Rev 1.11   Aug 04 2000 13:56:30   YINGBAOL
 // change validation
 // 
 //    Rev 1.10   Jun 30 2000 09:54:02   YINGBAOL
 // fix add copy and other bugs
 // 
 //    Rev 1.9   Jun 21 2000 16:03:44   YINGBAOL
 // use BF::HOST in setobject
 // 
 //    Rev 1.8   Jun 19 2000 11:32:24   YINGBAOL
 // change format
 // 
 //    Rev 1.7   Jun 13 2000 18:01:00   DT24433
 // new Infra interfaces use ClientLocale
 // 
 //    Rev 1.6   May 04 2000 16:56:12   WINNIE
 // change CURRENCY_HPP to CURRENCYCLASS_HPP
 // 
 //    Rev 1.5   May 01 2000 09:39:10   YINGBAOL
 // add validation logic
 // 
 //    Rev 1.4   Apr 18 2000 12:04:10   YINGZ
 // addcopy AutoTransAllocationList child list
 // 
 //    Rev 1.3   Apr 17 2000 17:15:54   YINGZ
 // add AddCopy function for systematic
 // 
 //    Rev 1.2   Apr 17 2000 11:22:54   YINGBAOL
 // fix M3 crash
 // 
 //    Rev 1.1   Apr 14 2000 12:03:02   YINGBAOL
 // change logic in init child list
 // 
 //    Rev 1.0   Mar 27 2000 13:29:14   YINGBAOL
 // Initial revision.
// 
*/

