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
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : TradeBankList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : March 2, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : TradeBankList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "bankinstructions.hpp"
#include "ClientBankInstructionsList.hpp"
#include "ShareholderBankInstructionsList.hpp"
#include <dataimpl\dse_dstc0052_vw.hpp>
#include <dataimpl\dse_dstc0055_vw.hpp>
#include <dataimpl\dse_dstc0055_req.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include "tradebankinstr.hpp"
#include "tradebanklist.hpp"
#include "trade.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTIONBANKINSTR;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME      = I_( "TradeBankList" );
   const I_CHAR * const BLANK_SUBSTITUTION = I_( " = ;"); // substitution with only one element with tag = value = " " 

   I_CHAR *  EFT_TRADE_BANK_OBJ        = I_( "1EFTTrade" );
   I_CHAR *  DEFAULT_BANK_OBJ          = I_( "2Default" );
   I_CHAR *  LAST_EFT_BANK_OBJ         = I_( "3LastUsedEFT" );
   I_CHAR *  CUSTOM_EFT_BANK_OBJ       = I_( "4Custom" );

   I_CHAR *  EFT_PURCHASE              = I_( "EDE" );   
   I_CHAR *  EFT_REDEMPTION            = I_( "PWE" );
	I_CHAR *  EFT_ADMINFEE              = I_( "AFE" );
   I_CHAR *  INTERNATIONAL_WIRE_REDEMPTION = I_( "PWI" ); 

   I_CHAR *  EFT_PURCHASE_BANK_CODE    = I_( "11" );
   I_CHAR *  EFT_REDEMPTION_BANK_CODE  = I_( "07" );
   I_CHAR *  DEFAULT_BANK_CODE         = I_( "00" );
   I_CHAR *  INTERNATIONAL_WIRE_BANK_CODE = I_( "24" );
   I_CHAR *  DIRECT_TRADING				= I_( "31" );
	I_CHAR *  COMM_CLEAR						= I_( "04" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankType;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId TradesPayType;
   extern CLASS_IMPORT const BFTextFieldId TradesTransType;
	extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFNumericFieldId InterDetlRid;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
	extern CLASS_IMPORT const BFTextFieldId BankInstrType;
};

namespace CND
{  // Conditions used
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_ACCTUSE_ALREADY_EXIST;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace BANKTYPE
{
	extern CLASS_IMPORT I_CHAR * const TRADE;
}

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//      Object Label,            State Flags,          Group Flags 
//   { EFT_TRADE_BANK_OBJ,   BFBase::NO_BASE_DELETE,    0   },
//   { DEFAULT_BANK_OBJ,        BFBase::NO_BASE_DELETE,    0   },
//   { LAST_EFT_BANK_OBJ,       BFBase::NO_BASE_DELETE,    0   },
   { CUSTOM_EFT_BANK_OBJ,     BFCBO::NONE,  0},

};

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   {  BFCBO::CLASS_FIELD_INFO( ifds::AccountNum,      BFCBO::NONE, 0 )}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
TradeBankList::TradeBankList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent ),
m_dstSettleCurrency( NULL_STRING ), 
m_dstShrNum( NULL_STRING ), 
m_dstAcctNum( NULL_STRING ), 
m_dstTransType( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
      0/*NUM_OBJECTS*/, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );

   setObjectAsList( );
}

//******************************************************************************
TradeBankList::~TradeBankList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY TradeBankList::init( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeBankList::init( const DString& shareholderNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY TradeBankList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY TradeBankList::doCreateNewObject( BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeBankList::refreshList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refreshList( const BFDataGroupId& idDataGroup )" ) );

   return(refreshList( idDataGroup, m_dstShrNum, m_dstAcctNum, m_dstSettleCurrency, m_dstTransType ));
}

//******************************************************************************
SEVERITY TradeBankList::refreshList( const BFDataGroupId& idDataGroup, const DString& dstShrNum, const DString& dstAcctNum, 
                                     const DString& dstSettleCurrency, const DString& dstTransType,
                                     const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refresh" ) );

   m_dstShrNum         = dstShrNum;
   m_dstAcctNum        = dstAcctNum;
   m_dstSettleCurrency = dstSettleCurrency;
   m_dstTransType      = dstTransType;


   SEVERITY sevRtn = NO_CONDITION;
   Shareholder* pShareholder = NULL;
   ShareholderBankInstructionsList* pShareholderBankInstructionsList = NULL;

   DString ldstSettleCurrency;
   DString ldstPayType;
   DString ldstAcctUseCode;

   bool bDefault(false), bEFTTrade(false);
   DString dstrAcctUsageCode (DEFAULT_BANK_CODE);

   getAcctUsageCode ( dstTransType, dstrAcctUsageCode );

   clearCustomBank( idDataGroup ); // delete custom bank
   BFObjIter thisIter( *this, idDataGroup, false );

   do  // delete shareholder EFT default bank
   {
      thisIter.positionByKey( EFT_TRADE_BANK_OBJ, OBJ_TYPE_NONE );
      if( !thisIter.end() )
         thisIter.removeObjectFromMap( false );
   }while( !thisIter.end() );

   do // delete shareholder default bank
   {
      thisIter.positionByKey( DEFAULT_BANK_OBJ, OBJ_TYPE_NONE );
      if( !thisIter.end() )
         thisIter.removeObjectFromMap( false );
   }while( !thisIter.end() );

   do // delete last EFT bank
   {
      thisIter.positionByKey( LAST_EFT_BANK_OBJ, OBJ_TYPE_NONE );
      if( !thisIter.end() )
         thisIter.removeObjectFromMap( false );
   }while( !thisIter.end() );

	// Get client bank for AdminFee
	if ( dstTransType == EFT_ADMINFEE )
	{
		ClientBankInstructionsList *pClientBankInstructionsList = NULL;
		if (getWorkSession().getClientBankInstructionsList( pClientBankInstructionsList, idDataGroup) <= WARNING
																			 && pClientBankInstructionsList)
		{
			BFObjIter iter( *pClientBankInstructionsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			while( !iter.end() )
			{
				iter.getObject()->getField( ifds::BankAcctCurrency, ldstSettleCurrency, idDataGroup );
				iter.getObject()->getField( ifds::AcctUseCode,    ldstAcctUseCode,    idDataGroup );
				ldstSettleCurrency.strip().upperCase();

				if( dstSettleCurrency == ldstSettleCurrency && ldstAcctUseCode == dstrAcctUsageCode)
				{
					setObject( iter.getObject(), EFT_TRADE_BANK_OBJ, OBJ_ACTIVITY_NONE, idDataGroup ); //,NO_BASE_DELETE );
					bEFTTrade = true;
				}
				++iter;
			}
		}
	}
   else if ( getWorkSession().getShareholder( idDataGroup, dstShrNum, pShareholder ) <= WARNING )
   {
      if( pShareholder->getShareholderBankInstructionsList( pShareholderBankInstructionsList, idDataGroup ) <= WARNING )
      {
         BFObjIter iter( *pShareholderBankInstructionsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         while( !iter.end() )
         {
            iter.getObject()->getField( ifds::BankAcctCurrency, ldstSettleCurrency, idDataGroup );
            iter.getObject()->getField( ifds::AcctUseCode,    ldstAcctUseCode,    idDataGroup );
            ldstSettleCurrency.strip().upperCase();

            if( dstrAcctUsageCode != DEFAULT_BANK_CODE && dstSettleCurrency == ldstSettleCurrency )
            {
               if( ldstAcctUseCode == dstrAcctUsageCode )
               {
                  setObject( iter.getObject(), EFT_TRADE_BANK_OBJ, OBJ_ACTIVITY_NONE, idDataGroup );
                  bEFTTrade = true;
               }
               else if( ldstAcctUseCode == DEFAULT_BANK_CODE && dstrAcctUsageCode != DIRECT_TRADING )
               {
                  setObject( iter.getObject(), DEFAULT_BANK_OBJ, OBJ_ACTIVITY_NONE, idDataGroup );
                  bDefault = true;
               }
            }
            ++iter;
         }

      }
   }

   //Direct trading won't get last trade bank if there is direct trading bank found.
   if( dstrAcctUsageCode != DIRECT_TRADING /*&& dstrAcctUsageCode != COMM_CLEAR*/ && getObject( LAST_EFT_BANK_OBJ, BF::HOST ) == NULL )
   {
      MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("block") );

      BFData queryData(ifds::DSTC0055_REQ);
      BFData *response = new BFData(ifds::DSTC0055_VW);
      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::Currency, dstSettleCurrency ); 
      queryData.setElementValue( ifds::TransPending, I_("L") );
      queryData.setElementValue( ifds::AccountNum, dstAcctNum );
      queryData.setElementValue( ifds::LastBankType, dstTransType ); // EDE, PWE or PWI

      bool dataFound = false;

      DSTCRequestor requestor( getSecurity(),true, false );

      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );

      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::TRANSACTIONBANKINSTR, queryData, *response, DSTCRequestor( getSecurity() ) /*requestor*/ )  > WARNING )
      {
         delete response;
         response = NULL;
      }
      else
      {
         int cRepeats = response->getRepeatCount();
         if( cRepeats >0 )
         {
            TradeBankInstr * pBI = new TradeBankInstr ( *this );
            BFData * rpt = new BFData(response->getRepeat(0));
            dataFound = true;
            pBI->initLastEFT( *rpt );
				pBI->setField( ifds::BankInstrType, BANKTYPE::TRADE, BF::HOST, false );
				pBI->setField( ifds::TransType, m_dstTransType, BF::HOST, false );
            pBI->setField( ifds::AcctUseCode, dstrAcctUsageCode, /*I_("LastTrade"),*/ BF::HOST, false );
            setObject( pBI, LAST_EFT_BANK_OBJ );
         }
      }      
   };

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY TradeBankList::getPendingTradeBank( const BFDataGroupId& idDataGroup, const Trade* pTrade, const DString& dstSettleCurrency, 
                                             const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingBank" ) );
   if( getObject( CUSTOM_EFT_BANK_OBJ, BF::HOST ) == NULL )
   {
      MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("block") );

      m_dstSettleCurrency = dstSettleCurrency;

      DString dstrPayType, dstrTransType, dstrTransPayType, dstrPendingRid;
      pTrade->getField ( ifds::TradesPayType, dstrPayType, idDataGroup, false);
      pTrade->getField ( ifds::TradesTransType, dstrTransType, idDataGroup, false);
      pTrade->getField ( ifds::InterDetlRid, dstrPendingRid, idDataGroup, false);

      dstrTransPayType = dstrTransType.strip().upperCase() + dstrPayType.strip().upperCase();
      m_dstTransType  = dstrTransPayType;

      DString mgmtCoIdOut;

      BFData queryData(ifds::DSTC0055_REQ);
      BFData *response = new BFData(ifds::DSTC0055_VW);
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::PendingRid, dstrPendingRid ); 
      queryData.setElementValue( ifds::TransPending, I_("P") );

      bool dataFound = false;

      DSTCRequestor requestor( getSecurity(), true, false );

      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );

      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::TRANSACTIONBANKINSTR, queryData, *response, DSTCRequestor( getSecurity() ) /*requestor*/ )  > WARNING )
      {
         delete response;
         response = NULL;

      }
      else
      {

         int cRepeats = response->getRepeatCount();

         if( cRepeats > 0 )
         {
            TradeBankInstr * pBI = new TradeBankInstr ( *this );
            BFData * rpt = new BFData( response->getRepeat(0));
            dataFound = true;


            //pBI->init( *rpt );

            DString dstrAcctUseCode;
            getAcctUsageCode ( dstrTransPayType, dstrAcctUseCode );

            pBI->initPendingTradeBank ( *rpt, pTrade, dstrAcctUseCode, dstSettleCurrency, BF::HOST );

            setObject( pBI, CUSTOM_EFT_BANK_OBJ );
         }

      }

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeBankList::clearCustomBank( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearCustomBank" ) );
   SEVERITY sevRtn = NO_CONDITION;

   BFObjIter iter( *this, idDataGroup );
   iter.positionByKey( CUSTOM_EFT_BANK_OBJ );
   if( !iter.end() )
      iter.removeObjectFromMap( true );

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
SEVERITY TradeBankList::checkCustomBank( const BFDataGroupId& idDataGroup, const DString& dstBankKey, const Trade* pTrade )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "refresh" ) );

   SEVERITY sevRtn = NO_CONDITION;

   BankInstructions * pModelBI = dynamic_cast < BankInstructions * >(getObject( dstBankKey, idDataGroup ));
   TradeBankInstr * pBI = dynamic_cast < TradeBankInstr * >(getObject( CUSTOM_EFT_BANK_OBJ, idDataGroup ));

   DString dstrPayType, dstrTransType, dstrTransPayType;
   pTrade->getField ( ifds::TradesPayType, dstrPayType, idDataGroup, false);
   pTrade->getField ( ifds::TradesTransType, dstrTransType, idDataGroup, false);
   dstrTransPayType = dstrTransType.strip().upperCase() + dstrPayType.strip().upperCase();

   if( !pBI )
   {
      DString dstrAcctUseCode;
      getAcctUsageCode ( dstrTransPayType, dstrAcctUseCode );
      BFData * pData = new BFData( ifds::DSTC0052_VWRepeat_Record );

      if( pModelBI )
      {
         pModelBI->getData( *pData, idDataGroup );
         pData->setElementValue(ifds::AcctUseCode, dstrAcctUseCode );
      }

      pBI = new TradeBankInstr( *this );
      //pBI->init( *pData );
      if( m_dstAcctNum.strip().empty() )
         pTrade->getField ( ifds::AccountNum, m_dstAcctNum, idDataGroup, false);
      pBI->initNewTradeBank ( *pData, (pModelBI == NULL), m_dstAcctNum.strip(), pTrade, dstrAcctUseCode, idDataGroup);
      setObject( pBI, CUSTOM_EFT_BANK_OBJ, OBJ_ACTIVITY_ADDED, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TradeBankList::setObjectFlags( const BFObjectKey & objKey, long& lStateFlags , long& lGroupFlags )
{
   if( objKey.getStringKey() == EFT_TRADE_BANK_OBJ || objKey.getStringKey() == DEFAULT_BANK_OBJ )
      lStateFlags = BFCBO::NO_BASE_DELETE;
   else
      lStateFlags = BFCBO::NONE;

   lGroupFlags = 0;
}


//******************************************************************************
void TradeBankList::getAcctUsageCode ( const DString& dstrTransPayType, DString& dstrAcctUseCode )
{

   if( dstrTransPayType == I_( "EDE" ) )
      dstrAcctUseCode = EFT_PURCHASE_BANK_CODE;
   if( dstrTransPayType == I_( "PWE" ) )
      dstrAcctUseCode = EFT_REDEMPTION_BANK_CODE;
   if( dstrTransPayType == I_( "PWI" ) )
      dstrAcctUseCode = INTERNATIONAL_WIRE_BANK_CODE;
   if( dstrTransPayType == I_("EDD") || dstrTransPayType == I_("PWD") )
      dstrAcctUseCode = DIRECT_TRADING;
	if( dstrTransPayType == I_("AFE"))
      dstrAcctUseCode = COMM_CLEAR;

}
//******************************************************************************

void TradeBankList::getCustomBank(BankInstructions*& pBankInstructions, const BFDataGroupId& idDataGroup)
{
   pBankInstructions = dynamic_cast < BankInstructions * >(getObject( CUSTOM_EFT_BANK_OBJ, idDataGroup ));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankList.cpp-arc  $
 * 
 *    Rev 1.41   Dec 22 2004 10:39:46   popescu
 * PTS 10036805, get the las eft transaction bank for AF's
 * 
 *    Rev 1.40   Sep 15 2004 11:43:46   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface - Set BankInstrType to BANKTYPE::TRADE and TransType to current Trans Type.
 * 
 *    Rev 1.39   Sep 09 2004 10:01:54   ZHANGCEL
 * PET1094_FN8 -- AdminFee related changed
 * 
 *    Rev 1.38   Oct 23 2003 17:58:40   FENGYONG
 * PET809 FN08 Direct trading enhancement
 * 
 *    Rev 1.37   Aug 14 2003 12:13:38   popescu
 * Acct name should be part of the banking list fields 
 * 
 *    Rev 1.36   May 31 2003 11:55:36   popescu
 * RRIF bank work
 * 
 *    Rev 1.35   May 22 2003 14:13:38   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.34   Mar 21 2003 18:27:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.33   Oct 09 2002 23:55:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.32   Aug 29 2002 12:56:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.31   Aug 09 2002 16:37:18   KOVACSRO
 * Fix for account number when refreshList hasn't been called before.
 * 
 *    Rev 1.30   Jun 21 2002 17:45:06   KOVACSRO
 * initLastEFT
 * 
 *    Rev 1.29   Jun 14 2002 17:37:46   KOVACSRO
 * new TradeBankInstr class modifications.
 * 
 *    Rev 1.28   Jun 13 2002 17:29:10   KOVACSRO
 * Pending trade modifications.
 * Added getCustomBank.
 * 
 *    Rev 1.27   Jun 07 2002 17:52:30   KOVACSRO
 * passing a trade pointer
 * 
 *    Rev 1.26   22 May 2002 18:30:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.25   Aug 17 2001 14:29:30   FENGYONG
 * fill company id before call 355
 * 
 *    Rev 1.24   Jul 20 2001 15:27:58   ZHANGCEL
 * Fixed the crash which caused by removing object from map in refreshList().
 * 
 *    Rev 1.23   16 Jul 2001 16:31:40   WINNIE
 * sync up 1.18.1.11 : delete and remove bankinstr object from the list in refresh method when switching to a different settle currency
 * 
 *    Rev 1.22   Jul 04 2001 11:32:18   ZHANGCEL
 * Sync up with 1.18.1.10
 * 
 *    Rev 1.21   May 16 2001 17:41:56   WINNIE
 * Fix bank type default value: sync up with 1.18.1.8
 * 
 *    Rev 1.20   11 May 2001 10:50:28   HSUCHIN
 * Sync up with SSB (1.18.1.7)
 * 
 *    Rev 1.18.1.7   Apr 30 2001 13:57:50   WINNIE
 * assign valid account usage code
 * 
 *    Rev 1.18.1.6   Apr 28 2001 15:36:10   WINNIE
 * Fix bank refresh with switching settlecurrency
 * 
 *    Rev 1.18.1.5   Apr 27 2001 14:28:56   WINNIE
 * Fix international wire for redemption; fix readonly set up for fields.
 * 
 *    Rev 1.18.1.4   Apr 18 2001 15:30:48   WINNIE
 * set default value for bank
 * 
 *    Rev 1.18.1.3   Apr 17 2001 13:24:28   WINNIE
 * set default value and readonly fields for custom bank
 * 
 *    Rev 1.18.1.2   16 Apr 2001 14:57:40   BUZILAMI
 * initalization of custom bank
 * 
 *    Rev 1.18.1.1   12 Apr 2001 15:27:48   BUZILAMI
 * Trading Bank Changes
 * 
 *    Rev 1.18.1.0   Apr 11 2001 09:50:46   ZHANGCEL
 * Added a new function: getPendingTradeBank()
 * 
 *    Rev 1.18   Apr 01 2001 16:19:48   WINNIE
 * fix crash for EFT purchase/redemption; use new class BankInstr; change input parameter for view 55 request
 * 
 *    Rev 1.17   Jan 18 2001 16:10:26   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.16   Jan 15 2001 17:04:26   WINNIE
 * bug fix : assign settlement currency
 * 
 *    Rev 1.15   Jan 12 2001 13:11:42   WINNIE
 * add logic to allow EFT redemption; assign bank account owner name if default value is blank
 * 
 *    Rev 1.14   Dec 17 2000 20:24:44   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.13   Dec 05 2000 16:15:46   OLTEANCR
 * fix
 * 
 *    Rev 1.12   Dec 05 2000 14:15:28   OLTEANCR
 * bug fix
 * 
 *    Rev 1.11   Dec 05 2000 11:41:18   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.10   Oct 02 2000 17:32:52   HUANGSHA
 * changed the Refresh function
 * 
 *    Rev 1.9   May 25 2000 14:05:40   BUZILA
 * refresh issues
 * 
 *    Rev 1.8   May 11 2000 16:13:14   BUZILA
 * passing  DBR::Currency to vw 55
 * 
 *    Rev 1.7   May 02 2000 10:30:54   BUZILA
 * M3
 * 
 *    Rev 1.6   Apr 28 2000 18:20:04   BUZILA
 * M3
 * 
 *    Rev 1.5   Apr 06 2000 16:41:20   BUZILA
 * trading changes
 * 
 *    Rev 1.4   Apr 04 2000 16:17:08   BUZILA
 * fixes
 * 
 *    Rev 1.3   Apr 03 2000 08:56:24   BUZILA
 * Trade changes
 * 
 *    Rev 1.2   Mar 30 2000 09:59:10   BUZILA
 * Trade Banking changes
 * 
 *    Rev 1.1   Mar 20 2000 09:29:24   BUZILA
 * temp
 * 
 *    Rev 1.0   Mar 08 2000 16:48:04   BUZILA
 * Initial revision.
 * 
*/

