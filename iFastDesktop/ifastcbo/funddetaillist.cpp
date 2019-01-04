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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundDetailList.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : Mar 5, 1999
//
// ^CLASS    : FundDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundlist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_DETAIL;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME             = I_( "FundDetailList" );
   const I_CHAR * const FUND_CODE_FIELD       = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE_FIELD      = I_( "ClassCode" );
   //sys [
   const I_CHAR * const FUND_DETAIL_LIST_NAME = I_( "FundDetailList" );
   //sys ]
   const I_CHAR * const NO                    = I_( "N" );
   const I_CHAR * const YES                   = I_( "Y" );
   const I_CHAR * const MINIMUM_AMT           = I_( "MINIMUM_AMT") ;  
   const I_CHAR * const FUND                  = I_( "FUND") ;
   const I_CHAR * const CLASS                 = I_( "CLASS") ;
   const I_CHAR * const TRADE_TYPE            = I_( "TRADE_TYPE") ;
   const I_CHAR   EQUAL_SIGN                  = I_( '=') ;
   const I_CHAR   COMMA_SIGN                  = I_( ',') ;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId UnitValue;
   extern CLASS_IMPORT const BFTextFieldId TransType;
//   extern CLASS_IMPORT const long ExchInFeeExist;
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT;
   extern const long ERR_MINIMUM_INIT_AMT;
   extern const long ERR_MINIMUM_SUBSEQUENT_AMT;
   extern CLASS_IMPORT const long ERR_INVALID_FUND_CODE;
}

namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}

//******************************************************************************
FundDetailList::FundDetailList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0056_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
FundDetailList::~FundDetailList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY FundDetailList::init (const DString& dstrTrack,
                               const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

//   BFData queryData(ifds::DSTC0056_REQ);
   BFData *receivedData = new BFData (ifds::DSTC0056_VW);
   DString mgmtCoIdOut;
   m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   m_requestData.setElementValue (ifds::Track, dstrTrack);
   m_requestData.setElementValue (ifds::Activity, dstrPageName);

//   AsyncReceiveData( DSTC_REQUEST::FUND_DETAIL, queryData, *receivedData, DSTCRequestor( getSecurity(), true) );
   AsyncReceiveData ( DSTC_REQUEST::FUND_DETAIL, 
                      m_requestData, 
                      *receivedData, 
                      DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY FundDetailList::init(   const DString& dstrSearchType,
                                 const DString& dstrFundCode,
                                 const DString& dstrClassCode,
                                 const DString& dstrFundName,
                                 const DString& dstrFundNumber,
                                 const DString& dstrWKN,
                                 const DString& dstrISIN,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::SearchFundType, dstrSearchType );
   m_requestData.setElementValue( ifds::FundCode, dstrFundCode );
   m_requestData.setElementValue( ifds::ClassCode, dstrClassCode );
   m_requestData.setElementValue( ifds::FundName, dstrFundName );
   m_requestData.setElementValue( ifds::FundNumber, dstrFundNumber );
   m_requestData.setElementValue( ifds::FundWKN, dstrWKN );
   m_requestData.setElementValue( ifds::FundISIN, dstrISIN );

   DSTCRequestor requestor (getSecurity(), false);

   requestor.filterHostCondition( CND::ERR_DATA_NOT_FOUND );
   requestor.filterHostCondition( CND::ERR_INVALID_FUND_CODE );

   ReceiveData (DSTC_REQUEST::FUND_DETAIL, m_requestData, ifds::DSTC0056_VW, requestor);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundDetailList::getStrKey( DString& strKey, const DString& dstFundCode, const DString& dstClassCode )
{
   strKey = dstFundCode;
   strKey.strip();
   strKey += I_("  ");
   strKey += dstClassCode;
   strKey.strip();
   strKey.upperCase();
}

//******************************************************************************
void FundDetailList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstFundCode  = data->getElementValue( FUND_CODE_FIELD );
      DString dstClassCode = data->getElementValue( CLASS_CODE_FIELD );
      getStrKey( strKey, dstFundCode, dstClassCode );
      strKey.strip().upperCase() ;
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
void FundDetailList::getField( const DString& strFundCode, const DString& strClassCode,
                               const BFFieldId& idField, DString& strValue, 
                               const BFDataGroupId& idDataGroup, bool formattedReturn
                             ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getField" ));

   DString strFund,strKey;
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   getStrKey(strKey, strFundCode, strClassCode );

   if( iter.positionByKey(strKey) )
   {
      iter.getObject()->getField( idField, strValue, idDataGroup, formattedReturn ); 
   }

}

//******************************************************************************
bool FundDetailList::IsFundClassExist( const DString& dstrFundCode, 
                                       const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) 
{
   DString dstrKey;
   getStrKey( dstrKey, dstrFundCode, dstrClassCode );
   BFObjIter iterList( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   return(iterList.positionByKey( dstrKey ));
}


//******************************************************************************
bool FundDetailList::IsExchInFeeExist( const DString& dstrFundCode, 
                                       const DString& dstrClassCode, const BFDataGroupId& idDataGroup ) 
{
   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   data.setElementValue( ifds::ClassCode, dstrClassCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );
   BFObjIter iterList( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   if( iterList.positionByKey( dstrKey ) )
   {
      DString dstrExchInFeeExist( I_( "N" ) );
      iterList.getObject()->getField( ifds::ExchInFeeExist, dstrExchInFeeExist, idDataGroup );
      if( dstrExchInFeeExist.stripAll().upperCase() == I_( "Y" ) )
         return(true);
   }

   return(false);
}

//******************************************************************************
bool FundDetailList::isFOFFund( const DString& dstrFundCode, 
                                const DString& dstrClassCode, 
                                const BFDataGroupId& idDataGroup ) 
{
   bool bIsFOFFund = false;

   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   data.setElementValue( ifds::ClassCode, dstrClassCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );
   BFObjIter iterList( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   if( iterList.positionByKey( dstrKey ) )
   {
      DString dstrIsFOFFund( I_( "N" ) );
      iterList.getObject()->getField( ifds::FOFFund, dstrIsFOFFund, idDataGroup );
      if( dstrIsFOFFund.stripAll().upperCase() == I_( "Y" ) )
         bIsFOFFund = true;
   }

   return bIsFOFFund;
}

//*****************************************************************************
bool FundDetailList::IsFundValidAtDate(const DString& dstrFundCode,
                                       const DString& dstrClassCode,
                                       const DString& dstrEffectiveDate, 
                                       const BFDataGroupId& idDataGroup ) 
{

   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   data.setElementValue( ifds::ClassCode, dstrClassCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );

   BFObjIter iterList( *this, idDataGroup, false, 
                       BFObjIter::ITERTYPE::NON_DELETED );
   if( iterList.positionByKey( dstrKey ) )
   {

      DString dstrFundClassEffectiveDate, dstrFundClassStopDate;

      iterList.getObject()->getField( ifds::EffectiveDate, 
                                      dstrFundClassEffectiveDate, idDataGroup );
      dstrFundClassEffectiveDate.strip();

      iterList.getObject()->getField( ifds::StopDate, 
                                      dstrFundClassStopDate, idDataGroup );
      dstrFundClassStopDate.strip();
      if( DSTCommonFunctions::IsDateBetween(
                                           dstrFundClassEffectiveDate, dstrFundClassStopDate,dstrEffectiveDate ) )
         return(true);

   }
   return(false);
}

//******************************************************************************
bool FundDetailList::getFundDetail( const DString& dstrFundCode, const DString& dstrClassCode,
                                    const BFDataGroupId& idDataGroup, FundDetail *&pFundDetail ) 
{
   if( dstrFundCode == NULL_STRING || dstrClassCode == NULL_STRING )
      return(false);

   pFundDetail = NULL;
   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   data.setElementValue( ifds::ClassCode, dstrClassCode, true, false );

   DString dstrKey;
   getStrKey( dstrKey, &data );
   BFObjIter iterList( *this, BF::HOST /*idDataGroup*/, false, BFObjIter::ITERTYPE::NON_DELETED );

   if( iterList.positionByKey( dstrKey ) )
   // A match was found, get the CBO  
   {
      pFundDetail = static_cast<FundDetail *>( iterList.getObject());  
      return(true);
   }
   else
      return(false);
}

//******************************************************************************
SEVERITY FundDetailList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   FundDetail * pFundDetail = new FundDetail( *this );
   pFundDetail->init( data );
   pObjOut = pFundDetail;

   DString dstrFundNumber, dstrWKN, dstrISIN, dstrFundIDVal, dstrFundListAppl, dstrLFC ;
   data.getElementValue( ifds::Baycom, dstrFundNumber );
   data.getElementValue( ifds::FundWKN, dstrWKN );
   data.getElementValue( ifds::FundISIN, dstrISIN );
   data.getElementValue( ifds::FundLFC, dstrLFC);
   dstrFundNumber.stripAll(); // Remove spaces throughout the string.
   dstrWKN.stripAll(); // Remove spaces throughout the string.
   dstrISIN.stripAll(); // Remove spaces throughout the string.
   dstrLFC.stripAll(); // Remove spaces throughout the string.
   if( !dstrFundNumber.empty() )
   {
   	m_FundNumberMap.insert( FUND_MAP_VALUE_TYPE( dstrFundNumber, pFundDetail ) );
   }
   if( !dstrWKN.empty() )
   {
   	m_WKNMap.insert( FUND_MAP_VALUE_TYPE( dstrWKN, pFundDetail ) );
   }
   if( !dstrISIN.empty() )
   {
   	m_ISINMap.insert( FUND_MAP_VALUE_TYPE( dstrISIN, pFundDetail ) );
   }
   if( !dstrLFC.empty() )
   {
   	m_LFCMap.insert( FUND_MAP_VALUE_TYPE( dstrLFC, pFundDetail ) );
   }
   data.getElementValue( ifds::Fund_ID_Values, dstrFundIDVal  );
   if( !dstrFundIDVal.stripAll().empty() )
	   insertFundIdValues( dstrFundIDVal, pFundDetail, BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool FundDetailList::isSameTradeDateLag(const DString& FrFundCode, const DString& FrClassCode, 
                                        const DString& ToFundCode, const DString& ToClassCode)
{
   FundDetail *pFromFundDetail, *pToFundDetail;
   if( getFundDetail( FrFundCode, FrClassCode, BF::HOST, pFromFundDetail) && 
       getFundDetail( ToFundCode, ToClassCode, BF::HOST, pToFundDetail) )
   {
      DString strFromDays, strToDays;
      pFromFundDetail->getField(ifds::AdditionalDays, strFromDays, BF::HOST, false);
      pToFundDetail->getField(ifds::AdditionalDays, strToDays, BF::HOST, false);
      return(strFromDays.strip() == strToDays.strip());
   }
   return(false);
}
//******************************************************************************

bool FundDetailList::isFundFCRebalElig(const DString& strFundCode)
{
   //rule : a fund is considered FC Rebalancing eligible if there is at least one Fund/class 
   //which has FCTransferElig == 'Y'
   BFObjIter iter( *this, BF::HOST );
   DString strElig, dstrFundCode;
   while (!iter.end())
   {      
      iter.getObject()->getField(ifds::FundCode, dstrFundCode, BF::HOST, false);
      if (dstrFundCode.strip().upperCase() == strFundCode)
      {
         iter.getObject()->getField(ifds::FCTransferElig, strElig, BF::HOST, false);
         if (strElig.strip()==YES)
            return true;
      }
      ++iter;
   }
   return false;
}
//******************************************************************************

bool FundDetailList::isStopSysGenTrfrIn(const DString& strFundCode)
{
   //rule : a fund is considered having AutoXferInStop = 'Y' if all the Fund/class 
   //records have StopSysGenTrnfrIn == 'Y'
   BFObjIter iter( *this, BF::HOST );
   DString strStop, dstrFundCode;
   bool bAtLeastOneMatch(false);
   while (!iter.end())
   {      
      iter.getObject()->getField(ifds::FundCode, dstrFundCode, BF::HOST, false);
      if (dstrFundCode.strip().upperCase() == strFundCode)
      {
         bAtLeastOneMatch = true;
         iter.getObject()->getField(ifds::StopSysGenTrnfrIn, strStop, BF::HOST, false);
         if (strStop.strip()==NO)
            return false;
      }
      ++iter;
   }
   return (bAtLeastOneMatch);
}

//******************************************************************************

SEVERITY FundDetailList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::FUND_DETAIL, m_requestData, ifds::DSTC0056_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

FundDetail* FundDetailList::getFundDetailByWKN( const DString& dstrWKN )
{
   FundDetail* pFundDetail = NULL;
   if( !m_WKNMap.empty() )
   {
      DString WKN( dstrWKN );
      WKN.strip().upperCase();
      FUND_MAP_ITER iter = m_WKNMap.find( WKN );
      if( iter != m_WKNMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

//******************************************************************************

FundDetail* FundDetailList::getFundDetailByLFC( const DString& dstrLFC )
{
   FundDetail* pFundDetail = NULL;
   if( !m_LFCMap.empty() )
   {
      DString LFC( dstrLFC );
      LFC.strip().upperCase();
      FUND_MAP_ITER iter = m_LFCMap.find( LFC );
      if( iter != m_LFCMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

//******************************************************************************

FundDetail* FundDetailList::getFundDetailByISIN( const DString& dstrISIN )
{
   FundDetail* pFundDetail = NULL;
   if( !m_ISINMap.empty() )
   {
      DString ISIN( dstrISIN );
      ISIN.strip().upperCase();
      FUND_MAP_ITER iter = m_ISINMap.find( ISIN );
      if( iter != m_ISINMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

//******************************************************************************

FundDetail* FundDetailList::getFundDetailByFundNumber( const DString& dstrFundNumber )
{
   FundDetail* pFundDetail = NULL;
   if( !m_FundNumberMap.empty() )
   {
      DString FundNumber( dstrFundNumber );
      FundNumber.strip().upperCase();
      FUND_MAP_ITER iter = m_FundNumberMap.find( FundNumber );
      if( iter != m_FundNumberMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

//******************************************************************************
bool FundDetailList::isInScope(const DString& dstrFundCode, const DString &dstrClassCode, const DString &dstrTradeDate)
{
   BFObjIter iter( *this, BF::HOST );
   DString strFundCode, strClassCode, strFirstScopeDate;
   while (!iter.end())
   {      
      iter.getObject()->getField(ifds::FundCode, strFundCode, BF::HOST, false);
		iter.getObject()->getField(ifds::ClassCode, strClassCode, BF::HOST, false);

      if (strFundCode.strip().upperCase() == dstrFundCode  && strClassCode.strip().upperCase() == dstrClassCode )
      {
			iter.getObject()->getField(ifds::FirstScopeDate, strFirstScopeDate, BF::HOST, false);         
			return ( strFirstScopeDate != NULL_STRING && DSTCommonFunctions::CompareDates(strFirstScopeDate, dstrTradeDate) != DSTCommonFunctions::SECOND_EARLIER ) ;								
      }
      ++iter;
   }
	return false;
}

//******************************************************************************
bool FundDetailList::isLookThru(const DString& dstrFundCode, const DString &dstrClassCode, const DString &dstrTradeDate)
{
   BFObjIter iter( *this, BF::HOST );
   DString strFundCode, strClassCode, strFirstLookThruDate;

   while (!iter.end())
   {      
      iter.getObject()->getField(ifds::FundCode, strFundCode, BF::HOST, false);
		iter.getObject()->getField(ifds::ClassCode, strClassCode, BF::HOST, false);

      if (strFundCode.strip().upperCase() == dstrFundCode  && strClassCode.strip().upperCase() == dstrClassCode )
      {
			iter.getObject()->getField(ifds::FirstLookThruDate, strFirstLookThruDate, BF::HOST, false); 
			return ( strFirstLookThruDate != NULL_STRING && DSTCommonFunctions::CompareDates(strFirstLookThruDate, dstrTradeDate) != DSTCommonFunctions::SECOND_EARLIER ) ;								
      }
      ++iter;
   }
	return false;
}

/******************************************************************************
 Input: String value to serach for
 OutPut:None
 Return:Fund class detail object with matching FundID
 Functionality:	Fund class details  of object with matching FUNDID
 ******************************************************************************/

FundDetail* FundDetailList::getFundDetailByCUSIP( const DString& dstrCUSIP )
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getFundDetailByCUSIP"));

   FundDetail* pFundDetail = NULL;
   if( !m_CUSIPMap.empty() )
   {
      DString CUSIP( dstrCUSIP );
      CUSIP.strip().upperCase();
      FUND_MAP_ITER iter = m_CUSIPMap.find( CUSIP  );
      if( iter != m_CUSIPMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

/******************************************************************************
 Input: String value to serach for
 OutPut:None
 Return:Fund class detail object with matching FundID
 Functionality:	Fund class details  of object with matching FUNDID
 ******************************************************************************/
FundDetail* FundDetailList::getFundDetailByTDCC( const DString& dstrTDCC )
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getFundDetailByTDCC"));

   FundDetail* pFundDetail = NULL;
   if( !m_TDCCMap.empty() )
   {
      DString TDCC( dstrTDCC );
      TDCC.strip().upperCase();
      FUND_MAP_ITER iter = m_TDCCMap.find( TDCC );
      if( iter != m_TDCCMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

/******************************************************************************
 Input: String value to serach for
 OutPut:None
 Return:Fund class detail object with matching FundID
 Functionality:	Fund class details  of object with matching FUNDID
 ******************************************************************************/
FundDetail* FundDetailList::getFundDetailByVAL( const DString& dstrVALOREN )
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("getFundDetailByVAL"));

   FundDetail* pFundDetail = NULL;
   if( !m_VALORENMap.empty() )
   {
      DString VALOREN( dstrVALOREN );
      VALOREN.strip().upperCase();
      FUND_MAP_ITER iter = m_VALORENMap.find( VALOREN );
      if( iter != m_VALORENMap.end() )
      {
         pFundDetail = (*iter).second;
      }
   }
   return( pFundDetail );
}

/******************************************************************************
 Input: FundIdvalues,FundDetailObjectPtr,const BFDataGroupId& idDataGroup
 OutPut:None
 Return:None
 Functionality:	Function that insert the FundID's and Fund Detail to the map 
 ******************************************************************************/
SEVERITY FundDetailList::insertFundIdValues(DString& dstrFundIDvalues, FundDetail *pFundDetail,
											const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("insertFundIdValues"));

	DString dstrTDCCValue,dstrCUSIPValue,dstrValorenValue;
	I_CHAR *temp = const_cast<I_CHAR*> (dstrFundIDvalues.c_str ());
	if(pFundDetail && DSTCommonFunctions::getMarket() != MARKET_IDS::CANADA )
	{
		do
		{
			DString dstrFundIDCode,dstrFundIDValue;
			temp = parseIdiString (temp, dstrFundIDCode, dstrFundIDValue, EQUAL_SIGN, COMMA_SIGN );
			if( dstrFundIDCode == FUND_ID_CODE::VALOREN )
			{
				m_VALORENMap.insert( FUND_MAP_VALUE_TYPE( dstrFundIDValue, pFundDetail ) );
				
			}
			else if( dstrFundIDCode == FUND_ID_CODE::TDCC )
			{
				m_TDCCMap.insert( FUND_MAP_VALUE_TYPE( dstrFundIDValue, pFundDetail ) );
			}
			else if(dstrFundIDCode  == FUND_ID_CODE::CUSIP )
			{
				m_CUSIPMap.insert( FUND_MAP_VALUE_TYPE( dstrFundIDValue, pFundDetail ) );
			} 
		}while (temp && temp != NULL_STRING && *temp);
	}
  return( GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/funddetaillist.cpp-arc  $
 * 
 *    Rev 1.38   24 Jul 2008 12:00:50   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.37   Jun 25 2007 11:36:32   porteanm
 * PET 2360 FN02 - Added isFOF()
 * 
 *    Rev 1.36   Nov 29 2005 15:23:32   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.35   Feb 24 2005 19:06:34   popescu
 * Incident# 243353, added boolean to flag if list has been fully loaded
 * 
 *    Rev 1.34   Feb 15 2005 20:36:20   hernando
 * 237768 - Added/recovered setVersionable( false ) to constructor.
 * 
 *    Rev 1.33   Dec 03 2004 17:24:52   hernando
 * PET1117 - Tuning Project - Stripped and uppercased values.
 * 
 *    Rev 1.32   Nov 29 2004 13:23:12   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.31   Nov 14 2004 14:41:56   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.30   Sep 09 2004 11:38:34   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.29   Aug 30 2004 14:53:08   YINGBAOL
 * PTS10032768: speed up list  for non updateable CBO.
 * 
 *    Rev 1.28   Mar 21 2003 18:11:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.27   Jan 14 2003 17:28:56   KOVACSRO
 * Added isFundFCRebalElig() and  isStopSysGenTrfrIn()
 * 
 *    Rev 1.26   Oct 09 2002 23:54:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.25   Aug 29 2002 12:55:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.24   22 May 2002 18:28:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.23   12 Dec 2001 16:09:54   KOVACSRO
 * Added isSameTradeDateLag()
 * 
 *    Rev 1.22   Oct 29 2001 16:14:48   ZHANGCEL
 * Fixed the bug in the getFundDetail()
 * 
 *    Rev 1.21   Jun 16 2001 15:34:04   ZHANGCEL
 * Added a new function isExchInFeeExist()
 * 
 *    Rev 1.20   03 May 2001 14:06:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.19   09 Feb 2001 14:56:16   SMITHDAV
 * Do Async Requests...
 * 
 *    Rev 1.18   Feb 06 2001 09:53:38   WINNIE
 * uncomment isFundClassExist
 * 
 *    Rev 1.17   Jan 31 2001 11:28:06   JANKAREN
 * Add getFundDetail and doCreateObject method and moved fundClassForPlanType, checkMinInitAmt, checkMinSubAmt methods to FundDetail CBO
 * 
 *    Rev 1.16   Jan 30 2001 10:07:44   VASILEAD
 * Added workSessionId for getUnitPrice()
 * 
 *    Rev 1.15   Jan 18 2001 16:04:52   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.14   Jan 15 2001 10:52:28   ZHANGCEL
 * Added the TransType checking in  getUnitPrice()
 * 
 *    Rev 1.13   Jan 12 2001 13:37:58   ZHANGCEL
 * Added a new funtion getUnitPrice()
 * 
 *    Rev 1.12   Dec 20 2000 09:44:02   WINNIE
 * New methods to check minimum at fund level
 * 
 *    Rev 1.11   Dec 17 2000 20:23:26   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.10   Nov 30 2000 12:40:58   VASILEAD
 * fixed the link warning
 * 
 *    Rev 1.9   Nov 24 2000 12:07:18   WINNIE
 * fix condition
 * 
 *    Rev 1.8   Nov 22 2000 14:26:50   WINNIE
 * Add fundClassForPlanType method
 * 
 *    Rev 1.7   Nov 20 2000 15:48:30   VASILEAD
 * Changed to return all funds not only the first 25
 * 
 *    Rev 1.6   Nov 17 2000 11:42:22   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.5   Sep 11 2000 10:42:14   YINGBAOL
 * add IsFundClassExist and IsFundValidAtDate method
 * 
 *    Rev 1.4   Sep 01 2000 14:34:04   ZHANGCEL
 * GetField problem
 * 
 *    Rev 1.3   Aug 15 2000 10:12:52   WINNIE
 * Add Getfield method
 * 
 *    Rev 1.2   Apr 20 2000 16:38:44   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.1   Apr 13 2000 10:39:32   BUZILA
 * added :getStrKey( strKey, dstFundCode, dstClassCode )
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Jan 05 2000 20:10:46   BUZILA
 * adding list flag
 * 
 *    Rev 1.6   Dec 12 1999 16:25:22   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/