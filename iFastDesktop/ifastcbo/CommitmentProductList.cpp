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
// ^FILE   : CommitmentProductList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : CommitmentProductList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "commitmentproductlist.hpp"
#include "commitmentproduct.hpp"
#include <ifastdataimpl\dse_dstc0435_req.hpp>
#include <ifastdataimpl\dse_dstc0435_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "CommitmentProductList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest COMMITMENT_PRODUCT_SETUP_INQUIRY;
}

//******************************************************************************
CommitmentProductList::CommitmentProductList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}


//******************************************************************************
CommitmentProductList::~CommitmentProductList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY CommitmentProductList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0435_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0435_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, I_("N"));

   ReceiveData( DSTC_REQUEST::COMMITMENT_PRODUCT_SETUP_INQUIRY, 
                queryData, *receivedData, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY CommitmentProductList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   CommitmentProduct * pCommitmentProduct = new CommitmentProduct( *this );
   pCommitmentProduct->init( data );
   pObjOut = pCommitmentProduct;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void CommitmentProductList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString commitmentUUID = data->getElementValue( I_( "CommitmentUUID" ) );
      strKey = commitmentUUID.strip().upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }

}

//******************************************************************************
SEVERITY CommitmentProductList::getSubstitutionList(DString& dstrSubstitutionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strTempSubList = I_("");
   while( !iter.end() )
   {
      CommitmentProduct* pObj = dynamic_cast<CommitmentProduct*>(iter.getObject());
      if(pObj)
      {
         DString strDescription, strCommitmentUUID;
         pObj->getField(ifds::Description, strDescription, idDataGroup, false);
         pObj->getField(ifds::CommitmentUUID, strCommitmentUUID, idDataGroup, false);
         strTempSubList += strCommitmentUUID;
         strTempSubList += I_("=");
         strTempSubList += strDescription;
         strTempSubList += I_(";");
      }
      ++iter; 
   }

   dstrSubstitutionList = strTempSubList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY CommitmentProductList::getActiveCommitment(DString& dstrCommitUUID, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString strTempSubList = I_("");
   while( !iter.end() )
   {
      CommitmentProduct* pObj = dynamic_cast<CommitmentProduct*>(iter.getObject());
      if(pObj)
      {
         DString strStopDate, strCommitmentUUID;
         pObj->getField(ifds::StopDate, strStopDate, idDataGroup, false);
         pObj->getField(ifds::CommitmentUUID, strCommitmentUUID, idDataGroup, false);
         if(strStopDate == I_("12319999"))
         {
            dstrCommitUUID = strCommitmentUUID;
            break;
         }
      }
      ++iter; 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool CommitmentProductList::isCommitmentProductEnded(const DString& productUUID, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSubstitutionList" ) );

   bool retVal = true;
   
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter.end() )
   {
      CommitmentProduct* pObj = dynamic_cast<CommitmentProduct*>(iter.getObject());
      if(pObj)
      {
         DString strStopDate, strCommitmentUUID;
         pObj->getField(ifds::StopDate, strStopDate, idDataGroup, false);
         pObj->getField(ifds::CommitmentUUID, strCommitmentUUID, idDataGroup, false);
         strCommitmentUUID.strip();
         if(strCommitmentUUID == productUUID && strStopDate == I_("12319999"))
            return false;
      }
      ++iter; 
   }

   return retVal;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CommitmentProductList.cpp-arc  $
// 
//    Rev 1.4   Mar 07 2012 11:32:48   if991250
// fixed logic for finding the active product
// 
//    Rev 1.3   Mar 02 2012 12:55:02   if991250
// Account Commitment in NASU
// 
//    Rev 1.2   Feb 27 2012 15:34:12   if991250
// NASU, Commitment Id
// 
//    Rev 1.1   Feb 24 2012 18:40:56   if991250
// Account Commitment
// 
//    Rev 1.0   Feb 24 2012 18:10:38   if991250
// Initial revision.
// 
*/