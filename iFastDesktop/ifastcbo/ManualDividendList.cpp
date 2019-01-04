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
//    Copyright 2003
//
//
//******************************************************************************
//
// ^FILE   : ManualDividendList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ManualDividendList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "ManualDividendList.hpp"
#include "ManualDividend.hpp"
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ManualDividendList" );
}

namespace CND
{
   extern const long WARN_BATCH_NAME_HAS_BEEN_CHANGED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDataId DSTC0124_REQ;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}

//******************************************************************************

ManualDividendList::ManualDividendList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

ManualDividendList::~ManualDividendList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************

SEVERITY ManualDividendList::init(const BFDataGroupId& idDataGroup, 
   const DString& dstrTrack /*=I_("N")*/, 
   const DString& dstrPageName /*=NULL_STRING*/)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   //this method does nothing, used to match the getObject_X template function
   //in DSTCWorkSession

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY ManualDividendList::initNew( const BFDataGroupId& idDataGroup, const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   
   m_dstrTrack = dstrTrack;
   m_dstrActivity = dstrPageName;
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************

SEVERITY ManualDividendList::doCreateNewObject( BFCBO*& pBase, DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   ManualDividend* pManualDividend = new ManualDividend( *this );
//   pManualDividend->setListKey( strKey );
   pManualDividend->init( idDataGroup );
   pBase = pManualDividend;

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************

SEVERITY ManualDividendList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrBatchName, dstrBatch;
   bool bBatchChanged = false;

   BFData queryData(ifds::DSTC0124_REQ);
   BFData *response = new BFData(ifds::DSTC0124_VW);
   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );  
   queryData.setElementValue( ifds::Track, I_("N") );
   queryData.setElementValue( ifds::Activity, NULL_STRING );

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, queryData, *response, DSTCRequestor(getSecurity()) ) <= WARNING )
   {
      response->getElementValue( ifds::rxBatchName, dstrBatchName );
      dstrBatchName.strip();
      delete response;
   }

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      if( iter.getObject()->isNew() && !iter.isDummy() )
      {
         iter.getObject()->getField( ifds::BatchName, dstrBatch, idDataGroup, false );
         dstrBatch.strip();
         if( dstrBatch != dstrBatchName )
         {
            iter.getObject()->setField( ifds::BatchName, dstrBatchName, idDataGroup, false );
            bBatchChanged = true;
         }
      }
      ++iter;
   }

   if( bBatchChanged )
   {
      ADDCONDITIONFROMFILE( CND::WARN_BATCH_NAME_HAS_BEEN_CHANGED );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
