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
// ^FILE   : RegPlanTransferList.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RegPlanTransferList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"

#include "RegPlanTransferList.hpp"
#include "RegPlanTransfer.hpp"

#include <ifastdataimpl\dse_dstc0472_vw.hpp>
#include <ifastdataimpl\dse_dstc0472_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0472_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REG_PLAN_TRANSF_INQUIRY;            
   extern CLASS_IMPORT const DSTCRequest REG_PLAN_TRANSF_ALLOC_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RegPlanTransferList" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
}
//*****************************************************************************

RegPlanTransferList::RegPlanTransferList( BFAbstractCBO &parent ) 
   : MFCanBFCbo( parent ), pRequestData(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
RegPlanTransferList::~RegPlanTransferList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY RegPlanTransferList::initNew( const DString& strAccountNumber)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _dstrAccountNum = strAccountNumber;


   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY RegPlanTransferList::init( const BFDataGroupId& idDataGroup, const DString& strAccountNumber,
                                   const DString& dstrTrack, const DString& dstrPageName, 
                                   const DString& dstrSrchBroker, 
                                   const DString& dstrSrchBranch, 
                                   const DString& dstrSrchSlsrep, 
                                   const DString& dstrSrchExtInst, 
                                   const DString& dstrSrchExtInstName, 
                                   const DString& dstrSrchExtInstAcct)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // get info for validation
   _dstrAccountNum = strAccountNumber;

   {
      // get systematic info
      pRequestData = new BFData(ifds::DSTC0472_REQ); 

      DString mgmtCoIdOut;
      pRequestData->setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
      pRequestData->setElementValue( ifds::SrchAccountNum,  _dstrAccountNum);
      pRequestData->setElementValue( ifds::SrchBroker,      dstrSrchBroker);
      pRequestData->setElementValue( ifds::SrchBranch,      dstrSrchBranch);
      pRequestData->setElementValue( ifds::SrchSlsrep,      dstrSrchSlsrep);
      pRequestData->setElementValue( ifds::SrchExtInst,     dstrSrchExtInst); 
      pRequestData->setElementValue( ifds::SrchExtInstName, dstrSrchExtInstName);
      pRequestData->setElementValue( ifds::SrchExtInstAcct, dstrSrchExtInstAcct);
      pRequestData->setElementValue( ifds::Track,           dstrTrack );
      pRequestData->setElementValue( ifds::Activity,        dstrPageName );

      BFData* responseData = new BFData(ifds::DSTC0472_VW);

      ReceiveData(DSTC_REQUEST::REG_PLAN_TRANSF_INQUIRY, *pRequestData, *responseData, DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY RegPlanTransferList::getNext()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   ReceiveData(DSTC_REQUEST::REG_PLAN_TRANSF_INQUIRY, *pRequestData, ifds::DSTC0472_VW, DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY RegPlanTransferList::getDataObjectKey( BFData &data, DString &strKey )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDataObjectKey" ) );
   //default ementation creates a sequential key
   strKey = data.getElementValue( ifds::RegTransferMstrUUID );

   return(NO_CONDITION);
}

//*****************************************************************************

void RegPlanTransferList::getStrKey (DString &strKey, const BFData *data)
{
   if( data )
      strKey = data->getElementValue( ifds::RegTransferMstrUUID );
   else
      BFCBO::getStrKey(strKey, NULL);
}

//*****************************************************************************

SEVERITY RegPlanTransferList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString strKey;

   getStrKey ( strKey, &data );
   DString dstrRegTransferMstrUUID = data.getElementValue( ifds::RegTransferMstrUUID );

   dstrRegTransferMstrUUID.strip().stripLeading( I_CHAR( '0' ) );

   RegPlanTransfer* _pRegPlanTransfer = new RegPlanTransfer( *this );
   _pRegPlanTransfer->init( BF::HOST, const_cast< BFData & >( data ));
   _pRegPlanTransfer->init2( BF::HOST, this );

   pObjOut = dynamic_cast<BFCBO* >(_pRegPlanTransfer);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RegPlanTransferList::doCreateNewObject(BFCBO *& pBase, DString &strKey,  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   RegPlanTransfer *pRegPlanTransfer = new RegPlanTransfer( *this );

   pRegPlanTransfer->initNew( idDataGroup );
   pRegPlanTransfer->init2( idDataGroup, this );

   pBase = pRegPlanTransfer;
   pRegPlanTransfer->setField(ifds::RegTransferMstrUUID, strKey, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RegPlanTransferList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

void RegPlanTransferList::getStrKeyForNewItem( DString & strKey )
{
   BFCBO::getStrKeyForNewItem( strKey );

   strKey = I_( "zz" ) + strKey;
}

bool RegPlanTransferList::areAllRecordsInactive (const BFDataGroupId& idDataGroup)
{
   bool bAreAllRecordsInactive = false;
   BFObjIter iter (*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   DString dstrCurrentBusinessDate;

   getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false );

   while (!iter.end()) 
   {
      RegPlanTransfer *pRegPlanTransfer = dynamic_cast <RegPlanTransfer*>(iter.getObject());

      if (pRegPlanTransfer)
      {
         DString dstrStopDate (NULL_STRING);
         DString dstrRecordStatus (NULL_STRING);

         pRegPlanTransfer->getField (ifds::ClosedDate, dstrStopDate, idDataGroup);
         pRegPlanTransfer->getField (ifds::RegTransferStatus, dstrRecordStatus, idDataGroup);

         dstrStopDate.strip().upperCase();
         dstrRecordStatus.strip().upperCase();

         bAreAllRecordsInactive = DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurrentBusinessDate) == DSTCommonFunctions::FIRST_EARLIER || dstrRecordStatus != I_("1");
         if (!bAreAllRecordsInactive)
         {
            break;
         }
      }
      ++iter;
   }
   return bAreAllRecordsInactive;
}

void RegPlanTransferList::CopyData(const BFDataGroupId& idDataGroup, const DString &fromKey, const DString &toKey)
{
   RegPlanTransfer *pFromRegPlanTransfer = NULL;
   RegPlanTransfer *pToRegPlanTransfer   = NULL;

   for( BFObjIter Iter( *this, idDataGroup ); !Iter.end(); ++Iter )
   {
      if( Iter.getStringKey() == fromKey )
      {
         pFromRegPlanTransfer = dynamic_cast< RegPlanTransfer * >( Iter.getObject( ) );
      }
      else if( Iter.getStringKey() == toKey )
      {
         pToRegPlanTransfer = dynamic_cast< RegPlanTransfer* >( Iter.getObject( ) );
      }
   }

   assert ( pFromRegPlanTransfer && pToRegPlanTransfer );

   pToRegPlanTransfer->ModelOffer(pFromRegPlanTransfer, idDataGroup);
}
