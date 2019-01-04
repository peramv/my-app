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
// ^FILE   : AutoAcctTransAllocationList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AutoAcctTransAllocationList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "autoaccttransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include "autotransallocation.hpp"
#include "autotransallocationlist.hpp"
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0007_req.hpp>
#include <ifastdataimpl\dse_dstc0007_vwrepeat_record.hpp>
#include "splitcommissionlist.hpp"
#include "systematic.hpp"
#include "mfaccount.hpp"
#include "amsfundalloclist.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AutoAcctTransAllocationList" );
   const I_CHAR * const YES = I_("Y");
}

namespace CND
{
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_ACCOUNT_EMPTY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::ReplaceAsDefault, BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//********************************************************************************
AutoAcctTransAllocationList::AutoAcctTransAllocationList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_bAddCopy(false),
_dstrAddCopyKey(NULL_STRING),
_strPacSwpId(NULL_STRING),
_bHasAcct(false),
_allocationData(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, ( const CLASS_FIELD_INFO * )&classFieldInfo, 0, NULL );
   setObjectAsList();
}

//********************************************************************************
AutoAcctTransAllocationList::~AutoAcctTransAllocationList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY AutoAcctTransAllocationList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************
SEVERITY AutoAcctTransAllocationList::init(const BFDataGroupId& idDataGroup, 
   const DString& strPacSwpId, const BFData &data, bool bHasAcct)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _strPacSwpId = strPacSwpId;
   _bHasAcct = bHasAcct;
   _allocationData = &data;
   createObjectForEachRepeat(data);
   clearUpdatedFlags(idDataGroup, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AutoAcctTransAllocationList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   
   DString dstrLevel = data.getElementValue(I_("Level"));
   DString dstrPACSWPId = data.getElementValue(I_("PACSWPId"));
   DString dstrTransType = data.getElementValue(ifds::TransType);
   DString dstrAccount = data.getElementValue( ifds::AllocAccountNum );

   dstrLevel.strip();
   dstrPACSWPId.strip().stripLeading(I_CHAR('0'));
   dstrAccount.strip().stripLeading(I_CHAR('0'));   
   
   AutoAcctTransAllocation *pAutoAcctTransAllocation = NULL;

   if (_bHasAcct)
   {  
      // in case there is no account level allocation while there is fund level allocation , 
      //we need to create one.
      if (dstrPACSWPId.compare(_strPacSwpId) == 0 && dstrLevel == I_("3"))
      {
         pAutoAcctTransAllocation = new AutoAcctTransAllocation(*this);         
         pAutoAcctTransAllocation->setSystematicPtr(getSystematicPtr());

         DString strAcct, strFundTo, strClassTo, strAmount;

         getSystematicPtr()->getParameter(strAcct, strFundTo, strClassTo, strAmount);
         pAutoAcctTransAllocation->init(strAcct, strFundTo, strClassTo, strAmount);
         pAutoAcctTransAllocation->initAtAlloc(BF::HOST, *_allocationData, 
            _strPacSwpId, dstrAccount, _bHasAcct);
      }
   }
   else if(dstrPACSWPId.compare(_strPacSwpId) == 0 && dstrLevel == I_("2"))
   {
      pAutoAcctTransAllocation = new AutoAcctTransAllocation(*this);
      pAutoAcctTransAllocation->setSystematicPtr(getSystematicPtr());
      pAutoAcctTransAllocation->init(data);
      //init 3 level AT Allocation
      pAutoAcctTransAllocation->initAtAlloc(BF::HOST, *_allocationData, _strPacSwpId, dstrAccount);
   }
   pObjOut = pAutoAcctTransAllocation;
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY AutoAcctTransAllocationList::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setFieldNoValidate( ifds::ReplaceAsDefault, I_( "N" ), idDataGroup );

   BFObjectKey objKey;
   getNewListItem( objKey );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AutoAcctTransAllocationList::doCreateNewObject( BFCBO *& pBase, 
   DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   if (_bAddCopy)
   {
      strKey= _dstrAddCopyKey;
   }

   AutoAcctTransAllocation *pAtAcctAllocation = new AutoAcctTransAllocation(*this);

   pAtAcctAllocation->setSystematicPtr(getSystematicPtr());
   pAtAcctAllocation->initNewAtAllocation( idDataGroup );
   pBase = pAtAcctAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoAcctTransAllocationList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   I_CHAR *stopstring;
   std::set< DString > setCharacteristic;
   double dMaxPercentage = 0, dTotalPercentage = 0;
   double dMaxAmount = 0, dTotalAmount = 0;
   DString dstrMaxPercentageKey, dstrMaxAmountKey;

   // 1. iterate through the list
   BFObjIter iter1( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter1.isDummy() )
   {
      DString strTransType;
      getParent()->getField(ifds::TransType, strTransType, idDataGroup, false);
      if( strTransType != I_("AT") )
         return(GETCURRENTHIGHESTSEVERITY());
   }

   if( iter1.end() )
   {
      ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   while( !iter1.end() )
   {
      DString  dstrAccount;
      iter1.getObject()->getField( ifds::AllocAccountNum, dstrAccount, idDataGroup );
      dstrAccount.strip().stripLeading('0');
      if( dstrAccount == I_("") )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCOUNT_EMPTY );    
      }

      // 1-2. calculate total percentage and maximal percentage
      DString dstrPercentage;
      iter1.getObject()->getField( ifds::Percentage, dstrPercentage, 
                                   idDataGroup );
      dstrPercentage.strip().stripAll( I_CHAR( ',' ) );
      double dPercentage = wcstod( dstrPercentage.c_str(), &stopstring );
      if( dPercentage > dMaxPercentage )
      {
         dMaxPercentage = dPercentage;
         dstrMaxPercentageKey = iter1.getStringKey();
      }
      dTotalPercentage += dPercentage;

      // 1-3. calculate total amount and maximal amount
      DString dstrAmount;
      iter1.getObject()->getField( ifds::AllocAmount, dstrAmount, 
                                   idDataGroup );
      dstrAmount.strip().stripAll( I_CHAR( ',' ) );
      double dAmount = wcstod( dstrAmount.c_str(), &stopstring );
      if( dAmount > dMaxAmount )
      {
         dMaxAmount = dAmount;
         dstrMaxAmountKey = iter1.getStringKey();
      }
      dTotalAmount += dAmount;

      ++iter1;
   }

   // 2. retrieve the systematic amount
   DString dstrTotalSysAmount;
   getParent()->getField( ifds::Amount, dstrTotalSysAmount, idDataGroup );
   dstrTotalSysAmount.strip().stripAll( I_CHAR( ',' ) );
   double dTotalSysAmount = wcstod( dstrTotalSysAmount.c_str(), &stopstring );

   // 3. calculate the percentage accuracy
   DString dstrPercentageMask = DSTCommonFunctions::getRawMask( ifds::Percentage );
   dstrPercentageMask.strip();
   int iPercentageNumDigitsAfterDecimalPoint = dstrPercentageMask.length() 
                                               - dstrPercentageMask.find( I_( "." ) ) - 1;
   double dPercentageThreshold = pow( 10.0, 
                                      -iPercentageNumDigitsAfterDecimalPoint );

   // 4. calculate the amount accuracy
   DString dstrAllocAmountMask = DSTCommonFunctions::getRawMask( ifds::AllocAmount );
   dstrAllocAmountMask.strip();
   int iAllocAmountNumDigitsAfterDecimalPoint = dstrAllocAmountMask.length() 
                                                - dstrAllocAmountMask.find( I_( "." ) ) - 1;
   double dAllocAmountThreshold = pow( 10.0, 
                                       -iAllocAmountNumDigitsAfterDecimalPoint );

   // 5. Eliminate rounding differences, or signal an error if the differences
   //    are larger than expected from the rounding effects.
   double dPercentageDiff = dTotalPercentage - 100;
   double dAllocAmountDiff = dTotalAmount - dTotalSysAmount;
   if( fabs( dPercentageDiff ) < dPercentageThreshold )
   {
      if( fabs( dAllocAmountDiff ) >= dAllocAmountThreshold )
      {
         dMaxAmount -= dAllocAmountDiff;
         char buffer[ 50 ];
         DString dstrMaxAmount = DStringA( _gcvt( dMaxAmount, 30, buffer ) );
         iter1.positionByKey( dstrMaxAmountKey );
         iter1.getObject()->setField( ifds::AllocAmount, dstrMaxAmount, 
                                      idDataGroup );
      }
   }
   else if( fabs( dAllocAmountDiff ) < dAllocAmountThreshold )
   {
      dMaxPercentage -= dPercentageDiff;
      char buffer[ 50 ];
      DString dstrMaxPercentage = DStringA( _gcvt( dMaxPercentage, 30, 
                                                   buffer ) );
      iter1.positionByKey( dstrMaxPercentageKey );
      iter1.getObject()->setField( ifds::Percentage, dstrMaxPercentage, 
                                   idDataGroup );
   }
   else
      ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );

   //Setup the SplitComm flag on validatation of Auto Transfers
   DString dstrSplitComm;
   GetSplitCommFlag ( idDataGroup, dstrSplitComm );
   getParent()->setField ( ifds::SplitComm, dstrSplitComm, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
void AutoAcctTransAllocationList::ModelOffer(AutoAcctTransAllocationList *Model, const BFDataGroupId& idDataGroup)
{
   AutoAcctTransAllocation * pAutoAcctTransAllocation;
   BFObjectKey objKey;
   _bAddCopy = true;

   BFObjIter iterDest(*this, idDataGroup);

   for( BFObjIter Iter( *Model, idDataGroup ); !Iter.end(); ++Iter )
   {
      //	objKey = Iter.getKey(); // we don't want to ruin old key, so make a copy
      //   objKey.getActivity() = OBJ_ADDED;
      //   objKey.getDataGroupId() = idDataGroup;
      _dstrAddCopyKey = Iter.getStringKey();
      if( iterDest.end() )
      {
         pAutoAcctTransAllocation = dynamic_cast< AutoAcctTransAllocation * >(getNewListItem( objKey ));
         pAutoAcctTransAllocation->ModelOffer(dynamic_cast< AutoAcctTransAllocation * >( Iter.getObject( ) ), idDataGroup);
         setObject(objKey, pAutoAcctTransAllocation);
      }
      else
      {
         pAutoAcctTransAllocation = dynamic_cast< AutoAcctTransAllocation * >(iterDest.getObject());
         pAutoAcctTransAllocation->ModelOffer(dynamic_cast< AutoAcctTransAllocation * >( Iter.getObject( ) ), idDataGroup);
         ++iterDest;
      }
   }
   _bAddCopy =false;
}

//******************************************************************************
void AutoAcctTransAllocationList::GetSplitCommFlag ( const BFDataGroupId& idDataGroup, DString &dstrSplitComm )
{
   AutoAcctTransAllocation *pAutoAcctTransAllocation;
   // There should always be one Account Transaction Allocation
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*>(iter.getObject());
      pAutoAcctTransAllocation->GetSplitCommFlag ( idDataGroup, dstrSplitComm );
      ++iter;
   }
}

//******************************************************************************
void AutoAcctTransAllocationList::GetDefaultSplitComm ( const BFDataGroupId& idDataGroup )
{
   AutoAcctTransAllocation *pAutoAcctTransAllocation;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*>(iter.getObject());   
      pAutoAcctTransAllocation->GetDefaultSplitComm ( idDataGroup );
      ++iter;
   }   
}

//********************************************************************************

SEVERITY AutoAcctTransAllocationList::initWithDefaultAllocations(const BFDataGroupId& idDataGroup, 
                                   const DString& dstrTransTypeIn, const DString& dstrAcctNumIn, 
                                   const DString& dstrCurrency, const DString& dstrAmount, const DString& dstrEffectiveDate)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initWithDefault"));

   setFieldNoValidate(ifds::ReplaceAsDefault, I_("N"), idDataGroup);
   setFieldNoValidate(ifds::SettleCurrency,NULL_STRING, idDataGroup, false);

   /*if(_dstrMultiCurrency.empty())
   {
      getWorkSession().getOption(ifds::MultiCurrency, _dstrMultiCurrency, idDataGroup, false);
   }*/

   if(dstrTransTypeIn == NULL_STRING || dstrAcctNumIn == NULL_STRING)
      return(GETCURRENTHIGHESTSEVERITY());

   SEVERITY sevRtn = SEVERE_ERROR;


   MFAccount* pMFAccount = NULL;
   sevRtn = getWorkSession().getMFAccount(idDataGroup, dstrAcctNumIn, pMFAccount);
   if(sevRtn > WARNING || pMFAccount == NULL)
      return(sevRtn);

   MFCanBFCbo *pAllocationList = NULL;
   //rule : if AMSCode in the account is
   //a) empty - get default allocations for the specified trans type
   //b) 0001 - use the Ams rebalancing default allocations
   //c) any other value - use the ams allocation list from MFAccount
   DString dstrPACSWPOverride;
   getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false);      
   if ( !pMFAccount->isAMSAccount ( idDataGroup ) && dstrPACSWPOverride != YES ) {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString strAccountNum, strAMSCode(NULL_STRING);
   pMFAccount->getField(ifds::AMSCode, strAMSCode, idDataGroup, false);

   getAMSDefAllocList(pAllocationList, idDataGroup, dstrAcctNumIn, dstrEffectiveDate);

   if (!pAllocationList)
      return(GETCURRENTHIGHESTSEVERITY());

   /**
     *   Fill in the Allocation List with the Default Allocation List
     */
   BFObjIter iter(*pAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   if(iter.getNumberOfItemsInList() <= 0)
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrKey, dstrFundCode, dstrClassCode, dstrAmt;
   while(!iter.end())
   {
      BFAbstractCBO *pBFCBO = iter.getObject();
      if(pBFCBO)
      {
         DString dstrLevel, dstrAccountNum, dstrTransType, dstrEffecDate;
         //pBFCBO->getField(ifds::Level, dstrLevel, idDataGroup, false);
         pBFCBO->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, true);
         if (dstrAccountNum.strip().empty())
            dstrAccountNum = dstrAcctNumIn;
         pBFCBO->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         if (dstrTransType.strip().upperCase().empty())
            dstrTransType = dstrTransTypeIn;
         pBFCBO->getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);

         //if(convertToULong(dstrLevel) == 3)       //Actually no need to check
         //{
            AutoAcctTransAllocation *pAutoAcctTransAllocation = new AutoAcctTransAllocation(*this);
            BFData *pDataAlloc = new BFData(ifds::DSTC0007_VWRepeat_Record);

            DString dstrValue;

            pDataAlloc->setElementValue(ifds::DistribDetlRid, I_("0"));
            pDataAlloc->setElementValue(ifds::TransType, dstrTransType);
            pDataAlloc->setElementValue(ifds::PACSWPId, I_("0"));
            pDataAlloc->setElementValue(ifds::Level, I_("3"));
            pDataAlloc->setElementValue(ifds::AllocAccountNum, dstrAccountNum);
            pDataAlloc->setElementValue(ifds::SettleCurrency, dstrCurrency);
            pBFCBO->getField(ifds::FundCode, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::FundCode, dstrFundCode);

            pBFCBO->getField(ifds::ClassCode, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::ClassCode, dstrClassCode);

            pBFCBO->getField(ifds::AllocPercentage, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::Percentage, dstrValue, false, false);
            if ( dstrAmount == I_("0") ) {
               pDataAlloc->setElementValue(ifds::AllocAmount, I_("0"));
            } else {
               double dPercent = DSTCommonFunctions::convertToDouble ( dstrValue );
               double dAmount = DSTCommonFunctions::convertToDouble ( dstrAmount );
               double dTotal = dAmount * dPercent / 100;
               dstrAmt = DSTCommonFunctions::doubleToDString ( ifds::AllocAmount, dTotal );
               pDataAlloc->setElementValue(ifds::AllocAmount, dstrAmt);
            }

            //create a new object
            getStrKey(dstrKey, pDataAlloc);
            pAutoAcctTransAllocation->setSystematicPtr(getSystematicPtr());
            pAutoAcctTransAllocation->init(dstrAccountNum, dstrFundCode, dstrClassCode, dstrAmt);            
            pAutoAcctTransAllocation->initAtAlloc( idDataGroup,*pDataAlloc,dstrKey, dstrAcctNumIn);
            setObject(pAutoAcctTransAllocation, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup);
            //pSysAllocation->GetDefaultSplitComm (idDataGroup);
         //}
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************

SEVERITY AutoAcctTransAllocationList::getAMSDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
                                                 const DString& strAccountNum, const DString& dstrEffectiveDate)
{   
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSDefAllocList"));
   DString dstrDate = dstrEffectiveDate;
   pDefaultAllocationList = NULL;

   MFAccount* pMFAccount = NULL;
   if (getWorkSession().getMFAccount(idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());
   AMSMstrList* pAMSMstrList = NULL;

   DString dstrPACSWPOverride;
   getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
   //If it PAC/SWP Override is Yes, then we will use the current business date except for future date.
   if ( dstrPACSWPOverride == YES ) {
      DString dstrCurrBusDate;
      getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
      if ( DSTCommonFunctions::CompareDates ( dstrEffectiveDate, dstrCurrBusDate ) 
         == DSTCommonFunctions::FIRST_EARLIER || dstrDate == NULL_STRING) {
         dstrDate = dstrCurrBusDate;
      }
   }
   DString dstrAMSCode;
   pMFAccount->getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );
   pMFAccount->getAMSMstrList ( pAMSMstrList, idDataGroup, dstrDate );
   if ( pAMSMstrList ) {
      AmsMstrInfo* pAMSMstrInfo = NULL;
      pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, dstrDate, pAMSMstrInfo, idDataGroup );
      AmsFundAllocList* pAmsFundAllocList = NULL;
      pAMSMstrInfo->getAMSFundAllocList( pAmsFundAllocList, idDataGroup );
      pDefaultAllocationList = dynamic_cast<MFCanBFCbo*>(pAmsFundAllocList);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AutoAcctTransAllocationList.cpp-arc  $
 // 
 //    Rev 1.26   Dec 10 2004 17:34:44   hernando
 // PET910 - Changed pow call.
 // 
 //    Rev 1.25   Nov 14 2004 14:27:34   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.24   Aug 15 2003 15:22:40   HSUCHIN
 // added method to init with default ams allocation.  Currently not used.
 // 
 //    Rev 1.23   Jun 11 2003 13:18:12   popescu
 // Removed unecessary GEtSplitCommissionList from the AutAccTransAllocationList level
 // 
 //    Rev 1.22   May 13 2003 17:06:52   popescu
 // Split commission re-work, part II
 // 
 //    Rev 1.21   Mar 21 2003 17:59:32   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.20   Oct 09 2002 23:54:02   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.19   Aug 29 2002 12:55:02   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.18   Jul 15 2002 14:47:26   YINGBAOL
 // PTS 10008987
 // 
 //    Rev 1.17   22 May 2002 18:26:26   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.16   05 Mar 2002 14:16:12   KOVACSRO
 // fix for fix dummy item.
 // 
 //    Rev 1.15   Aug 15 2001 11:47:10   YINGBAOL
 // fix dummy item
 // 
 //    Rev 1.14   09 May 2001 13:58:30   HSUCHIN
 // Sync up with SSB
 // 
 //    Rev 1.12.2.1   30 Apr 2001 15:41:34   HSUCHIN
 // fix to send the split comm flag back to systematic so that the button can be enabled
 // 
 //    Rev 1.12.2.0   14 Apr 2001 10:42:44   HSUCHIN
 // added function to get the SplitCommission List
 // 
 //    Rev 1.12   Dec 17 2000 20:22:34   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.11   Nov 16 2000 15:52:48   HUANGSHA
 // fixed in ModelOffer(..)
 // 
 //    Rev 1.10   Aug 24 2000 16:38:54   YINGBAOL
 // clean up file
 // 
 //    Rev 1.9   Jul 26 2000 16:26:30   YINGBAOL
 // change create new item logic
 // 
 //    Rev 1.8   Jun 30 2000 09:54:02   YINGBAOL
 // fix add copy and other bugs
 // 
 //    Rev 1.7   Jun 13 2000 18:04:06   DT24433
 // new Infra interfaces use ClientLocale
 // 
 //    Rev 1.6   Jun 12 2000 16:40:20   YINGBAOL
 // condition added
 // 
 //    Rev 1.5   May 31 2000 16:15:32   YINGBAOL
 // more validation added
 // 
 //    Rev 1.4   May 01 2000 09:39:26   YINGBAOL
 // add validation
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