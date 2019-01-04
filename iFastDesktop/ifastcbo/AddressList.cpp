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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AddressList.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 09/06/99
//
// ^CLASS    : AddressList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "addresslist.hpp"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include "address.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_req.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ADDRESS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME            = I_( "AddressList" );
   const I_CHAR * const K_STRING             = I_( "K" );
   const I_CHAR * const IDI_CODE             = I_( "CODE" );  
   const I_CHAR * const REDEMPTION_CODE      = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const SHRHLDR_LEVEL        = I_( "01" );
   const I_CHAR * const SHRHLDR_CATEGORY     = I_( "3" );
   const I_CHAR * const VERIFIED             = I_( "01" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_BROKER_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_NO_ADDRESS_RECORD_AVAILABLE;
   extern const long ERR_DEFF_STOP_DATE_RANGE_EXISTS;
   extern const long ERR_ADDRESS_CODE_USEDBY_MAILING;
   extern const long ERR_NO_ADDRESSES_FOR_THIS_SHAREHOLDER;
   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;
   extern const long ERR_ADDRESS_CODE_REQUIRED;
   extern const long ERR_UNKNOWN_ADDRESS_CODE;
   extern const long WARN_ADDRESS_CODE_NOT_EFFECTIVE;   
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::AccountNum,    BFCBO::NONE,  0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);


//******************************************************************************
AddressList::AddressList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_shareholderNum (NULL_STRING),
_bNew (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************
AddressList::~AddressList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AddressList::initNew (const DString &shareholderNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shareholderNum = shareholderNum;
   _bNew = true;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AddressList::init( const DString &shareholderNum, 
                            bool ignoreDataNotFound,
                            const DString &dstrTrack,
                            const DString &dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shareholderNum = shareholderNum;

   BFData queryData(ifds::DSTC0043_REQ);
   BFData *response = new BFData(ifds::DSTC0043_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::ShrNum, _shareholderNum); 
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   DSTCRequestor requestor (getSecurity(), true, false);

   if (ignoreDataNotFound)
   {
      requestor.filterHostCondition (CND::ERR_DATA_NOT_FOUND);
      requestor.filterHostCondition (CND::ERR_REGISTERED_ADDRESS_DEFAULT_NOT_FOUND);
      requestor.filterHostCondition (CND::ERR_BROKER_NOT_FOUND);
      requestor.filterHostCondition (CND::ERR_NO_ADDRESS_RECORD_AVAILABLE);
   }

   if (BFDataBroker::getInstance()->receive (DSTC_REQUEST::ADDRESS, 
      queryData, *response, requestor) > WARNING)
   {
      delete response;
      response = NULL;
   }
   else
   {
      attachDataObject (*response, true, true);
      init2 (*response);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AddressList::init2 (const BFData& recData) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init2" ) );

   DString strMarket = 
      DSTCommonFunctions::getMarket();
   
   int nNumRepeats = recData.getRepeatCount();
   if (nNumRepeats > 0)
   {
      BFCBO * pObj = NULL;
      DString strKey;

      for (int i = 0; i < nNumRepeats; i++)
      {
         DString strKey;
         getStrKey( strKey, &recData.getRepeat(i) );
         if (strMarket == MARKET_IDS::JAPAN)
         { // for MORGAN
            if (getObject (strKey, BF::HOST) == NULL)
            {  // object not exist, then create it
               initAddress (strKey, recData);
            }
         }
         else
         { //for other markets
            Address* _pAddress = new Address( *this );

            _pAddress->init (_shareholderNum, recData.getRepeat(i));
            setObject (_pAddress, strKey, OBJ_ACTIVITY_NONE, BF::HOST);
         }
      } 
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY  AddressList::initAddress (const DString &dstrKey, const BFData& recData)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "initAddress( const DString& , const BFData & )" ) );

   SEVERITY sevrt = SEVERE_ERROR;
   int iNo, 
      iNo2;

   if (isDataWanted (dstrKey, recData, iNo))
   {
      DString dstrAddrCode, 
         dstrAddrCode1,
         dstrAddrCode2,
         effDate;
      const BFData& ItemData = recData.getRepeat(iNo);
      dstrAddrCode = ItemData.getElementValue(ifds::AddrCode);
      dstrAddrCode.stripTrailing(); 
      effDate = ItemData.getElementValue(ifds::EffectiveDate);
      effDate.strip();
      dstrAddrCode1 = I_('k')+ dstrAddrCode + effDate;
      dstrAddrCode2 = I_('K') + dstrAddrCode + effDate;

      Address* _pAddress = new Address( *this );
      if( findKanaData( dstrAddrCode1, recData, iNo2 ) )
      {
         sevrt = _pAddress->init (_shareholderNum, ItemData, recData.getRepeat(iNo2) );
      }
      else if( findKanaData( dstrAddrCode2,recData, iNo2) )
      {
         sevrt = _pAddress->init(_shareholderNum, ItemData, recData.getRepeat(iNo2) );
      }
      else
      {
         DString dstrTemp = dstrAddrCode.left(1).upperCase();
         if( dstrTemp != K_STRING )
         {
            sevrt = _pAddress->init(_shareholderNum, ItemData);
         }
      }
      if( WARNING > sevrt )
      {
         setObject (_pAddress, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST);
      }
      else
      {
         delete _pAddress; 
         _pAddress = NULL;
      }
   }
   else
   {
      assert( 0 );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
bool AddressList::isDataWanted (const DString& dstrKey, const BFData& recData, int& iNo)
{
   int nNumRepeats = recData.getRepeatCount();
   if (nNumRepeats > 0)
   {
      for( int i = 0; i < nNumRepeats; i++ )
      {
         DString dstrTempKey;
         
         getStrKey (dstrTempKey, &recData.getRepeat(i) );
         if (dstrTempKey == dstrKey)
         {
            iNo = i; 
            return(true); 
         }
      }
   }
   return (false);

}

//******************************************************************************
void  AddressList::getStrKey (DString &strKey, const BFData *data)  //key by AddrCode and effective date
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getStrKey" ) );

   if (data)
   {
      DString effectiveDate = 
         data->getElementValue (ifds::EffectiveDate);
      DString addressCode = 
         data->getElementValue (ifds::AddrCode);

      effectiveDate.stripLeading();
      addressCode.strip('k');
      addressCode.strip('K');
      addressCode.stripTrailing();
      strKey = addressCode  + I_(" ") + effectiveDate;
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
SEVERITY AddressList::doCreateNewObject(
      BFCBO *&pBase, 
      DString &strKey, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new Address (*this);

   ((Address* )pBase)->init (_shareholderNum, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AddressList::findKanaData(DString dstrKanaAddrCode,const BFData& recData, int& iDataNo)
{
   DString dstrTemp,effDate;
   int nNumRepeats = recData.getRepeatCount();
   for( int i = 0; i < nNumRepeats; i++ )
   {
      const BFData& dataItem = recData.getRepeat(i);
      dstrTemp = dataItem.getElementValue( ifds::AddrCode );  
      dstrTemp.stripTrailing();
      effDate = dataItem.getElementValue(ifds::EffectiveDate);
      effDate.strip();
      dstrTemp = dstrTemp+effDate;
      if( dstrTemp == dstrKanaAddrCode )
      {
         iDataNo = i;
         return(true);
      }
   }
   return(false);
}

//******************************************************************************
bool AddressList::canDeleteObject (
            const DString &strKey, 
            const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canDeleteObject"));

   bool _bRet=true;

   DString addrCode;
   
   getObject (strKey, idDataGroup)->getField (ifds::AddrCode, addrCode, idDataGroup);
   addrCode.strip();
   if (addrCode.empty()) return true;
   if( getAccountMailingList (idDataGroup) == NULL) return true;
   if (getAccountMailingList(idDataGroup)->IsAddrCodeUsedByMailing (addrCode,idDataGroup))
   {
      DString effectiveDate, 
         stopDate, 
         currBusDate;

      getWorkSession().getOption (ifds::CurrBusDate, currBusDate, BF::HOST, false);
      getObject (strKey, idDataGroup)->getField (ifds::EffectiveDate, effectiveDate, idDataGroup);
      getObject (strKey, idDataGroup)->getField (ifds::StopDate, stopDate, idDataGroup);

      if (DSTCommonFunctions::IsDateBetween (effectiveDate, stopDate, currBusDate))
      {
         ADDCONDITIONFROMFILE (CND::ERR_ADDRESS_CODE_USEDBY_MAILING);
         _bRet = false;
      }
   }
   return _bRet;
}

//******************************************************************************
SEVERITY AddressList::doApplyRelatedChanges (
         const BFFieldId &idField, 
         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (idField == ifds::AccountNum)
   {
      refreshDefaultAddress01 (idDataGroup);
//the transaction builder should not pick this list up as updated
      setFieldUpdated (ifds::AccountNum, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AddressList::refreshDefaultAddress01 (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(  CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   bool bVerificationEnabled = false;

   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             SHRHLDR_CATEGORY, 
                                             SHRHLDR_LEVEL, 
                                             bVerificationEnabled);

   if (DSTCommonFunctions::getMarket() != MARKET_IDS::JAPAN)
   {
      Shareholder *pShareholder = NULL;

      if (getWorkSession().getShareholder (idDataGroup, 
            _shareholderNum, pShareholder) <= WARNING &&
         pShareholder)
      {
         DString designation;

         pShareholder->getField (ifds::AcctDesignation, designation, idDataGroup);
         designation.strip();    
         if (designation != NULL_STRING && 
            (designation == I_("2") || designation == I_("3")))
         {
            BFObjIter iter (
               *this, 
               idDataGroup, 
               true, 
               BFObjIter::ITERTYPE::NON_DELETED);

            while (!iter.end())
            {
               Address *pAddress = dynamic_cast<Address*> (iter.getObject());

               if (pAddress)
               {
                  DString addrCode;

                  pAddress->getField (ifds::AddrCode, addrCode, idDataGroup, false);
                  addrCode.strip();

                  if (addrCode == I_("01"))
                  {
                     DString accountNum;

                     getField (ifds::AccountNum, accountNum, idDataGroup, false);

                     MFAccount *pMFAccount = NULL;

                     if (getWorkSession().getMFAccount (idDataGroup, 
                              accountNum, pMFAccount) <= WARNING &&
                           pMFAccount)
                     {
                        DString taxType;

                        pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
                        taxType.strip();
//set the fields below to the child Address
                        pAddress->setField (ifds::TaxType, taxType, idDataGroup, 
                           false, false, false);
                        if (designation == I_("2")) //nominee
                        {
                           DString brokerCode;

                           pMFAccount->getField (ifds::BrokerCode, brokerCode, 
                              idDataGroup, false);
                           brokerCode.strip();
                           pAddress->setField (ifds::BrokerCode, brokerCode, idDataGroup, 
                              false, false, false);
                        }
                        else if (designation == I_("3"))//intermediary
                        {
                           DString interCode;

                           pMFAccount->getField (ifds::InterCode,	interCode, 
                              idDataGroup, false);
                           interCode.strip();
                           pAddress->setField (ifds::InterCode, interCode, idDataGroup, 
                              false, false, false);
                        }
                     }
                     //break;
                  }
               }
               ++iter;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//-----------------------------------------------------------------------------------
AccountMailingList*  AddressList::getAccountMailingList(const BFDataGroupId& idDataGroup)
{
   Shareholder* _pShareholder = NULL;
   SEVERITY sevRtn = getWorkSession().getShareholder( idDataGroup, _shareholderNum, _pShareholder );

   if( sevRtn <= WARNING )
   {
      AccountMailingList* _pAccountMailingList = NULL;
      sevRtn = _pShareholder->getAccountMailingList( _pAccountMailingList, idDataGroup );
      if( sevRtn <= WARNING )
      {
         return(_pAccountMailingList);
      }

   }
   return(NULL);
}


//--------------------------------------------------------------------------------- 
bool  AddressList::IsValidateAddressCode(DString& strCode, const BFDataGroupId& idDataGroup, bool &_bValid)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "IsValidateAddressCode" ) );
   bool _bRet =false;
   DString curDate,effDate,stopDate;
   getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate,curDate,idDataGroup);
   curDate.strip();
   BFObjIter iterAddrList( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   while( !iterAddrList.end() )
   {
      DString strCode1;
      Address* pAddress = dynamic_cast<Address*>(iterAddrList.getObject() );
      pAddress->getField(ifds::AddrCode,strCode1,idDataGroup,false);
      strCode1.strip().upperCase();
      if( strCode == strCode1 )
      {
         _bRet = true;
         pAddress->getField(ifds::EffectiveDate,effDate,idDataGroup);
         pAddress->getField(ifds::StopDate,stopDate,idDataGroup);
         if( DSTCommonFunctions::IsDateBetween(effDate, stopDate,curDate) )
         {
            _bValid = true;

            break;
         }
      }
      ++iterAddrList;
   }
   return(_bRet);
}

//******************************************************************************
SEVERITY AddressList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   bool bAnyAddrModified (false);

   validateAddrCodeDateRanges( idDataGroup, bAnyAddrModified );

   BFObjIter addressIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   //no address for this shareholder, then raise a condition
   if( addressIter.getNumberOfItemsInList() < 1 )
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_ADDRESSES_FOR_THIS_SHAREHOLDER );
   }
   DString strTemp;
   bool bValid = false;
   DString strCode = I_("01");

   if( IsValidateAddressCode( strCode, idDataGroup, bValid) )
   {
      if( !bValid )
      {
         addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
         ADDCONDITIONFROMFILEIDI( CND::WARN_ADDRESS_CODE_NOT_EFFECTIVE, strTemp );
      }
   }
   else
   {
      addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
      ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, strTemp);
   }

   DString strAcctDes;

   MFAccount* _pMFAcount;
   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getWorkSession().getMFAccount( idDataGroup, accountNum, _pMFAcount );
   if( _pMFAcount )
   {
      _pMFAcount->getField( ifds::AcctDesignation,strAcctDes,idDataGroup );

   }

   strAcctDes.strip();
   if( IsNew() && ( strAcctDes == I_("2") || strAcctDes == I_("3") ) )
   {
      BFObjIter iterAddrList( *this, idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
      if( !iterAddrList.end() )
      {
         Address* _pAddr = dynamic_cast<Address*>(iterAddrList.getObject() );
         _pAddr->setObjectUpdated(idDataGroup);
      }
      AccountMailingList* _pMailList = getAccountMailingList(idDataGroup);
      if( !_pMailList )
      {
         BFObjIter iterMailList(*_pMailList,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
         AccountMailingInfo* _pInfo = dynamic_cast<AccountMailingInfo*>(iterMailList.getObject() ); 
         _pInfo->setObjectUpdated(idDataGroup);
      }
   }

   if( strAcctDes != I_("1") )
   {
      strCode = I_("02");
      bValid = false;
      if( IsValidateAddressCode( strCode, idDataGroup, bValid ) )
      {
         if( !bValid )
         {
            addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
            ADDCONDITIONFROMFILEIDI( CND::WARN_ADDRESS_CODE_NOT_EFFECTIVE, strTemp );
         }
      }
/*		else
    {
      addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
      ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_REQUIRED, strTemp);
    }*/
   }

   if( bAnyAddrModified )
   {
      MFAccount* _pMFAcount;
      getWorkSession().getMFAccount( idDataGroup, accountNum, _pMFAcount );
      if( _pMFAcount )
         _pMFAcount->addrEscrow (idDataGroup );
   }


   //validation shouldn't pass if we do not have at least one address with CODE = '01', for the current shareholder
   return(GETCURRENTHIGHESTSEVERITY());

}
//-------------------------------------------------------------------------------------

SEVERITY AddressList::validateAddrCodeDateRanges( const BFDataGroupId& idDataGroup, bool& bmodified )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAddrCodeDateRanges" ) );
   BFObjIter                iter( *this, idDataGroup, false,BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter                iter2( *this, idDataGroup, false,BFObjIter::ITERTYPE::NON_DELETED);
   DString                  strAC1;
   DString                  strAC1EffectDate;
   DString                  strAC1StopDate;
   DString                  strAC2;
   DString                  strAC2EffectDate;
   DString                  strAC2StopDate;


   while( !iter.end() )
   {
      Address* pAddress = dynamic_cast<Address*>(iter.getObject() );

      pAddress->getField(ifds::AddrCode,strAC1,idDataGroup,false);
      pAddress->getField(ifds::EffectiveDate,strAC1EffectDate,idDataGroup);
      pAddress->getField(ifds::StopDate,strAC1StopDate,idDataGroup);
      //position iter2 on the next list item
      iter2.positionByKey( iter.getStringKey() ); 
      ++iter2;

      while( !iter2.end() )
      {
         iter2.getObject()->getField(ifds::AddrCode,strAC2,idDataGroup,false);
         if( ! iter2.isDummy() )
         {
            if( strAC1 == strAC2 )
            {
               iter2.getObject()->getField(ifds::EffectiveDate,strAC2EffectDate,idDataGroup);
               iter2.getObject()->getField(ifds::StopDate,strAC2StopDate,idDataGroup);

               if( DSTCommonFunctions::dateRangesOverlap( strAC1EffectDate, strAC1StopDate,
                                                          strAC2EffectDate, strAC2StopDate ) )
               {
                  DString strTemp;
                  int iCode =  strAC1.asInteger();
                  addIDITagValue( strTemp, IDI_CODE, iCode);
                  if( iCode == 0 )  strTemp = I_("CODE=   ;");
                  ADDCONDITIONFROMFILEIDI( CND::ERR_DEFF_STOP_DATE_RANGE_EXISTS, strTemp);
                  return(GETCURRENTHIGHESTSEVERITY());
               }
            }
         }
         ++iter2;
      }

      if( !bmodified )
         bmodified = ( !isNew() && pAddress->isUpdatedForDataGroup( idDataGroup, true ) );

      ++iter;

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY AddressList::validateAddressCode( const DString& dstrAddrCode, const BFDataGroupId& idDataGroup, 
                                           const DString& strDate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAddressCode" ) );

   DString addrEffDate,stopDate,strDate1(strDate);
	bool iValidAddrCodeExsit = false;
   //if no date provided, use current business date
   if( strDate1.strip().empty() )
      getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate,strDate1,idDataGroup, false);

   BFObjIter iterAddrList( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   while( !iterAddrList.end() )
   {
      DString strCode1;
      Address* pAddress = dynamic_cast<Address*>(iterAddrList.getObject() );
      pAddress->getField(ifds::AddrCode,strCode1,idDataGroup,false);
      strCode1.strip();
      if( dstrAddrCode == strCode1 )
      {
         pAddress->getField(ifds::EffectiveDate,addrEffDate,idDataGroup);
         pAddress->getField(ifds::StopDate,stopDate,idDataGroup);

         if( DSTCommonFunctions::IsDateBetween(addrEffDate, stopDate, strDate1) )
         {//found a valid address
				iValidAddrCodeExsit = true;
            return(NO_SEVERITY);
	      }
			/*  Comment out by Celia because it cause problem in the case of the second valid
			 *  Address existing
				else  {

            DString dstrFormatDate, idiString;
            pAddress->getField(ifds::EffectiveDate,addrEffDate,idDataGroup, true);
            addIDITagValue( idiString, IDI_CODE, dstrAddrCode );
            ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_EFFECTIVE, idiString );
            return(GETCURRENTHIGHESTSEVERITY());
         }*/
      }
      ++iterAddrList;
   }
	// Added by Celia -- Only in the case of no valid Address Code in the whole list, rise error
	if ( !iValidAddrCodeExsit )
	{
		DString idiString;
      addIDITagValue( idiString, IDI_CODE, dstrAddrCode );
      ADDCONDITIONFROMFILEIDI( CND::WARN_ADDRESS_CODE_NOT_EFFECTIVE, idiString );
      return(GETCURRENTHIGHESTSEVERITY());
	}
	
   //no valid address found; add the condition
   ADDCONDITIONFROMFILE( CND::ERR_UNKNOWN_ADDRESS_CODE );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
bool AddressList::DoesAddressCodeExist(const DString& dstrAddrCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "DoesAddressCodeExist" ) );
   DString dstrAddressCode;
   bool bExists = false;
   Address *pAddress = NULL;

   BFObjIter iter( *this, idDataGroup );
   while( !iter.end() )
   {
      pAddress = dynamic_cast < Address * >( iter.getObject());
      if( pAddress )
      {
         pAddress->getField( ifds::AddrCode, dstrAddressCode, idDataGroup );
         if( dstrAddressCode.strip() == dstrAddrCode )
         {
            bExists = true;
            break;
         }
      }
      ++iter;
   }

   return(bExists);
}

//*****************************************************************************
SEVERITY AddressList::getAddress (
      Address *&pAddress,
      const DString &addressCode, 
      const DString &date,
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAddressByCode"));

   pAddress = NULL;
   DString date_(date);

//if no date provided, use current business date
   if (date_.strip().empty())
   {
      getWorkSession().getOption (ifds::CurrBusDate, date_, 
         idDataGroup, false);
   }

   BFObjIter iter (*this, idDataGroup);

   while (!iter.end())
   {
      DString addressCode_;
      
      iter.getObject()->getField (ifds::AddrCode, addressCode_, idDataGroup, false);
      addressCode_.strip();
      if (addressCode_.strip() == addressCode)
      {
         DString addrEffectiveDate,
             addrStopDate;

         iter.getObject()->getField (ifds::EffectiveDate, addrEffectiveDate, 
            idDataGroup, false);
         iter.getObject()->getField (ifds::StopDate, addrStopDate, 
            idDataGroup, false);
         if (DSTCommonFunctions::IsDateBetween (addrEffectiveDate, addrStopDate, date_))
         {
            pAddress = dynamic_cast <Address *> (iter.getObject());
            break;
         }
      }
      ++iter;
   } //while
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool AddressList::isAfterPopupTaxJurisUpdate()
{
	/* 
		_bAfterPopupTaxJurisUpdate is used to identify the moment before or after open 
		the Pop up (small dialog) to Update Tax Jurisdiction to shareholder.
		This is benefit for the logic to validate the Country code (Sych to Tax Jurisdiction)
		after the user checked/unchecked the checkbox.
	*/
	return _bAfterPopupTaxJurisUpdate;
}
//******************************************************************************
void AddressList::setAfterPopupTaxJurisUpdate(bool bAfter)
{
	_bAfterPopupTaxJurisUpdate = bAfter;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AddressList.cpp-arc  $
 * 
 *    Rev 1.40   Mar 15 2010 18:01:26   popescu
 * Incident 2047778 - Desktop Error Message - unable to update record.
 * 
 *    Rev 1.39   Jan 25 2010 10:48:14   dchatcha
 * IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
 * 
 *    Rev 1.38   27 Nov 2008 15:02:44   kovacsro
 * IN#1412043 - GL-1280 Updating address on A/C 19998031 (Inter and Nominee Code needs to be set in all 01 addresses, not only in the active one)
 * 
 *    Rev 1.37   Apr 26 2006 12:20:52   porteanm
 * Incident 605455 - Replaced error with warning  WARN_ADDRESS_CODE_NOT_EFFECTIVE.
 * 
 *    Rev 1.36   Nov 14 2004 14:25:32   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.35   May 25 2004 20:34:14   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.34   May 25 2004 20:32:12   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.33   May 20 2004 14:16:54   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.32   Jul 10 2003 16:02:18   HERNANDO
 * Added DoesAddressCodeExist.
 * 
 *    Rev 1.31   Jul 02 2003 18:27:10   ZHANGCEL
 * PTS Ticket 10018762 : Bug fix to ensure an existing valid Address code can be pickup
 * 
 *    Rev 1.30   Mar 21 2003 17:56:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.29   Mar 10 2003 15:11:32   HSUCHIN
 * PTS 10013034 - wrong error message for ineffective address.
 * 
 *    Rev 1.28   Feb 26 2003 13:42:46   YINGBAOL
 * initialize _bNASU
 * 
 *    Rev 1.27   Oct 09 2002 23:53:58   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.26   Aug 29 2002 12:55:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.25   Aug 13 2002 10:33:04   KOVACSRO
 * More clean-up : commented out getAddessByCode since we introduced getAddressByCode.
 * 
 *    Rev 1.24   Aug 09 2002 18:05:56   KOVACSRO
 * beautified code.
 * 
 *    Rev 1.23   Aug 08 2002 17:17:50   KOVACSRO
 * PTS 10009353 : if multiple address for the same code, we'll check the right one, rather than the first one.
 * 
 *    Rev 1.22   Jul 25 2002 17:15:26   KOVACSRO
 * Added getAddressByCode and validateAddress to fix the redemption bug for address validation.
 * 
 *    Rev 1.21   Jun 21 2002 15:59:34   WINNIE
 * strip space and change to uppercase before comparing addrcode value
 * 
 *    Rev 1.20   22 May 2002 18:26:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.19   06 Dec 2001 14:49:52   HSUCHIN
 * removed nominal address check
 * 
 *    Rev 1.18   17 Sep 2001 11:50:34   WINNIE
 * Title restriction escrow enhancement for address changes
 * 
 *    Rev 1.17   Jul 29 2001 14:51:34   YINGBAOL
 * minor change
 * 
 *    Rev 1.16   03 May 2001 14:05:56   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.15   Mar 29 2001 15:55:06   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.14   Feb 12 2001 14:54:40   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.13   Feb 06 2001 14:03:06   YINGZ
 * change the signature of getStrKey
 * 
 *    Rev 1.12   Jan 18 2001 16:03:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.11   Jan 17 2001 12:08:34   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.10   Dec 17 2000 20:22:26   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.9   15 Nov 2000 15:30:18   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.8   Nov 03 2000 11:57:54   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.7   Oct 24 2000 11:45:46   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.6   Sep 28 2000 15:02:24   YINGBAOL
 * change getAddress
 * 
 *    Rev 1.5   Aug 29 2000 11:00:24   YINGBAOL
 * improve behavior for Canadian
 * 
 *    Rev 1.4   Aug 15 2000 10:28:10   YINGBAOL
 * fix Nasu and other bugs for C2
 * 
 *    Rev 1.3   Jul 17 2000 16:55:30   KOVACSRO
 * Added validation for Address Code
 * 
 *    Rev 1.2   Jun 02 2000 16:52:48   YINGZ
 * fix nasu close problem
 * 
 *    Rev 1.1   Mar 17 2000 14:23:00   BUZILA
 * added get01AddessPtr method
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.35   Feb 01 2000 14:36:24   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.34   Jan 31 2000 14:42:26   YINGBAOL
 * check dummy records
 * 
 *    Rev 1.33   Jan 28 2000 14:44:18   YINGBAOL
 * check in for release
 * 
 *    Rev 1.32   Jan 25 2000 18:04:24   YINGBAOL
 * 
 *    Rev 1.31   Jan 24 2000 11:58:18   YINGBAOL
 * fix
 * 
 *    Rev 1.30   Jan 21 2000 16:44:32   YINGBAOL
 * change the way access other list
 * 
 *    Rev 1.29   Jan 20 2000 15:55:36   POPESCUS
 * ignore data not found condition
 * 
 *    Rev 1.28   Jan 18 2000 18:18:10   POPESCUS
 * check in for point release
 * 
 *    Rev 1.27   Jan 17 2000 14:00:26   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.26   Jan 16 2000 16:59:22   POPESCUS
 * ignore address record not found
 * 
 *    Rev 1.25   Jan 14 2000 15:08:54   YINGBAOL
 * modify validation
 * 
 *    Rev 1.24   Jan 07 2000 17:12:38   YINGBAOL
 * modify validation
 * 
 *    Rev 1.23   Jan 06 2000 16:55:46   YINGBAOL
 * 
 *    Rev 1.22   Dec 30 1999 10:37:38   YINGBAOL
 * more validation added
 * 
 *    Rev 1.21   Dec 13 1999 10:43:00   YINGBAOL
 * 
 *    Rev 1.20   Dec 12 1999 16:25:08   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/

