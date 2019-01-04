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
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : MktIndexMasterList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "MktIndexMasterList.hpp"
#include "MktIndexMaster.hpp"
#include <ifastdataimpl\dse_dstc0240_vw.hpp>
#include <ifastdataimpl\dse_dstc0240_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INDEX_MASTER_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "MktIndexMasterList" );
}

namespace CND
{
	extern const long	ERR_DUPLICATE_MKT_INDEX_CODE;
}

//******************************************************************************

MktIndexMasterList::MktIndexMasterList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), m_requestData( ifds::DSTC0240_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

MktIndexMasterList::~MktIndexMasterList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexMasterList::init(const BFDataGroupId& idDataGroup,
                               const DString& dstrTrack,
                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::INDEX_MASTER_LIST, m_requestData, ifds::DSTC0240_VW, DSTCRequestor(getSecurity(), false, false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexMasterList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::INDEX_MASTER_LIST, m_requestData, ifds::DSTC0240_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexMasterList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY MktIndexMasterList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new MktIndexMaster( *this );
   ((MktIndexMaster*) pObjOut)->init( data);
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY MktIndexMasterList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new MktIndexMaster( *this );
   ((MktIndexMaster*) pObjOut)->initNew( idDataGroup );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY MktIndexMasterList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check for duplicates
   std::set< DString > setMktIndexCodes;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrMktIndexCode;
      iter.getObject()->getField(ifds::IndexCode, dstrMktIndexCode, idDataGroup, false);
      DString dstrEntry = dstrMktIndexCode.strip().upperCase();

      if( !setMktIndexCodes.insert( dstrEntry ).second )
      {
         DString dstrParameter = dstrMktIndexCode.strip().upperCase();
         DString dstrTag;
			addIDITagValue( dstrTag, I_("CODE"), dstrParameter );
         ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_MKT_INDEX_CODE, dstrTag );
         break;
      }
      ++iter; 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************

void  MktIndexMasterList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrMktIndexCode;
	if( data )
	{
		dstrMktIndexCode = data->getElementValue( I_( "IndexCode" ) );
		dstrMktIndexCode.strip().upperCase();
		strKey = dstrMktIndexCode;
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}

//************************************************************************************

bool MktIndexMasterList::isMktIndexCodeValid( DString& dstrMktIndexCode, const BFDataGroupId& idDataGroup )
{
	short nFound = 0;
	dstrMktIndexCode.strip().upperCase();

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
//	bValid = ( iter.positionByKey( dstrMktIndexCode ) );

   while( !iter.end() )
   {
      DString dstrValue;
      iter.getObject()->getField(ifds::IndexCode, dstrValue, idDataGroup, false);
      dstrValue.strip().upperCase();
      if( dstrValue == dstrMktIndexCode )
      {
         ++nFound;
      }
      ++iter;
   }

   return (nFound > 1);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexMasterList.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:50:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Mar 21 2003 18:19:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Jan 23 2003 10:30:48   HERNANDO
// Initial Revision
