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
// ^FILE   : RSPContribution.cpp
// ^AUTHOR : 
// ^DATE   : 01/08/2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RSPContribution
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0173_vw.hpp>
#include "rspcontribution.hpp"
#include "rspcontributionlist.hpp"
#include "rspreceiptslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RSPContribution" );
   const I_CHAR * const RSP_RECEIPTS_LIST = I_( "RSPReceiptsList" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::ContribYear, BFCBO::NONE, 0 }, 
   { ifds::First60days, BFCBO::NONE, 0 }, 
   { ifds::Remaining,   BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
//******************************************************************************
RSPContribution::RSPContribution( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Registers fields to be used for storing data
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
// Destructor
//******************************************************************************
RSPContribution::~RSPContribution()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Creates the RSPContribution CBO based on the data passed in.
// @param   const Data& data - pointer to data returned from the view.
// @param   bool bBaseDelete - Flag to detemine who deletes the CBO
//******************************************************************************
SEVERITY RSPContribution::init( const BFData& data, bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // Call BFBase attachDataObject for 
   attachDataObject( const_cast<BFData&>(data), bBaseDelete );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Gets the RSPReciptsList based on the current RSPContribution CBO
// @param   const BFDataGroupId& idDataGroup - current data group.
// @param   RSPReceitpsList *&pRSPReceiptsList - pointer to the retrieved 
//                                               RSPReceiptsList
//******************************************************************************
SEVERITY RSPContribution::getRSPReceiptsList( const BFDataGroupId& idDataGroup, RSPReceiptsList *& pRSPReceiptsList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRSPReceiptsList" ) );

   // try to get the RSPReceipts List from the Repository
   pRSPReceiptsList = dynamic_cast<RSPReceiptsList*>(getObject( RSP_RECEIPTS_LIST, idDataGroup ));
   if( !pRSPReceiptsList )
   {
      pRSPReceiptsList = new RSPReceiptsList( *this );
      if( pRSPReceiptsList )
      {
         DString dstrAccountNum, dstrContribYear;
         // Ask the parent for the Account Number to use to get the RSPReceipts List
         RSPContributionList *pRSPContributionList = dynamic_cast <RSPContributionList *> (getParent());
         pRSPContributionList->getAccountNum ( dstrAccountNum );         
         getField(ifds::ContribYear, dstrContribYear, idDataGroup, false);
         // Initializes RSPReceiptsList which requires Account Number and the Contribution Year of
         // the current RSPContribution CBO.
         if( pRSPReceiptsList->init( dstrAccountNum, dstrContribYear ) >= WARNING )
         {
            delete pRSPReceiptsList;
            pRSPReceiptsList = NULL;
         };
         // If everything succeeded, put the list into the repository.
         setObject( pRSPReceiptsList, RSP_RECEIPTS_LIST, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPContribution.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:53:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:23:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
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
//    Rev 1.1   20 Aug 2001 13:16:36   HSUCHIN
// code cleanup and added comments
// 
//    Rev 1.0   01 Aug 2001 14:28:14   HSUCHIN
// Initial revision.
*/

