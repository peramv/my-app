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
// ^FILE   : UnitFactorList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : UnitFactorList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\UnitFactor.hpp>
#include "UnitFactorList.hpp"

#include <ifastdataimpl\dse_dstc0313_req.hpp>
#include <ifastdataimpl\dse_dstc0313_vw.hpp>

namespace
{
   const I_CHAR *  CLASSNAME = I_( "UnitFactorList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest UNIT_FACTOR_LIST;
}

//******************************************************************************

UnitFactorList::UnitFactorList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData( ifds::DSTC0313_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

UnitFactorList::~UnitFactorList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY UnitFactorList::init( DString& UnitId, 
                              const DString& dstrTrack,
                              const DString& dstrPageName)                                         
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::UnitId, UnitId );

   ReceiveData(DSTC_REQUEST::UNIT_FACTOR_LIST, m_requestData, ifds::DSTC0313_VW, DSTCRequestor(getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UnitFactorList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::UNIT_FACTOR_LIST, m_requestData, ifds::DSTC0313_VW, DSTCRequestor(getSecurity(), false) );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UnitFactorList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new UnitFactor( *this );
   ((UnitFactor*) pObjOut)->init( data );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY UnitFactorList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new UnitFactor( *this );
   ((UnitFactor*) pObjOut)->initNew( idDataGroup );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UnitFactorList.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:59:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 09 2004 11:27:54   HERNANDO
// Initial revision.
