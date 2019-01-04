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
// ^FILE   : HistoricalSystematicIndexList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalSystematicIndexList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "historicalsystematicindexlist.hpp"
#include <ifastdataimpl\dse_dstc0160_vw.hpp>
#include <ifastdataimpl\dse_dstc0160_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HIST_SYS_INDEX_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalSystematicIndexList" );
}

HistoricalSystematicIndexList::HistoricalSystematicIndexList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_queryData( ifds::DSTC0160_REQ ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

HistoricalSystematicIndexList::~HistoricalSystematicIndexList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*******************************************************************************************

SEVERITY HistoricalSystematicIndexList::init( const DString& dstrTransactionNumber, const DString& dstrTrack, const DString& dstrActivity )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   

   DString mgmtCoIdOut;
   m_queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_queryData.setElementValue( ifds::TransNum, dstrTransactionNumber ); 
   m_queryData.setElementValue( ifds::Track, dstrTrack );
   m_queryData.setElementValue( ifds::Activity, dstrActivity );

   ReceiveData( DSTC_REQUEST::HIST_SYS_INDEX_LIST, 
                m_queryData, 
                ifds::DSTC0160_VW, 
                DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HistoricalSystematicIndexList::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );
   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
      m_queryData.setElementValue( ifds::NextKey, NULL_STRING );
   }

   return(ReceiveData(  DSTC_REQUEST::HIST_SYS_INDEX_LIST, 
                        m_queryData, 
                        ifds::DSTC0160_VW, 
                        DSTCRequestor( getSecurity(), false ) ));
}

//******************************************************************************

bool HistoricalSystematicIndexList::moreRecordsExist()
{
   MAKEFRAMEAUTOPROMOTE( CLASSNAME, I_( "moreRecordsExist" ) );
   return(doMoreRecordsExist());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalSystematicIndexList.cpp-arc  $
// 
//    Rev 1.8   Nov 14 2004 14:44:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Mar 21 2003 18:13:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:54:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:56:02   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:28:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   May 31 2001 14:58:32   HERNANDO
// Changed init fn. to include Track and Activity.
// 
//    Rev 1.2   May 24 2001 17:54:32   HERNANDO
// Session management restructuring.
// 
//    Rev 1.1   May 11 2001 12:26:54   HERNANDO
// _
// 
//    Rev 1.0   May 10 2001 14:14:14   HERNANDO
// Initial revision.
 * 
*/