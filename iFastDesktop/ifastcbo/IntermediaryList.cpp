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
// ^FILE   : IntermediaryList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : IntermediaryList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "intermediarylist.hpp"
#include "intermediary.hpp"
#include "nomineeinteraddr.hpp"
#include "nomineeinteraddrlist.hpp"
#include <ifastdataimpl\dse_dstc0086_req.hpp>
#include <ifastdataimpl\dse_dstc0086_vw.hpp>
#include <ifastdataimpl\dse_dstc0086_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INTERMEDIARY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "IntermediaryList" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId InterCode;

}

IntermediaryList::IntermediaryList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );
}

//*****************************************************************************

IntermediaryList::~IntermediaryList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************

SEVERITY IntermediaryList::init( const DString&  dstrIntrCode /*=NULL_STRING*/,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   BFData queryData(ifds::DSTC0086_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::IntrCode, dstrIntrCode  ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::INTERMEDIARY, queryData, ifds::DSTC0086_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void IntermediaryList::getInterCodeList( DString &dstList, bool bMakeUppercase )
{
   DString     dstInterCode = NULL_STRING;
   DString     dstIntermName = NULL_STRING;
   DString     dstCodeName = NULL_STRING;
   BFAbstractCBO *pCurrEntry  = NULL;
   BFSubst     lBFSubst;
   bool        bAddBlankCode = false;

   BFObjIter   iter( *this, BF::HOST );

   dstList = NULL_STRING;

   if( iter.end() )
      bAddBlankCode = true;

   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         pCurrEntry->getField( ifds::IntermCode, dstInterCode, BF::HOST );
         pCurrEntry->getField( ifds::IntermName, dstIntermName, BF::HOST );
         if( bMakeUppercase )
         {
            dstInterCode.upperCase();
            dstIntermName.upperCase();
         }
         dstCodeName = dstInterCode + I_(" - ") + dstIntermName;
         lBFSubst.addSubst( dstInterCode, dstCodeName );
      }
      ++iter;      
   }

   if( bAddBlankCode )
      lBFSubst.addSubst( BLANK_STRING, BLANK_STRING );

   lBFSubst.getList( dstList );

}

//*****************************************************************************

bool IntermediaryList::getIntermediary(const BFDataGroupId& idDataGroup, DString strInterCode, Intermediary *&pIntermediary)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getIntermediary") );
   pIntermediary = NULL;

   BFObjIter iterIntermediary( *this, BF::HOST );
   iterIntermediary.positionByKey( strInterCode );
   if( !iterIntermediary.end() )
   // A match was found, get the CBO  
   {
      pIntermediary = static_cast<Intermediary *>( iterIntermediary.getObject()); 
      return(true);
   }
   else
      return(false);
}

//*****************************************************************************

SEVERITY IntermediaryList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new Intermediary( *this );
   ((Intermediary*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
void IntermediaryList::getStrKey( DString &strKey, const BFData *data )  //key by Intermediary Code
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data != NULL )
   {
      DString strInterCode;

      strInterCode = data->getElementValue( ifds::IntermCode );
      buildKey( strKey, strInterCode.strip() );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

/*********************************************************************************
void IntermediaryList::getStrKeyForNewItem( DString &strKey )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKeyforNewItem" ) );

   buildKey( strKey, m_strNewBrokerCode );
}*/
//*****************************************************************************
void IntermediaryList::buildKey( DString &strKey, const DString& strInterCode )
{
   DString temp(strInterCode);
   strKey = temp.strip();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/IntermediaryList.cpp-arc  $
 * 
 *    Rev 1.22   Dec 10 2004 14:52:06   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.21   Nov 24 2004 10:18:38   yingbaol
 * PET1117:temperary take out version features
 * 
 *    Rev 1.20   Nov 18 2004 13:28:16   YINGBAOL
 * PET1117: Perfermance Tunning
 * 
 *    Rev 1.19   Nov 14 2004 14:48:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.18   Nov 04 2004 17:37:58   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.17   Mar 21 2003 18:16:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:54:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:56:04   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   Jun 06 2002 15:23:14   ZHANGCEL
 * PTS 10008308 -- Bug fix: display both IntermidaryCode and Name in the Intermidary Combo list
 * 
 *    Rev 1.13   22 May 2002 18:28:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   Feb 25 2002 18:55:46   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.11   03 May 2001 14:06:42   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Jan 18 2001 16:05:16   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.9   Dec 17 2000 20:23:52   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.8   Dec 06 2000 13:30:42   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.7   Nov 02 2000 13:38:18   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.6   Oct 27 2000 12:22:08   KOVACSRO
 * Modified getStrKey().
 * 
 *    Rev 1.5   Sep 20 2000 11:56:22   KOVACSRO
 * Modified getIntermediary() to use positionByKey().
 * 
 *    Rev 1.4   Sep 06 2000 16:48:08   KOVACSRO
 * Deleted getDefaultAddress() and added getIntermediary().
 * 
 *    Rev 1.3   Aug 17 2000 10:02:20   KOVACSRO
 * added Default field logic for getDefaultAddress.
 * 
 *    Rev 1.2   Aug 11 2000 14:24:24   KOVACSRO
 * added getDefaultAddress for an intermediary.
 * 
 *    Rev 1.1   Jul 14 2000 16:12:12   WINNIE
 * Create getInterCode for Intermediary substitution list
 * 
 *    Rev 1.0   Feb 15 2000 11:00:02   SMITHDAV
 * Initial revision.
// 
//    Rev 1.3   Jan 05 2000 20:10:56   BUZILA
// adding list flag
// 
//    Rev 1.2   Dec 12 1999 16:25:40   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/