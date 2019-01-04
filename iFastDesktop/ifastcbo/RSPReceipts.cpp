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
// ^FILE   : RSPReceipt.cpp
// ^AUTHOR : 
// ^DATE   : 01/08/2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RSPReceipt
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0174_vw.hpp>
#include "rspreceipts.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RSPReceipt" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::RcptNum,    BFCBO::NONE, 0 }, 
   { ifds::Issued,     BFCBO::NONE, 0 }, 
   { ifds::RcptStatus, BFCBO::NONE, 0 }, 
   { ifds::IssueDate,  BFCBO::NONE, 0 }, 
   { ifds::RcptAmount, BFCBO::NONE, 0 }, 
   { ifds::Duplicates, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
//******************************************************************************
RSPReceipts::RSPReceipts( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   // Registers fields to be used for storing data
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
}

//******************************************************************************
// Destructor
//******************************************************************************
RSPReceipts::~RSPReceipts()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Creates the RSPReceipts CBO based on the data passed in.
// @param   const Data& data - pointer to data returned from the view.
// @param   bool bBaseDelete - Flag to detemine who deletes the CBO
//******************************************************************************
SEVERITY RSPReceipts::init( const BFData& data, bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), bBaseDelete );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPReceipts.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:53:34   purdyech
// PET910 - .NET Conversion
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
//    Rev 1.1   20 Aug 2001 14:07:54   HSUCHIN
// added comments
// 
//    Rev 1.0   01 Aug 2001 14:28:26   HSUCHIN
// Initial revision.
*/

