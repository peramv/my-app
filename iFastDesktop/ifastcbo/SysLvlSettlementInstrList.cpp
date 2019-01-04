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
// ^FILE   : SysLvlSettlementInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SysLvlSettlementInstrList.hpp"
#include "SysLvlSettlementInstr.hpp"
#include <ifastdataimpl\dse_dstc0267_vw.hpp>
#include <ifastdataimpl\dse_dstc0267_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLE_LOCATION_SYS_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SysLvlSettlementInstrList" );
}

namespace CND
{
   extern const long	ERR_DUPLICATE_SETTLE_LOCATION;
}

//******************************************************************************

SysLvlSettlementInstrList::SysLvlSettlementInstrList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), m_requestData( ifds::DSTC0267_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

SysLvlSettlementInstrList::~SysLvlSettlementInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY SysLvlSettlementInstrList::init(const BFDataGroupId& idDataGroup,
                               const DString& dstrTrack,
                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::SETTLE_LOCATION_SYS_INQUIRY, m_requestData, ifds::DSTC0267_VW, DSTCRequestor(getSecurity(), /*allresults*/ false, /*noDataIsErrorCondition*/ false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SysLvlSettlementInstrList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::SETTLE_LOCATION_SYS_INQUIRY, m_requestData, ifds::DSTC0267_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SysLvlSettlementInstrList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY SysLvlSettlementInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new SysLvlSettlementInstr( *this );
   ((SysLvlSettlementInstr*) pObjOut)->init( data );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY SysLvlSettlementInstrList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new SysLvlSettlementInstr( *this );
   ((SysLvlSettlementInstr*) pObjOut)->initNew( idDataGroup );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************

SEVERITY SysLvlSettlementInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check for duplicates
   std::set< DString > setSettleLocationCodes;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString dstrSettleLocationCode;
      iter.getObject()->getField(ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup, false);
      DString dstrEntry = dstrSettleLocationCode.strip().upperCase();

      if( !setSettleLocationCodes.insert( dstrEntry ).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_SETTLE_LOCATION );
         break;
      }
      ++iter; 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************

void SysLvlSettlementInstrList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrSettleLocationCode;
	if( data )
	{
		dstrSettleLocationCode = data->getElementValue( I_( "SettleLocationCode" ) );
		dstrSettleLocationCode.strip().upperCase();
		strKey = dstrSettleLocationCode;
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}

//*****************************************************************************

bool SysLvlSettlementInstrList::isDuplicateSettlementLocation( DString &dstrSettleLocationCode, 
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateSettlementLocation") );

	short nFound = 0;
   DString dstrSettleLocationCodeTmp1( dstrSettleLocationCode );
   DString dstrSettleLocationCodeTmp2; 

   // Check current list
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      iter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCodeTmp2, idDataGroup, false );
      dstrSettleLocationCodeTmp1.stripAll().upperCase();
      dstrSettleLocationCodeTmp2.stripAll().upperCase();
      if( dstrSettleLocationCodeTmp1 == dstrSettleLocationCodeTmp2 ) 
      {
         ++nFound;
      }
      ++iter;
   }

   if( nFound >  1) 
   {
      return( TRUE );
   }

   bool bExist = false;

   if( doMoreRecordsExist() )
   {
      // Check back-end
	   BFData requestData( ifds::DSTC0267_REQ );

      requestData.setElementValue( ifds::NextKey, NULL_STRING );
      requestData.setElementValue( ifds::Track, I_("N") );
      requestData.setElementValue( ifds::Activity, NULL_STRING );
      requestData.setElementValue( ifds::SettleLocationCode, dstrSettleLocationCode );

      SEVERITY sevRtn = SEVERE_ERROR;
	   DSTCRequestor requestor( getSecurity(), true, true );
	   BFData receivedData(ifds::DSTC0267_VW);

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::SETTLE_LOCATION_SYS_INQUIRY, requestData, receivedData, requestor );
      if( sevRtn <= WARNING )
      {
		   bExist = true;
	   }
	   CLEARCONDITIONS();
   }

	return bExist;

}

//*****************************************************************************
SEVERITY SysLvlSettlementInstrList::getSysLvlSettlementInstr( const DString &dstrSettlementLocationCode, 
								  										      SysLvlSettlementInstr *&pSysLvlSettlementInstr, 
																		      const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSysLvlSettlementInstr") );

	pSysLvlSettlementInstr = NULL;
	DString dstrLocalSettlementLocationCode( dstrSettlementLocationCode );
   
   pSysLvlSettlementInstr = dynamic_cast<SysLvlSettlementInstr * >( getObject( dstrLocalSettlementLocationCode.strip().upperCase(), idDataGroup ) );

	return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SysLvlSettlementInstrList.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:56:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:02:24   VADEANUM
// Initial revision.
// 
//    Rev 1.2   Nov 25 2003 17:19:32   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support - added getSysLvlSettlementInstr().
// 
//    Rev 1.1   Nov 24 2003 18:13:20   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:46   HERNANDO
// Initial revision.
// 
