//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : RSPContributionList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RSPContributionList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0173_req.hpp>
#include <ifastdataimpl\dse_dstc0173_vw.hpp>
#include "mgmtco.hpp"
#include "rspcontribution.hpp"
#include "rspcontributionlist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RSP_CONTRIBUTION_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RSPContributionList" );   
}

//******************************************************************************
// Constructor
//******************************************************************************
RSPContributionList::RSPContributionList( BFAbstractCBO &parent ) :
MFCanBFCbo( parent ),
_dstrAccountNum ( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Defines this CBO Class as a List
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
RSPContributionList::~RSPContributionList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _dstrAccountNum = NULL_STRING;
}

//******************************************************************************
// Initialization of the request object and makes a View call 173
// @param   const DString& dstrAccountNum - Account Number (Required)
// @param   const DString& dstrTrack - Track value (Not required)
// @param   const DString& dstrPageName - Page Name (Not required)
//******************************************************************************
SEVERITY RSPContributionList::init( const DString& dstrAccountNum,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   _dstrAccountNum = dstrAccountNum;
   BFData _requestData(ifds::DSTC0173_REQ);
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   ReceiveData(DSTC_REQUEST::RSP_CONTRIBUTION_LIST, _requestData, ifds::DSTC0173_VW, DSTCRequestor( getSecurity(), false, true) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// Creates a RSPContribution CBO based on the data from the view transaction.
// Returns the RSPContrution CBO to be added to the RSPContributionList
// @param   const Data& data - Data from view call 173.
// @param   BFBase *&pObjOut - BFBase pointer to RSPContribution CBO
//********************************************************************************
SEVERITY RSPContributionList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new RSPContribution ( *this );
   dynamic_cast< RSPContribution * >( pObjOut )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
// Gets the Account Number stored by the init of this class
// @param   DString &dstrAccountNum - Account Number to be returned.
//********************************************************************************

void RSPContributionList::getAccountNum( DString &dstrAccountNum )
{
   dstrAccountNum = _dstrAccountNum;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPContributionList.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:53:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Jul 22 2003 18:24:12   ZHANGCEL
// PTS ticket 10019752 -- Retrun error whenever no datewas found on a view 173 calling
// 
//    Rev 1.4   Oct 09 2002 23:54:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:56:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 18:29:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   20 Aug 2001 12:50:56   HSUCHIN
// code cleanup and added comments
// 
//    Rev 1.0   01 Aug 2001 14:28:26   HSUCHIN
// Initial revision.
*/

