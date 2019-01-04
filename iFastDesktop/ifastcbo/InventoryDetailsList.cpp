//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial
//
//*****************************************************************************
//
// ^FILE   : InventoryDetailsList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : InventoryDetailsList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "InventoryDetailsList.hpp"
#include <ifastdataimpl\dse_dstc0292_req.hpp>
#include <ifastdataimpl\dse_dstc0292_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVENTORY_DETAILS_LIST;   
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "InventoryDetailsList" );
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************

InventoryDetailsList::InventoryDetailsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),  
_pRequestData ( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************

InventoryDetailsList::~InventoryDetailsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pRequestData )
      delete _pRequestData;
}

//******************************************************************************
// Initalize CBO and executes view call
// @param   const DString& dstrAccountNumber - Account Number ( Required )
// @param   const DString& dstrFundCode - Fund Code 
// @param   const DString& dstrClassCode - Class Code 
// @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
// @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
// @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY InventoryDetailsList::init( const DString& dstrInvSummId, 
										      const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _pRequestData = new BFData( ifds::DSTC0292_REQ );
	_pResponseData = new BFData( ifds::DSTC0292_VW );
   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::InvSummId, dstrInvSummId );   
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );

   // Execute view call.
   SEVERITY sevRtn = NO_CONDITION;
   sevRtn = ReceiveData(DSTC_REQUEST::INVENTORY_DETAILS_LIST, *_pRequestData, *_pResponseData /*ifds::DSTC0292_VW*/, DSTCRequestor( getSecurity(), false) );

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY InventoryDetailsList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
   ReceiveData(DSTC_REQUEST::INVENTORY_DETAILS_LIST, *_pRequestData, ifds::DSTC0292_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InventoryDetailsList.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:48:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   May 06 2004 16:48:46   HERNANDO
// Initial revision.
*/
