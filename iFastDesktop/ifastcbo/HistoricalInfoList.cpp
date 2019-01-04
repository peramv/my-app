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
// ^FILE   : HistoricalInfoList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : January 2003
//
// ^CLASS    : HistoricalInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "HistoricalInfoList.hpp"
#include "HistoricalInfo.hpp"
#include <ifastdataimpl\dse_dstc0110_req.hpp>
#include <ifastdataimpl\dse_dstc0249_req.hpp>
#include <ifastdataimpl\dse_dstc0249_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0249_vw.hpp>
#include <ifastdataimpl\dse_dstc0288_req.hpp>
#include <ifastdataimpl\dse_dstc0289_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_INFO_LIST;
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_SHAREHOLDER;
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_ACCT_KYC;
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_ACCOUNT;
}

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME  = I_( "HistoricalInfoList" );
   const I_CHAR * IDI_EMPTY_MARK = I_( "(null)" );
}

namespace AUDITTYPE
{
    extern CLASS_IMPORT I_CHAR * const ACCTCONTROL;
	extern CLASS_IMPORT I_CHAR * const ACTRDR;
}

//******************************************************************************

HistoricalInfoList::HistoricalInfoList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_pQueryData(NULL),
m_bMoreRecordsFromViewsExist( false ),
m_bMoreRecordsForShareholderKYC( false ),
m_bMoreRecordsForAccountKYC( false ),
m_bMoreRecordsForAccountHistInq( false ),
m_bMoreRecordsForMail( false ),
m_bMoreRecordsForAccountControl( false ),
m_dstrHistoricalType( NULL_STRING )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
    setObjectAsList();
}

//******************************************************************************

HistoricalInfoList::~HistoricalInfoList()
{
    TRACE_DESTRUCTOR( CLASSNAME );
    if (_pQueryData != NULL)
    {
        delete _pQueryData;
    }
}

//******************************************************************************

SEVERITY HistoricalInfoList::init(
   const DString& recId, 
   const DString& tableId,
   const DString& keys /*=NULL_STRING*/,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString mgmtCoIdOut;

   m_dstrHistoricalType = I_("SINGLE");

   if ( tableId == I_( "KYC" ) )
   {
      // View 110 - KYC Request
      DString dstrAccountNumber = keys;
      _pQueryDataAcctHistInq = new BFData (ifds::DSTC0110_REQ);
      _pQueryDataAcctHistInq->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
      _pQueryDataAcctHistInq->setElementValue(ifds::Track, dstrTrack);
      _pQueryDataAcctHistInq->setElementValue(ifds::Activity, dstrPageName);
      _pQueryDataAcctHistInq->setElementValue(ifds::AccountNum, dstrAccountNumber);
      _pQueryDataAcctHistInq->setElementValue(ifds::HistoricalType, I_("KYC"));

      ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
      ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
      m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
      CLEARCONDITIONS();      
   }

   _pQueryData = new BFData (ifds::DSTC0249_REQ);
   _pQueryData->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
   _pQueryData->setElementValue(ifds::Track, dstrTrack);
   _pQueryData->setElementValue(ifds::Activity, dstrPageName);
   _pQueryData->setElementValue(ifds::AuditType, tableId);
   _pQueryData->setElementValue(ifds::AuditRecId, recId.empty() ? I_("0") : recId);

   if ( !keys.empty() && tableId != I_( "KYC" ) )
   {
      I_CHAR *temp = const_cast < I_CHAR* > ( keys.c_str() );

      do
      {
         DString keyName, keyValue;

         temp = parseIdiString(temp, keyName, keyValue);

         BFData repeat(ifds::DSTC0249_REQRepeat_Record);

         if (IDI_EMPTY_MARK == keyValue)
         {
            keyValue = NULL_STRING;
         }
         repeat.setElementValue(ifds::KeyString, keyValue);
         _pQueryData->addRepeat(repeat);
      } while( temp && temp != NULL_STRING && *temp );

      DString dstRepeats = DString::asString( _pQueryData->getRepeatCount() );

      _pQueryData->setElementValue(ifds::RepeatCount, dstRepeats);
   }
   else
   {
      _pQueryData->setElementValue(ifds::RepeatCount, I_("0"));
   }
   ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryData, 
      ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
	CLEARCONDITIONS();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::init(
    HISTORICAL_VECTOR *pHistoricalVector,
    const DString& dstrTrack,        // = I_("N")
    const DString& dstrPageName)     // = NULL_STRING
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
    DString mgmtCoIdOut;

    m_dstrHistoricalType = I_("MULTI");

    // Walkthrough vector
    for( HISTORICAL_VECTOR::size_type iCtr = 0; iCtr < pHistoricalVector->size(); ++iCtr ) 
    {
        HistoricalData dataHistorical;
        dataHistorical.pQueryData = new BFData (ifds::DSTC0249_REQ);
        dataHistorical.pQueryData->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
        dataHistorical.pQueryData->setElementValue(ifds::Track, dstrTrack);
        dataHistorical.pQueryData->setElementValue(ifds::Activity, dstrPageName);
        dataHistorical.pQueryData->setElementValue(ifds::AuditType, pHistoricalVector->at( iCtr ).dstrTableId);
        dataHistorical.pQueryData->setElementValue(ifds::AuditRecId, pHistoricalVector->at( iCtr ).dstrRecord.empty() 
                                                   ? I_("0") : pHistoricalVector->at( iCtr ).dstrRecord );

        if ( pHistoricalVector->at( iCtr ).dstrKey.empty() ) 
        {
            dataHistorical.pQueryData->setElementValue(ifds::RepeatCount, I_("0"));
        } 
        else 
        {
            I_CHAR *temp = const_cast < I_CHAR* > ( pHistoricalVector->at( iCtr ).dstrKey.c_str() );
            do
            {
                DString keyName, keyValue;
                temp = parseIdiString(temp, keyName, keyValue);
                BFData repeat(ifds::DSTC0249_REQRepeat_Record);
                if (IDI_EMPTY_MARK == keyValue)
                {
                    keyValue = NULL_STRING;
                }
                repeat.setElementValue(ifds::KeyString, keyValue);
                dataHistorical.pQueryData->addRepeat(repeat);
            } while( temp && temp != NULL_STRING && *temp );

            DString dstRepeats = DString::asString( dataHistorical.pQueryData->getRepeatCount() );
            dataHistorical.pQueryData->setElementValue(ifds::RepeatCount, dstRepeats);
        }

        ReceiveData( DSTC_REQUEST::HISTORICAL_INFO_LIST, *dataHistorical.pQueryData, 
                     ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
        CLEARCONDITIONS();

        dataHistorical.bMoreAvailable = doMoreRecordsExist();
        m_bMoreRecordsFromViewsExist |= doMoreRecordsExist();

        m_vectorHistoricalData.push_back( dataHistorical );
    }

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::initShareholderInfo(
    const DString& dstrShareholderNumber, 
    const DString& dstrTrack /*= I_("N")*/, 
    const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initShareholderInfo" ) );
    DString mgmtCoIdOut;

    m_dstrHistoricalType = I_("SHRINFO");

    _pQueryDataShr = new BFData (ifds::DSTC0288_REQ);
    _pQueryDataShr->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataShr->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataShr->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataShr->setElementValue(ifds::ShareholderNum, dstrShareholderNumber);
    _pQueryDataShr->setElementValue(ifds::HistoricalType, I_("SHR"));

    ReceiveData( DSTC_REQUEST::HISTORICAL_SHAREHOLDER, *_pQueryDataShr, 
                 ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
    CLEARCONDITIONS();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::initKYC(
    const DString& dstrHistoricalType,
    const DString& dstrShareholderNumber,
    const DString& dstrAccountNumber, 
    const DString& dstrTrack /*= I_("N")*/, 
    const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initKYC" ) );
    DString mgmtCoIdOut;

    m_dstrHistoricalType = dstrHistoricalType;

    // Shareholder Information KYC
    _pQueryDataShr = new BFData (ifds::DSTC0288_REQ);
    _pQueryDataShr->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataShr->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataShr->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataShr->setElementValue(ifds::ShareholderNum, dstrShareholderNumber);
    _pQueryDataShr->setElementValue(ifds::HistoricalType, I_("KYC"));

    ReceiveData( DSTC_REQUEST::HISTORICAL_SHAREHOLDER, *_pQueryDataShr, 
                 ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
    CLEARCONDITIONS();
    m_bMoreRecordsForShareholderKYC = doMoreRecordsExist();

    // View 110 - KYC Request
    _pQueryDataAcctHistInq = new BFData (ifds::DSTC0110_REQ);
    _pQueryDataAcctHistInq->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataAcctHistInq->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataAcctHistInq->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataAcctHistInq->setElementValue(ifds::AccountNum, dstrAccountNumber);
    _pQueryDataAcctHistInq->setElementValue(ifds::HistoricalType, I_("KYC"));

    ReceiveData( DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
                ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));

    m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
    CLEARCONDITIONS();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::initMail(
    const DString& recId, 
    const DString& tableId,
    const DString& keys,
    const DString& dstrAccountNumber, 
    const DString& dstrTrack /*= I_("N")*/, 
    const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initMail" ) );
    DString mgmtCoIdOut;

    // View 110 Call
    _pQueryDataAcctHistInq = new BFData (ifds::DSTC0110_REQ);
    _pQueryDataAcctHistInq->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataAcctHistInq->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataAcctHistInq->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataAcctHistInq->setElementValue(ifds::AccountNum, dstrAccountNumber);
    _pQueryDataAcctHistInq->setElementValue(ifds::HistoricalType, I_("MAIL"));

    ReceiveData( DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
                 ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
    m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
    CLEARCONDITIONS();

    // View 249 with DELOPN
    init( recId, tableId, keys );
    m_dstrHistoricalType = I_("MAIL");     // Override init(,,)'s assignment.
    m_bMoreRecordsForMail = doMoreRecordsExist();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::initAcct(
   const DString& dstrAccountNumber, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAcct" ) );
    DString mgmtCoIdOut;
    
    m_dstrHistoricalType = I_("ACCT");
    
    // View 110 Call
    _pQueryDataAcctHistInq = new BFData (ifds::DSTC0110_REQ);
    _pQueryDataAcctHistInq->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataAcctHistInq->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataAcctHistInq->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataAcctHistInq->setElementValue(ifds::AccountNum, dstrAccountNumber);
    _pQueryDataAcctHistInq->setElementValue(ifds::HistoricalType, I_("Acct"));

    ReceiveData( DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
                 ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
    m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();  // Optional

    CLEARCONDITIONS();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY HistoricalInfoList::initAcctControl(
   const DString& dstrAccountNumber, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAcctControl" ) );
    DString mgmtCoIdOut;

    // View 249 Call
    _pQueryDataAcctControlHistInq = new BFData (ifds::DSTC0249_REQ);
    _pQueryDataAcctControlHistInq->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
    _pQueryDataAcctControlHistInq->setElementValue(ifds::Track, dstrTrack);
    _pQueryDataAcctControlHistInq->setElementValue(ifds::Activity, dstrPageName);
    _pQueryDataAcctControlHistInq->setElementValue(ifds::AccountNum, dstrAccountNumber);
    _pQueryDataAcctControlHistInq->setElementValue(ifds::HistoricalType, AUDITTYPE::ACCTCONTROL );

    ReceiveData( DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryDataAcctControlHistInq, 
                 ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
    m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();  // Optional

    CLEARCONDITIONS();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY HistoricalInfoList::initAcctRoundingRule(
   HISTORICAL_VECTOR *pHistoricalVector,
   const DString& dstrAccountNumber, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initAcctRoundingRule" ) );
    DString mgmtCoIdOut;
    
	// Walkthrough vector
    for( HISTORICAL_VECTOR::size_type iCtr = 0; iCtr < pHistoricalVector->size(); ++iCtr ) 
    {
        HistoricalData dataHistorical;
        dataHistorical.pQueryData = new BFData (ifds::DSTC0249_REQ);
        dataHistorical.pQueryData->setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
        dataHistorical.pQueryData->setElementValue(ifds::Track, dstrTrack);
        dataHistorical.pQueryData->setElementValue(ifds::Activity, dstrPageName);
		dataHistorical.pQueryData->setElementValue(ifds::AccountNum, dstrAccountNumber);
        dataHistorical.pQueryData->setElementValue(ifds::AuditType, pHistoricalVector->at( iCtr ).dstrTableId);
        dataHistorical.pQueryData->setElementValue(ifds::AuditRecId, I_("0"));

        if ( pHistoricalVector->at( iCtr ).dstrKey.empty() ) 
        {
            dataHistorical.pQueryData->setElementValue(ifds::RepeatCount, I_("0"));
        } 
        else 
        {
            I_CHAR *temp = const_cast < I_CHAR* > ( pHistoricalVector->at( iCtr ).dstrKey.c_str() );
            do
            {
                DString keyName, keyValue;
                temp = parseIdiString(temp, keyName, keyValue);
                BFData repeat(ifds::DSTC0249_REQRepeat_Record);
                if (IDI_EMPTY_MARK == keyValue)
                {
                    keyValue = NULL_STRING;
                }
                repeat.setElementValue(ifds::KeyString, keyValue);
                dataHistorical.pQueryData->addRepeat(repeat);
            } while( temp && temp != NULL_STRING && *temp );

            DString dstRepeats = DString::asString( dataHistorical.pQueryData->getRepeatCount() );
            dataHistorical.pQueryData->setElementValue(ifds::RepeatCount, dstRepeats);
        }

        ReceiveData( DSTC_REQUEST::HISTORICAL_INFO_LIST, *dataHistorical.pQueryData, 
                     ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false, false));
        CLEARCONDITIONS();

        dataHistorical.bMoreAvailable = doMoreRecordsExist();
        m_bMoreRecordsForAcctRoundingRuleHistInq |= doMoreRecordsExist();

        m_vectorHistoricalData.push_back( dataHistorical );
    }

    CLEARCONDITIONS();

    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( m_dstrHistoricalType == I_("MULTI") )
   {
      if( m_bMoreRecordsFromViewsExist )
      {
         m_bMoreRecordsFromViewsExist = false;
         for( HISTORICAL_DATA_VECTOR::size_type iCtr = 0; iCtr < m_vectorHistoricalData.size(); ++iCtr )
         {
            if( m_vectorHistoricalData[iCtr].bMoreAvailable )
            {
               ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *m_vectorHistoricalData[iCtr].pQueryData, 
                  ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
               CLEARCONDITIONS();
               m_vectorHistoricalData[iCtr].bMoreAvailable = doMoreRecordsExist();
               m_bMoreRecordsFromViewsExist |= doMoreRecordsExist();
            }
         }
      }
   } 
   else if( m_dstrHistoricalType == I_("SINGLE") )
   {
      if( doMoreRecordsExist() )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryData, 
            ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
         CLEARCONDITIONS();
      }
      // Account History Inquiry (possibly)
      if( m_bMoreRecordsForAccountHistInq )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
         ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
         m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
         CLEARCONDITIONS();
      }
   }
   else if( m_dstrHistoricalType == I_("SHRINFO") )
   {
      if( doMoreRecordsExist() )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_SHAREHOLDER, *_pQueryDataShr, 
            ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
         CLEARCONDITIONS();
      }
   }
   else if( m_dstrHistoricalType == I_("KYC") )
   {
      // Shareholder call
      if( m_bMoreRecordsForShareholderKYC )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_SHAREHOLDER, *_pQueryDataShr, 
         ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
         m_bMoreRecordsForShareholderKYC = doMoreRecordsExist();
         CLEARCONDITIONS();
      }
      // Account History Inquiry
      if( m_bMoreRecordsForAccountHistInq )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
         ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
         m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
         CLEARCONDITIONS();
      }
   }
   else if( m_dstrHistoricalType == I_("MAIL") )
   {
      if( m_bMoreRecordsForMail )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryData, 
            ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
         m_bMoreRecordsForMail = doMoreRecordsExist();
         CLEARCONDITIONS();
      }
      // Account History Inquiry (possibly)
      if( m_bMoreRecordsForAccountHistInq )
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
         ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
         m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();
         CLEARCONDITIONS();
      }
   }
   else if( m_dstrHistoricalType == I_("ACCT") )
   {
      // Account History Inquiry (possibly)
      if( doMoreRecordsExist() ) // We can use m_bMoreRecordsForAccountHistInq if we want
      {
         ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
         ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
         m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();  // Optional
         CLEARCONDITIONS();
      }
   }
   else if( m_dstrHistoricalType == AUDITTYPE::ACCTCONTROL )
   {
	   if( m_bMoreRecordsForAccountControl )
	   {
		   ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryData, 
			   ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
		   m_bMoreRecordsForAccountControl = doMoreRecordsExist();
		   CLEARCONDITIONS();
	   }

	   //if( doMoreRecordsExist() )
	   //{
	   //    ReceiveData(DSTC_REQUEST::HISTORICAL_ACCOUNT, *_pQueryDataAcctHistInq, 
	   //    ifds::DSTC0249_VW, DSTCRequestor(getSecurity(), false));
	   //    m_bMoreRecordsForAccountHistInq = doMoreRecordsExist();  // Optional
	   //    CLEARCONDITIONS();
	   //}
   }
   else if( m_dstrHistoricalType == AUDITTYPE::ACTRDR )
   {
	   if( m_bMoreRecordsForAcctRoundingRule )
	   {
		   ReceiveData(DSTC_REQUEST::HISTORICAL_INFO_LIST, *_pQueryData, 
			   ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false));
		   m_bMoreRecordsForAcctRoundingRule = doMoreRecordsExist();
		   CLEARCONDITIONS();
	   }        
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   HistoricalInfo * pHistoricalInfo = new HistoricalInfo( *this );
   pHistoricalInfo->init( data );
   pObjOut = pHistoricalInfo;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool HistoricalInfoList::doMoreHistoricalRecordsExist()
{
	bool bReturn = false;

	if( m_dstrHistoricalType == I_("MULTI") )
	{
		bReturn = m_bMoreRecordsFromViewsExist;
	}
	else if( m_dstrHistoricalType == I_("SINGLE")   || 
			 m_dstrHistoricalType == I_("SHRINFO")  || 
			 m_dstrHistoricalType == I_("ACCT") )
	{
		bReturn = doMoreRecordsExist();
	}
	else if( m_dstrHistoricalType == I_("KYC") )
	{
		bReturn = m_bMoreRecordsForShareholderKYC   || 
				  m_bMoreRecordsForAccountKYC       || 
				  m_bMoreRecordsForAccountHistInq;
	}
	else if( m_dstrHistoricalType == I_("MAIL") )
	{
		bReturn = m_bMoreRecordsForMail             || 
				  m_bMoreRecordsForAccountHistInq;
	}
	else if( m_dstrHistoricalType == AUDITTYPE::ACCTCONTROL )
	{
		bReturn = m_bMoreRecordsForAccountControl   || 
				  m_bMoreRecordsForAccountHistInq;
	}
	else if( m_dstrHistoricalType == AUDITTYPE::ACTRDR )
	{
		bReturn = m_bMoreRecordsForAcctRoundingRule   || 
				  m_bMoreRecordsForAcctRoundingRuleHistInq;
	}

	return bReturn;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfoList.cpp-arc  $
// 
//    Rev 1.19   Apr 16 2008 18:52:54   daechach
// PET2385 FN02&07 - Modified code regarding code review.
// 
//    Rev 1.18   Mar 11 2008 20:10:26   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.17   Aug 09 2007 11:31:24   kovacsro
// PET2372FN02 FDP-AIM KYC - fixed GetMore functionality
// 
//    Rev 1.16   Aug 06 2007 16:20:26   kovacsro
// PET 2372 FN02 FDP-AIM KYC - new approach for KYC historical due to base changes
// 
//    Rev 1.15   Nov 17 2004 15:02:16   PURDYECH
// PET910 - .NET Conversion:  Fixed compiler warning messages
// 
//    Rev 1.14   Nov 14 2004 14:44:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Mar 15 2004 17:54:36   HERNANDO
// PET965 FN11 - Changed initKYC.  Added ClearConditions until we filter.
// 
//    Rev 1.12   Mar 03 2004 17:29:20   HERNANDO
// PET965 FN11 - Added initAcct.
// 
//    Rev 1.11   Mar 02 2004 14:27:16   HERNANDO
// PET965 FN11 - Clearing the conditions after the view calls.  This is to ensure that the dialog will be displayed on 'No Data Found' and the record specific error conditions.  In the future, this will be filtered with the specific error conditions that are acceptable.
// 
//    Rev 1.10   Feb 28 2004 15:58:34   HERNANDO
// PET965 FN11 - Additional historical enhancement.
// 
//    Rev 1.9   Mar 21 2003 18:13:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Feb 11 2003 14:41:48   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.7   Feb 06 2003 12:03:18   popescu
// Checking in for Historical Info Search screen
// 
//    Rev 1.6   Feb 03 2003 11:54:06   popescu
// Changes to support the KeyString field of view 249
// 
//    Rev 1.5   Jan 29 2003 16:42:46   popescu
// Showing the data not found error
// 
//    Rev 1.4   Jan 29 2003 14:58:12   popescu
// FIxes related to view layout change and error reporting
// 
//    Rev 1.3   Jan 28 2003 16:56:36   popescu
// Fixes for the More button in the Historical Info dialog
// 
//    Rev 1.2   Jan 28 2003 13:16:14   popescu
// Historical Info feature implementation
// 
//    Rev 1.1   Jan 26 2003 16:10:42   popescu
// List and CBO object for the Historical Info feature
// 
//    Rev 1.0   Jan 26 2003 15:52:28   popescu
// Initial Revision
 *
 */
