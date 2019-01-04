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
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : SystematicList.cpp
// ^AUTHOR : David Smith
// ^DATE   : Feburary 25, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SystematicList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "autotransallocation.hpp"
#include "autotransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include "autoaccttransallocationlist.hpp"
//#include "bankinstructions.hpp"
#include "dstcommonfunction.hpp"
#include "systematiclist.hpp"
#include "mfaccount.hpp"
#include "systematic.hpp"
#include "sysallocation.hpp"
#include "sysallocationlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_req.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SYSTEMATIC;            
   extern CLASS_IMPORT const DSTCRequest SYSTEMATIC_ALLOCATIONS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SystematicList" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const EFT_PAY_TYPE = I_( "E" );
   const I_CHAR * const TRANS_TYPE_SAVING_PLAN = I_( "V" );
   const I_CHAR * const IDI_TRANSTYPE = I_("TRANSTYPE");
   const I_CHAR * const IDI_FUNDNAME = I_("FUNDNAME");
   const I_CHAR * const IDI_CLASSNAME = I_("CLASSNAME");
   const I_CHAR * const IDI_EFFECDATE = I_("EFFECDATE");
   const I_CHAR * const IDI_CURRENCY = I_("CURRENCY");
   const I_CHAR * const IDI_PLANCODE = I_("PLANCODE");
}

namespace TRID
{
   extern const I_CHAR* PACSWPCLAN;
   extern const I_CHAR* PACSWPALLOCATIONS;
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_PAC_SWP_ALLOCATION_REQUIRED;
   extern const long ERR_DUPLICATE_SYSTEMATIC;
   extern const long ERR_WARN_DUPLICATE_SYSTEMATIC;
   extern const long ERR_BANK_IS_USED;
   extern const long ERR_DUPLICATE_SAVING_PLAN;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long  ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern const long  WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
}
namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
}
namespace ifds
{
 extern CLASS_IMPORT const BFTextFieldId UCITFlag;
}
//*****************************************************************************

SystematicList::SystematicList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), 
_pSysAllocRecvData( NULL ),
_pAtAllocRecvData( NULL ), 
_pMgmtCoOption( NULL ),
_dstrTransTypeParam( NULL_STRING ),
_bValidateAll( true )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
SystematicList::~SystematicList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pSysAllocRecvData )
   {
      delete _pSysAllocRecvData;
      _pSysAllocRecvData = NULL;
   }
   if( _pAtAllocRecvData )
   {
      delete _pAtAllocRecvData;
      _pAtAllocRecvData = NULL;
   }
}

//******************************************************************************

SEVERITY SystematicList::initNew( const DString& strAccountNumber,
								  const DString &strPayType,
							      const DString &strAmount,
							      const DString &strAmountType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _dstrAccountNum = strAccountNumber;
   _dstrPayType = strPayType;
   _dstrAmount = strAmount;
   _dstrAmountType = strAmountType;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY SystematicList::enquiryATAllocation( const DString& strAccountNumber,
                                              const DString& dstrTrack,
                                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString  strAccount(strAccountNumber);

   BFData requestData(ifds::DSTC0007_REQ); 

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::AccountNum, strAccount);
   requestData.setElementValue( ifds::AllocType, I_("AT"));
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   _pAtAllocRecvData = new BFData(ifds::DSTC0007_VW);

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::SYSTEMATIC_ALLOCATIONS, 
                                                            requestData, 
                                                            *_pAtAllocRecvData, 
                                                            DSTCRequestor( getSecurity(), true ) );  
   if( sevRtn > WARNING )
   {
      delete _pAtAllocRecvData;
      _pAtAllocRecvData = NULL;   
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//
// Initialization from the Fund Code and Account Number
//*****************************************************************************
//
SEVERITY SystematicList::init( const DString& strAccountNumber,
							   const DString &strPayType,
							   const DString &strAmount,
							   const DString &strAmountType,
                               const DString& dstrTrack,
                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // get info for validation
   _dstrAccountNum = strAccountNumber;
   _dstrPayType = strPayType;
   _dstrAmount = strAmount;
   _dstrAmountType = strAmountType;

   getInfoForValidation( BF::HOST );

   // get automatic transfer
   SEVERITY sevRtn = enquiryATAllocation( strAccountNumber );
   if( sevRtn > WARNING )
      return(sevRtn);

   {
      // get sysAlocation
      BFData requestData(ifds::DSTC0007_REQ);  

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::AccountNum, _dstrAccountNum);
      requestData.setElementValue( ifds::AllocType, I_("PS"));
      requestData.setElementValue( ifds::Track, dstrTrack );
      requestData.setElementValue( ifds::Activity, dstrPageName );

      _pSysAllocRecvData = new BFData(ifds::DSTC0007_VW);
      sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::SYSTEMATIC_ALLOCATIONS, 
                                                      requestData, 
                                                      *_pSysAllocRecvData, 
                                                      DSTCRequestor( getSecurity(), true ) );  
      if( sevRtn > WARNING )
      {
         delete _pSysAllocRecvData;
         _pSysAllocRecvData = NULL; 
         return(sevRtn);
      }
   }

   {
      // get systematic info
      BFData requestData(ifds::DSTC0006_REQ); 

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::AccountNum, _dstrAccountNum);
      requestData.setElementValue( ifds::Track, dstrTrack );
      requestData.setElementValue( ifds::Activity, dstrPageName );

      BFData* responseData = new BFData(ifds::DSTC0006_VW);

      ReceiveData(DSTC_REQUEST::SYSTEMATIC, requestData, *responseData, DSTCRequestor( getSecurity(), true ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

void SystematicList::getInfoForValidation( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getInfoForValidation" ) );

   if( _pMgmtCoOption ) return;
   try
   {
      getWorkSession().getMFAccount( idDataGroup, const_cast<DString&>(_dstrAccountNum), _pMFAccount); 

      MgmtCo &mgmtCo = getMgmtCo();
      mgmtCo.getMgmtCoOptions( _pMgmtCoOption );
      mgmtCo.getCurrencyList( _pCurrencyList );
//		mgmtCo.getGroupFundList( _pGroupFundList );
      mgmtCo.getFundMasterList(_pFundMasterList);
      mgmtCo.getFundDetailList(_pFundDetailList);
      mgmtCo.getGroupList( _pGroupList );

      getWorkSession().getFirstSequenced01AccountholderEntityName( idDataGroup, _dstrAccountNum, _EntityName );

      DString ShareholderNum;
      _pMFAccount->getField( ifds::ShrNum, ShareholderNum, idDataGroup );
      getWorkSession().getShareholder( idDataGroup, ShareholderNum, _pShareholder );

   }
   catch( ConditionException &ce )
   {
      _pMgmtCoOption = NULL;
      SETCONDITIONFROMEXCEPTION( ce );
   }
}

//*****************************************************************************

SEVERITY SystematicList::getDataObjectKey( BFData &data, DString &strKey )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDataObjectKey" ) );

   //default ementation creates a sequential key
   strKey = data.getElementValue( ifds::PACSWPId );

   return(NO_CONDITION);
}

//*****************************************************************************

void SystematicList::getStrKey (DString &strKey, const BFData *data)
{
   if( data )
      strKey = data->getElementValue( ifds::PACSWPId );
   else
      BFCBO::getStrKey(strKey, NULL);
}

//*****************************************************************************

SEVERITY SystematicList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString strKey;

   getStrKey ( strKey, &data );
   DString dstrPACSWPId = data.getElementValue( ifds::PACSWPId );
   DString dstrTransType = data.getElementValue(ifds::TransType);

   dstrPACSWPId.strip().stripLeading( I_CHAR( '0' ) );

   Systematic* _pSystematic = new Systematic( *this );
   _pSystematic->init( BF::HOST, const_cast< BFData & >( data ), _pSysAllocRecvData, _pAtAllocRecvData, dstrPACSWPId,
	                   _dstrPayType, _dstrAmount, _dstrAmountType );
//	_pSystematic->initAtAcctAlloc( BF::HOST, _pAtAllocRecvData, dstrPACSWPId);
   _pSystematic->init2( BF::HOST, this );

   pObjOut = dynamic_cast<BFCBO* >(_pSystematic);
   //_pSystematic->processSplitCommOption( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SystematicList::doCreateNewObject(BFCBO *& pBase, DString &strKey, 
                                           const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

	// get info for validation
	getInfoForValidation( idDataGroup );

	Systematic *pSystematic = new Systematic( *this );

	pSystematic->initNew( idDataGroup , _dstrPayType, _dstrAmount, _dstrAmountType );
	pSystematic->init2( idDataGroup, this );

	pBase = pSystematic;
	pSystematic->setField(ifds::PACSWPId, strKey, idDataGroup, false );

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

// Should be setEntityName
void SystematicList::getEntityName(DString &EntityName)
{
   _EntityName = EntityName;
}

//******************************************************************************

SEVERITY SystematicList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   const BFFieldId idMonth[] = { ifds::January, ifds::February, ifds::March, ifds::April,
      ifds::May, ifds::June, ifds::July, ifds::August,
      ifds::September, ifds::October, ifds::November, ifds::December};

   if( !_bValidateAll )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   // Duplicate Systematic Check
   DString dstrFundCode1, dstrClassCode1, dstrTransType1, dstrPayType1, dstrEffecDate1, 
   dstrMonthIndicator1, dstrFundToCode1, dstrClassToCode1, dstrAccountTo1;
   DString dstrInstCode1, dstrBankAcctNum1, dstrStopDate1, dstrStatusCode1, dstrSourceOfFund1;
   DString dstrFundCode2, dstrClassCode2, dstrTransType2, dstrPayType2, dstrEffecDate2, 
   dstrMonthIndicator2, dstrFundToCode2, dstrClassToCode2, dstrAccountTo2;
   DString dstrInstCode2, dstrBankAcctNum2, dstrStopDate2, dstrStatusCode2, dstrSourceOfFund2;
   DString dstrTemp, dstrAllowMultPacSwp( NULL_STRING ), dstrMarket = DSTCommonFunctions::getMarket();

   // Check Allow Multiple Pac/Swp
   if( _pMgmtCoOption )
   {
      _pMgmtCoOption->getField( ifds::AllowMultiplePacSwp, dstrAllowMultPacSwp, BF::HOST, false );
   }

   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter2( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter1.end() )
   {
      BFAbstractCBO *pBFCBO1 = iter1.getObject();
	  DString dstrAccountNum;
	  getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	  dstrAccountNum.strip ().stripLeading ('0');
	  MFAccount *pMFAccount = NULL;
	  if (isUpdatedForDataGroup (idDataGroup) && 
	   	getWorkSession().getMFAccount (idDataGroup, dstrAccountNum,
		pMFAccount) <= WARNING && pMFAccount)
	   {	
			bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
			pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
			if(bDisplyWarnSICAV)
				ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
			if(bDisplyWarnOEIC)
				ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
		} 
		DString dstrEventReceiptDate,dstrEventReceiptTime,dstrTransType,dstrUCITSEnv;
		bool bEventReceiptDateTimeAppl = false;
		getWorkSession().getOption(ifds::UCITFlag, dstrUCITSEnv, idDataGroup, false );
		pBFCBO1->getField(ifds::TransType, dstrTransType, idDataGroup, false);
        dstrTransType.strip().upperCase();  
        bEventReceiptDateTimeAppl =  (( dstrUCITSEnv == YES ) && 
									  (dstrTransType == I_("P") || dstrTransType == I_("S") ||
									   dstrTransType == I_("AT"))); 

		pBFCBO1->getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
		pBFCBO1->getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
		if(dstrEventReceiptDate.stripAll().empty() && dstrEventReceiptTime.stripAll().empty()&&
		   bEventReceiptDateTimeAppl)
		{
			 getErrMsg ( IFASTERR::EVENT_RECIEPT_DATE_AND_TIME_EMPTY,
						 CND::ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY,
						 CND::WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY,                     
						 idDataGroup); 
		}
	
	  //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
	   if( iter1.isDummy() )
	   {
		   Systematic *pSystematic = NULL;
		   pSystematic = dynamic_cast <Systematic*>(iter1.getObject());
		   pSystematic->setAllFieldsValid(idDataGroup);
		   return(GETCURRENTHIGHESTSEVERITY());
	   }//end - ticket 2404299

      if( !iter1.isDummy() && pBFCBO1 )
      {
         // Validate bank
         checkBankCurrency( idDataGroup, pBFCBO1 );

         // Validate Systematic
         pBFCBO1->getField(ifds::TransType, dstrTransType1, idDataGroup, false);
         dstrTransType1.strip().upperCase();

         if( dstrTransType1 == I_("P") || dstrTransType1 == I_("S") || dstrTransType1 == I_("AT")
             || dstrTransType1 == TRANS_TYPE_SAVING_PLAN )
         {
            // Common Field Values
            if( dstrTransType1 == I_("AT") )
            {
               pBFCBO1->getField(ifds::FundToCode, dstrFundToCode1, idDataGroup, false);
               pBFCBO1->getField(ifds::ClassToCode, dstrClassToCode1, idDataGroup, false);
               pBFCBO1->getField(ifds::AccountTo, dstrAccountTo1, idDataGroup, false);
            }
            pBFCBO1->getField(ifds::FundCode, dstrFundCode1, idDataGroup, false);
            pBFCBO1->getField(ifds::ClassCode, dstrClassCode1, idDataGroup, false);

            dstrFundCode1.strip().upperCase();
            dstrClassCode1.strip().upperCase();
            dstrFundToCode1.strip().upperCase();
            dstrClassToCode1.strip().upperCase();
            dstrAccountTo1.strip();

            pBFCBO1->getField(ifds::StatusCode, dstrStatusCode1, idDataGroup, false);
            dstrStatusCode1.strip().upperCase();

            if( (
				(dstrTransType1 != I_("AT") && dstrAllowMultPacSwp != YES ) || 
				(dstrTransType1 == I_("AT") && !( dstrFundToCode1 == NULL_STRING && dstrClassToCode1 == NULL_STRING) )
				)
				&& dstrStatusCode1 == YES && !dstrFundCode1.empty() && !dstrClassCode1.empty() )
            {
               // Retrieve Other Field Values
               pBFCBO1->getField(ifds::BankIdValue, dstrInstCode1, idDataGroup, false);
               pBFCBO1->getField(ifds::BankAcctNum, dstrBankAcctNum1, idDataGroup, false);
               pBFCBO1->getField(ifds::EffectiveDate, dstrEffecDate1, idDataGroup, false);
               pBFCBO1->getField(ifds::StopDate, dstrStopDate1, idDataGroup, false);
               pBFCBO1->getField(ifds::PayType, dstrPayType1, idDataGroup, false);

               dstrInstCode1.strip().upperCase();
               dstrBankAcctNum1.strip().upperCase();
               dstrPayType1.strip().upperCase();


               // Monthly Indicator
               dstrMonthIndicator1 = NULL_STRING;
               for( int iMonth = 0; iMonth < 12; iMonth++ )
               {
                  pBFCBO1->getField( idMonth[iMonth], dstrTemp, idDataGroup, false);
                  dstrMonthIndicator1 += dstrTemp.substr(0, 1);
               }
               dstrMonthIndicator1.upperCase();

               // position to the next item
               iter2.positionByKey( iter1.getStringKey() );

               while( true )
               {
                  ++iter2;
                  if( iter2.end() )
                     break;
                  BFAbstractCBO *pBFCBO2 = iter2.getObject();
                  if( !iter2.isDummy() && pBFCBO2 )
                  {
                     pBFCBO2->getField(ifds::TransType, dstrTransType2, idDataGroup, false);
                     dstrTransType2.strip().upperCase();
                     if( dstrTransType1 != dstrTransType2 )
                        continue;

                     pBFCBO2->getField(ifds::FundCode, dstrFundCode2, idDataGroup, false);
                     pBFCBO2->getField(ifds::ClassCode, dstrClassCode2, idDataGroup, false);
                     pBFCBO2->getField(ifds::StatusCode, dstrStatusCode2, idDataGroup, false);
                     pBFCBO2->getField(ifds::BankIdValue, dstrInstCode2, idDataGroup, false);
                     pBFCBO2->getField(ifds::BankAcctNum, dstrBankAcctNum2, idDataGroup, false);
                     pBFCBO2->getField(ifds::EffectiveDate, dstrEffecDate2, idDataGroup, false);
                     pBFCBO2->getField(ifds::StopDate, dstrStopDate2, idDataGroup, false);
                     pBFCBO2->getField(ifds::PayType, dstrPayType2, idDataGroup, false);
                     if( dstrTransType2 == I_("AT") )
                     {
                        pBFCBO2->getField(ifds::FundToCode, dstrFundToCode2, idDataGroup, false);
                        pBFCBO2->getField(ifds::ClassToCode, dstrClassToCode2, idDataGroup, false);
                        pBFCBO2->getField(ifds::AccountTo, dstrAccountTo2, idDataGroup, false);
                     }
                     dstrFundCode2.strip().upperCase();   
                     dstrClassCode2.strip().upperCase();
                     dstrStatusCode2.strip().upperCase();
                     dstrInstCode2.strip().upperCase();
                     dstrBankAcctNum2.strip().upperCase();
                     dstrPayType2.strip().upperCase();
                     dstrFundToCode2.strip().upperCase();
                     dstrClassToCode2.strip().upperCase();
                     dstrAccountTo2.strip();

                     // we should only check good status record
                     if( dstrStatusCode2 == YES && !dstrFundCode2.empty() && !dstrClassCode2.empty() )
                     {
                        // Monthly Indicator
                        dstrMonthIndicator2 = NULL_STRING;
                        for( int iMonth = 0; iMonth < 12; iMonth++ )
                        {
                           pBFCBO2->getField( idMonth[iMonth], dstrTemp, idDataGroup, false);
                           dstrMonthIndicator2 += dstrTemp.substr(0, 1);
                        }
                        dstrMonthIndicator2.upperCase();

                        // Compare
                        bool bInValid = false;

                        dstrInstCode1.stripLeading('0');
                        dstrInstCode2.stripLeading('0');
                        bInValid = dstrFundCode1 == dstrFundCode2 && dstrClassCode1 == dstrClassCode2;
                        
						if( bInValid && dstrTransType2 == I_("AT") )
                           bInValid &= dstrFundToCode1 == dstrFundToCode2 && dstrClassToCode1 == dstrClassToCode2;                        						                        

                        if( dstrPayType1 == EFT_PAY_TYPE && 
							dstrPayType2 == EFT_PAY_TYPE )
						{
                           bInValid &= dstrInstCode1 == dstrInstCode2 && dstrBankAcctNum1 == dstrBankAcctNum2;
						}

                        if( dstrMarket != MARKET_IDS::CANADA )
                        {
                           bInValid &= ( dstrMonthIndicator1 == dstrMonthIndicator2 );
                        }

                        //for AT check AccountTo also for displaying an error
                        if( bInValid && dstrTransType2 == I_("AT") )
						{
                           bInValid &= dstrAccountTo1 == dstrAccountTo2;
						}

                        // Automatic Transfer for all Market : Check if Effective date are equal 
                        // Canadian Market for PAC/SWP/ Saving Plan : Check if Effective date are equal
                        // Other Market for PAC/SWP/Saving Plan : Check if there is overlapping based on start date and end date
                        if( dstrMarket == MARKET_IDS::CANADA ||  dstrTransType1 == I_("AT") )
                        {
                           // Equal
                           bInValid &= (DSTCommonFunctions::CompareDates( dstrEffecDate1, dstrEffecDate2) == DSTCommonFunctions::EQUAL );
                        }
                        else
                        {
                           // Overlap
                           bInValid &= (DSTCommonFunctions::dateRangesOverlap( dstrEffecDate1, dstrStopDate1, dstrEffecDate2, dstrStopDate2 ) );
                        }                        

                        DString idiStr, dstrTransTypeDesc1;
                        pBFCBO1->getField(ifds::TransType, dstrTransTypeDesc1, idDataGroup, true);
                        dstrTransTypeDesc1.strip().upperCase();
                        addIDITagValue( idiStr, IDI_TRANSTYPE, dstrTransTypeDesc1 );
                        addIDITagValue( idiStr, IDI_FUNDNAME,  dstrFundCode1 );
                        addIDITagValue( idiStr, IDI_CLASSNAME, dstrClassCode1 );
						addIDITagValue( idiStr, IDI_EFFECDATE, dstrEffecDate1 );
                        if( bInValid )
                        {
                           addIDITagValue( idiStr, IDI_EFFECDATE, dstrEffecDate1 );
                           ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_SYSTEMATIC, idiStr );
                        }
						/*
                        else
                        {
                           //ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_DUPLICATE_SYSTEMATIC, idiStr );            
						   ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_SYSTEMATIC, idiStr );	
                        }                        
						*/

						if( GETCURRENTHIGHESTSEVERITY() > WARNING )
                        {
                           return(GETCURRENTHIGHESTSEVERITY());
                        }

                     }//if status2 is good
                     //++iter2;
                  }
               }
            }

            // Validate Systematic Allocations
            if( dstrFundCode1.strip().empty() && dstrStatusCode1 == YES )
            {
               if( dstrTransType1 == I_("P") || dstrTransType1 == I_("S") )
               {
                  SysAllocationList *pSysAllocationList;
                  dynamic_cast<Systematic*>(pBFCBO1)->getSysAllocationList(pSysAllocationList);
                  BFObjIter iterAlloc(*pSysAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                  if( iterAlloc.end() || iterAlloc.getNumberOfItemsInList() <= 0 )
                  {
                     ADDCONDITIONFROMFILE( CND::ERR_PAC_SWP_ALLOCATION_REQUIRED );
                     return(GETCURRENTHIGHESTSEVERITY());
                  }
                  else if( iterAlloc.getNumberOfItemsInList() == 1 )
                  {
                     DString dstrFundCode;
                     BFAbstractCBO *pBFCBO = iterAlloc.getObject();
                     pBFCBO->getField(ifds::FundCode, dstrFundCode, idDataGroup);
                     if( dstrFundCode.strip().empty() )
                     {
                        ADDCONDITIONFROMFILE( CND::ERR_PAC_SWP_ALLOCATION_REQUIRED );
                        return(GETCURRENTHIGHESTSEVERITY());
                     }
                  }
               }
               else if( dstrTransType1 == I_("AT") )
               {
                  AutoAcctTransAllocationList* pAutoAcctTransAllocationList = NULL;
                  dynamic_cast<Systematic*>(pBFCBO1)->getAtAcctAllocationList(pAutoAcctTransAllocationList);
                  BFObjIter iter3 (*pAutoAcctTransAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                  if( !iter3.end() )
                  {
                     AutoTransAllocationList* pAutoTransAllocationList = NULL;
                     AutoTransAllocation* pAutoTransAllocation = NULL;
                     dynamic_cast<AutoAcctTransAllocation*> (iter3.getObject())->getAtAllocationList ( pAutoTransAllocationList );
                     BFObjIter iter4 (*pAutoTransAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
                     if( iter4.end() || iter4.getNumberOfItemsInList() <= 0 )
                     {
                        ADDCONDITIONFROMFILE( CND::ERR_PAC_SWP_ALLOCATION_REQUIRED );
                        return(GETCURRENTHIGHESTSEVERITY());
                     }
                     else if( iter4.getNumberOfItemsInList() == 1 )
                     {
                        DString dstrFundCode;
                        BFAbstractCBO *pBFCBO = iter4.getObject();
                        pBFCBO->getField(ifds::FundCode, dstrFundCode, idDataGroup);
                        if( dstrFundCode.strip().empty() )
                        {
                           ADDCONDITIONFROMFILE( CND::ERR_PAC_SWP_ALLOCATION_REQUIRED );
                           return(GETCURRENTHIGHESTSEVERITY());
                        }
                     }
                  } //if ( !iter3.end() ) 
               } // else if ( dstrTransType1 == I_("AT") )
            } // if (dstrFundCode1.strip().empty())
         }  //if ( dstrTransType1 == I_("P") || dstrTransType1 == I_("S") || dstrTransType1 == I_("AT") || dstrTransType1 == TRANS_TYPE_SAVING_PLAN )
      } // if ( !iter1.isDummy() && pBFBase1 )
      ++iter1;
   } //while (!iter1.end())
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

void SystematicList::AddCopy(DString &orgKey, DString &destKey, const BFDataGroupId& idDataGroup)
{
   Systematic *pOrgSystematic = NULL, *pDestSystematic = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == orgKey )
      {
         pOrgSystematic = dynamic_cast< Systematic * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == destKey )
      {
         pDestSystematic = dynamic_cast< Systematic * >( Iter.getObject( ) );
      }
   }

   assert ( pOrgSystematic && pDestSystematic );

   pDestSystematic->ModelOffer(pOrgSystematic, idDataGroup);
}

//******************************************************************************

SEVERITY SystematicList::doDeleteObject ( const DString&  strKey,   const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doDeleteObject " ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void SystematicList::checkBankCurrency( const BFDataGroupId& idDataGroup, BFAbstractCBO *pSystematic )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "checkBankCurrency( long, BFAbstractCBO * )" ) );
//   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBankCurrency " ) );
   DString dstrMultiCurrency;
   getWorkSession().getOption( ifds::MultiCurrency, dstrMultiCurrency, idDataGroup, false );
   if( dstrMultiCurrency != YES )
   {
      DString dstrPayType, dstrBankAcctNum0, dstrBankAcctCurrency0, dstrBankAcctNum, dstrBankAcctCurrency;

      pSystematic->getField(ifds::BankAcctNum, dstrBankAcctNum0, idDataGroup, false);
      pSystematic->getField(ifds::BankAcctCurrency, dstrBankAcctCurrency0, idDataGroup, false);

      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      while( !iter.end() )
      {
         BFAbstractCBO *_pSystematic = iter.getObject();

         if( pSystematic != _pSystematic )
         {
            _pSystematic->getField(ifds::PayType, dstrPayType, idDataGroup, false);

            if( dstrPayType == EFT_PAY_TYPE )
            {
               _pSystematic->getField(ifds::BankAcctNum, dstrBankAcctNum, idDataGroup, false);
               _pSystematic->getField(ifds::BankAcctCurrency, dstrBankAcctCurrency, idDataGroup, false);
               if( dstrBankAcctNum == dstrBankAcctNum0 && dstrBankAcctCurrency != dstrBankAcctCurrency0 )
               {
                  DString idiStr;
                  addIDITagValue( idiStr, IDI_CURRENCY, dstrBankAcctCurrency );
                  ADDCONDITIONFROMFILEIDI( CND::ERR_BANK_IS_USED,idiStr );          
                  break;
               }
            }
         }
         ++iter;
      }
   }
}

//*****************************************************************************

void SystematicList::checkSavingPlanDuplication( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkSavingPlanDuplication " ) );
   DString dstrFundCode, dstrClassCode, dstrPlanCode, dstrEffecDate, dstrStopDate, dstrStatusCode, dstrTransType;
   DString dstrFundCode1, dstrClassCode1, dstrPlanCode1, dstrEffecDate1, dstrStopDate1;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO;
   BFAbstractCBO *pBFCBO1;

   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      if( !iter.isDummy()  && pBFCBO )
      {
         pBFCBO->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         pBFCBO->getField(ifds::StatusCode, dstrStatusCode, idDataGroup, false);

         if( dstrTransType == TRANS_TYPE_SAVING_PLAN && dstrStatusCode == YES )
         {
            pBFCBO->getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup);
            pBFCBO->getField(ifds::StopDate, dstrStopDate, idDataGroup);

            if( DSTCommonFunctions::CompareDates( dstrEffecDate, dstrStopDate ) // check only when date are valid
                == DSTCommonFunctions::FIRST_EARLIER )
            {
               pBFCBO->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
               pBFCBO->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
               pBFCBO->getField(ifds::PlanCode, dstrPlanCode, idDataGroup, false);
               dstrFundCode.strip().upperCase();   
               dstrClassCode.strip().upperCase();

               // position to the next item
               iter1.positionByKey( iter.getStringKey() );
               if( !iter1.end() )++iter1;

               while( !iter1.end() )
               {
                  pBFCBO1 = iter1.getObject();
                  if( !iter1.isDummy()  && pBFCBO1 )
                  {
                     pBFCBO1->getField(ifds::TransType, dstrTransType, idDataGroup, false);
                     pBFCBO1->getField(ifds::StatusCode, dstrStatusCode, idDataGroup, false);

                     if( dstrTransType == TRANS_TYPE_SAVING_PLAN && dstrStatusCode == YES )
                     {
                        pBFCBO1->getField(ifds::EffectiveDate, dstrEffecDate1, idDataGroup);
                        pBFCBO1->getField(ifds::StopDate, dstrStopDate1, idDataGroup);
                        pBFCBO1->getField(ifds::FundCode, dstrFundCode1, idDataGroup, false);
                        pBFCBO1->getField(ifds::ClassCode, dstrClassCode1, idDataGroup, false);
                        pBFCBO1->getField(ifds::PlanCode, dstrPlanCode1, idDataGroup, false);
                        dstrFundCode1.strip().upperCase();   
                        dstrClassCode1.strip().upperCase();

                        if( dstrFundCode == dstrFundCode1 && dstrClassCode == dstrClassCode1
                            && dstrPlanCode == dstrPlanCode1 &&
                            DSTCommonFunctions::CompareDates( dstrEffecDate1, dstrStopDate1 ) // check only when date are valid
                            == DSTCommonFunctions::FIRST_EARLIER )
                        {
                           if( DSTCommonFunctions::CompareDates( dstrEffecDate1, dstrStopDate ) 
                               == DSTCommonFunctions::FIRST_EARLIER  &&
                               DSTCommonFunctions::CompareDates( dstrEffecDate, dstrStopDate1 ) 
                               == DSTCommonFunctions::FIRST_EARLIER )
                           {
                              DString idiStr;
                              addIDITagValue( idiStr, IDI_FUNDNAME,  dstrFundCode);
                              addIDITagValue( idiStr, IDI_CLASSNAME, dstrClassCode);
                              addIDITagValue( idiStr, IDI_PLANCODE, dstrPlanCode);
                              pBFCBO->getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, true);
                              addIDITagValue( idiStr, IDI_EFFECDATE, dstrEffecDate);
                              ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_SAVING_PLAN,idiStr );
                              return;
                           }
                        }
                     }
                  }
                  ++iter1;
               }
            }
         }
      }
      ++iter;
   }
}
//******************************************************************************
bool SystematicList::hasGoodSWPAtDate(const BFDataGroupId& idDataGroup,const DString& dstrDate )
{
  bool bRet = false;
  BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
  while( !iter.end() )
  {
	 Systematic* pSys = dynamic_cast<Systematic* >( iter.getObject() );
	 if( pSys->isSWPGoodAtDate( idDataGroup, dstrDate ) )
	 {
		bRet = true;
		break;
	 }  
	 ++iter;
  }
	
  return bRet;
}

//******************************************************************************
bool SystematicList::hasNonAMSFunds(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   while (!retVal && !iter.end()) 
   {
		DString dstrTransType;
      Systematic *pSystematic = dynamic_cast <Systematic*>(iter.getObject());
      if(pSystematic)
      {
         pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup);
         dstrTransType.strip().upperCase();  
         if(dstrTransType == I_("P"))
         {
            retVal = pSystematic->hasNonAMSFunds(idDataGroup);
		   }     		
      }
		++iter;
   }
	return retVal;
}

//******************************************************************************
bool SystematicList::areAllSytematicRecordsInactive (const BFDataGroupId& idDataGroup)
{
	bool bAreAllSytematicRecordsInactive = false;
	BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
	
	DString dstrCurrentBusinessDate;
	
	getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );
   
	while (!iter.end()) 
	{
		Systematic *pSystematic = dynamic_cast <Systematic*>(iter.getObject());

		if (pSystematic)
		{
			DString dstrStopDate (NULL_STRING), 
				dstrRecordStatus (NULL_STRING);

			pSystematic->getField (ifds::StopDate, dstrStopDate, idDataGroup);
			pSystematic->getField (ifds::StatusCode, dstrRecordStatus, idDataGroup);

			dstrStopDate.strip().upperCase();
			dstrRecordStatus.strip().upperCase();
			
			bAreAllSytematicRecordsInactive = DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurrentBusinessDate) == 
					DSTCommonFunctions::FIRST_EARLIER || dstrRecordStatus != Y;
			if (!bAreAllSytematicRecordsInactive)
			{
				break;
			}
		}
		++iter;
	}
	return bAreAllSytematicRecordsInactive;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SystematicList.cpp-arc  $
 * 
 *    Rev 1.57   Feb 27 2011 21:06:04   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.56   Nov 24 2010 18:53:46   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.55   Jun 19 2006 09:07:46   porteanm
 * Incident 641896 - Rejecting multiple PACs in doValidateAll().
 * 
 *    Rev 1.54   Oct 31 2005 16:49:50   porteanm
 * Incident 440904 - Skip allocation check for a bad record.
 * 
 *    Rev 1.53   Nov 14 2004 14:56:48   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.52   Oct 03 2003 19:19:36   popescu
 * CIBC PET 809, FN13, removed references to BankSearch and BankList objects
 * 
 *    Rev 1.51   Aug 11 2003 11:57:12   YINGBAOL
 * add method hasGoodSWPAtDate;
 * 
 *    Rev 1.50   Jun 11 2003 16:53:22   FENGYONG
 * duplicate checking
 * 
 *    Rev 1.49   Jun 06 2003 13:52:36   FENGYONG
 * 10017701
 * 
 *    Rev 1.48   Jun 01 2003 17:08:06   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.47   May 22 2003 14:13:30   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.46   Mar 21 2003 18:25:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.45   Oct 25 2002 17:17:42   HERNANDO
 * Fix - Duplicate date comparison.  Compares unformatted dates.  Previously European Display format caused undesirable results.
 * 
 *    Rev 1.44   Oct 09 2002 23:55:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.43   Sep 20 2002 14:00:30   KOVACSRO
 * More fix for AT duplicate check (checking AccountTo also to decide if we show the error message)
 * 
 *    Rev 1.42   Sep 20 2002 13:22:00   KOVACSRO
 * synced up AT fix for uniqueness check (1.37.0.1)
 * 
 *    Rev 1.41   Sep 04 2002 18:44:56   PURDYECH
 * Corrected incorrect use of BFFieldId arrays.
 * 
 *    Rev 1.40   Aug 29 2002 12:56:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.39   22 May 2002 18:30:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.38   Feb 25 2002 18:55:52   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.37   27 Dec 2001 16:24:30   KOVACSRO
 * Fixed a couple of bugs when checking for duplicate systematics.
 * 
 *    Rev 1.36   Nov 29 2001 14:44:42   ZHANGCEL
 * Comment "getGroupFundList" since it is useless
 * 
 *    Rev 1.35   21 Nov 2001 10:10:02   HSUCHIN
 * bug fix to sysallocation check during an Auto Transfer
 * 
 *    Rev 1.34   Oct 26 2001 14:13:06   ZHANGCEL
 * Added logic to validate an automatic transfer without entering fundto/classto nor allocation for fundto
 * 
 *    Rev 1.33   Aug 23 2001 09:30:50   YINGBAOL
 * do not validate duplicate transfer if there are allocation list
 * 
 *    Rev 1.32   22 Aug 2001 11:46:54   WINNIE
 * code clean up to speed up and remove duplicate code
 * 
 *    Rev 1.31   Aug 02 2001 02:55:02   YINGBAOL
 * fix check for transfer time overlap
 * 
 *    Rev 1.30   Jul 29 2001 15:01:16   YINGBAOL
 * fix validate for 2 items with time overlap
 * 
 *    Rev 1.29   05 Jul 2001 15:11:02   YINGZ
 * bus rules
 * 
 *    Rev 1.28   Jul 03 2001 15:08:10   HERNANDO
 * Changed doValidateAll() to check for Duplicates.
 * 
 *    Rev 1.27   16 Jun 2001 14:30:28   YINGZ
 * check saving plan duplication
 * 
 *    Rev 1.26   11 May 2001 15:01:32   HSUCHIN
 * added missing sync checkbankcurrency from (1.23.1.3)
 * 
 *    Rev 1.25   11 May 2001 10:24:44   HSUCHIN
 * Sync up with SSB (1.23.1.3)
 * 
 *    Rev 1.24   03 May 2001 14:07:08   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.23   30 Mar 2001 17:09:36   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.22   Mar 09 2001 11:39:26   OLTEANCR
 * modified doValidateAll(..)
 * 
 *    Rev 1.21   Mar 05 2001 16:16:12   YINGBAOL
 * validate fundclass transfer
 * 
 *    Rev 1.20   27 Feb 2001 10:54:22   KOVACSRO
 * Duplicate PAC/SWP doesn't show any more for bad ones.
 * 
 *    Rev 1.19   Jan 18 2001 16:09:56   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.18   Jan 17 2001 12:08:24   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.17   Dec 17 2000 20:24:36   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.16   Nov 03 2000 11:34:46   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.15   Nov 02 2000 14:11:38   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.14   Sep 29 2000 13:27:12   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.13   Sep 06 2000 14:49:12   YINGBAOL
 * change sync.
 * 
 *    Rev 1.12   Aug 04 2000 13:58:42   YINGBAOL
 * change enquiry bank 
 * 
 *    Rev 1.11   Aug 01 2000 12:12:06   HUANGSHA
 * more validations
 * 
 *    Rev 1.10   Jun 27 2000 10:54:14   HUANGSHA
 * added check for duplicaticate systematic record
 * 
 *    Rev 1.9   Jun 06 2000 15:11:14   HUANGSHA
 * add setValidateFlag(bool)
 * 
 *    Rev 1.8   May 19 2000 17:10:26   HUANGSHA
 * Removed the Market Condition for AT
 * 
 *    Rev 1.7   May 01 2000 09:40:08   YINGBAOL
 * add validation and other logic
 * 
 *    Rev 1.6   Apr 17 2000 17:15:58   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.5   Apr 14 2000 11:58:34   YINGBAOL
 * init logic and add some function for automatic transfer
 * 
 *    Rev 1.4   Apr 05 2000 16:00:24   HUANGSHA
 * bug fix
 * 
 *    Rev 1.3   Apr 04 2000 10:47:18   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.2   Mar 31 2000 16:21:46   YINGBAOL
 * 
 *    Rev 1.1   Feb 28 2000 15:31:10   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.37   Feb 09 2000 12:12:54   HUANGSHA
 * check in for release
 * 
 *    Rev 1.36   Feb 07 2000 12:30:42   BUZILA
 * fix
 * 
 *    Rev 1.35   Feb 01 2000 14:36:30   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.34   Jan 28 2000 10:23:38   BUZILA
 * don't want to do validation on dummy items
 * 
 *    Rev 1.33   Jan 26 2000 18:03:34   HUANGSHA
 * check in
 * 
 *    Rev 1.32   Jan 25 2000 17:10:10   HUANGSHA
 * Fixed bugs
 * 
 *    Rev 1.31   Jan 18 2000 11:23:54   YINGZ
 * getInfoForValidation
 * 
 *    Rev 1.30   Jan 14 2000 14:20:48   YINGZ
 * forget one param!
 * 
 *    Rev 1.29   Jan 14 2000 14:14:48   YINGZ
 * change init to initNew
 * 
 *    Rev 1.28   Jan 06 2000 14:13:48   YINGZ
 * reflect base changes
 * 
 *    Rev 1.27   Jan 04 2000 17:43:20   YINGZ
 * save work
 * 
 *    Rev 1.26   Dec 23 1999 14:29:46   YINGZ
 * release
 * 
 *    Rev 1.25   Dec 21 1999 17:25:28   YINGZ
 * add validation
 * 
 */
