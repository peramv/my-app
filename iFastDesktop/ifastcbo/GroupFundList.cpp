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
// ^FILE   : GroupFundList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 12/09/99
//
// ^CLASS    : GroupFundList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <bfutil\bfguard.hpp>
#include "groupfundlist.hpp"
#include "groupfund.hpp"
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0098_vw.hpp>
#include <ifastdataimpl\dse_dstc0098_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GROUPFUNDLIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_( "GroupFundList" );

   const I_CHAR *  GROUPCODE  = I_( "GroupCode" );
   const I_CHAR *  FUNDCODE   = I_( "FundCode" );
   const I_CHAR *  CLASSCODE  = I_( "ClassCode" );
   const I_CHAR *  YES        = I_( "Y" );

}



//******************************************************************************
GroupFundList::GroupFundList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}

//******************************************************************************
GroupFundList::~GroupFundList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//******************************************************************************
SEVERITY GroupFundList::init( const DString& dstrGroupCode, const DString& dstrTrack, const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData (ifds::DSTC0098_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::GroupCode, dstrGroupCode);
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::GROUPFUNDLIST, 
                 queryData, 
                 ifds::DSTC0098_VW, 
                 DSTCRequestor (getSecurity()));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY GroupFundList::initWithFund ( const DString &dstrGroupCode, 
                                       const DString &dstrFundCode, 
                                       const DString &dstrTrack, 
                                       const DString &dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initWithFund"));

   bool bMakeViewCall = false;

   {
      BFGuard cs (_csFundCodes);
      bMakeViewCall = fundCodes.insert (dstrFundCode).second;
   }

   if (bMakeViewCall)
   {
      BFData queryData (ifds::DSTC0098_REQ);

      DString mgmtCoIdOut;
      queryData.setElementValue (ifds::GroupCode, dstrGroupCode);
      queryData.setElementValue (ifds::FundCode, dstrFundCode);
      queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
      queryData.setElementValue (ifds::Track, dstrTrack);
      queryData.setElementValue (ifds::Activity, dstrPageName);

      ReceiveData (DSTC_REQUEST::GROUPFUNDLIST, queryData, ifds::DSTC0098_VW, DSTCRequestor (getSecurity()));
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void GroupFundList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      DString GroupCode = data->getElementValue( GROUPCODE );
      DString FundCode  = data->getElementValue( FUNDCODE );
      DString ClassCode = data->getElementValue( CLASSCODE );

      getStrKey (strKey, GroupCode, FundCode, ClassCode);
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
void GroupFundList::getStrKey ( DString& strKey, const DString&  dstGroupCode, const DString&  dstFundCode, const DString&  dstClassCode )
{
   strKey = dstGroupCode; 
   strKey.strip();
   strKey += I_(" ");
   strKey += dstFundCode;
   strKey.strip();
   strKey += I_(" ");
   strKey += dstClassCode;
   strKey.strip();
   strKey.upperCase();
}

//******************************************************************************
void GroupFundList::getAllowedFunds( DString &dstList, const DString& dstGroupCode, bool bMakeUppercase, bool bAddBlankFund )
{
   DString     dstFundCode = NULL_STRING;
   BFAbstractCBO *pCurrEntry  = NULL;
   BFSubst     lBFSubst;

   if( dstGroupCode == NULL_STRING )
      bAddBlankFund = true;
   else
   {
      BFObjIter   iter( *this, BF::HOST );

      dstList = NULL_STRING;

      iter.setKeyFilter( dstGroupCode, true );  //we want the filter condition to match the begining of the key

/*
      DString lDataFilter = DString::asString( DBR::StopPurchase );
      lDataFilter += I_("<=");
      lDataFilter += I_("Y");

      iter.setDataFilter( lDataFilter );
*/

      if( iter.end() )
         bAddBlankFund = true;

      while( !iter.end() )
      {
         pCurrEntry = iter.getObject();
         if( pCurrEntry != NULL )
         {
            pCurrEntry->getField( ifds::FundCode, dstFundCode, BF::HOST );
            if( bMakeUppercase )
               dstFundCode.upperCase();
            lBFSubst.addSubst( dstFundCode, dstFundCode );
         }
         ++iter;      
      };
   };

   if( bAddBlankFund )
      lBFSubst.addSubst( BLANK_STRING, BLANK_STRING );

   lBFSubst.getList( dstList );

};
//******************************************************************************
void GroupFundList::getAllowedClasses( DString &dstList, const DString& dstGroupCode, const DString& dstFundCode, bool bMakeUppercase )
{
   DString     dstFilter    = NULL_STRING;
   DString     dstClassCode = NULL_STRING;
   BFAbstractCBO *pCurrEntry   = NULL;
   BFSubst     lBFSubst;
   bool        bAddBlankClass = false;

   if( dstFundCode == NULL_STRING )
      bAddBlankClass = true;
   else
   {
      BFObjIter   iter( *this, BF::HOST );
      dstList = NULL_STRING;
      getStrKey( dstFilter, dstGroupCode, dstFundCode, NULL_STRING );

      iter.setKeyFilter( dstFilter, true );  //we want the filter condition to match the begining of the key
      if( iter.end() )
         bAddBlankClass = true ;
      while( !iter.end() )
      {
         pCurrEntry = iter.getObject();
         if( pCurrEntry != NULL )
         {
            pCurrEntry->getField( ifds::ClassCode, dstClassCode, BF::HOST );
            if( bMakeUppercase )
               dstClassCode.upperCase();
            lBFSubst.addSubst( dstClassCode, dstClassCode );
         }
         ++iter;      
      };
   };

   if( bAddBlankClass )
      lBFSubst.addSubst( BLANK_STRING, BLANK_STRING );

   lBFSubst.getList( dstList );
};

//******************************************************************************
SEVERITY GroupFundList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   GroupFund * pGroupFund = new GroupFund( *this );
   pGroupFund->init( data );
   pObjOut = pGroupFund;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool GroupFundList::isESoPEligibleFundClass(const DString& strGroup, const DString& strFund, const DString& strClass)
{
   bool bRetVal = false;
   BFObjIter iter(*this, BF::HOST);
   DString strKey;
   getStrKey(strKey, strGroup, strFund, strClass);
   if( iter.positionByKey(strKey) )
   {
      DString strESoPEligible;
      iter.getObject()->getField(ifds::ESoPEligible, strESoPEligible, BF::HOST, false);
      if( strESoPEligible.strip().upperCase() == YES )
         bRetVal = true;
   }
   return(bRetVal);
}

//******************************************************************************

bool GroupFundList::doesGroupFundClassExist( const DString& dstrGroup, const DString& dstrFund, const DString& dstrClass)
{
   BFObjIter iter(*this, BF::HOST);
   DString dstrKey;
   getStrKey( dstrKey, dstrGroup, dstrFund, dstrClass );
   return( iter.positionByKey( dstrKey ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GroupFundList.cpp-arc  $
 * 
 *    Rev 1.25   Sep 29 2005 09:15:40   popescu
 * Incident# 406322 - cached call to view 98
 * 
 *    Rev 1.24   Aug 31 2005 10:40:48   popescu
 * 63 - BPS performance issues. cached the 98 view call.
 * 
 *    Rev 1.23   Feb 15 2005 20:20:50   winnie
 * PTS 237768 : Get Group Fund by Fund Code to speed up the performance. New method to call view 98 with fund code.
 * 
 *    Rev 1.22   Dec 10 2004 14:36:18   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.21   Nov 24 2004 10:18:36   yingbaol
 * PET1117:temperary take out version features
 * 
 *    Rev 1.20   Nov 18 2004 13:28:14   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.19   Nov 14 2004 14:43:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.18   Nov 04 2004 17:37:52   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.17   Sep 12 2004 17:19:10   HERNANDO
 * PET1117 FN22 - Support for Group Fund List.
 * 
 *    Rev 1.16   Mar 21 2003 18:12:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 12:56:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:28:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   Feb 25 2002 18:55:44   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.11   Nov 29 2001 16:25:32   ZHANGCEL
 * Set GroupCode as an element for a  view98 call
 * 
 *    Rev 1.10   14 Sep 2001 16:58:26   KOVACSRO
 * Added isESoPEligibleFundClass.
 * 
 *    Rev 1.9   03 May 2001 14:06:38   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 18 2001 16:05:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.7   Dec 17 2000 20:23:42   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 06 2000 11:37:08   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.5   Nov 02 2000 10:27:40   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.4   May 04 2000 14:09:10   BUZILA
 * changed tha way FunDetails is found. Now we are using getParent mechanism
 * 
 *    Rev 1.3   Apr 13 2000 10:40:44   BUZILA
 * added GroupFund
 * 
 *    Rev 1.2   Apr 03 2000 08:52:44   BUZILA
 * Added    void getStrKey ( DString& strKey, const DString&  dstGroupCode, const DString&  dstFundCode, const DString&  dstClassCode )
 * 
 *    Rev 1.1   Mar 17 2000 14:24:20   BUZILA
 * added   getStrKey ( strKey, dstGroupCode, dstFundCode, dstClassCode ) method
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 05 2000 20:10:50   BUZILA
// adding list flag
// 
//    Rev 1.4   Dec 23 1999 17:36:44   YINGZ
// use different version of getdataelement
// 
//    Rev 1.3   Dec 14 1999 14:19:00   YINGZ
// add getStrKey
// 
//    Rev 1.2   Dec 12 1999 16:25:24   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.1   Dec 12 1999 15:18:16   YINGZ
// ?
 * 
*/
