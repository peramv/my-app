//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : SettlementTradeList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"

#include "SettlementTradeList.hpp"
#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0200_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

#include "SettlementTrade.hpp"



namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_LIST;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;


}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME        = I_( "SettlementTradeList" );
   const I_CHAR * const ALL_TRADE        = I_( "AL" );
   const I_CHAR * const ACCOUNT          = I_( "AC" );
   const I_CHAR * const WIRE_ORDER       = I_( "WO" );
   const I_CHAR * const ACCOUNT_WIRE     = I_( "AW" );
   const I_CHAR * const TRADE_DATE       = I_( "TD" );
   const I_CHAR * const SETTLE_DATE      = I_( "SD" );
   const I_CHAR * const SETTLE_CURRENCY  = I_( "CU" );
   const I_CHAR * const BROKER           = I_( "BR" );
   const I_CHAR * const FUND             = I_( "FN" );
   const I_CHAR * const SINGLESEARCH     = I_( "TX" );
   const I_CHAR * const TRANS_NUMBER     = I_( "TN" );
   const I_CHAR * const EXTERNAL_ID_TYPE = I_( "ET" );
   const I_CHAR * const REDEMPTION       = I_( "PW" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const EPA_BROKER       = I_( "EP" );
   const I_CHAR * const REGISTRATION_AGENT = I_( "RA");

}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_NO_ACTIVE_BATCH;   // remove CLASS_IMPORT to avoid getting the databroker condition with the same error name
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Settled;
   extern CLASS_IMPORT const BFTextFieldId SettlementListHeadSet;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,           State Flags,         Group Flags 
   { ifds::SettleAll,      BFCBO::NONE,              0 },
   { ifds::SettlementListHeadSet,	BFCBO::NONE,			  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );



const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "" ),       BFCBO::NONE,         0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );
//******************************************************************************

SettlementTradeList::SettlementTradeList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),_requestData(ifds::DSTC0200_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   _bInAll = false;
}

//******************************************************************************

SettlementTradeList::~SettlementTradeList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
void SettlementTradeList::prepareParameter(const BFDataGroupId& idDataGroup)
{
   DString  dstrSearchType, dstrExcludeStopSettle;
   DString  dstrPara;

   getParent()->getField(ifds::SearchType,dstrSearchType,idDataGroup,false );
   dstrSearchType.strip();

   getParent()->getField(ifds::ExcludeStopSettle, dstrExcludeStopSettle, idDataGroup, false);

   _requestData.setElementValue( ifds::SearchType,     dstrSearchType );
   _requestData.setElementValue( ifds::ExcludeStopSettle, dstrExcludeStopSettle );

   BFFieldId lFields[10]={ ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId};

   if( dstrSearchType  == ALL_TRADE )
   {

   }
   else if( dstrSearchType  == ACCOUNT )
   {
      lFields[0] = ifds::AccountNum;
      lFields[1] = ifds::SettleCurrency;
   }
   else if( dstrSearchType  ==  ACCOUNT_WIRE)
   {
      lFields[0] = ifds::AccountNum;
      lFields[1] = ifds::WireOrdNum;
   }
   else if( dstrSearchType  == FUND )
   {
      lFields[0] = ifds::FundCode;
   }
   else if( dstrSearchType  == WIRE_ORDER )
   {
      lFields[0] = ifds::WireOrdNum;      
   }
	else if( dstrSearchType  == TRANS_NUMBER )
   {
      lFields[0] = ifds::TransNum;      
   }
   else if( dstrSearchType  == TRADE_DATE ||   dstrSearchType  == SETTLE_DATE )
   {
      lFields[0] = ifds::StartDate;
      lFields[1] = ifds::EndDate;
      lFields[2] = ifds::SettleCurrency;
      lFields[3] = ifds::TransType;
      lFields[4] = ifds::SettleDate;
      lFields[5] = ifds::TradeDate;

   }

   else if( dstrSearchType  == SETTLE_CURRENCY )
   {
      lFields[0] = ifds::SettleCurrency;  
   }
   else if( dstrSearchType  == BROKER )
   {
      lFields[0] = ifds::BrokerCode;
      lFields[1] = ifds::VolSettleType;
      lFields[2] = ifds::TransType;
      lFields[3] = ifds::TradeDate;
      lFields[4] = ifds::SettleDate;
      lFields[5] = ifds::SettleCurrency;
      lFields[6] = ifds::FundCode;
   }
   else if( dstrSearchType == SINGLESEARCH)
   {
      lFields[0] = ifds::AccountNum;
      lFields[1] = ifds::TransNum;
      lFields[2] = ifds::FundCode;
      lFields[3] = ifds::ClassCode;
      lFields[4] = ifds::TransType;

      lFields[5] = ifds::TradeDate;		//Optional
      lFields[6] = ifds::SettleDate;	//Optional
      lFields[7] = ifds::BrokerCode;	//Optional
   }
   else if ( dstrSearchType == EXTERNAL_ID_TYPE )
   {
      lFields[0] = ifds::ExternalIdType;
      lFields[1] = ifds::ExternalId;
   }
   else if ( dstrSearchType == EPA_BROKER )
   {
      lFields[0] = ifds::SettleDate;
      lFields[1] = ifds::BrokerCode;
   }
   else if(dstrSearchType == REGISTRATION_AGENT)
   {
      lFields[0] = ifds::RegAgentCode;
      lFields[1] = ifds::TransType;
      lFields[2] = ifds::SettleDate;

   }
   int i = 0;
   while( lFields[i] != ifds::NullFieldId )
   {
      getParent()->getField(lFields[i],dstrPara,idDataGroup,false );
      dstrPara.strip();

      if( dstrSearchType == EPA_BROKER && lFields[i] == ifds::BrokerCode )
      {
         dstrPara.upperCase();

         if ( dstrPara == I_("ALL"))
            dstrPara = NULL_STRING;
      }

      _requestData.setElementValue( lFields[i],     dstrPara,false,false );

      i++;
   }
}

//******************************************************************************
SEVERITY SettlementTradeList::init( const BFDataGroupId& idDataGroup,
                                    const DString& dstrSearchType,
                                    const bool bIndvdl,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   _bIndividual = bIndvdl;
   _dstrSearchType = dstrSearchType;
   DString dstrSettleAll;
   getWorkSession().getOption2( ifds::SettleAll, dstrSettleAll, BF::HOST, false);
   setFieldNoValidate(ifds::SettleAll,dstrSettleAll,BF::HOST,false );   
   prepareParameter(idDataGroup);
   _requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData(DSTC_REQUEST::SETTLEMENT_LIST, _requestData, ifds::DSTC0200_VW, DSTCRequestor(getSecurity(), false,true) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY SettlementTradeList::setSetAllFields( const BFDataGroupId& idDataGroup,const DString& dstrValue,bool bFormat )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSetAllFields" ) );
   DString dstrSettleAll;
   _bInAll = true;
   getField(ifds::SettleAll,dstrSettleAll,idDataGroup,false );
   dstrSettleAll.strip();
   if( dstrSettleAll != dstrValue )
   {
      setFieldNoValidate(ifds::SettleAll,dstrValue,BF::HOST,false ); 
      BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         SettlementTrade* pTrade = dynamic_cast<SettlementTrade*>(iter.getObject() );
         if( pTrade )
         {
            pTrade->setSetAllFlag();
			pTrade->setField(ifds::Settled,dstrValue,idDataGroup, false );
            pTrade->setSetAllFlag(false);

			DString dstrCashDate;
			pTrade->getField ( ifds::CashDate, dstrCashDate , BF::HOST, false) ;
			pTrade->setField ( ifds::CashDate, dstrCashDate, idDataGroup, true, true, true);
			if (dstrSettleAll == YES)
				pTrade->setFieldReadOnly (ifds::CashDate, idDataGroup, false);
			else
				pTrade->setFieldReadOnly (ifds::CashDate, idDataGroup, true);
         }
         ++iter;
      }
   }

   Settlement* pSettlement = dynamic_cast<Settlement* >(getParent());
   pSettlement->UserChangeSettle( this,ifds::SettleAll,idDataGroup );
   _bInAll = false;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SettlementTradeList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::SETTLEMENT_LIST, _requestData, ifds::DSTC0200_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY SettlementTradeList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY SettlementTradeList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new SettlementTrade( *this );
   ((SettlementTrade*) pObjOut)->init( data,_dstrSearchType,_bIndividual );

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************************
void  SettlementTradeList::UserChangeSettle(const MFCanBFCbo* pCbo ,const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{

}

//****************************************************************************************
SEVERITY SettlementTradeList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   DString dstrBatchName;

   getParent ()->getField (ifds::rxBatchName, dstrBatchName, idDataGroup);
   
   if( dstrBatchName == NULL_STRING)
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_ACTIVE_BATCH ); 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
bool SettlementTradeList::settleMoreThenOne( const BFDataGroupId& idDataGroup,DString& dstrAccount )
{ 
   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrSettle;
   int iNum = 0;
   while( !iter.end() )
   {
      iter.getObject()->getField(ifds::Settled,dstrSettle,idDataGroup,false);
      dstrSettle.strip();
      if( I_("Y") == dstrSettle )
      {
         iNum++;
         iter.getObject()->getField(ifds::AccountNum,dstrAccount,idDataGroup);
      }
      if( iNum>1 ) return(true);
      ++iter;
   }
   return(false);

}
//******************************************************************************************
void SettlementTradeList::clearUnsettleUpdatedFalg(const BFDataGroupId& idDataGroup)
{

   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrSettle;  
   while( !iter.end() )
   {
      iter.getObject()->getField(ifds::Settled,dstrSettle,idDataGroup,false);
      dstrSettle.strip();
      if( I_("N") == dstrSettle )
      {

         iter.getObject()->clearUpdatedFlags(idDataGroup,true);
      }
      ++iter;
   }
}

//*****************************************************************************************
bool SettlementTradeList ::doYouHaveLegalToSettle(const BFDataGroupId& idDataGroup)
{
   bool bLegal = false;

   if( doMoreRecordsExist() )
   {
      return true;
   }

   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrSettle,dstrTransType;  
   while( !iter.end() )
   {
      SettlementTrade* pTrade = dynamic_cast<SettlementTrade* >(iter.getObject() );
      if( pTrade )
      {

         pTrade->getField(ifds::Settled,dstrSettle,idDataGroup,false);
         dstrSettle.strip().upperCase();
         pTrade->getField(ifds::TransType,dstrTransType, idDataGroup,false);
         if(YES == dstrSettle || _bInAll )
         {
            if ( dstrTransType != REDEMPTION ||  (dstrTransType == REDEMPTION &&
                 pTrade->isSettleRedemptionAllowed(idDataGroup ) ) )
            {
               bLegal = true;
               break;
            }
         }
      }
      ++iter;
   }

   return bLegal;
}

//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTradeList.cpp-arc  $
// 
//    Rev 1.23   Apr 27 2012 09:54:12   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.22   Dec 09 2010 15:11:30   jankovii
// IN 2339013 - P0175778: Uptreaming QA testing
// 
//    Rev 1.21   Dec 01 2010 06:08:26   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.20   May 12 2009 13:53:28   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.19   Apr 25 2005 17:49:12   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.18   Nov 14 2004 14:54:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Oct 12 2004 14:23:56   YINGBAOL
// PTS10034502: Issue chritical error when user check "SettleAll" and all records selected is not allowed to settle.
// 
//    Rev 1.17   Oct 12 2004 14:13:56   YINGBAOL
// PTS10034502: issue critical error when user select settleall and all records can not be settled.
// 
//    Rev 1.16   Sep 16 2004 14:19:40   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.15   Aug 13 2004 13:58:18   YINGBAOL
// PET1027:StopRedemptionSettlement
// 
//    Rev 1.14   Apr 07 2003 15:11:42   FENGYONG
// Add SINGLESEARCH type
// 
//    Rev 1.13   Mar 21 2003 18:24:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Dec 11 2002 16:53:38   YINGBAOL
// fix individual Settlement
// 
//    Rev 1.11   Oct 09 2002 23:55:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.10   Sep 30 2002 11:01:18   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.9   Aug 29 2002 12:56:38   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   Aug 21 2002 11:28:44   WINNIE
// remove CLASS_IMPORT to stop system from founding the same condition name in the databroker project. It caused error number not found when the condition occur
// 
//    Rev 1.7   Jul 10 2002 16:25:06   YINGBAOL
// add clearUnsettleUpdatedFalg  method
// 
//    Rev 1.6   Jul 05 2002 13:45:12   YINGBAOL
// add settlemorethanOne function
// 
//    Rev 1.5   Jun 20 2002 14:05:54   YINGBAOL
// add doValidateAll
// 
//    Rev 1.4   Jun 14 2002 14:40:50   YINGBAOL
// change search type FD to FN etc.
// 
//    Rev 1.3   Jun 11 2002 11:42:40   YINGBAOL
// more business rules added
// 
//    Rev 1.2   Jun 06 2002 16:08:26   YINGBAOL
// save work
//



//