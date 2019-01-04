//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransactionList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/20/99
//
// ^CLASS    : TransactionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "transactionlist.hpp"
#include "transactiondetails.hpp"
#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0017_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_LIST;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "TransactionList" );
   const I_CHAR *  YES       = I_( "Y" );
   const I_CHAR *  NO        = I_( "N" );

}

//******************************************************************************
TransactionList::TransactionList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_queryData(ifds::DSTC0017_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
TransactionList::~TransactionList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TransactionList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransactionList::init( const DString& AccountNum,
                                const DString& FundCode,
                                const DString& ClassCode ,
                                const DString& NumEntry ,
                                const DString& AllFundMode,
                                const DString& ReqTransid,
                                const DString& UseDateFlag,
                                const DString& FromDate,
                                const DString& ToDate,
                                const DString& dstrTrack,
                                const DString& dstrPageName,
                                const DString& dstrNextKey,
								const DString& dstrExcludeReversal,
				                const DString& dstrTransType,
				                const DString& dstrEUSDScope,
								const DString& dstrSearchType,
								bool reciveAll )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _queryData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
   _queryData.setElementValue( ifds::AccountNum,      AccountNum ); 
   _queryData.setElementValue( ifds::FundCode,        FundCode );
   _queryData.setElementValue( ifds::ClassCode,       ClassCode );
   _queryData.setElementValue( ifds::AllFundMode,     AllFundMode, false, false );
   _queryData.setElementValue( ifds::UseDateFlag,     UseDateFlag );
   _queryData.setElementValue( ifds::FromDate,        FromDate, false, false );
   _queryData.setElementValue( ifds::ToDate,          ToDate, false, false );
   _queryData.setElementValue( ifds::ReqTransid,      ReqTransid, false, false );
   _queryData.setElementValue( ifds::TransType,       dstrTransType, false, false );
   _queryData.setElementValue( ifds::EUSDScope,       dstrEUSDScope, false, false );
   _queryData.setElementValue( ifds::ExcludeReversal, dstrExcludeReversal, false, false );
   _queryData.setElementValue( ifds::SearchType,      dstrSearchType, false, false );
   _queryData.setElementValue( ifds::NextKey,         dstrNextKey );
   _queryData.setElementValue( ifds::Track,           dstrTrack );
   _queryData.setElementValue( ifds::Activity,        dstrPageName );
   _queryData.setElementValue( ifds::OverrideRepeats, NumEntry );

   ReceiveData( DSTC_REQUEST::TRANSACTION_LIST, _queryData, ifds::DSTC0017_VW, DSTCRequestor( getSecurity(), reciveAll) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TransactionList::anotherAccount( DString& AccountNum,
                                          DString& FundCode,DString& ClassCode ,
                                          DString& NumEntry ,DString& AllFundMode,
                                          const DString& UseDateFlag,
                                          const DString& FromDate,
                                          const DString& ToDate,
                                          const DString& dstrTrack,const DString& dstrPageName
                                        )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "" ) );

   //if already called view 17 for these params, don't do it again
   DString dstrDup = AccountNum.strip().stripLeading('0');
   dstrDup += FundCode.strip();
   dstrDup += ClassCode.strip();
   //dstrDup += NumEntry.strip();
   //dstrDup += AllFundMode.strip();
   //dstrDup += UseDateFlag;
   //dstrDup += FromDate;
   //dstrDup += ToDate;
   //dstrDup += dstrTrack;
   //dstrDup += dstrPageName;

   if( setDuplication.insert(dstrDup).second )
   {
      BFData queryData(ifds::DSTC0017_REQ);   

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::AccountNum, AccountNum ); 
      queryData.setElementValue( ifds::FundCode, FundCode );
      queryData.setElementValue( ifds::ClassCode, ClassCode );
      queryData.setElementValue( ifds::AllFundMode, AllFundMode, false, false );
      queryData.setElementValue( ifds::UseDateFlag, UseDateFlag );
      queryData.setElementValue( ifds::FromDate, FromDate, false, false );
      queryData.setElementValue( ifds::ToDate, ToDate, false, false );
      queryData.setElementValue( ifds::NextKey, NULL_STRING );
      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );
      queryData.setElementValue( ifds::OverrideRepeats, NumEntry );

      ReceiveData( DSTC_REQUEST::TRANSACTION_LIST, queryData, ifds::DSTC0017_VW, DSTCRequestor( getSecurity(), false) );  
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// get cbo and set it
//******************************************************************************
TransactionDetails* TransactionList::getItem( const DString& strObjLabel, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getObject" ) );

   BFAbstractCBO* trans = BFCBO::getObject(strObjLabel, idDataGroup);
   DString TransId;
   trans->getField( ifds::TransId, TransId, BF::HOST, true );
   TransId.stripLeading('0');
   ((TransactionDetails* )trans)->getDetails( TransId );

   return(TransactionDetails*)trans;
}

//******************************************************************************
SEVERITY TransactionList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* pSecurity =  dynamic_cast<const DSTCSecurity *>(getSecurity());
      ReceiveData( DSTC_REQUEST::TRANSACTION_LIST, _queryData, ifds::DSTC0017_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY TransactionList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new TransactionDetails( *this );
   ( ( TransactionDetails* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY TransactionList::doCreateNewObject(BFCBO *& pBase, DString &strKey )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new TransactionDetails( *this );

   return(GETCURRENTHIGHESTSEVERITY());
}


//********************************************************************************
void TransactionList::getStrKey( DString& dstKey, const DString& dstrFund, 
                                 const DString& dstrClass, const DString& dstrTransType)
{
   dstKey = dstrFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrClass;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrTransType;
   dstKey.strip();

   dstKey.upperCase();
}

//********************************************************************************
bool TransactionList::fundclasstrxExist ( const DString& dstrFund, const DString& dstrClass, const DString& dstrTransType,
                                          const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fundclassExist" ));

   DString strKey,tmp(dstrTransType);
   bool trans_exist ( false );
   BFAbstractCBO * pCurrEntry  = NULL;

   if( dstrTransType == I_("Redemption") ) tmp =I_("PW");
   getStrKey(strKey, dstrFund, dstrClass,tmp );

   BFObjIter iter(*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         DString tradeFund, tradeClass, pendingStrKey,transtype;

         pCurrEntry->getField( ifds::rxFundCode, tradeFund,     idDataGroup );
         pCurrEntry->getField( ifds::rxClassCode,tradeClass,    idDataGroup );
         pCurrEntry->getField( ifds::TransType,transtype,    idDataGroup );
         getStrKey(pendingStrKey, tradeFund, tradeClass,transtype );

		 if(dstrTransType == NULL_STRING )
		 {
			 //check only for fund and class
			 if(pendingStrKey.find(strKey) != DString::npos)
			 {
				 trans_exist = true;
				 break;
			 }
		 }
         else if( pendingStrKey == strKey )
         {
            trans_exist = true;
            break;
         }
      }
      ++iter;
   }

   return(trans_exist);   
}

//********************************************************************************
void TransactionList::getStrKey( DString &strKey, const BFData *data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   BFCBO::getStrKey( strKey, data );
   if( data )
   {
      DString dstrAccountNum, dstrTransNum, dstrTransType, dstrFund, dstrClass, dstrTransId;
	  data->getElementValue( ifds::AccountNum,  dstrAccountNum );	  
      data->getElementValue( ifds::TransNum,    dstrTransNum );
      data->getElementValue( ifds::TransType,   dstrTransType );
      data->getElementValue( ifds::rxFundCode,  dstrFund );
      data->getElementValue( ifds::rxClassCode, dstrClass );
	  data->getElementValue( ifds::TransId,     dstrTransId );
		
      strKey += I_(" ");
	  strKey += dstrAccountNum.strip();	  
      strKey += dstrTransNum.strip();
	  strKey += dstrTransType.strip();
	  strKey += dstrFund.strip();
	  strKey += dstrClass.strip();
	  strKey += dstrTransId.strip();		
   }
}

//********************************************************************************
void TransactionList::getStrKey( DString& strKey, 
								 const DString& dstrFund, 
                                 const DString& dstrClass, 
								 const DString& dstrTransNum,
								 const DString& dstrTransType)
{
      strKey += I_(" ");
	  strKey.strip();
      strKey += dstrTransNum;
	  strKey.strip();
	  strKey += dstrTransType;
	  strKey.strip();
	  strKey += dstrFund;
	  strKey.strip();
	  strKey += dstrClass;
	  strKey.strip();
}
//******************************************************************************

SEVERITY TransactionList::initSearch( 
                  const DString& strSearchType,
				  const DString& strAccountNum,
                  const DString& strTransNum,
                  const DString& strWireOrdNum, 
                  const DString& strNetworkID, 
                  const DString& strExtTransNum, 
                  const DString& strSendRefNum,
                  const DString& strMasterRefNum, 
                  const DString& strPartRefNum,
                  const DString& strFromDate, 
                  const DString& strToDate,
				  const DString& strExternalIdType,
				  const DString& strExternalId,
				  const DString& strAltAccount,
				  const DString& strFundIDType,
				  const DString& strFundIDValue,
				  const DString& strTransType,
				  const DString& strUnits,
  				  const DString& strNSCCControlNumber,
				  const DString& strTradeDate,
				  const DString& strFundCode,
				  const DString& strClassCode,
                  const DString& dstrTrack,
                  const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initSearch" ) );

   DString mgmtCoIdOut;
   _queryData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
   _queryData.setElementValue( ifds::SearchType,      strSearchType );
	_queryData.setElementValue( ifds::AccountNum,      strAccountNum );
   _queryData.setElementValue( ifds::TransNum,        strTransNum );
   _queryData.setElementValue( ifds::WireOrdNum,      strWireOrdNum );
   _queryData.setElementValue( ifds::NetworkID,       strNetworkID );
   _queryData.setElementValue( ifds::ExtTransNum,     strExtTransNum );
   _queryData.setElementValue( ifds::SendRefNum,      strSendRefNum );
   _queryData.setElementValue( ifds::MasterRefNum,    strMasterRefNum );
   _queryData.setElementValue( ifds::PartRefNum,      strPartRefNum );
   _queryData.setElementValue( ifds::Track,           dstrTrack );
   _queryData.setElementValue( ifds::Activity,        dstrPageName );
   _queryData.setElementValue( ifds::OverrideRepeats, I_("0") );
   _queryData.setElementValue( ifds::AllFundMode,     YES, false, false );
	_queryData.setElementValue( ifds::ExternalIdType,  strExternalIdType );
	_queryData.setElementValue( ifds::ExternalId,      strExternalId );
	
	_queryData.setElementValue( ifds::AltAccount,      strAltAccount );
	_queryData.setElementValue( ifds::FundIDType,      strFundIDType );
	_queryData.setElementValue( ifds::FundIDValue,     strFundIDValue );
	_queryData.setElementValue( ifds::TransType,			strTransType );
	_queryData.setElementValue( ifds::Units,				strUnits );
	_queryData.setElementValue( ifds::TradeDate,			strTradeDate );
	_queryData.setElementValue( ifds::FundCode,			strFundCode );
	_queryData.setElementValue( ifds::ClassCode,			strClassCode );
	_queryData.setElementValue( ifds::NSCCControlNumber,	strNSCCControlNumber );

   DString dstrFromDate(strFromDate), dstrToDate(strToDate);
   if (!dstrFromDate.strip().empty() || !dstrToDate.strip().empty())
   {
      _queryData.setElementValue( ifds::UseDateFlag, YES, false, false);
      _queryData.setElementValue( ifds::FromDate, strFromDate, false, false );
      _queryData.setElementValue( ifds::ToDate, strToDate, false, false );
   }
   else
      _queryData.setElementValue( ifds::UseDateFlag, NO, false, false);

   ReceiveData( DSTC_REQUEST::TRANSACTION_LIST, _queryData, ifds::DSTC0017_VW, DSTCRequestor( getSecurity(), false) );
   //actually, backend does not read UseDateFlag
   //rules:
   //1. If both FromDate and ToDate are empty, all the trades that match the criteria
   //will be returned, from the very first one to the last one
   //2. If Fromdate is a valid date and ToDate is empty, all the trades that match the criteria
   //starting from FromDate to the latest one will be returned (empty means 9999/12/31
   //3. The situation when FromDate is empty and ToDate is specified is an error.It should never happen
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
// Input : Addiotnal filters like All fund mode,Tarde status,Exclude cnacel,exclude 
//		   reversal,currency etc has been added to the new serach below to utilize
//		   all the filters that is avilable in View17 Request,for perfomance improvement
// OutPut:   none
// Return:SEVERITY
// Functionality:To get the list of Historical trades based on filter criteria
//******************************************************************************
SEVERITY TransactionList::initSearch(	
						 const DString& dstrSearchType,
						 const DString& dstrAccountNum,
						 const DString& dstrTransNum,
						 const DString& dstrWireOrdNum, 
						 const DString& dstrNetworkID, 
						 const DString& dstrExtTransNum, 
						 const DString& dstrSendRefNum,
						 const DString& dstrMasterRefNum, 
						 const DString& dstrPartRefNum,
						 const DString& dstrFromDate, 
						 const DString& dstrToDate,
						 const DString& dstrExternalIdType,
						 const DString& dstrExternalId,
						 const DString& dstrAltAccount,
						 const DString& dstrFundIDType,
						 const DString& dstrFundIDValue,
						 const DString& dstrTransType,
						 const DString& dstrUnits,
						 const DString& dstrNSCCControlNumber,
						 const DString& dstrTradeDate,
						 const DString& dstrFundCode,
						 const DString& dstrClassCode,
						 //additonal filters added are below
						 const DString& dstrAllFundMode,
						 const DString& dstrTradeStatus,
						 const DString& dstrEUSDScope,
						 const DString& dstrReportingCurrency,
						 const DString& dstrExcludeReversal,
						 const DString& dstrExcludeCancelled ,
						 const DString& dstrTrack ,
						 const DString& dstrPageName )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initSearch" ) );

    DString mgmtCoIdOut;
    _queryData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
    _queryData.setElementValue( ifds::SearchType,      dstrSearchType );
    _queryData.setElementValue( ifds::AccountNum,      dstrAccountNum );
    _queryData.setElementValue( ifds::TransNum,        dstrTransNum );
    _queryData.setElementValue( ifds::WireOrdNum,      dstrWireOrdNum );
    _queryData.setElementValue( ifds::NetworkID,       dstrNetworkID );
    _queryData.setElementValue( ifds::ExtTransNum,     dstrExtTransNum );
    _queryData.setElementValue( ifds::SendRefNum,      dstrSendRefNum );
    _queryData.setElementValue( ifds::MasterRefNum,    dstrMasterRefNum );
    _queryData.setElementValue( ifds::PartRefNum,      dstrPartRefNum );
    _queryData.setElementValue( ifds::Track,           dstrTrack );
    _queryData.setElementValue( ifds::Activity,        dstrPageName );
    _queryData.setElementValue( ifds::OverrideRepeats, I_("0") );
    _queryData.setElementValue( ifds::AllFundMode,     YES, false, false );
    _queryData.setElementValue( ifds::ExternalIdType,  dstrExternalIdType );
    _queryData.setElementValue( ifds::ExternalId,      dstrExternalId );  	
    _queryData.setElementValue( ifds::AltAccount,      dstrAltAccount );
    _queryData.setElementValue( ifds::FundIDType,      dstrFundIDType );
    _queryData.setElementValue( ifds::FundIDValue,     dstrFundIDValue );
    _queryData.setElementValue( ifds::TransType,		  dstrTransType );
    _queryData.setElementValue( ifds::Units,			  dstrUnits );
    _queryData.setElementValue( ifds::TradeDate,		  dstrTradeDate );
    _queryData.setElementValue( ifds::FundCode,		  dstrFundCode );
    _queryData.setElementValue( ifds::ClassCode,		  dstrClassCode );
    _queryData.setElementValue( ifds::NSCCControlNumber,	dstrNSCCControlNumber );
    DString strFromDate(dstrFromDate), strToDate(dstrToDate);
    if (!strFromDate.strip().empty() || !strToDate.strip().empty())
    {
      _queryData.setElementValue( ifds::UseDateFlag, YES, false, false);
      _queryData.setElementValue( ifds::FromDate, strFromDate, false, false );
      _queryData.setElementValue( ifds::ToDate, strToDate, false, false );
    }
    else
       _queryData.setElementValue( ifds::UseDateFlag, NO, false, false);

   //The below are the additonal filters added to the new search
    _queryData.setElementValue( ifds::AllFundMode,	dstrAllFundMode );
    _queryData.setElementValue( ifds::TradeStatus,	dstrTradeStatus );
    _queryData.setElementValue( ifds::EUSDScope,	dstrEUSDScope );
    _queryData.setElementValue( ifds::ReportingCurrency,	dstrReportingCurrency );
    _queryData.setElementValue( ifds::ExcludeReversal  ,	dstrExcludeReversal );
    _queryData.setElementValue( ifds::ExcludeCancelled ,	dstrExcludeCancelled );

    ReceiveData( DSTC_REQUEST::TRANSACTION_LIST, _queryData, ifds::DSTC0017_VW, DSTCRequestor( getSecurity(), false) );
    //actually, backend does not read UseDateFlag
    //rules:
    //1. If both FromDate and ToDate are empty, all the trades that match the criteria
    //will be returned, from the very first one to the last one
    //2. If Fromdate is a valid date and ToDate is empty, all the trades that match the criteria
    //starting from FromDate to the latest one will be returned (empty means 9999/12/31
    //3. The situation when FromDate is empty and ToDate is specified is an error.It should never happen
    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionList.cpp-arc  $
 * 
 *    Rev 1.39   Mar 02 2006 16:28:06   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.38   Nov 08 2005 19:17:54   porteanm
 * PET 1286 FN01 - Bulk Cancellation.
 * 
 *    Rev 1.37   Nov 04 2005 10:57:50   ZHANGCEL
 * PET 1286  FN01 -- Add TradeDate search related issue
 * 
 *    Rev 1.36   Sep 20 2005 12:51:42   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.35   Jul 19 2005 16:56:22   porteanm
 * PET1171 EUSD 1B - Added parameters to init().
 * 
 *    Rev 1.34   Jul 06 2005 16:29:54   porteanm
 * PET1171 EUSD 1B - Added parameters to init().
 * 
 *    Rev 1.33   Feb 03 2005 13:38:46   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.32   Nov 14 2004 14:58:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.31   Sep 07 2004 14:25:56   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.30   May 11 2004 11:07:08   ZHANGCEL
 * PET1046_FN02 -- Trade Search by account enhancement
 * 
 *    Rev 1.29   Apr 12 2003 13:44:54   FENGYONG
 * Add findexist record only for fund and class
 * 
 *    Rev 1.28   Apr 10 2003 09:32:26   FENGYONG
 * Add getStrKey
 * 
 *    Rev 1.27   Mar 21 2003 18:27:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.26   Mar 03 2003 09:45:28   KOVACSRO
 * Added initSearch
 * 
 *    Rev 1.25   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.24   Aug 29 2002 12:56:58   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.23   Jun 18 2002 15:42:58   KOVACSRO
 * unformatted date.
 * 
 *    Rev 1.22   13 Jun 2002 14:40:26   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.21   Jun 10 2002 17:03:50   KOVACSRO
 * Formatted versus unformatted.
 * 
 *    Rev 1.20   24 May 2002 15:14:10   KOVACSRO
 * strip the leading zeros for the AccountNum
 * 
 *    Rev 1.19   22 May 2002 18:30:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   Feb 25 2002 18:55:54   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.17   22 Nov 2001 16:56:18   KOVACSRO
 * fix for getStrKey (was causing a bug in AccountDetailsProcess)
 * 
 *    Rev 1.16   20 Nov 2001 16:39:00   KOVACSRO
 * modified anotherAccount() to check if it was called before for the same AccountNum, FundCode and ClassCode.
 * 
 *    Rev 1.15   16 Nov 2001 13:50:14   KOVACSRO
 * Num entry logic is back.
 * 
 *    Rev 1.14   Nov 02 2001 11:12:12   FENGYONG
 * Add nextKey to init
 * 
 *    Rev 1.13   05 Jul 2001 14:12:02   WINNIE
 * Bug fix for sorting
 * 
 *    Rev 1.12   22 Jun 2001 11:37:18   HSUCHIN
 * getStrKey uniqueness fix
 * 
 *    Rev 1.11   30 May 2001 09:48:56   YINGZ
 * add getStrKey
 * 
 *    Rev 1.10   May 08 2001 13:31:26   FENGYONG
 * add getstrkey and fundclassexist
 * 
 *    Rev 1.9   03 May 2001 14:07:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Apr 02 2001 15:23:50   OLTEANCR
 * fix: setElementValue(DBR::FromDate,..  )
 *      setElementValue(DBR::ToDate,..  )
 * 
 *    Rev 1.7   Mar 09 2001 13:10:18   HSUCHIN
 * code cleanup and split commision hook up
 * 
 *    Rev 1.6   Mar 01 2001 16:39:32   BUZILAMI
 * field NumEntry was removed from view
 * 
 *    Rev 1.5   Jan 18 2001 16:10:38   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:24:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 15:21:06   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Nov 01 2000 11:33:46   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.1   May 16 2000 14:33:02   YINGZ
 * support usedateflag
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 05 2000 20:11:04   BUZILA
 * adding list flag
 * 
 *    Rev 1.9   Dec 12 1999 16:25:58   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/