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
// ^FILE   : AccountContractList.cpp
// ^AUTHOR : 
// ^DATE   : Jan 09, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AccountContractList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "accountcontractlist.hpp"
#include <ifastdataimpl\dse_dstc0239_req.hpp>
#include <ifastdataimpl\dse_dstc0239_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_CONTRACT_LIST;   
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AccountContractList" );
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************

AccountContractList::AccountContractList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),  
_pRequestData ( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************

AccountContractList::~AccountContractList()
{
   if( _pRequestData )
      delete _pRequestData;
   TRACE_DESTRUCTOR( CLASSNAME );
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

SEVERITY AccountContractList::init( const DString& dstrAccountNumber, 
                                    const DString& dstrFundCode,
                                    const DString& dstrClassCode,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _pRequestData = new BFData(ifds::DSTC0239_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::AccountNum,  dstrAccountNumber  );   
   _pRequestData->setElementValue( ifds::FundCode,  dstrFundCode );   
   _pRequestData->setElementValue( ifds::ClassCode,  dstrClassCode );   
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );

   // Execute view call.
   SEVERITY sevRtn = NO_CONDITION;
   sevRtn = ReceiveData(DSTC_REQUEST::ACCOUNT_CONTRACT_LIST, *_pRequestData, ifds::DSTC0239_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY AccountContractList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
   ReceiveData(DSTC_REQUEST::ACCOUNT_CONTRACT_LIST, *_pRequestData, ifds::DSTC0239_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountContractList.cpp-arc  $
// 
//    Rev 1.2   Mar 21 2003 17:53:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Jan 20 2003 14:58:28   HSUCHIN
// minor clean up
// 
//    Rev 1.0   Jan 17 2003 13:30:10   HSUCHIN
// Initial Revision
*/
