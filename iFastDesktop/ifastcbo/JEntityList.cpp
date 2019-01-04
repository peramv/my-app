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
// ^FILE   : JEntityList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 08/13/2000
//
// ^CLASS    : JEntityList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "jentitylist.hpp"
#include <ifastdataimpl\dse_dstc0050_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ENTITY;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "JEntityList" );
}

//******************************************************************************
JEntityList::JEntityList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
JEntityList::~JEntityList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY JEntityList::init( DString& dstrAccountNum,
                            const DString& dstrTrack,
                            const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0050_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ENTITY, requestData, ifds::DSTC0050_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/JEntityList.cpp-arc  $
 // 
 //    Rev 1.10   Nov 14 2004 14:48:58   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.9   Mar 21 2003 18:17:28   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.8   Oct 09 2002 23:54:42   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.7   Aug 29 2002 12:56:06   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.6   22 May 2002 18:28:56   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.5   03 May 2001 14:06:44   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.4   Jan 18 2001 16:05:18   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.3   Dec 17 2000 20:23:58   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.2   Dec 06 2000 13:45:52   OLTEANCR
 // modif. ReceiveData
 // 
 //    Rev 1.1   Nov 02 2000 13:22:50   YINGBAOL
 // use new databroker
 // 
 //    Rev 1.0   Aug 13 2000 12:28:42   YINGZ
 // Initial revision.
 * 
*/