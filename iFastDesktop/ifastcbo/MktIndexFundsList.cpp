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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MktIndexFundsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MktIndexFundsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "MktIndexFunds.hpp"
#include "MktIndexFundsList.hpp"
#include <ifastdataimpl\dse_dstc0241_req.hpp>
#include <ifastdataimpl\dse_dstc0241_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MktIndexFundsList" );
}

namespace CND
{
   extern const long	ERR_DUPLICATE_FUND_CLASS;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INDEX_FUNDS_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::IndexCode, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

MktIndexFundsList::MktIndexFundsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

MktIndexFundsList::~MktIndexFundsList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexFundsList::initExisting(const DString& dstrTrack, const DString& dstrPageName,
                                         const DString& dstrMktIndexCode )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   DString dstrIndexCode( dstrMktIndexCode );
   if( dstrIndexCode.empty() )
   {
	   getField(ifds::IndexCode, dstrIndexCode, BF::HOST, false);
	   dstrIndexCode.strip();
   }

   BFData* pReqFundsList =  new BFData( ifds::DSTC0241_REQ );

   DString mgmtCoIdOut;
   pReqFundsList->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pReqFundsList->setElementValue( ifds::NextKey, NULL_STRING );
   pReqFundsList->setElementValue( ifds::Track, dstrTrack );
	pReqFundsList->setElementValue( ifds::IndexCode, dstrIndexCode );
   pReqFundsList->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::INDEX_FUNDS_LIST, *pReqFundsList, ifds::DSTC0241_VW, 
               DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFundsList::initNew(  const BFDataGroupId& idDataGroup,
                                   bool bGetDefault,
                                   const DString& dstrTrack,
                                   const DString& dstrPageName,
                                   const DString& dstrIndexCode )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFundsList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   MktIndexFunds *pMktIndexFunds = new MktIndexFunds( *this );
   pMktIndexFunds->initNew( idDataGroup );
   pBase = pMktIndexFunds;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY MktIndexFundsList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new MktIndexFunds ( *this );
   dynamic_cast< MktIndexFunds * >( pObjOut )->initExisting( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MktIndexFundsList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check for duplicates
   std::set< DString > setFundClassCodes;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrFundCode, dstrClassCode;
      iter.getObject()->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      iter.getObject()->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
      DString dstrEntry = dstrFundCode.strip().upperCase() + dstrClassCode.strip().upperCase();

      if( !setFundClassCodes.insert( dstrEntry ).second )
      {
         DString dstrParameter = dstrFundCode.strip().upperCase() + I_(", ");
         dstrParameter += dstrClassCode.strip().upperCase();
         DString dstrTag;
			addIDITagValue( dstrTag, I_("CODE"), dstrParameter );
         ADDCONDITIONFROMFILEIDI( CND::ERR_DUPLICATE_FUND_CLASS, dstrTag );
         break;
      }
      ++iter; 
   }

	return (GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MktIndexFundsList.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:50:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Mar 21 2003 18:19:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 06 2003 13:39:24   HERNANDO
// Clean-up.
// 
//    Rev 1.2   Feb 03 2003 15:53:52   HERNANDO
// Revised.
// 
//    Rev 1.1   Jan 29 2003 14:10:42   HERNANDO
// Revised.
// 
//    Rev 1.0   Jan 23 2003 10:30:44   HERNANDO
// Initial Revision
 */