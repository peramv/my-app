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
// ^FILE   : UserAccessList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 28/06/99
//
// ^CLASS    : UserAccessList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "useraccesslist.hpp"
#include <ifastdataimpl\dse_dstc0064_req.hpp>
#include <ifastdataimpl\dse_dstc0064_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest USER_ACCESS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME  = I_( "UserAccessList" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//******************************************************************************
UserAccessList::UserAccessList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
UserAccessList::~UserAccessList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY UserAccessList::init( const DString& mgmtCoId, const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0064_REQ);

   queryData.setElementValue( ifds::CompanyId, mgmtCoId );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   if (!bfutil::isServerContext())
   {
      const DSTCSecurity *security = getSecurity();
      queryData.setElementValue( ifds::UserType, security->getAccessID() );
   }

   ReceiveData( DSTC_REQUEST::USER_ACCESS, queryData, ifds::DSTC0064_VW, DSTCRequestor( getSecurity() ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void UserAccessList::getStrKey( DString &strKey, const BFData *data)
{
   data->getElementValue( ifds::FunctionId, strKey);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/UserAccessList.cpp-arc  $
 * 
 *    Rev 1.15   Jun 15 2010 23:05:00   popescu
 * Incident 2154310 - Unable to update iFast - user access security list access id should be set only for Deskop context
 * 
 *    Rev 1.14   Mar 05 2010 15:54:34   yingz
 * view 64 send accesstype for rrid ffid fix
 * 
 *    Rev 1.13   Nov 14 2004 14:59:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Mar 21 2003 18:28:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:55:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:57:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:30:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   14 Jun 2001 11:56:32   SMITHDAV
 * Re-worked user access list and permission checking code.
 * 
 *    Rev 1.7   03 May 2001 14:07:16   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:10:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:24:50   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 15:21:32   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   Nov 07 2000 13:20:54   YINGBAOL
 * fix bug for init
 * 
 *    Rev 1.2   Nov 02 2000 16:13:54   OLTEANCR
 * no change
 * 
 *    Rev 1.1   Nov 02 2000 16:07:12   OLTEANCR
 * new data broker
 * 
 *    Rev 1.0   Feb 15 2000 11:00:08   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Jan 05 2000 20:11:06   BUZILA
 * adding list flag
 * 
 *    Rev 1.10   Dec 12 1999 16:26:00   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/