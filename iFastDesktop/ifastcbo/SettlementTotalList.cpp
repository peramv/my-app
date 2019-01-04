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
// ^FILE   : SettlementTotalList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"

#include "SettlementTotalList.hpp"
#include "SettlementTotal.hpp"

#include <ifastdataimpl\dse_dstc0206_req.hpp>
#include <ifastdataimpl\dse_dstc0206_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_TOTAL;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME        = I_( "SettlementTotalList" );
   const I_CHAR * const ALL_TRADE        = I_( "AL" );
   const I_CHAR * const ACCOUNT          = I_( "AC" );
   const I_CHAR * const WIRE_ORDER       = I_( "WO" );
   const I_CHAR * const TRADE_DATE       = I_( "TD" );
   const I_CHAR * const SETTLE_DATE      = I_( "SD" );
   const I_CHAR * const SETTLE_CURRENCY  = I_( "CU" );
   const I_CHAR * const BROKER           = I_( "BR" );
   const I_CHAR * const FUND             = I_( "FN" );
   const I_CHAR * const EXTERNAL_ID_TYPE = I_( "ET" );
   const I_CHAR * const TRANS_NUMBER     = I_( "TN" );
   const I_CHAR * const EPA_BROKER       = I_( "EP" );
   const I_CHAR * const ACCOUNT_WIRE     = I_( "AW" );
   const I_CHAR * const REGISTRATION_AGENT = I_( "RA" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_SHAREHOLDER_NUMBER_EXISTS;
   extern const long ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO;
   extern const long ERR_SHAREHOLDER_NUMBER_EMPTY;
   extern const long ERR_RESIDENCE_PROVINCE_EMPTY;
   extern const long ERR_TAX_JURIS_EMPTY;
   extern const long ERR_INVALID_SHAREHOLDER_NUM;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SettleAll;
   extern CLASS_IMPORT const BFDecimalFieldId CountTotalSettel;
}

//******************************************************************************

SettlementTotalList::SettlementTotalList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),Noticement()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

}

//******************************************************************************

SettlementTotalList::~SettlementTotalList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY SettlementTotalList::init( const BFDataGroupId& idDataGroup,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0206_REQ);
   prepareParameter(requestData,idDataGroup);

   requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   ReceiveData(DSTC_REQUEST::SETTLEMENT_TOTAL, requestData, ifds::DSTC0206_VW, 
               DSTCRequestor(getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SettlementTotalList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY SettlementTotalList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new SettlementTotal( *this );
   ((SettlementTotal*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
//key by currency   
void SettlementTotalList::getStrKey( DString &strKey, const BFData * data )
{
   if( !data )
   {
      BFCBO::getStrKey( strKey, data );
   }
   else
   {
      data->getElementValue( ifds::Currency, strKey );
   } 

}
//******************************************************************************
void SettlementTotalList::prepareParameter(BFData& requestData,const BFDataGroupId& idDataGroup)
{
   DString  dstrSearchType;
   DString  dstrPara;
   getParent()->getField(ifds::SearchType,dstrSearchType,idDataGroup,false );
   dstrSearchType.strip();
   requestData.setElementValue( ifds::SearchType,     dstrSearchType );
   BFFieldId lFields[10]={ ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId}; 

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
	else if ( dstrSearchType == EXTERNAL_ID_TYPE )
	{
		lFields[0] = ifds::ExternalIdType;
	   lFields[1] = ifds::ExternalId;
	}
   else if ( dstrSearchType == EPA_BROKER )
   {
      lFields[0] = ifds::SettleDate;
      lFields[1] = ifds::BrokerCode;
      lFields[2] = ifds::AccountNum;
      lFields[3] = ifds::SettleCurrency;
	  lFields[4] = ifds::ExcludeStopSettle;
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
      getParent()->getField(lFields[i], dstrPara, idDataGroup, false );
      dstrPara.strip();

      if( dstrSearchType == EPA_BROKER && lFields[i] == ifds::BrokerCode )
      {
         dstrPara.upperCase();

         if ( dstrPara == I_("ALL"))
            dstrPara = NULL_STRING;
      }

      requestData.setElementValue( lFields[i], dstrPara, false );
      i++;
   }
}

//*****************************************************************************
void  SettlementTotalList::UserChangeSettle(const MFCanBFCbo* pCbo ,const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{ 
   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   if( idField == ifds::SettleAll )
   {
      DString dstrSettleAll;
      pCbo->getField(ifds::SettleAll,dstrSettleAll,idDataGroup,false);
      dstrSettleAll.strip();    
      while( !iter.end() )
      {
         SettlementTotal* pTotal = dynamic_cast<SettlementTotal* >( iter.getObject() );
         if( pTotal ) {
            pTotal->setAllTotal(pCbo, dstrSettleAll == I_("Y"), idDataGroup );
			//pTotal->CalculateTotal(pCbo, idField,  idDataGroup );
		 }
         ++iter;
      } 
   }
   else
   {
      DString dstrCurrency;
      pCbo->getField(ifds::SettleCurrency,dstrCurrency,idDataGroup,false);
      dstrCurrency.strip();
      if( iter.positionByKey( dstrCurrency ) )
      {
         SettlementTotal* pTotal = dynamic_cast<SettlementTotal* >( iter.getObject() );
         if( pTotal )
            pTotal->CalculateTotal(pCbo, idField,  idDataGroup );

      }

   }
}

//***********************************************************************************
DString  SettlementTotalList::getCountNum(bool bSettle,const BFDataGroupId& idDataGroup )
{
   DString dstrCount;
   int iCount = 0;
   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      BFFieldId idField = ifds::CountTotal; 
      if( bSettle )
      {
         idField = ifds::CountTotalSettel;
      }
      DString dstrCountTotal;
      iter.getObject()->getField(idField,dstrCountTotal,idDataGroup);
      iCount += dstrCountTotal.asInteger();
      ++iter;
   }
   dstrCount = DString::asString( iCount );
   return(dstrCount);
}

//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementTotalList.cpp-arc  $
// 
//    Rev 1.16   Apr 27 2012 09:53:56   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.15   Dec 09 2010 15:10:32   jankovii
// IN 2339013 - P0175778: Uptreaming QA testing
// 
//    Rev 1.14   Dec 01 2010 06:40:44   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.13   Apr 25 2005 17:47:20   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.12   Nov 14 2004 14:54:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Sep 16 2004 14:20:18   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.10   Mar 21 2003 18:24:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:54:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Sep 30 2002 11:01:16   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.7   Aug 29 2002 12:56:38   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Aug 06 2002 15:04:08   HERNANDO
// PTS 10009268 - Clean up.  Removed ERR_DATE_FUNCTIONS from Namespace.
// 
//    Rev 1.5   Jun 14 2002 14:39:56   YINGBAOL
// change search type FD to FN etc.
// 
//    Rev 1.4   Jun 12 2002 17:03:12   YINGBAOL
// add getCountNum and Total logic
// 
//    Rev 1.3   Jun 11 2002 11:42:40   YINGBAOL
// more business rules added
// 
//    Rev 1.2   Jun 06 2002 16:08:24   YINGBAOL
// save work
//



//